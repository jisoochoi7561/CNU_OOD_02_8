#pragma once
#ifndef Card_h
#define Card_h
#include <iostream>
#include <string>

//�߿�!!!! 9�� ù��° ī�� �ݵ�� ����


// ���� : �� �ʴ� û�� ȫ�� �� ���� ����
// ���´� card.txt�� �ִ� ���� �������� �Ͽ����ϴ�.
enum State { gwang, bigwang, hongdan, chodan, cheongdan, pi, kkeut, ssangpi };
// Card Ŭ����
class Card {
 public:
  explicit Card();

  // Card ���� : ��,����
  Card(const int month, const State state, const bool isPpuk);

  // Card �� ����
  int GetMonthOfCard() const;
  // Card ���� ����
  State GetStateOfCard() const;
  // �� ���� ����
  bool IsPpuk() const;
  // Card ���� ���ڿ��� ��ȯ
  std::string stateToString();
  // Card ���� ���
  std::string toString();
  void setState(State state);
  void setPpuk(bool p);
  // Card�� equality�� ���� �������� �Ͽ���.
  bool operator==(const Card& other);

  // CardSet���� ������ ���� < operator overloading
  bool operator<(const Card& other);

 private:
  State state_;
  int month_;
  bool isPpuk_;
};

#endif