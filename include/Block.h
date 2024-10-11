#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <string>
#include <ctime>
#include "Transaction.h"
#include <openssl/sha.h>

class Block {
public:
    int index;
    time_t timestamp;
    std::vector<Transaction> transactions;
    std::string previous_hash;
    std::string hash;
    uint64_t nonce;

    Block() : index(0), timestamp(std::time(nullptr)), nonce(0) {}

    Block(int index, const std::vector<Transaction>& transactions, const std::string& previous_hash)
        : index(index), transactions(transactions), previous_hash(previous_hash), timestamp(std::time(nullptr)), nonce(0) {}

    // Serialize block data for hashing
    std::string serialize() const {
        std::string data = std::to_string(index) + std::to_string(timestamp) + previous_hash;
        for (const auto& tx : transactions) {
            data += tx.serialize();
        }
        data += std::to_string(nonce);
        return data;
    }

    // Calculate hash using SHA-256
    std::string calculate_hash() const {
        std::string data = serialize();
        unsigned char hash_bytes[SHA256_DIGEST_LENGTH];
        SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash_bytes);

        // Convert hash bytes to hex string
        std::string hash_string;
        char buf[3];
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            sprintf(buf, "%02x", hash_bytes[i]);
            hash_string += buf;
        }
        return hash_string;
    }

    // Proof of Work (Mining) - Placeholder
    void mine_block(int difficulty) {
        std::string prefix(difficulty, '0');
        while (hash.substr(0, difficulty) != prefix) {
            nonce++;
            hash = calculate_hash();
        }
    }
};

#endif // BLOCK_H