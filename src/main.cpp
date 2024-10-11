#include "Blockchain.h"
#include "Transaction.h"
#include <iostream>

int main() {
  Blockchain myBlockchain;

  // Create some transactions
  Transaction tx1("Alice", "Bob", 10.0, 1, "signature1");
  Transaction tx2("Bob", "Charlie", 5.0, 1, "signature2");

  // Add transactions to the blockchain
  myBlockchain.add_transaction(tx1);
  myBlockchain.add_transaction(tx2);

  // Mine the pending transactions
  std::cout << "Mining pending transactions..." << std::endl;
  myBlockchain.mine_pending_transactions("Miner1");

  // Display the blockchain
  for (const auto &block : myBlockchain.chain) {
    std::cout << "Block #" << block.index << " [Hash: " << block.hash << "]"
              << std::endl;
    for (const auto &tx : block.transactions) {
      std::cout << "  " << tx.sender << " -> " << tx.receiver << " : "
                << tx.amount << std::endl;
    }
  }

  // Validate the blockchain
  std::cout << "Blockchain valid? "
            << (myBlockchain.is_chain_valid() ? "Yes" : "No") << std::endl;

  return 0;
}
