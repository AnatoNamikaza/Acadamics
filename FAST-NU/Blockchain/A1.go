package main

import (
	"crypto/sha256"
	"encoding/hex"
	"fmt"
)

// Block
type Block struct {
	transactions []string
	prevPointer  *Block
	prevHash     string
	currentHash  string
}

// CalculateHash calculates the hash of a Block
func CalculateHash(inputBlock *Block) string {
	data := ""
	for _, tx := range inputBlock.transactions {
		data += tx
	}
	data += inputBlock.prevHash
	hash := sha256.Sum256([]byte(data))
	return hex.EncodeToString(hash[:])
}

// InsertBlock inserts a new block and returns the head pointer
func InsertBlock(transactionsToInsert []string, chainHead *Block) *Block {
	newBlock := &Block{
		transactions: transactionsToInsert,
		prevPointer:  chainHead,
		prevHash:     chainHead.currentHash,
	}
	newBlock.currentHash = CalculateHash(newBlock)
	return newBlock
}

// ChangeBlock changes transaction data inside a block
func ChangeBlock(oldTrans string, newTrans string, chainHead *Block) {
	currentBlock := chainHead
	for currentBlock != nil {
		for i, tx := range currentBlock.transactions {
			if tx == oldTrans {
				currentBlock.transactions[i] = newTrans
				currentBlock.currentHash = CalculateHash(currentBlock)
				return
			}
		}
		currentBlock = currentBlock.prevPointer
	}
}

// ListBlocks displays the data (transactions) inside all blocks
func ListBlocks(chainHead *Block) {
	currentBlock := chainHead
	blockNumber := 0
	for currentBlock != nil {
		fmt.Printf("Block %d:\n", blockNumber)
		fmt.Printf("Previous Hash: %s\n", currentBlock.prevHash)
		fmt.Printf("Current Hash: %s\n", currentBlock.currentHash)
		fmt.Println("Transactions:")
		for _, tx := range currentBlock.transactions {
			fmt.Printf("- %s\n", tx)
		}
		fmt.Println()
		currentBlock = currentBlock.prevPointer
		blockNumber++
	}
}

// VerifyChain checks whether the blockchain is compromised or unchanged
func VerifyChain(chainHead *Block) {
	currentBlock := chainHead
	for currentBlock != nil {
		// Recalculate the hash of the current block and compare it to the stored hash
		calculatedHash := CalculateHash(currentBlock)
		if calculatedHash != currentBlock.currentHash {
			fmt.Println("Blockchain is compromised!")
			return
		}
		currentBlock = currentBlock.prevPointer
	}
	fmt.Println("Blockchain is unchanged.")
}

func main() {
	genesisBlock := &Block{ // Initialize the genesis block
		transactions: []string{"Zavian sent 10 BTC to Waseef", "Zain sent 5 BTC to Rehan"},
		prevPointer:  nil,
		prevHash:     "",
		currentHash:  "",
	}

	genesisBlock.currentHash = CalculateHash(genesisBlock)

	Block2 := InsertBlock([]string{"Hafiz sent 3 BTC to Zavian", "Waseef sent 2 BTC to Rehan"}, genesisBlock)
	Block3 := InsertBlock([]string{"Hassan sent 7 BTC to Hafiz", "Zavian sent 4 BTC to Zain"}, Block2)
	fmt.Println("Original Blockchain:")
	ListBlocks(Block3)
	VerifyChain(Block3)
	ChangeBlock("Hafiz sent 3 BTC to Zavian", "Hafiz sent 30 BTC to Zavian", Block3)
	fmt.Println("\nBlockchain After Alteration:")
	ListBlocks(Block3)
	VerifyChain(Block3)
}
