#include <iostream>

// 화투패 클래스
class Card {
 public:
  explicit Card() { name_[0] = 0; }

  // 생성자 : 카드 이름을 인자로 받아 멤버 변수 name_에 복사합니다.
  explicit Card(const char* name) {
    strcpy_s(name_, 4, name);
  }

  // 카드의 월은 이름의 첫 번째 글자입니다.
  // 10~12월은 예외로 각각 K, L, M로 나타냅니다.
  int GetMonthOfCard() const {
    if (isdigit(name_[0])) return name_[0] - '0';
    if (name_[0] == 'K') return 10;
    if (name_[0] == 'L') return 11;
    return 12;
  }

  // 카드의 종류를 숫자로 반환합니다.
  // 크게 광, 열(열끗), 단(띠), 피의 4가지로 나누고,
  // 중복된 특성이 있는 경우(ex. 열끗이자 고도리, 열끗이자 쌍피 등) 혹은
  // 홍단,청단,초단,비광,쌍피의 구분이 필요한 경우(점수계산 등)에는
  // 해당 함수에서 카드의 월을 확인하여 구분하면 될 것 같습니다.
  // ex) 열끗&고도리인지 확인 ->
  // if(CardSet[3].GetTypeOfCard() == 1 && CardSet[3].GetMonthOfCard() == 2 or 4 or 8)
  int GetTypeOfCard() const {
    // 
    if (strcmp(&name_[1], "광") == 0) return 0;
    if (strcmp(&name_[1], "열") == 0) return 1;
    if (strcmp(&name_[1], "단") == 0) return 2;
    return 3;
  }

  // 카드 이름을 반환하는 함수
  char* GetName() { return name_;  }

  // 현재 카드와 다른 카드가 같은지 비교하는 함수(== 연산자 overloading)
  bool operator==(const Card& other) { 
    if (strcmp(name_, other.name_) == 0)
      return true;
    else
      return false;
  }

  // *** 또다른 비교 함수가 필요하다면 추가해 주세요 ***

 private:
  char name_[4];
};

int main() { 
  Card CardSet[2] = {Card("1광"), Card("1열")};
  std::cout << CardSet[0].GetName() << std::endl;
  std::cout << CardSet[1].GetName() << std::endl;
  if (CardSet[0] == CardSet[1]) 
    std::cout << "same" << std::endl;
  else
    std::cout << "different" << std::endl;

  return 0;
}