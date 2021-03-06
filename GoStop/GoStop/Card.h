#pragma once
#ifndef Card_h
#define Card_h
#include <iostream>
#include <string>

//중요!!!! 9월 첫번째 카드 반드시 수정


// 상태 : 광 초단 청단 홍단 피 열끗 쌍피
// 상태는 card.txt에 있는 것을 기준으로 하였습니다.
enum State { gwang, bigwang, hongdan, chodan, cheongdan, pi, kkeut, ssangpi };
// Card 클래스
class Card {
 public:
  explicit Card();

  // Card 생성 : 월,상태
  Card(const int month, const State state, const bool isPpuk);

  // Card 월 리턴
  int GetMonthOfCard() const;
  // Card 상태 리턴
  State GetStateOfCard() const;
  // 뻑 여부 리턴
  bool IsPpuk() const;
  // Card 상태 문자열로 변환
  std::string stateToString();
  // Card 정보 출력
  std::string toString();
  void setState(State state);
  void setPpuk(bool p);
  // Card의 equality는 월을 기준으로 하였음.
  bool operator==(const Card& other);

  // CardSet에서 정렬을 위한 < operator overloading
  bool operator<(const Card& other);

 private:
  State state_;
  int month_;
  bool isPpuk_;
};

#endif