package main

import (
	"DS_PA1/pa1"
	"fmt"
)

const defaultPort = 9999

func main() {
	// Initialize the server.
	server := pa1.New()
	if server == nil {
		fmt.Println("New() returned a nil server. Exiting...")
		return
	}

	// Start the server and continue listening for client connections in the background.
	// Use StartModel2 to start the Model 2 server
	if err := server.StartModel1(defaultPort); err != nil {
		fmt.Printf("KeyValueServer could not be started: %s\n", err)
		return
	}

	fmt.Printf("Started KeyValueServer on port %d...\n", defaultPort)

	// Block forever.
	select {}
}
