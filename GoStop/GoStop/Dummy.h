#pragma once
#ifndef Dummy_h
#define Dummy_h
#include "CardSet.h"
#include <algorithm>

// 플레이어, 바닥, 더미는 아래와 같이 CardSet을 상속시키는 것으로 구현해
// 봤습니다.
class Dummy : public CardSet {
 public:
  // 카드 셋에 있는 카드들을 무작위로 섞는 함수
  void Shuffle();
  // override AddCard
  virtual void AddCard(Card card);
  // 더미의 가장 위에 있는 카드를 하나 빼내는 함수
  Card PopOneCard();
  // 더미에 남은 카드가 없는지 확인하는 함수
  bool isEmpty();
};

#endif