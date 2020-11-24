#pragma once
#ifndef Player_h
#define Player_h

#include "CardSet.h"
#include "PlayerWinCardSet.h"

// 게임 중의 플레이어의 CardSet이 관리됩니다.
// 이미 먹은 카드셋을 멤버로 갖게 구현했습니다.
class Player : public CardSet {
 public:
  Player();
  // 플레이어가 손에 쥐고 있는 패는 나중에 게임 시작할 때 추가하면서
  // 초기화하면 될 것 같습니다.

  PlayerWinCardSet getPlayerWinCardSet();
  std::vector<Card> getPlayerCard();
  int score();
  void addScore(int score);
  void multScore(int ratio);

 private:
  PlayerWinCardSet winset_;
  std::vector<Card> player_card_;  // 플레이어가 손에 쥐고 있는 패
  int score_;                      // 플레이어의 점수
};

#endif