#pragma once

#ifndef BlockChain_h
#define BlockChain_h

#include "Block.h"
#include <vector>

using namespace std;

class BlockChain {
private:
    Block createGenesisBlock(); // chain의 초기 block을 생성
    vector<Block> chain;

public:
    BlockChain();

    vector<Block> getChain();
    Block* getLatestBlock();
    void addBlock(TransactionData data);
    bool isChainValid();
    void printChain();
};

#endif