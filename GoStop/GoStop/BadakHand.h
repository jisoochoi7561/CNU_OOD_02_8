#pragma once
#ifndef BadakHand_h
#define BadakHand_h

class Player;
#include "CardSet.h"

// 플레이어가 이미 먹은 Card들이 관리됩니다.
class BadakHand : public CardSet {
 public:
  BadakHand();
  // 점수 계산에 관련된 함수들을 여기에 작성하면 될 것 같네요

  // 규칙 보면 아시겠지만 패의 점수들로 한 계산이고
  // 추후에 플레이어 간 스탑을 했을 시 점수 계산은
  // 추후에 구현하면 될 것 같습니다.
  // 일단 패를 한 번만 훑었을 때를 기준으로 만들었습니다.
  // 후에 패를 또 훑었을 때 계산되도록 수정하면 될 것 같습니다.
  // 영어는 위키피디아 영어판 참조했습니다.
  void calc();
  int getScore();
  // 광 관련
  int calcScoreFromGwang();
  // 열끗 관련
  int calcScoreFromKkeut();
  // 띠 관련
  int calcScoreFromTti();
  // 피 관련
  int calcScoreFromPi();
  // 고도리 확인
  bool isGodori(BadakHand& cardSet);
  // 초단 확인
  bool isChodan(BadakHand& cardSet);

 private:
  int score;
};

#endif