package raft

//
// this is an outline of the API that raft must expose to
// the service (or tester). see comments below for
// each of these functions for more details.
//
// rf = Make(...)
//   create a new Raft server.
// rf.Start(command interface{}) (LogIndex, Term, isleader)
//   start agreement on a new log entry
// rf.GetState() (Term, isLeader)
//   ask a Raft for its current Term, and whether it thinks it is leader
// ApplyMsg
//   each time a new entry is committed to the log, each Raft peer
//   should send an ApplyMsg to the service (or tester)
//   in the same server.
//

import (
	"bytes"
	"encoding/gob"
	"labrpc"
	"math/rand"
	"sync"
	"time"
)

// import "bytes"
// import "encoding/gob"

// as each Raft peer becomes aware that successive log Entries are
// committed, the peer should send an ApplyMsg to the service (or
// tester) on the same server, via the applyCh passed to Make().
type ApplyMsg struct {
	Index       int
	Command     interface{}
	UseSnapshot bool   // ignore for lab2; only used in lab3
	Snapshot    []byte // ignore for lab2; only used in lab3
}

const (
	HBINTERVAL = 100 * time.Millisecond
)
const (
	LEADER StateType = iota
	FOLLOWER
	CANDIDATE
)

type StateType uint

// A Go object implementing a single Raft peer.
type Raft struct {
	mu        sync.Mutex          // Lock to protect shared access to this peer's state
	peers     []*labrpc.ClientEnd // RPC end points of all peers
	persister *Persister          // Object to hold this peer's persisted state
	me        int                 // this peer's LogIndex into peers[]

	// Your data here (2A, 2B, 2C).
	// Look at the paper's Figure 2 for a description of what
	// state a Raft server must maintain.
	currentTerm int
	votedFor    int
	log         []LogEntry

	state     StateType
	voteCount int

	chanHb     chan bool
	chanLeader chan bool
	chanCommit chan bool

	// Volatile state
	commitIndex int
	lastApplied int

	// leader
	nextIndex  []int
	matchIndex []int
}

type LogEntry struct {
	LogIndex int
	LogTerm  int
	Cmd      interface{}
}

func (rf *Raft) getLastIndex() int {
	return rf.log[len(rf.log)-1].LogIndex
}

func (rf *Raft) getLastTerm() int {
	return rf.log[len(rf.log)-1].LogTerm
}

// return Term and whether this server
// believes it is the leader.
func (rf *Raft) GetState() (int, bool) {
	// Your code here (2A).
	return rf.currentTerm, rf.state == LEADER
}

// save Raft's persistent state to stable storage,
// where it can later be retrieved after a crash and restart.
// see paper's Figure 2 for a description of what should be persistent.
func (rf *Raft) persist() {
	// Your code here (2C).
	// Example:
	w := new(bytes.Buffer)
	e := gob.NewEncoder(w)
	e.Encode(rf.log)
	e.Encode(rf.currentTerm)
	e.Encode(rf.votedFor)
	data := w.Bytes()
	rf.persister.SaveRaftState(data)
}

// restore previously persisted state.
func (rf *Raft) readPersist(data []byte) {
	if data == nil || len(data) < 1 { // bootstrap without any state?
		return
	}
	// Your code here (2C).
	r := bytes.NewBuffer(data)
	d := gob.NewDecoder(r)
	d.Decode(&rf.log)
	d.Decode(&rf.currentTerm)
	d.Decode(&rf.votedFor)
}

// example RequestVote RPC arguments structure.
// field names must start with capital letters!
type RequestVoteArgs struct {
	// Your data here (2A, 2B).
	Term         int
	CandidateId  int
	LastLogIndex int
	LastLogTerm  int
}

// example RequestVote RPC reply structure.
// field names must start with capital letters!
type RequestVoteReply struct {
	// Your data here (2A).
	Term        int
	VoteGranted bool
}

// example RequestVote RPC handler.
func (rf *Raft) RequestVote(args *RequestVoteArgs, reply *RequestVoteReply) {
	// Your code here (2A, 2B).
	//DPrintf("%d Receive vote request from %d", rf.me, args.CandidateId)
	rf.mu.Lock()
	defer rf.mu.Unlock()
	//DPrintf("term1: %d term2: %d", rf.currentTerm, args.CandidateId)

	if rf.currentTerm < args.Term {
		rf.becomeFollower(args.Term)
		//DPrintf("%d become a follower after receiving from %d", rf.me, args.CandidateId)
	}

	reply.Term = rf.currentTerm

	if args.LastLogTerm < rf.getLastTerm() ||
		args.LastLogTerm == rf.getLastTerm() && args.LastLogIndex < rf.getLastIndex() {
		reply.VoteGranted = false
	} else if rf.votedFor == -1 {
		reply.VoteGranted = true
		rf.votedFor = args.CandidateId
	} else {
		reply.VoteGranted = false
		//DPrintf("%d reject the request from %d, because it has vote for %d", rf.me, args.CandidateId, rf.votedFor)
	}
}

// example code to send a RequestVote RPC to a server.
// server is the LogIndex of the target server in rf.peers[].
// expects RPC arguments in args.
// fills in *reply with RPC reply, so caller should
// pass &reply.
// the types of the args and reply passed to Call() must be
// the same as the types of the arguments declared in the
// handler function (including whether they are pointers).
//
// The labrpc package simulates a lossy network, in which servers
// may be unreachable, and in which requests and replies may be lost.
// Call() sends a request and waits for a reply. If a reply arrives
// within a timeout interval, Call() returns true; otherwise
// Call() returns false. Thus Call() may not return for a while.
// A false return can be caused by a dead server, a live server that
// can't be reached, a lost request, or a lost reply.
//
// Call() is guaranteed to return (perhaps after a delay) *except* if the
// handler function on the server side does not return.  Thus there
// is no need to implement your own timeouts around Call().
//
// look at the comments in ../labrpc/labrpc.go for more details.
//
// if you're having trouble getting RPC to work, check that you've
// capitalized all field names in structs passed over RPC, and
// that the caller passes the address of the reply struct with &, not
// the struct itself.
func (rf *Raft) sendRequestVote(server int, args *RequestVoteArgs, reply *RequestVoteReply) bool {
	ok := rf.peers[server].Call("Raft.RequestVote", args, reply)
	rf.mu.Lock()
	defer rf.mu.Unlock()
	if ok {
		if rf.state != CANDIDATE {
			return ok
		}

		if rf.currentTerm < reply.Term {
			rf.becomeFollower(reply.Term)
			return ok
		}

		if reply.VoteGranted {
			rf.voteCount++
			//DPrintf("%d get the vote from %d, vote count: %d", rf.me, server, rf.voteCount)
			if rf.voteCount == len(rf.peers)/2+1 {
				//DPrintf("%d chanleader", rf.me)
				rf.chanLeader <- true
			}
		}
	}
	return ok
}

func (rf *Raft) broadcastRequestVote() {
	rf.mu.Lock()
	args := &RequestVoteArgs{
		Term:         rf.currentTerm,
		CandidateId:  rf.me,
		LastLogIndex: rf.getLastIndex(),
		LastLogTerm:  rf.getLastTerm(),
	}
	rf.mu.Unlock()
	for i := range rf.peers {
		if i != rf.me {
			go func(i int) {
				rf.sendRequestVote(i, args, &RequestVoteReply{})
			}(i)
		}
	}
}

type AppendEntriesArgs struct {
	Term         int
	LeaderId     int
	PreLogIndex  int
	PreLogTerm   int
	Entries      []LogEntry
	LeaderCommit int
}

type AppendEntriesReply struct {
	Term      int
	Success   bool
	NextIndex int
}

func min(a, b int) int {
	if a <= b {
		return a
	}
	return b
}

func (rf *Raft) AppendEntries(args *AppendEntriesArgs, reply *AppendEntriesReply) {
	rf.mu.Lock()
	defer rf.mu.Unlock()
	reply.Success = false

	// if current term is bigger than old leader
	if args.Term < rf.currentTerm {
		reply.Term = rf.currentTerm
		return
	}

	// heartbeat detected
	rf.chanHb <- true
	reply.Term = args.Term

	// if leader term is bigger than current term, update current term
	if args.Term > rf.currentTerm {
		rf.becomeFollower(args.Term)
	}

	// todo ????
	if args.PreLogIndex > rf.getLastIndex() {
		reply.NextIndex = rf.getLastIndex() + 1
		return
	}

	// todo ????
	term := rf.log[args.PreLogIndex].LogTerm
	if args.PreLogTerm != term {
		for i := args.PreLogIndex - 1; i >= 0; i-- {
			if rf.log[i].LogTerm != term {
				reply.NextIndex = i + 1
				break
			}
		}
		return
	}

	// append entries
	rf.log = rf.log[:args.PreLogIndex+1]
	rf.log = append(rf.log, args.Entries...)
	rf.persist()
	reply.Success = true
	reply.NextIndex = rf.getLastIndex() + 1

	// commit log
	if args.LeaderCommit > rf.commitIndex {
		rf.commitIndex = min(args.LeaderCommit, rf.getLastIndex())
		rf.chanCommit <- true
	}

}

func (rf *Raft) sendAppendEntries(server int, args *AppendEntriesArgs, reply *AppendEntriesReply) bool {
	ok := rf.peers[server].Call("Raft.AppendEntries", args, reply)
	rf.mu.Lock()
	defer rf.mu.Unlock()

	//DPrintf("%d send append entities to %d :%s",rf.me,server,reply)

	if ok {
		// if rf is not the leader or outofdate, return
		if rf.state != LEADER || args.Term != rf.currentTerm {
			return ok
		}

		// if higher term is found, set follower and return
		if rf.currentTerm < reply.Term {
			rf.becomeFollower(reply.Term)
			return ok
		}

		// set the next index of follower
		rf.nextIndex[server] = reply.NextIndex
		// if append entries successfully, set match index of follower
		if reply.Success {
			rf.matchIndex[server] = rf.nextIndex[server] - 1
		}
	}
	return ok
}

func (rf *Raft) broadcastAppendEntries() {
	rf.mu.Lock()
	defer rf.mu.Unlock()

	// update commit index
	newCommitIndex := rf.commitIndex
	for i := rf.commitIndex + 1; i <= rf.getLastIndex(); i++ {
		num := 1
		for server := range rf.peers {
			if server != rf.me && rf.matchIndex[server] >= i && rf.log[i].LogTerm == rf.currentTerm {
				num++
				//DPrintf("num %d, len(rf.peers): %d, matchIndex:%d", num, len(rf.peers),rf.matchIndex)
				if num == len(rf.peers)/2+1 {
					newCommitIndex = i
					break
				}
			}
		}
	}

	//DPrintf("new commit index %d, old: %d", newCommitIndex, rf.commitIndex)

	if newCommitIndex != rf.commitIndex {
		rf.commitIndex = newCommitIndex
		rf.chanCommit <- true
	}

	for i := range rf.peers {
		if i != rf.me {
			go func(i int) {
				args := &AppendEntriesArgs{
					Term:         rf.currentTerm,
					LeaderId:     rf.me,
					PreLogIndex:  rf.nextIndex[i] - 1,
					PreLogTerm:   rf.log[rf.nextIndex[i]-1].LogTerm,
					LeaderCommit: rf.commitIndex,
				}
				args.Entries = make([]LogEntry, len(rf.log[rf.nextIndex[i]:]))
				copy(args.Entries, rf.log[rf.nextIndex[i]:])

				//DPrintf("append entities: %d",args.Entries)
				reply := &AppendEntriesReply{}
				rf.sendAppendEntries(i, args, reply)
			}(i)
		}
	}
}

// the service using Raft (e.g. a k/v server) wants to start
// agreement on the next command to be appended to Raft's log. if this
// server isn't the leader, returns false. otherwise start the
// agreement and return immediately. there is no guarantee that this
// command will ever be committed to the Raft log, since the leader
// may fail or lose an election.
//
// the first return value is the LogIndex that the command will appear at
// if it's ever committed. the second return value is the current
// Term. the third return value is true if this server believes it is
// the leader.
func (rf *Raft) Start(command interface{}) (int, int, bool) {
	rf.mu.Lock()
	defer rf.mu.Unlock()
	term, isLeader := rf.GetState()
	//DPrintf("server %d start a cmd %d",rf.me,command)
	if !isLeader {
		return -1, term, isLeader
	}

	// Your code here (2B).
	rf.log = append(rf.log, LogEntry{
		LogTerm:  rf.currentTerm,
		LogIndex: len(rf.log),
		Cmd:      command,
	})
	rf.persist()

	index := rf.getLastIndex()

	return index, term, isLeader
}

//
// the tester calls Kill() when a Raft instance won't
// be needed again. you are not required to do anything
// in Kill(), but it might be convenient to (for example)
// turn off debug output from this instance.
//

func (rf *Raft) Kill() {
	// Your code here, if desired.
}

func (rf *Raft) becomeCandidate() {
	rf.state = CANDIDATE
	rf.currentTerm = rf.currentTerm + 1
	rf.voteCount = 1
	rf.votedFor = rf.me
	rf.persist()
	//DPrintf("%d become a candidate", rf.me)
}

func (rf *Raft) becomeLeader() {
	rf.state = LEADER
	rf.votedFor = -1
	rf.nextIndex = make([]int, len(rf.peers))
	rf.matchIndex = make([]int, len(rf.peers))
	for i := range rf.peers {
		rf.nextIndex[i] = rf.getLastIndex() + 1
		rf.matchIndex[i] = 0
	}
	rf.persist()

	//DPrintf("%d become a leader", rf.me)
}

func (rf *Raft) becomeFollower(term int) {
	rf.state = FOLLOWER
	rf.currentTerm = term
	rf.votedFor = -1
	rf.persist()
	//DPrintf("%d become a follower", rf.me)
}

// the service or tester wants to create a Raft server. the ports
// of all the Raft servers (including this one) are in peers[]. this
// server's port is peers[me]. all the servers' peers[] arrays
// have the same order. persister is a place for this server to
// save its persistent state, and also initially holds the most
// recent saved state, if any. applyCh is a channel on which the
// tester or service expects Raft to send ApplyMsg messages.
// Make() must return quickly, so it should start goroutines
// for any long-running work.
func Make(peers []*labrpc.ClientEnd, me int,
	persister *Persister, applyCh chan ApplyMsg) *Raft {
	rf := &Raft{}
	rf.peers = peers
	rf.persister = persister
	rf.me = me
	rf.log = append(rf.log, LogEntry{LogTerm: 0})
	rf.chanHb = make(chan bool, 100)
	rf.chanLeader = make(chan bool, 100)
	rf.chanCommit = make(chan bool, 100)
	rf.state = FOLLOWER
	rf.currentTerm = 0
	rf.votedFor = -1

	// Your initialization code here (2A, 2B, 2C).

	// initialize from state persisted before a crash
	rf.readPersist(persister.ReadRaftState())
	rf.persist()

	go func() {
		for {
			switch rf.state {
			case LEADER:
				rf.broadcastAppendEntries()
				time.Sleep(HBINTERVAL)
			case FOLLOWER:
				select {
				case <-rf.chanHb:
				case <-time.After(time.Duration(rand.Int63()%300+300) * time.Millisecond):
					rf.mu.Lock()
					rf.becomeCandidate()
					rf.mu.Unlock()
				}
			case CANDIDATE:
				rf.broadcastRequestVote()
				select {
				case <-rf.chanLeader:
					rf.mu.Lock()
					rf.becomeLeader()
					rf.mu.Unlock()
				case <-rf.chanHb:
					rf.mu.Lock()
					rf.becomeFollower(rf.currentTerm)
					rf.mu.Unlock()
				case <-time.After(time.Duration(rand.Int63()%300+300) * time.Millisecond):
					rf.mu.Lock()
					rf.becomeCandidate()
					rf.mu.Unlock()
				}
			}

		}
	}()

	go func() {
		for {
			select {
			case <-rf.chanCommit:
				rf.mu.Lock()
				for i := rf.lastApplied + 1; i <= rf.commitIndex; i++ {
					applyCh <- ApplyMsg{Index: i, Command: rf.log[i].Cmd}
					//DPrintf("%d apply index %d: %d", rf.me, i, rf.log[i])
					rf.lastApplied = i
				}
				//DPrintf("server:%d lastApplied: %d, commitIndex: %d",rf.me,rf.lastApplied,rf.commitIndex)

				rf.mu.Unlock()
			}
		}
	}()

	return rf
}
