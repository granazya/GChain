#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <cstdint>
#include <ctime>
#include <string>

class Transaction {
public:
  std::string sender;
  std::string receiver;
  double amount;
  time_t timestamp;
  uint64_t nonce;
  std::string signature;

  Transaction() : amount(0), timestamp(std::time(nullptr)), nonce(0) {}

  Transaction(const std::string &sender, const std::string &receiver,
              double amount, uint64_t nonce, const std::string &signature)
      : sender(sender), receiver(receiver), amount(amount),
        timestamp(std::time(nullptr)), nonce(nonce), signature(signature) {}

  // Serialize transaction data for hashing/signing
  std::string serialize() const {
    return sender + receiver + std::to_string(amount) +
           std::to_string(timestamp) + std::to_string(nonce);
  }

  // Placeholder for signature verification
  bool verify_signature() const {
    // Implement signature verification logic using cryptographic functions
    return true;
  }
};

#endif // TRANSACTION_H