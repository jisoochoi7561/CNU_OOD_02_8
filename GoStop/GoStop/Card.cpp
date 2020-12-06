#include "Card.h"
#include <iostream>

// Card 클래스
Card::Card() : month_(1), state_(광) {}
// Card 생성 : 월,상태
Card::Card(const int month, const State state) : month_(month), state_(state) {}
// Card 월 리턴
int Card::GetMonthOfCard() const { return this->month_; }
// Card 상태 리턴
State Card::GetStateOfCard() const {
  //
  return this->state_;
}
// Card 상태 문자열로 변환
std::string Card::stateToString() {
  // switch 문으로 구현
  switch (this->state_) {
    case 광:
      return "광";
      break;
    case 비광:
      return "비광";
      break;
    case 홍단:
      return "홍단";
      break;
    case 초단:
      return "초단";
      break;
    case 청단:
      return "청단";
      break;
    case 피:
      return "피";
      break;
    case 열끗:
      return "열끗";
      break;
    case 쌍피:
      return "쌍피";
      break;
  }
}
// Card 정보 출력
std::string Card::toString() {
  return ("card info: month = " + std::to_string(this->month_)) +
         (" state = " + this->stateToString());
}

// Card의 equality는 월을 기준으로 하였음.
bool Card::operator==(const Card& other) {
  if (this->month_ == other.month_) {
    return true;
  }
  return false;
}

// CardSet에서 정렬을 위한 < operator overloading
bool Card::operator<(const Card& other) {
  if (this->month_ == other.month_) {
    return this->state_ < other.state_;
  } else {
    return this->month_ < other.month_;
  }
}
void Card::setState(State state) { this->state_ = state; }