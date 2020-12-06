#pragma once
#ifndef Player_h
#define Player_h

#include "CardSet.h"
#include "BadakHand.h"
#include <string>
// ���� ���� �÷��̾��� CardSet�� �����˴ϴ�.
// �̹� ���� ī����� ����� ���� �����߽��ϴ�.
class Player  {
 public:
  Player();
  Player(std::string);
  // �÷��̾ �տ� ��� �ִ� �д� ���߿� ���� ������ �� �߰��ϸ鼭
  // �ʱ�ȭ�ϸ� �� �� �����ϴ�.

  BadakHand& getBadakHand();
  CardSet& getHand();
  int getScore();
  void setScore(int score);
  std::string getName();
  void setChoice(const Card& card);
  // ������ ���� < operator overloading
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

 private:
  std::string name_;
  CardSet hand_;
  BadakHand badakhand_;
  int score_;
  int choice;
  int go;
  bool sayGo_;  //�÷��̾ �� ���ߴ����� ����
  bool scoredByGwang_;  //���� ���� ������ ������ ����
  bool scoredByPi_;  //�ǿ� ���� ������ ������ ����
  int scoreToPay_;  // ������ �ݾ׿� �ش��ϴ� ���� ����

};

#endif