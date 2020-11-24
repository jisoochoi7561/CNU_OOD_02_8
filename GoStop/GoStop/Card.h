#pragma once
#ifndef Card_h
#define Card_h
#include <iostream>
#include <string>
// 상태 : 광 초단 청단 홍단 피 열끗 쌍피
// 상태는 card.txt에 있는 것을 기준으로 하였습니다.
enum State { 광, 비광, 홍단, 초단, 청단, 피, 열끗, 쌍피 };
// Card 클래스
class Card {
 public:
  explicit Card();

  // Card 생성 : 월,상태
  Card(const int month, const State state);

  // Card 월 리턴
  int GetMonthOfCard() const;
  State GetStateOfCard() const;
  // Card 상태 문자열로 변환
  std::string stateToString();
  // Card 정보 출력
  std::string toString();

  // Card의 equality는 월을 기준으로 하였음.
  bool operator==(const Card& other);

  // CardSet에서 정렬을 위한 < operator overloading
  bool operator<(const Card& other);

 private:
  State state_;
  int month_;
};

#endif