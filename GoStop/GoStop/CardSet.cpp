#include "CardSet.h"

// ���� �ִ� ī�� ������ ����
int CardSet::GetNumOfCards() { return cardset_.size(); }
// ī�� ���� Ư�� �ε����� ī�带 ����
Card CardSet::GetCard(int index) { return cardset_[index]; }
// ī�带 ī��¿� �߰�
void CardSet::AddCard(Card card) {
    cardset_.push_back(card);  // ī�� �߰�
    std::sort(cardset_.begin(),
              cardset_.end());  // �߰� �� < operator�� ���� ����
  return;
}


std::vector<Card>& CardSet::getCardset() { return this->cardset_; }
// ī�� �¿��� Ư�� �ε����� ī�带 ����(ī�� �¿��� ���ŵ�)
Card CardSet::PopIdxCard(int index) {
  Card popped;
  if (!(index < 0 || index >= this->GetNumOfCards())) {
    popped = cardset_[index];             // ���� ī��
    cardset_.erase(cardset_.begin() + index);  // ī��¿��� ����
    // --�߰�-- �ε����� ������ 1���͸� index-1�� �ϴ� ���� �´µ�
    // �� �������� �״�� 0���ͷ� �����ϴ� ���� �����Ͻ� �� ���Ƽ�
    // �̷� ��쿡�� begin�� ���� �ּҸ� ��ȯ�ϹǷ� index�� ���Ͻô�
    // ���� �½��ϴ�. Ȥ�� 1���� �����ϴ� �ɷ� �����ϼ̴ٸ�
    // �ٽ� index-1�� �ٲ��ּ���.
  }
  return popped;
}
//� ���� pop
Card CardSet::PopCard() {
  Card popped = cardset_.back();
  cardset_.pop_back();  // ���̿��� ����
  return popped;
}
    // Ư�� ���� ī�尡 �� �� �ִ��� ����
int CardSet::FindNumOfSameMonthCards(int month) {
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
int CardSet::FindNumOfSameStateCards(State state) {
  int i = 0;
  for (Card c : cardset_) {
    if (c.GetStateOfCard() == state) i++;
  }
  return i;
}


//ī����� ������ ����մϴ�
//ī����� ������ �ִ¸�ŭ ���������� ����� �͵� ���ͽ��ϴ�.
void CardSet::printCardSet() {
  int size = this->cardset_.size();
  for (int i = 0; i < size; i++) {
    std::cout << i << " " << this->cardset_.at(i).toString() << std::endl;
  }

}