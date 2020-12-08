#include "Dummy.h"
#include <algorithm>
#include <random>
// 카드 셋에 있는 카드들을 무작위로 섞는 함수
auto rd = std::random_device{};
auto rng = std::default_random_engine{ rd() };
//셔플 작동하지 않습니다.이함수문제인지는 모르겠지만 분명 수정이 필요합니다.정확히 말하면 섞이긴한거같은데 매게임이 모두 똑같이 섞입니다.
// ---- 추가 ----- 해결하였습니다    -MinsuHan
void Dummy::Shuffle() {
  if (cardset_.size() > 1) {
    std::shuffle(cardset_.begin(), cardset_.end(), rng);
    std::cout << ">> 더미의 셔플이 완료되엇습니다." << std::endl;
  }
}

//더미를 생성합니다. 포장을 뜯지않은 카드뭉치.
void Dummy::reset() {
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 4; j++) {
      // 첫 번째 카드 초기화
      if (j == 0) {
        switch (i) {
          case 0:
          case 2:
          case 7:
          case 10:
            this->AddCard(Card(i + 1, 광, false));
            break;
          case 11:
            this->AddCard(Card(i + 1, 비광, false));
            break;
          case 8:
            this->AddCard(Card(i + 1, 열끗, false));
            break;
          default: 
            this->AddCard(Card(i + 1, 열끗, false));
            break;
        }
      } else if (j == 1) {  // 두 번째 카드 초기화
        switch (i) {
          case 0:
          case 1:
          case 2:
            this->AddCard(Card(i + 1, 홍단, false));
            break;
          case 3:
          case 4:
          case 6:
            this->AddCard(Card(i + 1, 초단, false));
            break;
          case 5:
          case 8:
          case 9:
            this->AddCard(Card(i + 1, 청단, false));
            break;
          case 11:
            this->AddCard(Card(i + 1, 쌍피, false));
            break;
          default:
            this->AddCard(Card(i + 1, 열끗, false));
            break;
        }
      } else {          // 세 번째, 네 번째 카드 초기화
        if (i == 11) {  // 12월달
          if (j == 2) {
            this->AddCard(Card(i + 1, 초단, false));
          } else if (j == 3) {
            this->AddCard(Card(i + 1, 쌍피, false));
          }
        } else {
          this->AddCard(Card(i + 1, 피, false));
        }
      }
    }
  }
  
}
// override AddCard
void Dummy::AddCard(Card card) {
  
  if (!(card.GetMonthOfCard() == 0 || card.GetMonthOfCard() > 12)) {
    cardset_.push_back(card);  // 카드 추가
    // 정렬하지 않음
  }
  return;
}

// 더미에 남은 카드가 없는지 확인하는 함수
bool Dummy::isEmpty() { return this->GetNumOfCards() == 0; }