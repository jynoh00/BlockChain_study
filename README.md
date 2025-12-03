# BLOCK_CHAIN 개념 구현 in C++
> C++ 언어를 사용하여, 간단하게 Block Chain의 개념을 구현한다.

## 주요 컴포넌트 설명

> 1: Block.h, Block.cpp
- Block : 개별 블록 객체로 고유 인덱스와 해시값들을 가지고 있다.

```cpp
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
```


<br>

> 2: BlockChain.h, BlockChain.cpp
- BlockChain : 각 블록 객체를 연결하는 체인으로 vector로 구현하였다.

```cpp
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

```
> TransactionData.h
- TransactionData : 개별 거래 내역을 담고 있는 구조체로, 송-수신자와 거래량, 거래 시각을 담고 있다.

```cpp
struct TransactionData {
    double amount; // 코인 거래 양
    string senderKey; // 보내는 사람의 지갑 주소
    string receiverKey; // 받는 사람의 지갑 주소
    time_t timestamp; // 거래가 이루어지는 시간

    TransactionData() {};

    TransactionData(double amt, string sender, string receiver, time_t time) {
        amount = amt;
        senderKey = sender;
        receiverKey = receiver;
        timestamp = time;
    };
};
```

## Simulator

```cpp
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
```

## output 1 : 정상 블록 생성 및 출력

```bash
Block ===========================
Index: 0
Amount: 0
SenderKey: Genesis
ReceiverKey: Genesis
Timestamp: 1764764421
Hash: 12892418728636888799
Previous Hash: 12892418728636888799
Is Block Valid: 1

Block ===========================
Index: 1
Amount: 1.5
SenderKey: Star
ReceiverKey: Bucks
Timestamp: 1764764421
Hash: 14279230466928270956
Previous Hash: 14279230466928270956
Is Block Valid: 1

Block ===========================
Index: 2
Amount: 1
SenderKey: Korea
ReceiverKey: Star
Timestamp: 1764764421
Hash: 1723938870647919277
Previous Hash: 1723938870647919277
Is Block Valid: 1
is chain valid: 1
```

## output 2 : 블록 정보 임의 수정 결과

```bash
Block ===========================
Index: 0
Amount: 0
SenderKey: Genesis
ReceiverKey: Genesis
Timestamp: 1764764421
Hash: 12892418728636888799
Previous Hash: 12892418728636888799
Is Block Valid: 1

Block ===========================
Index: 1
Amount: 1.5
SenderKey: Star
ReceiverKey: Bucks
Timestamp: 1764764421
Hash: 14279230466928270956
Previous Hash: 14279230466928270956
Is Block Valid: 1

Block ===========================
Index: 2
Amount: 10000
SenderKey: Korea
ReceiverKey: Hacker
Timestamp: 1764764421
Hash: 1723938870647919277
Previous Hash: 1723938870647919277
Is Block Valid: 0 // 블록 검증 실패
is chain valid: 0 // 체인 검증 실패
```

블록의 정보를 임의 수정함으로서 해당 블록의 유효성이 false가 됨가 동시에, 전체 chain의 유효성도 false가 된다.
<br>

이를 통해 알 수 있는 것은 
- 블록 데이터는 변경 순간, 즉시 무결성이 깨지며
- 한 블록의 변조가 체인 전체를 붕괴시킨다는 것이다.

<br>
간략하게 블록체인의 기본 기능을 구현한 위 결과를 통해서
<br>
결국 체인의 모든 블록은 신뢰를 함께 공유하는 분산형 데이터 저장 구조를 가지며,<br>해시 기반의 불변성을 가지는 블록체인의 특성상 임의 개별 데이터 조작(해킹)이 발생할 경우<br>각 노드가 서로 판별하여 안전성을 보장한다는 것을 알 수 있다.