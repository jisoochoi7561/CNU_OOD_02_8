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
  int getScore();
  void setScore(int score);
  std::string getName();
  void setChoice(const Card& card);
  // 정렬을 위한 < operator overloading
  bool operator<(const Player& other);

  bool getSayGo();
  void setSayGo(bool sayGo);
  int getGo();
  void setGo(int go);
  bool getScoredByGwang();
  void setScoredByGwang(bool flag);
  bool getScoredByPi();
  void setScoredByPi(bool flag);
  int getScoreToPay();
  void setScoreToPay(int score);
  bool getIsPresident();
  void setIsPresident(bool isPresident);
  void getPiFromPlayer(std::vector<Player>& players);

 private:
  std::string name_;
  CardSet hand_;
  BadakHand badakhand_;
  int score_;
  int choice;
  int go;
  bool sayGo_;  //플레이어가 고를 말했는지의 상태
  bool scoredByGwang_;  //광에 의해 점수가 났는지 상태
  bool scoredByPi_;  //피에 의해 점수가 났는지 상태
  int scoreToPay_;  // 지불할 금액에 해당하는 최종 점수
  bool isPresident_; // 총통 여부

};

#endif