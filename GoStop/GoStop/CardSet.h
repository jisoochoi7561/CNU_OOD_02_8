#pragma once
#ifndef CardSet_h
#define CardSet_h

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Card.h"

// 뒤집을 카드를 쌓아 놓은 더미(dummy), 바닥, 플레이어가 각각 갖고 있는 카드
// 집합 더미, 바닥, 플레이어가 상속받습니다. random access 할 수 있고 카드를
// 추가했다 제거했다 할 일이 많으므로 vector를 선택했습니다. 다른 의견 있으시면
// 주석과 함께 수정해주세요
class CardSet {
 public:
  // 갖고 있는 카드 개수를 리턴
  int GetNumOfCards();
  // 카드 셋의 특정 인덱스의 카드를 리턴
  Card GetCard(int index);
  // 카드를 카드셋에 추가
  virtual void AddCard(Card card);
  // 카드 셋에서 특정 인덱스의 카드를 뽑음(카드 셋에서 제거됨)
  Card PopIdxCard(int index);
  // 카드 셋의 맨위카드를 뽑음(카드 셋에서 제거됨)
  Card PopCard();
  // 특정 월의 카드가 몇 개 있는지 리턴
  int FindNumOfSameMonthCards(int month);
  // 특정 state의 카드가 몇 개 있는지 리턴
  // 여기서 state가 제가 이전에 업로드한 card.txt에서 카드 이름의 'A,B,C,D'인지
  // 아니면 광, 피, 열, 단과 같이 카드 종류를 나타내는 것인지 모르겠습니다.
  // 후자라면 코드는 아래와 같고.. 아니라면 수정해야 합니다.
  // --추가-- state 후자로 수정했습니다. 그냥 두시면 될 것 같습니다.
  int FindNumOfSameStateCards(State state);
  std::vector<Card>& getCardset();
  void printCardSet();
 protected:
  std::vector<Card> cardset_;
};

#endif