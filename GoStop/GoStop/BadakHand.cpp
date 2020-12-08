#include "BadakHand.h"
#include "Player.h"

//�ڽ��� �ٴڿ� ������ �е��Դϴ�.
BadakHand::BadakHand() : CardSet() { score = 0; }

// ���� ��꿡 ���õ� �Լ����� ���⿡ �ۼ��ϸ� �� �� ���׿�

// ��Ģ ���� �ƽð����� ���� ������� �� ����̰�
// ���Ŀ� �÷��̾� �� ��ž�� ���� �� ���� �����
// ���Ŀ� �����ϸ� �� �� �����ϴ�.
// �ϴ� �и� �� ���� �Ⱦ��� ���� �������� ��������ϴ�.
// �Ŀ� �и� �� �Ⱦ��� �� ���ǵ��� �����ϸ� �� �� �����ϴ�.
// ����� ��Ű�ǵ�� ������ �����߽��ϴ�.

// �� ����

//�ٴ����� ������ ����մϴ�.
void BadakHand::calc(Player& player) {
  int gwangScore = calcScoreFromGwang();
  int piScore = calcScoreFromPi();
  int score=0;

  if (gwangScore != 0) {  //������ ������ �� ���
    score += gwangScore;
    player.setScoredByGwang(true);  //������ ������ ���ٰ� ǥ��
  }
  if (piScore != 0) {  //�Ƿ� ������ �� ���
    score += piScore;
    player.setScoredByPi(true);  //�Ƿ� ������ ���ٰ� ǥ��
  }
  this->score=
  calcScoreFromKkeut()+
  calcScoreFromTti()+score;
}

//�ٴ����� ������ �����մϴ�.
int BadakHand::getScore() { return this->score; }

//������ �������
int BadakHand::calcScoreFromGwang() {
  int score = 0;

  int numOfGwang =
      this->FindNumOfSameStateCards(��);  // �� ����
  int numOfBiGwang = this->FindNumOfSameStateCards(��);  // �� ����

  if (numOfBiGwang == 0) {  // ���� ���� ���
    if (numOfGwang == 3) {  // ���� 3��
      score += 3;
    } else if (numOfGwang == 4) {  // ���� 4��
      score += 4;
    }
  } else {                  // �ִ� ���
    if (numOfGwang == 2) {  // ���� ������ ���� 3��
      score += 2;
    } else if (numOfGwang == 3) {  // ���� ������ ���� 4��
      score+=4;

    } else if (numOfGwang == 4) {  // �� ��� ���� ���
      score += 15;
    }
  }

  return score;
}
// ���� ����
int BadakHand::calcScoreFromKkeut() {
  int score = 0;
  int numOfKkeut = this->FindNumOfSameStateCards(����);
  BadakHand playerSet = *this;

  if (numOfKkeut >= 5) {  // ������ 5�� �̻��� ���
   score+=(numOfKkeut - 4);
  }
  if (isGodori(playerSet)) {
    score+=(5);  // ���� ���� �߰�
  }
  return score;
}
// �� ����
int BadakHand::calcScoreFromTti() {
  int score = 0;
  int numOfHongdan = this->FindNumOfSameStateCards(ȫ��);
  int numOfCheongdan =
      this->FindNumOfSameStateCards(û��);
  int numOfChodan = this->FindNumOfSameStateCards(�ʴ�);
  BadakHand cardSet = *this;

  int totalNumOfTti =
      numOfHongdan + numOfCheongdan + numOfChodan;  // ��� �� ����

  if (numOfHongdan == 3) {  // ȫ���� ���
    score+=(3);
  }
  if (numOfCheongdan == 3) {  // û���� ���
    score+=(3);
  }
  if (isChodan(cardSet)) {  // �ʴ��� ���
    score+=(3);
  }
  if (totalNumOfTti >= 5) {
    score += (totalNumOfTti - 4);
    // �� �� �Ϲ����� �� ���� ���
  }
    
  return score;
}
// �� ����
int BadakHand::calcScoreFromPi() {
  int score = 0;
  int numOfPi =this->FindNumOfSameStateCards(��);
  int numOfSsangPi =this->FindNumOfSameStateCards(����);
  int totalNumOfPi = numOfPi + 2 * numOfSsangPi;
  if (totalNumOfPi>=10) {
    score += (totalNumOfPi - 9);
  }
 
  // 9�� ���� ī��� ���߿� �п��� �� ��
  // �������� ���Ŀ� ���� ���¸� �����ϸ�
  // �� �� �����ϴ�.
 return score;
}
// ���� Ȯ��
bool BadakHand::isGodori(BadakHand& cardSet) {
  std::vector<Card> checkCard;  //���� Ȯ�ο� ����

  int numOfCards = cardSet.GetNumOfCards();
  for (int i = 0; i < numOfCards; i++) {
    Card card = cardSet.GetCard(i);
    int month = card.GetMonthOfCard();
    if (month == 2 || month == 4 || month == 8) {
      if (card.GetStateOfCard() == ����) {  // ������ �ش��ϴ� ī���� ���
        checkCard.push_back(card);  // ���Ϳ� �߰�
      }
    }
  }

  return (checkCard.size() == 3);
}
// �ʴ� Ȯ��
bool BadakHand::isChodan(BadakHand& cardSet) {
  std::vector<Card> checkCard;  //�ʴ� Ȯ�ο� ����

  int numOfCards = cardSet.GetNumOfCards();
  for (int i = 0; i < numOfCards; i++) {
    Card card = cardSet.GetCard(i);
    int month = card.GetMonthOfCard();
    if (month == 4 || month == 5 || month == 7) {
      if (card.GetStateOfCard() == �ʴ�) {  // �ʴܿ� �ش��ϴ� ī���� ���
        checkCard.push_back(card);  // ���Ϳ� �߰�
      }
    }
  }

  return (checkCard.size() == 3);
}