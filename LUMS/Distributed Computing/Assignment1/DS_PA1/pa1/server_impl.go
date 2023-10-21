// Implementation of a KeyValueServer. Students should write their code in this file.

package pa1

import "DS_PA1/rpcs"

type keyValueServer struct {
	// TODO: implement this!
}

// New creates and returns (but does not start) a new KeyValueServer.
func New() KeyValueServer {
	// TODO: implement this!
	return nil
}

func (kvs *keyValueServer) StartModel1(port int) error {
	// TODO: implement this!
	return nil
}

func (kvs *keyValueServer) Close() {
	// TODO: implement this!
}

func (kvs *keyValueServer) Count() int {
	// TODO: implement this!
	return -1
}

func (kvs *keyValueServer) StartModel2(port int) error {
	// TODO: implement this!
	//
	// Do not forget to call rpcs.Wrap(...) on your kvs struct before
	// passing it to <sv>.Register(...)
	//
	// Wrap ensures that only the desired methods (RecvGet and RecvPut)
	// are available for RPC access. Other KeyValueServer functions
	// such as Close(), StartModel1(), etc. are forbidden for RPCs.
	//
	// Example: <sv>.Register(rpcs.Wrap(kvs))
	return nil
}

func (kvs *keyValueServer) RecvGet(args *rpcs.GetArgs, reply *rpcs.GetReply) error {
	// TODO: implement this!
	return nil
}

func (kvs *keyValueServer) RecvPut(args *rpcs.PutArgs, reply *rpcs.PutReply) error {
	// TODO: implement this!
	return nil
}

// TODO: add additional methods/functions below!
