#pragma once
#ifndef Dummy_h
#define Dummy_h
#include "CardSet.h"
#include <algorithm>

// �÷��̾�, �ٴ�, ���̴� �Ʒ��� ���� CardSet�� ��ӽ�Ű�� ������ ������
// �ý��ϴ�.
class Dummy : public CardSet {
 public:
  // ī�� �¿� �ִ� ī����� �������� ���� �Լ�
  void Shuffle();
  // override AddCard
  virtual void AddCard(Card card);
  // ������ ���� ���� �ִ� ī�带 �ϳ� ������ �Լ�
  Card PopOneCard();
  // ���̿� ���� ī�尡 ������ Ȯ���ϴ� �Լ�
  bool isEmpty();
};

#endif