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
  int score();
  void setScore(int score);
  std::string getName();
  int choice;
  void setChoice(const Card& card);
  // ������ ���� < operator overloading
  bool operator<(const Player& other);

 private:
  std::string name_;
  CardSet hand_;
  BadakHand badakhand_;
  int score_;           
  int go;

};

#endif