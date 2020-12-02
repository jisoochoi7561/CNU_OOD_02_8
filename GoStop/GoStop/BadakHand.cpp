#include "BadakHand.h"

#include "Player.h"

BadakHand::BadakHand() : CardSet() { num_of_go = 0; }

// 점수 계산에 관련된 함수들을 여기에 작성하면 될 것 같네요

// 규칙 보면 아시겠지만 패의 점수들로 한 계산이고
// 추후에 플레이어 간 스탑을 했을 시 점수 계산은
// 추후에 구현하면 될 것 같습니다.
// 일단 패를 한 번만 훑었을 때를 기준으로 만들었습니다.
// 후에 패를 또 훑었을 때 계산되도록 수정하면 될 것 같습니다.
// 영어는 위키피디아 영어판 참조했습니다.

// 광 관련
void BadakHand::calcScoreFromGwang(Player& player) {
  int numOfGwang =
      player.getBadakHand().FindNumOfSameStateCards(광);  // 광 갯수
  int numOfBiGwang =
      player.getBadakHand().FindNumOfSameStateCards(비광);  // 비광 갯수

  if (numOfBiGwang == 0) {  // 비광이 없는 경우
    if (numOfGwang == 3) {  // 광이 3개
      player.addScore(3);
    } else if (numOfGwang == 4) {  // 광이 4개
      player.addScore(4);
    }
  } else {                  // 있는 경우
    if (numOfGwang == 2) {  // 비광을 포함한 광이 3개
      player.addScore(2);
    } else if (numOfGwang == 3) {  // 비광을 포함한 광이 4개
      player.addScore(4);
    } else if (numOfGwang == 4) {  // 광 모두 모은 경우
      player.addScore(15);
    }
  }
}
// 열끗 관련
void BadakHand::calcScoreFromKkeut(Player& player) {
  int numOfKkeut = player.getBadakHand().FindNumOfSameStateCards(열끗);
  BadakHand playerSet = player.getBadakHand();

  if (numOfKkeut >= 5) {  // 열끗이 5개 이상인 경우
    player.addScore(numOfKkeut - 4);
  }
  if (isGodori(playerSet)) {
    player.addScore(5);  // 고도리 점수 추가
  }
}
// 띠 관련
void BadakHand::calcScoreFromTti(Player& player) {
  int numOfHongdan = player.getBadakHand().FindNumOfSameStateCards(홍단);
  int numOfCheongdan =
      player.getBadakHand().FindNumOfSameStateCards(청단);
  int numOfChodan = player.getBadakHand().FindNumOfSameStateCards(초단);
  BadakHand cardSet = player.getBadakHand();

  int totalNumOfTti =
      numOfHongdan + numOfCheongdan + numOfChodan;  // 모든 띠 갯수

  if (numOfHongdan == 3) {  // 홍단인 경우
    player.addScore(3);
  }
  if (numOfCheongdan == 3) {  // 청단인 경우
    player.addScore(3);
  }
  if (isChodan(cardSet)) {  // 초단인 경우
    player.addScore(3);
  }

  player.addScore(totalNumOfTti - 4);  // 그 외 일반적인 띠 점수 계산
}
// 피 관련
void BadakHand::calcScoreFromPi(Player& player) {
  int numOfPi = player.getBadakHand().FindNumOfSameStateCards(피);
  int numOfSsangPi = player.getBadakHand().FindNumOfSameStateCards(쌍피);
  int totalNumOfPi = numOfPi + 2 * numOfSsangPi;

  player.addScore(totalNumOfPi - 9);
  // 9월 열끗 카드는 나중에 패에서 낼 때
  // 무엇으로 내냐에 따라서 상태를 변경하면
  // 될 것 같습니다.
}
// 고도리 확인
bool BadakHand::isGodori(BadakHand& cardSet) {
  std::vector<Card> checkCard;  //고도리 확인용 벡터

  int numOfCards = cardSet.GetNumOfCards();
  for (int i = 0; i < numOfCards; i++) {
    Card card = cardSet.GetCard(i);
    int month = card.GetMonthOfCard();
    State state = card.GetStateOfCard();
    if (month == 2 || month == 4 || month == 8) {
      if (state == 열끗) {  // 고도리에 해당하는 카드인 경우
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
    State state = card.GetStateOfCard();
    if (month == 4 || month == 5 || month == 7) {
      if (state == 초단) {          // 초단에 해당하는 카드인 경우
        checkCard.push_back(card);  // 벡터에 추가
      }
    }
  }

  return (checkCard.size() == 3);
}