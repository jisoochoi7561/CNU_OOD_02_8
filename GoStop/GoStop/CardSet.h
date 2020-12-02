#pragma once
#ifndef CardSet_h
#define CardSet_h

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Card.h"

// ������ ī�带 �׾� ���� ����(dummy), �ٴ�, �÷��̾ ���� ���� �ִ� ī��
// ���� ����, �ٴ�, �÷��̾ ��ӹ޽��ϴ�. random access �� �� �ְ� ī�带
// �߰��ߴ� �����ߴ� �� ���� �����Ƿ� vector�� �����߽��ϴ�. �ٸ� �ǰ� �����ø�
// �ּ��� �Բ� �������ּ���
class CardSet {
 public:
  // ���� �ִ� ī�� ������ ����
  int GetNumOfCards();
  // ī�� ���� Ư�� �ε����� ī�带 ����
  Card GetCard(int index);
  // ī�带 ī��¿� �߰�
  virtual void AddCard(Card card);
  // ī�� �¿��� Ư�� �ε����� ī�带 ����(ī�� �¿��� ���ŵ�)
  Card PopIdxCard(int index);
  // ī�� ���� ����ī�带 ����(ī�� �¿��� ���ŵ�)
  Card PopCard();
  // Ư�� ���� ī�尡 �� �� �ִ��� ����
  int FindNumOfSameMonthCards(int month);
  // Ư�� state�� ī�尡 �� �� �ִ��� ����
  // ���⼭ state�� ���� ������ ���ε��� card.txt���� ī�� �̸��� 'A,B,C,D'����
  // �ƴϸ� ��, ��, ��, �ܰ� ���� ī�� ������ ��Ÿ���� ������ �𸣰ڽ��ϴ�.
  // ���ڶ�� �ڵ�� �Ʒ��� ����.. �ƴ϶�� �����ؾ� �մϴ�.
  // --�߰�-- state ���ڷ� �����߽��ϴ�. �׳� �νø� �� �� �����ϴ�.
  int FindNumOfSameStateCards(State state);
  std::vector<Card>& getCardset();
  void printCardSet();
 protected:
  std::vector<Card> cardset_;
};

#endif