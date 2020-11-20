#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

  // CardSet에서 정렬을 위한 < operator overloading
  bool operator<(const Card& other) {
    if (this->month_ == other.month_) {
      return this->state_ < other.state_;
    } else {
      return this->month_ < other.month_;
    }
  }

 private:
  State state_;
  int month_;
};

// 뒤집을 카드를 쌓아 놓은 더미(dummy), 바닥, 플레이어가 각각 갖고 있는 카드 집합
// 더미, 바닥, 플레이어가 상속받습니다.
// random access 할 수 있고 카드를 추가했다 제거했다 할 일이 많으므로 vector를 선택했습니다.
// 다른 의견 있으시면 주석과 함께 수정해주세요
class CardSet {
 public:
  // 갖고 있는 카드 개수를 리턴
  int GetNumOfCards() { return cardset_.size(); }
  // 카드 셋의 특정 인덱스의 카드를 리턴
  Card GetCard(int index) { return cardset_[index]; }
  // 카드를 카드셋에 추가
  virtual void AddCard(Card card) {
    if (!(card.GetMonthOfCard() == 0 || card.GetMonthOfCard() > 12)) {
      cardset_.push_back(card); // 카드 추가
      std::sort(cardset_.begin(), cardset_.end());  // 추가 후 < operator에 따라 정렬
    }
    return;
  }
  // 카드 셋에서 특정 인덱스의 카드를 뽑음(카드 셋에서 제거됨)
  Card PopIdxCard(int index) { 
    if (!(index < 0 || index >= this->GetNumOfCards())) {
      Card popped = cardset_[index];  // 뽑은 카드
      cardset_.erase(cardset_.begin() + (index - 1)); // 카드셋에서 제거
      return popped;
    }
  }
  // 특정 월의 카드가 몇 개 있는지 리턴
  int FindNumOfSameMonthCards(int month) {
    int i = 0;
    for (Card c : cardset_) {
      if (c.GetMonthOfCard() == month) i++;
    }
    return i;
  }
  // 특정 state의 카드가 몇 개 있는지 리턴
  // 여기서 state가 제가 이전에 업로드한 card.txt에서 카드 이름의 'A,B,C,D'인지
  // 아니면 광, 피, 열, 단과 같이 카드 종류를 나타내는 것인지 모르겠습니다.
  // 후자라면 코드는 아래와 같고.. 아니라면 수정해야 합니다.
  int FindNumOfSameStateCards(State state) {
    int i = 0;
    for (Card c : cardset_) {
      if (c.GetStateOfCard() == state) i++;
    }
    return i;
  }

 protected:
  std::vector<Card> cardset_;
};

// 플레이어, 바닥, 더미는 아래와 같이 CardSet을 상속시키는 것으로 구현해 봤습니다.
class Dummy : public CardSet {
 public:
  // 카드 셋에 있는 카드들을 무작위로 섞는 함수
  void Shuffle() {
    if (cardset_.size() > 1) {
      std::random_shuffle(cardset_.begin(), cardset_.end());
    }
  }
  // override AddCard
  virtual void AddCard(Card card) {
    if (!(card.GetMonthOfCard() == 0 || card.GetMonthOfCard() > 12)) {
      cardset_.push_back(card);  // 카드 추가
      // 정렬하지 않음
    }
    return;
  }
  // 더미의 가장 위에 있는 카드를 하나 빼내는 함수
  Card PopOneCard() { 
    Card popped = cardset_.back();
    cardset_.pop_back();  // 더미에서 제거
    return popped;
  }
  // 더미에 남은 카드가 없는지 확인하는 함수
  bool isEmpty() { return this->GetNumOfCards() == 0;  }
};

// 플레이어가 이미 먹은 Card들이 관리됩니다.
class PlayerWinCardSet : public CardSet {
 public:
  PlayerWinCardSet() : CardSet() { num_of_go = 0; }

  // 점수 계산에 관련된 함수들을 여기에 작성하면 될 것 같네요


 private:
  int num_of_go;
};

// 게임 중의 플레이어의 CardSet이 관리됩니다.
// 이미 먹은 카드셋을 멤버로 갖게 구현했습니다.
class Player : public CardSet {
 public:
  Player() : CardSet() { winset_ = PlayerWinCardSet(); }
 private:
  PlayerWinCardSet winset_;
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

  Dummy dummy;
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 4; j++) {
      dummy.AddCard(deck[i][j]);
    }
  }
  dummy.Shuffle();

  while (!dummy.isEmpty()) {
    std::cout << dummy.PopOneCard().toString() << std::endl;
  }

  return 0;
}