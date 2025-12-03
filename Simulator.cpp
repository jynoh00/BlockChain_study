#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "Block.h"
#include "BlockChain.h"
#include "TransactionData.h"

using namespace std;

int main() {
    BlockChain MyCoin;
    
    time_t data1Time;
    // Star -> Bucks : Mycoin 1.5개 전송, block 추가
    TransactionData data1(1.5, "Star", "Bucks", time(&data1Time));
    MyCoin.addBlock(data1);

    time_t data2Time;
    // Korea -> Star : Mycoin 1.0개 전송, block 추가
    TransactionData data2(1.0, "Korea", "Star", time(&data2Time));
    MyCoin.addBlock(data2);

    MyCoin.printChain();

    cout << endl << "is chain valid: " << MyCoin.isChainValid();
    
    // 기존 블록의 정보를 수정 시도 (hack)
    Block* hackBlock = MyCoin.getLatestBlock(); // 해킹할 블록을 가져온다.
    hackBlock->data.amount = 10000;
    hackBlock->data.receiverKey = "Hacker";

    MyCoin.printChain();

    cout << endl << "is chain valid: " << MyCoin.isChainValid();
}