#include "Dummy.h"
#include <algorithm>
#include <random>
// 카드 셋에 있는 카드들을 무작위로 섞는 함수
auto rng = std::default_random_engine{};
void Dummy::Shuffle() {
  if (cardset_.size() > 1) {
    std::shuffle(cardset_.begin(), cardset_.end(), rng);
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
// 더미의 가장 위에 있는 카드를 하나 빼내는 함수
Card Dummy::PopOneCard() {
  Card popped = cardset_.back();
  cardset_.pop_back();  // 더미에서 제거
  return popped;
}
// 더미에 남은 카드가 없는지 확인하는 함수
bool Dummy::isEmpty() { return this->GetNumOfCards() == 0; }