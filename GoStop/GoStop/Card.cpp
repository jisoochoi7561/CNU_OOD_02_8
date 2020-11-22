#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// ���� : �� �ʴ� û�� ȫ�� �� ���� ����
// ���´� card.txt�� �ִ� ���� �������� �Ͽ����ϴ�.
enum State { ��, ��, ȫ��, �ʴ�, û��, ��, ����, ���� };
// Card Ŭ����
class Card {
 public:
  explicit Card() : month_(1), state_(��) {}

  // Card ���� : ��,����
  Card(const int month, const State state) : month_(month), state_(state) {}

  // Card �� ����
  int GetMonthOfCard() const { return this->month_; }
  // Card ���� ����
  State GetStateOfCard() const {
    //
    return this->state_;
  }
  // Card ���� ���ڿ��� ��ȯ
  std::string stateToString() {
    // switch ������ ����
    switch (this->state_) {
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
  std::string toString() {
    return ("card info: month = " + std::to_string(this->month_)) +
           (" state = " + this->stateToString());
  }

  // Card�� equality�� ���� �������� �Ͽ���.
  bool operator==(const Card& other) {
    if (this->month_ == other.month_) {
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

// ������ ī�带 �׾� ���� ����(dummy), �ٴ�, �÷��̾ ���� ���� �ִ� ī��
// ���� ����, �ٴ�, �÷��̾ ��ӹ޽��ϴ�. random access �� �� �ְ� ī�带
// �߰��ߴ� �����ߴ� �� ���� �����Ƿ� vector�� �����߽��ϴ�. �ٸ� �ǰ� �����ø�
// �ּ��� �Բ� �������ּ���
class CardSet {
 public:
  // ���� �ִ� ī�� ������ ����
  int GetNumOfCards() { return cardset_.size(); }
  // ī�� ���� Ư�� �ε����� ī�带 ����
  Card GetCard(int index) { return cardset_[index]; }
  // ī�带 ī��¿� �߰�
  virtual void AddCard(Card card) {
    if (!(card.GetMonthOfCard() == 0 || card.GetMonthOfCard() > 12)) {
      cardset_.push_back(card);  // ī�� �߰�
      std::sort(cardset_.begin(),
                cardset_.end());  // �߰� �� < operator�� ���� ����
    }
    return;
  }
  // ī�� �¿��� Ư�� �ε����� ī�带 ����(ī�� �¿��� ���ŵ�)
  Card PopIdxCard(int index) {
    if (!(index < 0 || index >= this->GetNumOfCards())) {
      Card popped = cardset_[index];             // ���� ī��
      cardset_.erase(cardset_.begin() + index);  // ī��¿��� ����
      // --�߰�-- �ε����� ������ 1���͸� index-1�� �ϴ� ���� �´µ�
      // �� �������� �״�� 0���ͷ� �����ϴ� ���� �����Ͻ� �� ���Ƽ�
      // �̷� ��쿡�� begin�� ���� �ּҸ� ��ȯ�ϹǷ� index�� ���Ͻô�
      // ���� �½��ϴ�. Ȥ�� 1���� �����ϴ� �ɷ� �����ϼ̴ٸ�
      // �ٽ� index-1�� �ٲ��ּ���.
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
  // --�߰�-- state ���ڷ� �����߽��ϴ�. �׳� �νø� �� �� �����ϴ�.
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

// �÷��̾�, �ٴ�, ���̴� �Ʒ��� ���� CardSet�� ��ӽ�Ű�� ������ ������
// �ý��ϴ�.
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
  bool isEmpty() { return this->GetNumOfCards() == 0; }
};

// �÷��̾ �̹� ���� Card���� �����˴ϴ�.
class PlayerWinCardSet : public CardSet {
 public:
  PlayerWinCardSet() : CardSet() { num_of_go = 0; }

  // ���� ��꿡 ���õ� �Լ����� ���⿡ �ۼ��ϸ� �� �� ���׿�

  // ��Ģ ���� �ƽð����� ���� ������� �� ����̰�
  // ���Ŀ� �÷��̾� �� ��ž�� ���� �� ���� �����
  // ���Ŀ� �����ϸ� �� �� �����ϴ�.
  // �ϴ� �и� �� ���� �Ⱦ��� ���� �������� ��������ϴ�.
  // �Ŀ� �и� �� �Ⱦ��� �� ���ǵ��� �����ϸ� �� �� �����ϴ�.
  // ����� ��Ű�ǵ�� ������ �����߽��ϴ�.

  // �� ����
  void calcScoreFromGwang(Player& player) {
    int numOfGwang = player.getPlayerWinCardSet().FindNumOfSameStateCards(��);  // �� ����
    int numOfBiGwang =
        player.getPlayerWinCardSet().FindNumOfSameStateCards(��);  // �� ����

    if (numOfBiGwang == 0) {  // ���� ���� ���
      if (numOfGwang == 3) {  // ���� 3��
        player.addScore(3);
      } else if (numOfGwang == 4) {  // ���� 4��
        player.addScore(4);
      }
    } else {  // �ִ� ���
      if (numOfGwang == 2) {  // ���� ������ ���� 3��
        player.addScore(2);
      } else if (numOfGwang == 3) {  // ���� ������ ���� 4��
        player.addScore(4);
      }
      else if (numOfGwang == 4) {  // �� ��� ���� ���
        player.addScore(15);
      }
    }
  }
  // ���� ����
  void calcScoreFromKkeut(Player& player) {
    int numOfKkeut = player.getPlayerWinCardSet().FindNumOfSameStateCards(����);
    PlayerWinCardSet playerSet = player.getPlayerWinCardSet();

    if (numOfKkeut >= 5) {  // ������ 5�� �̻��� ���
      player.addScore(numOfKkeut - 4);
    }
    if (isGodori(playerSet)) {
      player.addScore(5);  // ���� ���� �߰�
    }
  }
  // �� ����
  void calcScoreFromTti(Player& player) {
    int numOfHongdan =
        player.getPlayerWinCardSet().FindNumOfSameStateCards(ȫ��);
    int numOfCheongdan =
        player.getPlayerWinCardSet().FindNumOfSameStateCards(û��);
    int numOfChodan =
        player.getPlayerWinCardSet().FindNumOfSameStateCards(�ʴ�);
    PlayerWinCardSet cardSet = player.getPlayerWinCardSet();

    int totalNumOfTti = numOfHongdan + numOfCheongdan + numOfChodan;  // ��� �� ����

    if (numOfHongdan == 3) {  // ȫ���� ���
      player.addScore(3);
    }
    if (numOfCheongdan == 3) {  // û���� ���
      player.addScore(3);
    }
    if (isChodan(cardSet)) {  // �ʴ��� ���
      player.addScore(3);
    }
    
    player.addScore(totalNumOfTti - 4);  // �� �� �Ϲ����� �� ���� ���
  }
  // �� ����
  void calcScoreFromPi(Player& player) {
    int numOfPi = player.getPlayerWinCardSet().FindNumOfSameStateCards(��);
    int numOfSsangPi = player.getPlayerWinCardSet().FindNumOfSameStateCards(����);
    int totalNumOfPi = numOfPi + 2 * numOfSsangPi;

    player.addScore(totalNumOfPi - 9);
    // 9�� ���� ī��� ���߿� �п��� �� ��
    // �������� ���Ŀ� ���� ���¸� �����ϸ�
    // �� �� �����ϴ�.
  }

  bool isGodori(PlayerWinCardSet& cardSet) {
    std::vector<Card> checkCard;  //���� Ȯ�ο� ����

    int numOfCards = cardSet.GetNumOfCards();
    for (int i = 0; i < numOfCards; i++) {
      Card card = cardSet.GetCard(i);
      int month = card.GetMonthOfCard();
      State state = card.GetStateOfCard();
      if (month == 2 || month == 4 || month == 8) {
        if (state == ����) {  // ������ �ش��ϴ� ī���� ���
          checkCard.push_back(card);  // ���Ϳ� �߰�
        }
      }
    }

    return (checkCard.size() == 3);
  }

  bool isChodan(PlayerWinCardSet& cardSet) {
    std::vector<Card> checkCard;  //�ʴ� Ȯ�ο� ����

    int numOfCards = cardSet.GetNumOfCards();
    for (int i = 0; i < numOfCards; i++) {
      Card card = cardSet.GetCard(i);
      int month = card.GetMonthOfCard();
      State state = card.GetStateOfCard();
      if (month == 4 || month == 5 || month == 7) {
        if (state == �ʴ�) {  // �ʴܿ� �ش��ϴ� ī���� ���
          checkCard.push_back(card);  // ���Ϳ� �߰�
        }
      }
    }

    return (checkCard.size() == 3);
  }

 private:
  int num_of_go;
};

// ���� ���� �÷��̾��� CardSet�� �����˴ϴ�.
// �̹� ���� ī����� ����� ���� �����߽��ϴ�.
class Player : public CardSet {
 public:
  Player() : CardSet() { winset_ = PlayerWinCardSet(); }
  // �÷��̾ �տ� ��� �ִ� �д� ���߿� ���� ������ �� �߰��ϸ鼭
  // �ʱ�ȭ�ϸ� �� �� �����ϴ�.

  PlayerWinCardSet getPlayerWinCardSet() { return this->winset_; }
  std::vector<Card> getPlayerCard() { return this->player_card_; }
  int score() { return this->score; }
  void addScore(int score) { this->score += score; }
  void multScore(int ratio) { this->score *= ratio; }

 private:
  PlayerWinCardSet winset_;
  std::vector<Card> player_card_;  // �÷��̾ �տ� ��� �ִ� ��
  int score_;                      // �÷��̾��� ����
};

int main() {
  // state �������� ���� ����
  Card deck[12][4];
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 4; j++) {
      // ù ��° ī�� �ʱ�ȭ
      if (j == 0) {
        switch (i) {
          case 0:
          case 2:
          case 7:
          case 10:
            deck[i][j] = Card(i + 1, ��);
            break;
          case 11:
            deck[i][j] = Card(i + 1, ��);
            break;
          default:  // ������ ���� �ʱ�ȭ, 9�� ù ��° ī�忡 �ش��ϴ� ī���
                    // �ϴ� �������� �ʱ�ȭ
            deck[i][j] = Card(i + 1, ����);
            break;
        }
      } else if (j == 1) {  // �� ��° ī�� �ʱ�ȭ
        switch (i) {
          case 0:
          case 1:
          case 2:
            deck[i][j] = Card(i + 1, ȫ��);
            break;
          case 3:
          case 4:
          case 6:
            deck[i][j] = Card(i + 1, �ʴ�);
            break;
          case 5:
          case 8:
          case 9:
            deck[i][j] = Card(i + 1, û��);
            break;
          case 11:
            deck[i][j] = Card(i + 1, ����);
            break;
          default:
            deck[i][j] = Card(i + 1, ����);
            break;
        }
      } else {          // �� ��°, �� ��° ī�� �ʱ�ȭ
        if (i == 11) {  // 12����
          if (j == 2) {
            deck[i][j] = Card(i + 1, �ʴ�);
          } else if (j == 3) {
            deck[i][j] = Card(i + 1, ����);
          }
        } else {
          deck[i][j] = Card(i + 1, ��);
        }
      }
    }
  }

  // �׽�Ʈ ���� �� ������
  // ��Ȯ�� �뵵�� ����
  // A, B�� ���Ƿ� �����߽��ϴ�.
  Card card = Card(1, ��);
  Card card2 = Card(2, ����);
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
