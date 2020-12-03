#include "Dummy.h"
#include <algorithm>
#include <random>
// ī�� �¿� �ִ� ī����� �������� ���� �Լ�
auto rd = std::random_device{};
auto rng = std::default_random_engine{ rd() };
//���� �۵����� �ʽ��ϴ�.���Լ����������� �𸣰����� �и� ������ �ʿ��մϴ�.��Ȯ�� ���ϸ� ���̱��ѰŰ����� �Ű����� ��� �Ȱ��� ���Դϴ�.
// ---- �߰� ----- �ذ��Ͽ����ϴ�    -MinsuHan
void Dummy::Shuffle() {
  if (cardset_.size() > 1) {
    std::shuffle(cardset_.begin(), cardset_.end(), rng);
    std::cout << "������ ������ �Ϸ�Ǿ����ϴ�." << std::endl;
  }
}

//���̸� �����մϴ�. ������ �������� ī�并ġ.
void Dummy::reset() {
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 4; j++) {
      // ù ��° ī�� �ʱ�ȭ
      if (j == 0) {
        switch (i) {
          case 0:
          case 2:
          case 7:
          case 10:
            this->AddCard(Card(i + 1, ��));
            break;
          case 11:
            this->AddCard(Card(i + 1, ��));
            break;
          case 8:
            this->AddCard(Card(i + 1, ����));
            break;
          default: 
            this->AddCard(Card(i + 1, ����));
            break;
        }
      } else if (j == 1) {  // �� ��° ī�� �ʱ�ȭ
        switch (i) {
          case 0:
          case 1:
          case 2:
            this->AddCard(Card(i + 1, ȫ��));
            break;
          case 3:
          case 4:
          case 6:
            this->AddCard(Card(i + 1, �ʴ�));
            break;
          case 5:
          case 8:
          case 9:
            this->AddCard(Card(i + 1, û��));
            break;
          case 11:
            this->AddCard(Card(i + 1, ����));
            break;
          default:
            this->AddCard(Card(i + 1, ����));
            break;
        }
      } else {          // �� ��°, �� ��° ī�� �ʱ�ȭ
        if (i == 11) {  // 12����
          if (j == 2) {
            this->AddCard(Card(i + 1, �ʴ�));
          } else if (j == 3) {
            this->AddCard(Card(i + 1, ����));
          }
        } else {
          this->AddCard(Card(i + 1, ��));
        }
      }
    }
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

// ���̿� ���� ī�尡 ������ Ȯ���ϴ� �Լ�
bool Dummy::isEmpty() { return this->GetNumOfCards() == 0; }