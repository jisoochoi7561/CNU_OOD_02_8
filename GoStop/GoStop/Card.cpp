#include "Card.h"
#include <iostream>

// Card Ŭ����
Card::Card() : month_(1), state_(gwang), isPpuk_(false) {}
// Card ���� : ��,����
Card::Card(const int month, const State state, const bool isPpuk) : month_(month), state_(state), isPpuk_(isPpuk) {}
// Card �� ����
int Card::GetMonthOfCard() const { return this->month_; }
// Card ���� ����
State Card::GetStateOfCard() const {  return this->state_; }
// �� ���� ����
bool Card::IsPpuk() const { return isPpuk_; }
// �� ���� ����
void Card::setPpuk(bool p) { this->isPpuk_ = p; }
// Card ���� ���ڿ��� ��ȯ
std::string Card::stateToString() {
  // switch ������ ����
  switch (this->state_) {
    case gwang:
      return "��";
      break;
    case bigwang:
      return "��";
      break;
    case hongdan:
      return "ȫ��";
      break;
    case chodan:
      return "�ʴ�";
      break;
    case cheongdan:
      return "û��";
      break;
    case pi:
      return "��";
      break;
    case kkeut:
      return "����";
      break;
    case ssangpi:
      return "����";
      break;
  }
}
// Card ���� ���
std::string Card::toString() {
  return ("card info: month = " + std::to_string(this->month_)) +
         (" state = " + this->stateToString() + ((isPpuk_)? " - ��" : ""));
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