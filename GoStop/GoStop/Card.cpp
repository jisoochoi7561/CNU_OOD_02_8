#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// 상태 : 광 초단 청단 홍단 피 열끗 쌍피
// 상태는 card.txt에 있는 것을 기준으로 하였습니다.
enum State { 광, 비광, 홍단, 초단, 청단, 피, 열끗, 쌍피 };
// Card 클래스
class Card {
 public:
  explicit Card() : month_(1), state_(광) {}

  // Card 생성 : 월,상태
  Card(const int month, const State state) : month_(month), state_(state) {}

  // Card 월 리턴
  int GetMonthOfCard() const { return this->month_; }
  // Card 상태 리턴
  State GetStateOfCard() const {
    //
    return this->state_;
  }
  // Card 상태 문자열로 변환
  std::string stateToString() {
    // switch 문으로 구현
    switch (this->state_) {
      case 광:
        return "광";
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
  std::string toString() {
    return ("card info: month = " + std::to_string(this->month_)) +
           (" state = " + this->stateToString());
  }

  // Card의 equality는 월을 기준으로 하였음.
  bool operator==(const Card& other) {
    if (this->month_ == other.month_) {
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

// 뒤집을 카드를 쌓아 놓은 더미(dummy), 바닥, 플레이어가 각각 갖고 있는 카드
// 집합 더미, 바닥, 플레이어가 상속받습니다. random access 할 수 있고 카드를
// 추가했다 제거했다 할 일이 많으므로 vector를 선택했습니다. 다른 의견 있으시면
// 주석과 함께 수정해주세요
class CardSet {
 public:
  // 갖고 있는 카드 개수를 리턴
  int GetNumOfCards() { return cardset_.size(); }
  // 카드 셋의 특정 인덱스의 카드를 리턴
  Card GetCard(int index) { return cardset_[index]; }
  // 카드를 카드셋에 추가
  virtual void AddCard(Card card) {
    if (!(card.GetMonthOfCard() == 0 || card.GetMonthOfCard() > 12)) {
      cardset_.push_back(card);  // 카드 추가
      std::sort(cardset_.begin(),
                cardset_.end());  // 추가 후 < operator에 따라 정렬
    }
    return;
  }
  // 카드 셋에서 특정 인덱스의 카드를 뽑음(카드 셋에서 제거됨)
  Card PopIdxCard(int index) {
    if (!(index < 0 || index >= this->GetNumOfCards())) {
      Card popped = cardset_[index];             // 뽑은 카드
      cardset_.erase(cardset_.begin() + index);  // 카드셋에서 제거
      // --추가-- 인덱스의 범위가 1부터면 index-1을 하는 것이 맞는데
      // 제 생각에는 그대로 0부터로 시작하는 것을 생각하신 것 같아서
      // 이럴 경우에는 begin이 시작 주소를 반환하므로 index를 더하시는
      // 것이 맞습니다. 혹시 1부터 시작하는 걸로 생각하셨다면
      // 다시 index-1로 바꿔주세요.
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
  // --추가-- state 후자로 수정했습니다. 그냥 두시면 될 것 같습니다.
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

// 플레이어, 바닥, 더미는 아래와 같이 CardSet을 상속시키는 것으로 구현해
// 봤습니다.
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
  bool isEmpty() { return this->GetNumOfCards() == 0; }
};

// 플레이어가 이미 먹은 Card들이 관리됩니다.
class PlayerWinCardSet : public CardSet {
 public:
  PlayerWinCardSet() : CardSet() { num_of_go = 0; }

  // 점수 계산에 관련된 함수들을 여기에 작성하면 될 것 같네요

  // 규칙 보면 아시겠지만 패의 점수들로 한 계산이고
  // 추후에 플레이어 간 스탑을 했을 시 점수 계산은
  // 추후에 구현하면 될 것 같습니다.
  // 일단 패를 한 번만 훑었을 때를 기준으로 만들었습니다.
  // 후에 패를 또 훑었을 때 계산되도록 수정하면 될 것 같습니다.
  // 영어는 위키피디아 영어판 참조했습니다.

  // 광 관련
  void calcScoreFromGwang(Player& player) {
    int numOfGwang = player.getPlayerWinCardSet().FindNumOfSameStateCards(광);  // 광 갯수
    int numOfBiGwang =
        player.getPlayerWinCardSet().FindNumOfSameStateCards(비광);  // 비광 갯수

    if (numOfBiGwang == 0) {  // 비광이 없는 경우
      if (numOfGwang == 3) {  // 광이 3개
        player.addScore(3);
      } else if (numOfGwang == 4) {  // 광이 4개
        player.addScore(4);
      }
    } else {  // 있는 경우
      if (numOfGwang == 2) {  // 비광을 포함한 광이 3개
        player.addScore(2);
      } else if (numOfGwang == 3) {  // 비광을 포함한 광이 4개
        player.addScore(4);
      }
      else if (numOfGwang == 4) {  // 광 모두 모은 경우
        player.addScore(15);
      }
    }
  }
  // 열끗 관련
  void calcScoreFromKkeut(Player& player) {
    int numOfKkeut = player.getPlayerWinCardSet().FindNumOfSameStateCards(열끗);
    PlayerWinCardSet playerSet = player.getPlayerWinCardSet();

    if (numOfKkeut >= 5) {  // 열끗이 5개 이상인 경우
      player.addScore(numOfKkeut - 4);
    }
    if (isGodori(playerSet)) {
      player.addScore(5);  // 고도리 점수 추가
    }
  }
  // 띠 관련
  void calcScoreFromTti(Player& player) {
    int numOfHongdan =
        player.getPlayerWinCardSet().FindNumOfSameStateCards(홍단);
    int numOfCheongdan =
        player.getPlayerWinCardSet().FindNumOfSameStateCards(청단);
    int numOfChodan =
        player.getPlayerWinCardSet().FindNumOfSameStateCards(초단);
    PlayerWinCardSet cardSet = player.getPlayerWinCardSet();

    int totalNumOfTti = numOfHongdan + numOfCheongdan + numOfChodan;  // 모든 띠 갯수

    if (numOfHongdan == 3) {  // 홍단인 경우
      player.addScore(3);
    }
    if (numOfCheongdan == 3) {  // 청단인 경우
      player.addScore(3);
    }
    if (isChodan(cardSet)) {  // 초단인 경우
      player.addScore(3);
    }
    
    player.addScore(totalNumOfTti - 4);  // 그 외 일반적인 띠 점수 계산
  }
  // 피 관련
  void calcScoreFromPi(Player& player) {
    int numOfPi = player.getPlayerWinCardSet().FindNumOfSameStateCards(피);
    int numOfSsangPi = player.getPlayerWinCardSet().FindNumOfSameStateCards(쌍피);
    int totalNumOfPi = numOfPi + 2 * numOfSsangPi;

    player.addScore(totalNumOfPi - 9);
    // 9월 열끗 카드는 나중에 패에서 낼 때
    // 무엇으로 내냐에 따라서 상태를 변경하면
    // 될 것 같습니다.
  }
  // 고도리 확인
  bool isGodori(PlayerWinCardSet& cardSet) {
    std::vector<Card> checkCard;  //고도리 확인용 벡터

    int numOfCards = cardSet.GetNumOfCards();
    for (int i = 0; i < numOfCards; i++) {
      Card card = cardSet.GetCard(i);
      int month = card.GetMonthOfCard();
      State state = card.GetStateOfCard();
      if (month == 2 || month == 4 || month == 8) {
        if (state == 열끗) {  // 고도리에 해당하는 카드인 경우
          checkCard.push_back(card);  // 벡터에 추가
        }
      }
    }

    return (checkCard.size() == 3);
  }
  // 초단 확인
  bool isChodan(PlayerWinCardSet& cardSet) {
    std::vector<Card> checkCard;  //초단 확인용 벡터

    int numOfCards = cardSet.GetNumOfCards();
    for (int i = 0; i < numOfCards; i++) {
      Card card = cardSet.GetCard(i);
      int month = card.GetMonthOfCard();
      State state = card.GetStateOfCard();
      if (month == 4 || month == 5 || month == 7) {
        if (state == 초단) {  // 초단에 해당하는 카드인 경우
          checkCard.push_back(card);  // 벡터에 추가
        }
      }
    }

    return (checkCard.size() == 3);
  }

 private:
  int num_of_go;
};

// 게임 중의 플레이어의 CardSet이 관리됩니다.
// 이미 먹은 카드셋을 멤버로 갖게 구현했습니다.
class Player : public CardSet {
 public:
  Player() : CardSet() { winset_ = PlayerWinCardSet(); }
  // 플레이어가 손에 쥐고 있는 패는 나중에 게임 시작할 때 추가하면서
  // 초기화하면 될 것 같습니다.

  PlayerWinCardSet getPlayerWinCardSet() { return this->winset_; }
  std::vector<Card> getPlayerCard() { return this->player_card_; }
  int score() { return this->score; }
  void addScore(int score) { this->score += score; }
  void multScore(int ratio) { this->score *= ratio; }

 private:
  PlayerWinCardSet winset_;
  std::vector<Card> player_card_;  // 플레이어가 손에 쥐고 있는 패
  int score_;                      // 플레이어의 점수
};

int main() {
  // state 변경으로 인해 수정
  Card deck[12][4];
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 4; j++) {
      // 첫 번째 카드 초기화
      if (j == 0) {
        switch (i) {
          case 0:
          case 2:
          case 7:
          case 10:
            deck[i][j] = Card(i + 1, 광);
            break;
          case 11:
            deck[i][j] = Card(i + 1, 비광);
            break;
          default:  // 나머지 월들 초기화, 9월 첫 번째 카드에 해당하는 카드는
                    // 일단 열끗으로 초기화
            deck[i][j] = Card(i + 1, 열끗);
            break;
        }
      } else if (j == 1) {  // 두 번째 카드 초기화
        switch (i) {
          case 0:
          case 1:
          case 2:
            deck[i][j] = Card(i + 1, 홍단);
            break;
          case 3:
          case 4:
          case 6:
            deck[i][j] = Card(i + 1, 초단);
            break;
          case 5:
          case 8:
          case 9:
            deck[i][j] = Card(i + 1, 청단);
            break;
          case 11:
            deck[i][j] = Card(i + 1, 쌍피);
            break;
          default:
            deck[i][j] = Card(i + 1, 열끗);
            break;
        }
      } else {          // 세 번째, 네 번째 카드 초기화
        if (i == 11) {  // 12월달
          if (j == 2) {
            deck[i][j] = Card(i + 1, 초단);
          } else if (j == 3) {
            deck[i][j] = Card(i + 1, 쌍피);
          }
        } else {
          deck[i][j] = Card(i + 1, 피);
        }
      }
    }
  }

  // 테스트 용인 것 같은데
  // 정확한 용도는 몰라서
  // A, B는 임의로 변경했습니다.
  Card card = Card(1, 광);
  Card card2 = Card(2, 열끗);
  Card card3 = deck[3][2];
  std::cout << card3.toString() << std::endl;
  std::cout << (card == card2) << std::endl;

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
