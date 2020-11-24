#include <iostream>

#include "Card.h"
#include "CardSet.h"
#include "Dummy.h"
#include "Player.h"
#include "PlayerWinCardSet.h"

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