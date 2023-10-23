// This file contains constants and arguments used to perform RPCs between
// the KeyValueServer and its clients. DO NOT MODIFY!

package rpcs

// GetArgs contains the RecvGet RPC arguments
type GetArgs struct {
	Key string
}

// GetReply contains the RecvGet RPC return values
type GetReply struct {
	Value []byte
}

// PutArgs contains the RecvPut RPC arguments
type PutArgs struct {
	Key   string
	Value []byte
}

// PutReply contains the RecvPut RPC return values
type PutReply struct {
}
