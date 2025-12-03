#include <iostream>
#include <string>

#include "Block.h"
#include "TransactionData.h"

using namespace std;

Block::Block(int idx, TransactionData d, size_t prevHash) {
    index = idx;
    data = d;
    previousHash = prevHash;
    blockHash = generateHash();
}

// 해시 생성 함수가 TransactionData의 모든 정보를 사용해 만든 해시와 이전 해시를 결합하여 반환
size_t Block::generateHash() {
    string toHashS = to_string(data.amount) + data.senderKey + data.receiverKey + to_string(data.timestamp);

    hash<string> tDataHash;
    hash<string> prevHash;

    return tDataHash(toHashS) ^ (prevHash(to_string(previousHash)) << 1);
}

size_t Block::getHash() { return blockHash; }
size_t Block::getPreviousHash() { return previousHash; }
size_t Block::getIndex() { return index; }
bool Block::isHashValid() { return generateHash() == getHash(); }