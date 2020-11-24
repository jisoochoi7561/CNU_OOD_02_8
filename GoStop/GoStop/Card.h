#pragma once
#ifndef Card_h
#define Card_h
#include <iostream>
#include <string>
// ���� : �� �ʴ� û�� ȫ�� �� ���� ����
// ���´� card.txt�� �ִ� ���� �������� �Ͽ����ϴ�.
enum State { ��, ��, ȫ��, �ʴ�, û��, ��, ����, ���� };
// Card Ŭ����
class Card {
 public:
  explicit Card();

  // Card ���� : ��,����
  Card(const int month, const State state);

  // Card �� ����
  int GetMonthOfCard() const;
  State GetStateOfCard() const;
  // Card ���� ���ڿ��� ��ȯ
  std::string stateToString();
  // Card ���� ���
  std::string toString();

  // Card�� equality�� ���� �������� �Ͽ���.
  bool operator==(const Card& other);

  // CardSet���� ������ ���� < operator overloading
  bool operator<(const Card& other);

 private:
  State state_;
  int month_;
};

#endif