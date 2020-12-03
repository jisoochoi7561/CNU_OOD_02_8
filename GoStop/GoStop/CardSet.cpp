#include "CardSet.h"

// 갖고 있는 카드 개수를 리턴
int CardSet::GetNumOfCards() { return cardset_.size(); }
// 카드 셋의 특정 인덱스의 카드를 리턴
Card CardSet::GetCard(int index) { return cardset_[index]; }
// 카드를 카드셋에 추가
void CardSet::AddCard(Card card) {
    cardset_.push_back(card);  // 카드 추가
    std::sort(cardset_.begin(),
              cardset_.end());  // 추가 후 < operator에 따라 정렬
  return;
}


std::vector<Card>& CardSet::getCardset() { return this->cardset_; }
// 카드 셋에서 특정 인덱스의 카드를 뽑음(카드 셋에서 제거됨)
Card CardSet::PopIdxCard(int index) {
  Card popped;
  if (!(index < 0 || index >= this->GetNumOfCards())) {
    popped = cardset_[index];             // 뽑은 카드
    cardset_.erase(cardset_.begin() + index);  // 카드셋에서 제거
    // --추가-- 인덱스의 범위가 1부터면 index-1을 하는 것이 맞는데
    // 제 생각에는 그대로 0부터로 시작하는 것을 생각하신 것 같아서
    // 이럴 경우에는 begin이 시작 주소를 반환하므로 index를 더하시는
    // 것이 맞습니다. 혹시 1부터 시작하는 걸로 생각하셨다면
    // 다시 index-1로 바꿔주세요.
  }
  return popped;
}
//어떤 한장 pop
Card CardSet::PopCard() {
  Card popped = cardset_.back();
  cardset_.pop_back();  // 더미에서 제거
  return popped;
}
    // 특정 월의 카드가 몇 개 있는지 리턴
int CardSet::FindNumOfSameMonthCards(int month) {
  int i = 0;
  for (Card c : cardset_) {
    if (c.GetMonthOfCard() == month) i++;
  }
  return i;
}
// 특정 state의 카드가 몇 개 있는지 리턴
// 여기서 state가 제가 이전에 업로드한 card.txt에서 카드 이름의 'A,B,C,D'인지
// 아니면 광, 피, 열, 단과 같이 카드 종류를 나타내는 것인지 모르겠습니다.
// 후자라면 코드는 아래와 같고.. 아니라면 수정해야 합니다.
// --추가-- state 후자로 수정했습니다. 그냥 두시면 될 것 같습니다.
int CardSet::FindNumOfSameStateCards(State state) {
  int i = 0;
  for (Card c : cardset_) {
    if (c.GetStateOfCard() == state) i++;
  }
  return i;
}


//카드셋의 정보를 출력합니다
//카드셋이 여러개 있는만큼 여러버전을 만드는 것도 어떨까싶습니다.
void CardSet::printCardSet() {
  int size = this->cardset_.size();
  for (int i = 0; i < size; i++) {
    std::cout << i << " " << this->cardset_.at(i).toString() << std::endl;
  }

}