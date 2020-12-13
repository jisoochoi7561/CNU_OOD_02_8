#pragma once
#ifndef EndGameUtil_h
#define EndGameUtil_h

#include "Player.h"
#include<vector>

// ��� �� ��츦 �����ִ� Ŭ����
// singleton design �������� ����
class EndGameUtil {
 public:
  static EndGameUtil* GetInstance();
  void calcByMungBak(Player& player);
  void checkGoBak(std::vector<Player>& players, Player& player);
  void calcByPiBak(std::vector<Player>& players, Player& player);
  void calcByGwangBak(std::vector<Player>& players, Player& player);
  void calcScoreByGo(Player& player);  // �߰� �Լ�

 private:
  EndGameUtil() {}
  static EndGameUtil* instance_;
};

#endif