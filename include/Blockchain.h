#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "Block.h"
#include <string>
#include <vector>

class Blockchain {
public:
  std::vector<Block> chain;
  std::vector<Transaction> pending_transactions;
  int difficulty;

  Blockchain() : difficulty(2) {
    // Create the genesis block
    Block genesis = create_genesis_block();
    genesis.hash = genesis.calculate_hash();
    chain.push_back(genesis);
  }

  Block create_genesis_block() const {
    std::vector<Transaction> genesis_transactions;
    // Optionally add genesis transactions
    return Block(0, genesis_transactions, "0");
  }

  Block get_latest_block() const { return chain.back(); }

  void add_transaction(const Transaction &transaction) {
    // Verify transaction before adding
    if (transaction.verify_signature()) {
      pending_transactions.push_back(transaction);
    }
  }

  void mine_pending_transactions(const std::string &miner_address) {
    // Create a reward transaction for the miner
    Transaction reward_tx("Network", miner_address, 1.0, 0,
                          ""); // Signature omitted for reward

    std::vector<Transaction> block_transactions = pending_transactions;
    block_transactions.push_back(reward_tx);
    Block new_block(chain.size(), block_transactions, get_latest_block().hash);
    new_block.mine_block(difficulty);
    chain.push_back(new_block);
    pending_transactions.clear();
  }

  bool is_chain_valid() const {
    for (size_t i = 1; i < chain.size(); ++i) {
      const Block &current = chain[i];
      const Block &previous = chain[i - 1];
      if (current.hash != current.calculate_hash()) {
        return false;
      }
      if (current.previous_hash != previous.hash) {
        return false;
      }
      // Additional validation like transaction integrity can be added here
    }
    return true;
  }
};

#endif // BLOCKCHAIN_H
