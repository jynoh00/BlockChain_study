#include <iostream>
#include <string>
#include <vector>

#include "BlockChain.h"

#define endl "\n"

using namespace std;

BlockChain::BlockChain() {
    Block genesis = createGenesisBlock();
    chain.emplace_back(genesis);
}

vector<Block> BlockChain::getChain() { return chain; }

Block BlockChain::createGenesisBlock() {
    time_t current; // 현재 시간
    
    TransactionData d(0, "Genesis", "Genesis", time(&current));

    string toHashS = to_string(d.amount) + d.senderKey + d.receiverKey + to_string(d.timestamp);

    hash<string> tDataHash;
    hash<string> prevHash;

    size_t hash = tDataHash(toHashS) ^ (prevHash(to_string(0)) << 1);

    Block genesis(0, d, hash);

    return genesis;
}

Block* BlockChain::getLatestBlock() { return &chain.back(); }

void BlockChain::addBlock(TransactionData d) {
    int index = (int)chain.size(); // genesis 블록의 index는 0
    size_t lastHash = (int)chain.size() > 0 ? getLatestBlock()->getHash() : 0;
    Block newBlock(index, d, lastHash);
    
    chain.emplace_back(newBlock);
}

bool BlockChain::isChainValid() {
    vector<Block>::iterator iter;

    for (iter = chain.begin(); iter != chain.end(); iter++) {
        Block currentBlock = *iter;
        if (!currentBlock.isHashValid()) return false;

        if (iter != chain.begin()) { // genesis block이 아닌 경우, default
            Block previousBlock = *(iter - 1);
            if (currentBlock.getPreviousHash() != previousBlock.getHash()) return false;
        }
    }

    return true;
}

void BlockChain::printChain() {
    vector<Block>::iterator iter;

    for (iter = chain.begin(); iter != chain.end(); iter++) {
        Block currentBlock = *iter;
        cout << endl << endl << "Block ===========================";
        cout << endl << "Index: " << currentBlock.getIndex();
        cout << endl << "Amount: " << currentBlock.data.amount;
        cout << endl << "SenderKey: " << currentBlock.data.senderKey.c_str();
        cout << endl << "ReceiverKey: " << currentBlock.data.receiverKey.c_str();
        cout << endl << "Timestamp: " << currentBlock.data.timestamp;
        cout << endl << "Hash: " << currentBlock.getHash();
        cout << endl << "Previous Hash: " << currentBlock.getHash();
        cout << endl << "is Block Valid: " << currentBlock.isHashValid();
    }

    return;
}