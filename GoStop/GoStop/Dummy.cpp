#include "Dummy.h"
#include <algorithm>
#include <random>
// ī�� �¿� �ִ� ī����� �������� ���� �Լ�
auto rng = std::default_random_engine{};
void Dummy::Shuffle() {
  if (cardset_.size() > 1) {
    std::shuffle(cardset_.begin(), cardset_.end(), rng);
  }
}
// override AddCard
void Dummy::AddCard(Card card) {
  if (!(card.GetMonthOfCard() == 0 || card.GetMonthOfCard() > 12)) {
    cardset_.push_back(card);  // ī�� �߰�
    // �������� ����
  }
  return;
}
// ������ ���� ���� �ִ� ī�带 �ϳ� ������ �Լ�
Card Dummy::PopOneCard() {
  Card popped = cardset_.back();
  cardset_.pop_back();  // ���̿��� ����
  return popped;
}
// ���̿� ���� ī�尡 ������ Ȯ���ϴ� �Լ�
bool Dummy::isEmpty() { return this->GetNumOfCards() == 0; }