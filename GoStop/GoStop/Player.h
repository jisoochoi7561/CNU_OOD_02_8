#pragma once
#ifndef Player_h
#define Player_h

#include "CardSet.h"
#include "BadakHand.h"
#include <string>
// 게임 중의 플레이어의 CardSet이 관리됩니다.
// 이미 먹은 카드셋을 멤버로 갖게 구현했습니다.
class Player  {
 public:
  Player();
  Player(std::string);
  // 플레이어가 손에 쥐고 있는 패는 나중에 게임 시작할 때 추가하면서
  // 초기화하면 될 것 같습니다.

  BadakHand& getBadakHand();
  CardSet& getHand();
  int score();
  void setScore(int score);
  std::string getName();
  int choice;
  void setChoice(const Card& card);
  // 정렬을 위한 < operator overloading
  bool operator<(const Player& other);

 private:
  std::string name_;
  CardSet hand_;
  BadakHand badakhand_;
  int score_;           
  int go;

};

#endif