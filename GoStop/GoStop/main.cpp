#include <iostream>

#include "Card.h"
#include "CardSet.h"
#include "Dummy.h"
#include "Player.h"
#include "PlayerWinCardSet.h"

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