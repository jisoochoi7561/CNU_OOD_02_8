#include "BadakHand.h"
#include "Player.h"

//자신의 바닥에 가져온 패들입니다.
BadakHand::BadakHand() : CardSet() { score = 0; }

// 점수 계산에 관련된 함수들을 여기에 작성하면 될 것 같네요

// 규칙 보면 아시겠지만 패의 점수들로 한 계산이고
// 추후에 플레이어 간 스탑을 했을 시 점수 계산은
// 추후에 구현하면 될 것 같습니다.
// 일단 패를 한 번만 훑었을 때를 기준으로 만들었습니다.
// 후에 패를 또 훑었을 때 계산되도록 수정하면 될 것 같습니다.
// 영어는 위키피디아 영어판 참조했습니다.

// 광 관련

//바닥패의 점수를 계산합니다.
void BadakHand::calc(Player& player) {
  int gwangScore = calcScoreFromGwang();
  int piScore = calcScoreFromPi();
  int score=0;

  if (gwangScore != 0) {  //광으로 점수가 난 경우
    score += gwangScore;
    player.setScoredByGwang(true);  //광으로 점수를 났다고 표기
  }
  if (piScore != 0) {  //피로 점수가 난 경우
    score += piScore;
    player.setScoredByPi(true);  //피로 점수가 났다고 표기
  }
  this->score=
  calcScoreFromKkeut()+
  calcScoreFromTti()+score;
}

//바닥패의 점수를 리턴합니다.
int BadakHand::getScore() { return this->score; }

//광관련 점수계산
int BadakHand::calcScoreFromGwang() {
  int score = 0;

  int numOfGwang =
      this->FindNumOfSameStateCards(gwang);  // 광 갯수
  int numOfBiGwang = this->FindNumOfSameStateCards(bigwang);  // 비광 갯수

  if (numOfBiGwang == 0) {  // 비광이 없는 경우
    if (numOfGwang == 3) {  // 광이 3개
      score += 3;
    } else if (numOfGwang == 4) {  // 광이 4개
      score += 4;
    }
  } else {                  // 있는 경우
    if (numOfGwang == 2) {  // 비광을 포함한 광이 3개
      score += 2;
    } else if (numOfGwang == 3) {  // 비광을 포함한 광이 4개
      score+=4;

    } else if (numOfGwang == 4) {  // 광 모두 모은 경우
      score += 15;
    }
  }

  return score;
}
// 열끗 관련
int BadakHand::calcScoreFromKkeut() {
  int score = 0;
  int numOfKkeut = this->FindNumOfSameStateCards(kkeut);
  BadakHand playerSet = *this;

  if (numOfKkeut >= 5) {  // 열끗이 5개 이상인 경우
   score+=(numOfKkeut - 4);
  }
  if (isGodori(playerSet)) {
    score+=(5);  // 고도리 점수 추가
  }
  return score;
}
// 띠 관련
int BadakHand::calcScoreFromTti() {
  int score = 0;
  int numOfHongdan = this->FindNumOfSameStateCards(hongdan);
  int numOfCheongdan =
      this->FindNumOfSameStateCards(cheongdan);
  int numOfChodan = this->FindNumOfSameStateCards(chodan);
  BadakHand cardSet = *this;

  int totalNumOfTti =
      numOfHongdan + numOfCheongdan + numOfChodan;  // 모든 띠 갯수

  if (numOfHongdan == 3) {  // 홍단인 경우
    score+=(3);
  }
  if (numOfCheongdan == 3) {  // 청단인 경우
    score+=(3);
  }
  if (isChodan(cardSet)) {  // 초단인 경우
    score+=(3);
  }
  if (totalNumOfTti >= 5) {
    score += (totalNumOfTti - 4);
    // 그 외 일반적인 띠 점수 계산
  }
    
  return score;
}
// 피 관련
int BadakHand::calcScoreFromPi() {
  int score = 0;
  int numOfPi =this->FindNumOfSameStateCards(pi);
  int numOfSsangPi =this->FindNumOfSameStateCards(ssangpi);
  int totalNumOfPi = numOfPi + 2 * numOfSsangPi;
  if (totalNumOfPi>=10) {
    score += (totalNumOfPi - 9);
  }
 
  // 9월 열끗 카드는 나중에 패에서 낼 때
  // 무엇으로 내냐에 따라서 상태를 변경하면
  // 될 것 같습니다.
 return score;
}
// 고도리 확인
bool BadakHand::isGodori(BadakHand& cardSet) {
  std::vector<Card> checkCard;  //고도리 확인용 벡터

  int numOfCards = cardSet.GetNumOfCards();
  for (int i = 0; i < numOfCards; i++) {
    Card card = cardSet.GetCard(i);
    int month = card.GetMonthOfCard();
    if (month == 2 || month == 4 || month == 8) {
      if (card.GetStateOfCard() == kkeut) {  // 고도리에 해당하는 카드인 경우
        checkCard.push_back(card);  // 벡터에 추가
      }
    }
  }

  return (checkCard.size() == 3);
}
// 초단 확인
bool BadakHand::isChodan(BadakHand& cardSet) {
  std::vector<Card> checkCard;  //초단 확인용 벡터

  int numOfCards = cardSet.GetNumOfCards();
  for (int i = 0; i < numOfCards; i++) {
    Card card = cardSet.GetCard(i);
    int month = card.GetMonthOfCard();
    if (month == 4 || month == 5 || month == 7) {
      if (card.GetStateOfCard() == chodan) {  // 초단에 해당하는 카드인 경우
        checkCard.push_back(card);  // 벡터에 추가
      }
    }
  }

  return (checkCard.size() == 3);
}