#include <iostream>
#include <string>
 // ���� A B C D
enum State { 
 
  A, B, C, D
};
 // Card Ŭ����
class Card {
 public:
  explicit Card() : month_(1),state_(A) {  }

  // Card ���� : ��,����
  Card(const int month,const State state) : month_(month),state_(state)  {
  }

  // Card �� ����
  int GetMonthOfCard() const { return this->month_;
  }
  // Card ���� ����
  State GetStateOfCard() const {
    // 
    return this->state_;
  }
  // Card ���� ���ڿ��� ��ȯ
  std::string stateToString() {
    if (this->state_==A) {
      return "A";
    }
    if (this->state_ == B) {
      return "B";
    }
    if (this->state_ == C) {
      return "C";
    }
    if (this->state_ == D) {
      return "D";
    }
  }
 // Card ���� ���
  std::string toString() {
    return ("card info: month = " + std::to_string(this->month_)) +
           (" state = " + this->stateToString());
  }

  // Card�� equality�� ���� �������� �Ͽ���.
  bool operator==(const Card& other) { 
    if (this->month_==other.month_) {
      return true;
    } 
    return false;
  }



 private:
  State state_;
  int month_;
};

int main() { 
  Card deck[12][4] ;
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 4; j++) {
      if (j==0) {
        deck[i][j] = Card(i+1,A);
      }
      else if (j == 1) {
        deck[i][j] = Card(i + 1, B);
      }
      else if (j == 2) {
        deck[i][j] = Card(i + 1, C);
      } else{
        deck[i][j] = Card(i + 1, D);
      }
    }
  }
  Card card = Card(1, A);
  Card card2 = Card(2, B);
  Card card3 = deck[3][2];
  std::cout << card3.toString() << std::endl;
  std::cout << (card==card2) << std::endl;

  return 0;
}