#pragma once

#ifndef Block_h
#define Block_h

#include "TransactionData.h"

class Block {
private:
    int index; // 블록의 인덱스
    size_t blockHash; // 현재 블록의 해시값
    size_t previousHash; // 이전 블록의 해시값
    size_t generateHash(); // 현재 들어온 값들을 기반으로 해시값을 생성

public:
    Block(int idx, TransactionData d, size_t prevHash);

    size_t getIndex();
    size_t getHash();
    size_t getPreviousHash();

    TransactionData data; // 원래는 private이지만, 해킹 상황에서 블록체인의 안전성을 검증하기 위해 public으로

    bool isHashValid(); // 생성한 해시값이 현재 블록의 해시값과 일치하는 지 검증
};

#endif


/*
private:
    TransactionData data;
public:
    TransactionDate getData();
*/