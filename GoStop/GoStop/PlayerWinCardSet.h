#pragma once
#ifndef PlayerWinCardSet_h
#define PlayerWinCardSet_h

class Player;
#include "CardSet.h"

// 플레이어가 이미 먹은 Card들이 관리됩니다.
class PlayerWinCardSet : public CardSet {
 public:
  PlayerWinCardSet();

  // 점수 계산에 관련된 함수들을 여기에 작성하면 될 것 같네요

  // 규칙 보면 아시겠지만 패의 점수들로 한 계산이고
  // 추후에 플레이어 간 스탑을 했을 시 점수 계산은
  // 추후에 구현하면 될 것 같습니다.
  // 일단 패를 한 번만 훑었을 때를 기준으로 만들었습니다.
  // 후에 패를 또 훑었을 때 계산되도록 수정하면 될 것 같습니다.
  // 영어는 위키피디아 영어판 참조했습니다.

  // 광 관련
  void calcScoreFromGwang(Player& player);
  // 열끗 관련
  void calcScoreFromKkeut(Player& player);
  // 띠 관련
  void calcScoreFromTti(Player& player);
  // 피 관련
  void calcScoreFromPi(Player& player);
  // 고도리 확인
  bool isGodori(PlayerWinCardSet& cardSet);
  // 초단 확인
  bool isChodan(PlayerWinCardSet& cardSet);

 private:
  int num_of_go;
};

#endif