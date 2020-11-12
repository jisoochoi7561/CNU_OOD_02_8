#include <iostream>
#include <string>
 // 상태 A B C D
enum State { 
 
  A, B, C, D
};
 // Card 클래스
class Card {
 public:
  explicit Card() : month_(1),state_(A) {  }

  // Card 생성 : 월,상태
  Card(const int month,const State state) : month_(month),state_(state)  {
  }

  // Card 월 리턴
  int GetMonthOfCard() const { return this->month_;
  }
  // Card 상태 리턴
  State GetStateOfCard() const {
    // 
    return this->state_;
  }
  // Card 상태 문자열로 변환
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
 // Card 정보 출력
  std::string toString() {
    return ("card info: month = " + std::to_string(this->month_)) +
           (" state = " + this->stateToString());
  }

  // Card의 equality는 월을 기준으로 하였음.
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