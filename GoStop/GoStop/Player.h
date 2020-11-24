#pragma once
#ifndef Player_h
#define Player_h

#include "CardSet.h"
#include "PlayerWinCardSet.h"

// ���� ���� �÷��̾��� CardSet�� �����˴ϴ�.
// �̹� ���� ī����� ����� ���� �����߽��ϴ�.
class Player : public CardSet {
 public:
  Player();
  // �÷��̾ �տ� ��� �ִ� �д� ���߿� ���� ������ �� �߰��ϸ鼭
  // �ʱ�ȭ�ϸ� �� �� �����ϴ�.

  PlayerWinCardSet getPlayerWinCardSet();
  std::vector<Card> getPlayerCard();
  int score();
  void addScore(int score);
  void multScore(int ratio);

 private:
  PlayerWinCardSet winset_;
  std::vector<Card> player_card_;  // �÷��̾ �տ� ��� �ִ� ��
  int score_;                      // �÷��̾��� ����
};

#endif