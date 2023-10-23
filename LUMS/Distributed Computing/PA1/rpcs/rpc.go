package rpcs

// STAFF USE ONLY! Students should not use this interface in their code.
type RemoteKeyValueServer interface {
	// RPC Functions called by clients.
	RecvGet(args *GetArgs, reply *GetReply) error
	RecvPut(args *PutArgs, reply *PutReply) error
}

type KeyValueServer struct {
	// Embed all methods into the struct. See the Effective Go section about
	// embedding for more details: golang.org/doc/effective_go.html#embedding
	RemoteKeyValueServer
}

// Wrap wraps t in a type-safe wrapper struct to ensure that only the desired
// methods are exported to receive RPCs. Any other methods already in the
// input struct are protected from receiving RPCs.
func Wrap(t RemoteKeyValueServer) RemoteKeyValueServer {
	return &KeyValueServer{t}
}
