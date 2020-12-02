#include "BadakHand.h"

#include "Player.h"

BadakHand::BadakHand() : CardSet() { num_of_go = 0; }

// ���� ��꿡 ���õ� �Լ����� ���⿡ �ۼ��ϸ� �� �� ���׿�

// ��Ģ ���� �ƽð����� ���� ������� �� ����̰�
// ���Ŀ� �÷��̾� �� ��ž�� ���� �� ���� �����
// ���Ŀ� �����ϸ� �� �� �����ϴ�.
// �ϴ� �и� �� ���� �Ⱦ��� ���� �������� ��������ϴ�.
// �Ŀ� �и� �� �Ⱦ��� �� ���ǵ��� �����ϸ� �� �� �����ϴ�.
// ����� ��Ű�ǵ�� ������ �����߽��ϴ�.

// �� ����
void BadakHand::calcScoreFromGwang(Player& player) {
  int numOfGwang =
      player.getBadakHand().FindNumOfSameStateCards(��);  // �� ����
  int numOfBiGwang =
      player.getBadakHand().FindNumOfSameStateCards(��);  // �� ����

  if (numOfBiGwang == 0) {  // ���� ���� ���
    if (numOfGwang == 3) {  // ���� 3��
      player.addScore(3);
    } else if (numOfGwang == 4) {  // ���� 4��
      player.addScore(4);
    }
  } else {                  // �ִ� ���
    if (numOfGwang == 2) {  // ���� ������ ���� 3��
      player.addScore(2);
    } else if (numOfGwang == 3) {  // ���� ������ ���� 4��
      player.addScore(4);
    } else if (numOfGwang == 4) {  // �� ��� ���� ���
      player.addScore(15);
    }
  }
}
// ���� ����
void BadakHand::calcScoreFromKkeut(Player& player) {
  int numOfKkeut = player.getBadakHand().FindNumOfSameStateCards(����);
  BadakHand playerSet = player.getBadakHand();

  if (numOfKkeut >= 5) {  // ������ 5�� �̻��� ���
    player.addScore(numOfKkeut - 4);
  }
  if (isGodori(playerSet)) {
    player.addScore(5);  // ���� ���� �߰�
  }
}
// �� ����
void BadakHand::calcScoreFromTti(Player& player) {
  int numOfHongdan = player.getBadakHand().FindNumOfSameStateCards(ȫ��);
  int numOfCheongdan =
      player.getBadakHand().FindNumOfSameStateCards(û��);
  int numOfChodan = player.getBadakHand().FindNumOfSameStateCards(�ʴ�);
  BadakHand cardSet = player.getBadakHand();

  int totalNumOfTti =
      numOfHongdan + numOfCheongdan + numOfChodan;  // ��� �� ����

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
void BadakHand::calcScoreFromPi(Player& player) {
  int numOfPi = player.getBadakHand().FindNumOfSameStateCards(��);
  int numOfSsangPi = player.getBadakHand().FindNumOfSameStateCards(����);
  int totalNumOfPi = numOfPi + 2 * numOfSsangPi;

  player.addScore(totalNumOfPi - 9);
  // 9�� ���� ī��� ���߿� �п��� �� ��
  // �������� ���Ŀ� ���� ���¸� �����ϸ�
  // �� �� �����ϴ�.
}
// ���� Ȯ��
bool BadakHand::isGodori(BadakHand& cardSet) {
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
// �ʴ� Ȯ��
bool BadakHand::isChodan(BadakHand& cardSet) {
  std::vector<Card> checkCard;  //�ʴ� Ȯ�ο� ����

  int numOfCards = cardSet.GetNumOfCards();
  for (int i = 0; i < numOfCards; i++) {
    Card card = cardSet.GetCard(i);
    int month = card.GetMonthOfCard();
    State state = card.GetStateOfCard();
    if (month == 4 || month == 5 || month == 7) {
      if (state == �ʴ�) {          // �ʴܿ� �ش��ϴ� ī���� ���
        checkCard.push_back(card);  // ���Ϳ� �߰�
      }
    }
  }

  return (checkCard.size() == 3);
}