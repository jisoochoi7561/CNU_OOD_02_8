#include "EndGameUtil.h"
#include <iostream>
#include <vector>
#include <cmath>

// 객체를 반환하는 함수
EndGameUtil* EndGameUtil::GetInstance() {
  if (instance_ == NULL) {
    instance_ = new EndGameUtil;
  }
  return instance_;
}

// 고를 적용해 점수 계산
void EndGameUtil::calcScoreByGo(Player& player) {
  switch (player.getGo()) {
    case 0:  // 고가 없으면 그냥 원점수
      break;
    case 1:  // 1고인 경우
      player.setScore(player.getScore() + 1);
      break;
    case 2:  // 2고인 경우
      player.setScore(player.getScore() + 3);
      break;
    default:  // 3고 이상인 경우
      player.setScore((player.getScore()+3) * pow(2, player.getGo() - 2));
      break;
  }
}

void EndGameUtil::calcByMungBak(Player& player) {  //멍박으로 점수 계산하는 함수
  if (player.getBadakHand().FindNumOfSameStateCards(kkeut) >= 7) {  //이긴 사람이 끗이 7장 이상인 경우
    std::cout << player.getName() << "님은 멍박입니다." << std::endl;
    std::cout << player.getName() << "님의 점수가 2배가 됩니다." << std::endl;
    player.setScore(player.getScore() * 2);  //점수 두배
  }
}

void EndGameUtil::checkGoBak(std::vector<Player>& players, Player& player) {  //고박인 경우를 따지는 함수
  std::vector<Player> sayGoPlayers;
  // 지금까지 고를 외친 사람들을 가져옴
  for (int i = 0; i < 3; i++) {
    if (players.at(i).getSayGo()) {
      sayGoPlayers.push_back(players.at(i));
    }
  }
  // 자신이 고를 외쳤는데 이긴 사람이 자신이 아닌 경우 고박이므로
  for (int i = 0; i < sayGoPlayers.size(); i++) {
    if (sayGoPlayers.at(i).getName() != player.getName()) {  //이름이 다른 경우 고박이다.
      std::cout << "고박입니다. " << sayGoPlayers.at(i).getName()
                << " 님이 다른 사람의 금액까지 지불해야 합니다." << std::endl;
    }
  }
}
// 광박은 진 사람에 따라 달라지므로 자신의 입장에서 승자의 점수(scoreToPay)를
// 변경
void EndGameUtil::calcByGwangBak(std::vector<Player>& players, Player& player) {
  if (player.getScoredByGwang()) {  // 광에 의해 점수가 난 경우
    for (int i = 0; i < 3; i++) {
      if (players.at(i).getName() == player.getName()) {  // 이긴 사람인 경우
        continue;
      } else {  // 진 사람인 경우
        int numOfGwang = players.at(i).getBadakHand().FindNumOfSameStateCards(
            gwang);  // 광 갯수
        int numOfBiGwang = players.at(i).getBadakHand().FindNumOfSameStateCards(
            bigwang);                             // 비광 갯수
        if (numOfGwang + numOfBiGwang == 0) {  // 광이 하나도 없어 광박인 경우
          std::cout << player.getName() << "님은 광박입니다." << std::endl;
          std::cout << player.getName() << "님은 승자에게 지불할 금액에 해당하는 점수가 2배가 됩니다." << std::endl;
          players.at(i).setScoreToPay(players.at(i).getScoreToPay()*2);  // 점수를 2배
          // 광박인 경우 금액으로 2배를 내야하므로 자신의 입장에서 승자의 점수를 2배로
        }
      }
    }
  }
}
// 피박은 진 사람의 바닥패에 따라 점수 계산이 달라지므로 자신의 입장에서 승자의
// 점수(scoreToPay)를 변경
void EndGameUtil::calcByPiBak(std::vector<Player>& players, Player& player) {
  if (player.getScoredByPi()) {  // 피에 의해 점수가 난 경우
    for (int i = 0; i < 3; i++) {
      if (players.at(i).getName() == player.getName()) {  // 이긴 사람인 경우
        continue;
      } else {  // 진 사람인 경우
        int numOfPi = players.at(i).getBadakHand().FindNumOfSameStateCards(pi);  // 피 갯수
        int numOfSsangPi = players.at(i).getBadakHand().FindNumOfSameStateCards(ssangpi);   // 쌍피 갯수
        if ((numOfPi + numOfSsangPi) <= 5 && (numOfPi + numOfSsangPi)>=1) {  // 피가 5장 이하인 경우는 피박
          // 단 피가 한장도 없으면 피박이 아님
          std::cout << player.getName() << "님은 피박입니다." << std::endl;
          std::cout<< player.getName()<< "님은 승자에게 지불할 금액에 해당하는 점수가 2배가 됩니다."
              << std::endl;
          players.at(i).setScoreToPay(players.at(i).getScoreToPay()*2);  // 점수를 2배
          // 피박인 경우 금액으로 2배를 내야하므로 자신의 입장에서 승자의 점수를 2배로
        }
      }
    }
  }
}

EndGameUtil* EndGameUtil::instance_ = NULL;