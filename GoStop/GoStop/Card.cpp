#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

  // CardSet���� ������ ���� < operator overloading
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

// ������ ī�带 �׾� ���� ����(dummy), �ٴ�, �÷��̾ ���� ���� �ִ� ī�� ����
// ����, �ٴ�, �÷��̾ ��ӹ޽��ϴ�.
// random access �� �� �ְ� ī�带 �߰��ߴ� �����ߴ� �� ���� �����Ƿ� vector�� �����߽��ϴ�.
// �ٸ� �ǰ� �����ø� �ּ��� �Բ� �������ּ���
class CardSet {
 public:
  // ���� �ִ� ī�� ������ ����
  int GetNumOfCards() { return cardset_.size(); }
  // ī�� ���� Ư�� �ε����� ī�带 ����
  Card GetCard(int index) { return cardset_[index]; }
  // ī�带 ī��¿� �߰�
  virtual void AddCard(Card card) {
    if (!(card.GetMonthOfCard() == 0 || card.GetMonthOfCard() > 12)) {
      cardset_.push_back(card); // ī�� �߰�
      std::sort(cardset_.begin(), cardset_.end());  // �߰� �� < operator�� ���� ����
    }
    return;
  }
  // ī�� �¿��� Ư�� �ε����� ī�带 ����(ī�� �¿��� ���ŵ�)
  Card PopIdxCard(int index) { 
    if (!(index < 0 || index >= this->GetNumOfCards())) {
      Card popped = cardset_[index];  // ���� ī��
      cardset_.erase(cardset_.begin() + (index - 1)); // ī��¿��� ����
      return popped;
    }
  }
  // Ư�� ���� ī�尡 �� �� �ִ��� ����
  int FindNumOfSameMonthCards(int month) {
    int i = 0;
    for (Card c : cardset_) {
      if (c.GetMonthOfCard() == month) i++;
    }
    return i;
  }
  // Ư�� state�� ī�尡 �� �� �ִ��� ����
  // ���⼭ state�� ���� ������ ���ε��� card.txt���� ī�� �̸��� 'A,B,C,D'����
  // �ƴϸ� ��, ��, ��, �ܰ� ���� ī�� ������ ��Ÿ���� ������ �𸣰ڽ��ϴ�.
  // ���ڶ�� �ڵ�� �Ʒ��� ����.. �ƴ϶�� �����ؾ� �մϴ�.
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

// �÷��̾�, �ٴ�, ���̴� �Ʒ��� ���� CardSet�� ��ӽ�Ű�� ������ ������ �ý��ϴ�.
class Dummy : public CardSet {
 public:
  // ī�� �¿� �ִ� ī����� �������� ���� �Լ�
  void Shuffle() {
    if (cardset_.size() > 1) {
      std::random_shuffle(cardset_.begin(), cardset_.end());
    }
  }
  // override AddCard
  virtual void AddCard(Card card) {
    if (!(card.GetMonthOfCard() == 0 || card.GetMonthOfCard() > 12)) {
      cardset_.push_back(card);  // ī�� �߰�
      // �������� ����
    }
    return;
  }
  // ������ ���� ���� �ִ� ī�带 �ϳ� ������ �Լ�
  Card PopOneCard() { 
    Card popped = cardset_.back();
    cardset_.pop_back();  // ���̿��� ����
    return popped;
  }
  // ���̿� ���� ī�尡 ������ Ȯ���ϴ� �Լ�
  bool isEmpty() { return this->GetNumOfCards() == 0;  }
};

// �÷��̾ �̹� ���� Card���� �����˴ϴ�.
class PlayerWinCardSet : public CardSet {
 public:
  PlayerWinCardSet() : CardSet() { num_of_go = 0; }

  // ���� ��꿡 ���õ� �Լ����� ���⿡ �ۼ��ϸ� �� �� ���׿�


 private:
  int num_of_go;
};

// ���� ���� �÷��̾��� CardSet�� �����˴ϴ�.
// �̹� ���� ī����� ����� ���� �����߽��ϴ�.
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