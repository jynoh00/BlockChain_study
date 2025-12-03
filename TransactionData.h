// 거래 내역을 나타내는 구조체

#pragma once

#ifndef TransactionData_h
#define TransactionData_h

#include <string>

using namespace std;

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

#endif