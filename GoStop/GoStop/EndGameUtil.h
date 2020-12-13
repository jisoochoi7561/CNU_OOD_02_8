#pragma once
#ifndef EndGameUtil_h
#define EndGameUtil_h

#include "Player.h"
#include<vector>

// 결산 시 경우를 따져주는 클래스
// singleton design 패턴으로 설계
class EndGameUtil {
 public:
  static EndGameUtil* GetInstance();
  void calcByMungBak(Player& player);
  void checkGoBak(std::vector<Player>& players, Player& player);
  void calcByPiBak(std::vector<Player>& players, Player& player);
  void calcByGwangBak(std::vector<Player>& players, Player& player);
  void calcScoreByGo(Player& player);  // 추가 함수

 private:
  EndGameUtil() {}
  static EndGameUtil* instance_;
};

#endif