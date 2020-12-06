#include "Card.h"
#include <iostream>

// Card Ŭ����
Card::Card() : month_(1), state_(��) {}
// Card ���� : ��,����
Card::Card(const int month, const State state) : month_(month), state_(state) {}
// Card �� ����
int Card::GetMonthOfCard() const { return this->month_; }
// Card ���� ����
State Card::GetStateOfCard() const {
  //
  return this->state_;
}
// Card ���� ���ڿ��� ��ȯ
std::string Card::stateToString() {
  // switch ������ ����
  switch (this->state_) {
    case ��:
      return "��";
      break;
    case ��:
      return "��";
      break;
    case ȫ��:
      return "ȫ��";
      break;
    case �ʴ�:
      return "�ʴ�";
      break;
    case û��:
      return "û��";
      break;
    case ��:
      return "��";
      break;
    case ����:
      return "����";
      break;
    case ����:
      return "����";
      break;
  }
}
// Card ���� ���
std::string Card::toString() {
  return ("card info: month = " + std::to_string(this->month_)) +
         (" state = " + this->stateToString());
}

// Card�� equality�� ���� �������� �Ͽ���.
bool Card::operator==(const Card& other) {
  if (this->month_ == other.month_) {
    return true;
  }
  return false;
}

// CardSet���� ������ ���� < operator overloading
bool Card::operator<(const Card& other) {
  if (this->month_ == other.month_) {
    return this->state_ < other.state_;
  } else {
    return this->month_ < other.month_;
  }
}
void Card::setState(State state) { this->state_ = state; }