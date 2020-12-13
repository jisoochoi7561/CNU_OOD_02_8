#include "EndGameUtil.h"
#include <iostream>
#include <vector>
#include <cmath>

// ��ü�� ��ȯ�ϴ� �Լ�
EndGameUtil* EndGameUtil::GetInstance() {
  if (instance_ == NULL) {
    instance_ = new EndGameUtil;
  }
  return instance_;
}

// �� ������ ���� ���
void EndGameUtil::calcScoreByGo(Player& player) {
  switch (player.getGo()) {
    case 0:  // �� ������ �׳� ������
      break;
    case 1:  // �� 1�� ���
      player.setScore(player.getScore() + 1);
      break;
    case 2:  // �� 2�� ���
      player.setScore(player.getScore() + 3);
      break;
    default:  // �� �� ���
      player.setScore((player.getScore()+3) * pow(2, player.getGo() - 2));
      break;
  }
}

void EndGameUtil::calcByMungBak(Player& player) {  //�۹����� ���� ����ϴ� �Լ�
  if (player.getBadakHand().FindNumOfSameStateCards(kkeut) >= 7) {  //�̱� ����� ���� 7�� �̻��� ���
    std::cout << player.getName() << "���� �۹��Դϴ�." << std::endl;
    std::cout << player.getName() << "���� ������ 2�谡 �˴ϴ�." << std::endl;
    player.setScore(player.getScore() * 2);  //���� �ι�
  }
}

void EndGameUtil::checkGoBak(std::vector<Player>& players, Player& player) {  //����� ��츦 ������ �Լ�
  std::vector<Player> sayGoPlayers;
  // ���ݱ��� �� ��ģ ������� ������
  for (int i = 0; i < 3; i++) {
    if (players.at(i).getSayGo()) {
      sayGoPlayers.push_back(players.at(i));
    }
  }
  // �ڽ��� �� ���ƴµ� �̱� ����� �ڽ��� �ƴ� ��� ����̹Ƿ�
  for (int i = 0; i < sayGoPlayers.size(); i++) {
    if (sayGoPlayers.at(i).getName() != player.getName()) {  //�̸��� �ٸ� ��� ����̴�.
      std::cout << "����Դϴ�. " << sayGoPlayers.at(i).getName()
                << " ���� �ٸ� ����� �ݾױ��� �����ؾ� �մϴ�." << std::endl;
    }
  }
}
// ������ �� ����� ���� �޶����Ƿ� �ڽ��� ���忡�� ������ ����(scoreToPay)��
// ����
void EndGameUtil::calcByGwangBak(std::vector<Player>& players, Player& player) {
  if (player.getScoredByGwang()) {  // ���� ���� ������ �� ���
    for (int i = 0; i < 3; i++) {
      if (players.at(i).getName() == player.getName()) {  // �̱� ����� ���
        continue;
      } else {  // �� ����� ���
        int numOfGwang = players.at(i).getBadakHand().FindNumOfSameStateCards(
            gwang);  // �� ����
        int numOfBiGwang = players.at(i).getBadakHand().FindNumOfSameStateCards(
            bigwang);                             // �� ����
        if (numOfGwang + numOfBiGwang == 0) {  // ���� �ϳ��� ���� ������ ���
          std::cout << player.getName() << "���� �����Դϴ�." << std::endl;
          std::cout << player.getName() << "���� ���ڿ��� ������ �ݾ׿� �ش��ϴ� ������ 2�谡 �˴ϴ�." << std::endl;
          players.at(i).setScoreToPay(players.at(i).getScoreToPay()*2);  // ������ 2��
          // ������ ��� �ݾ����� 2�踦 �����ϹǷ� �ڽ��� ���忡�� ������ ������ 2���
        }
      }
    }
  }
}
// �ǹ��� �� ����� �ٴ��п� ���� ���� ����� �޶����Ƿ� �ڽ��� ���忡�� ������
// ����(scoreToPay)�� ����
void EndGameUtil::calcByPiBak(std::vector<Player>& players, Player& player) {
  if (player.getScoredByPi()) {  // �ǿ� ���� ������ �� ���
    for (int i = 0; i < 3; i++) {
      if (players.at(i).getName() == player.getName()) {  // �̱� ����� ���
        continue;
      } else {  // �� ����� ���
        int numOfPi = players.at(i).getBadakHand().FindNumOfSameStateCards(pi);  // �� ����
        int numOfSsangPi = players.at(i).getBadakHand().FindNumOfSameStateCards(ssangpi);   // ���� ����
        if ((numOfPi + numOfSsangPi) <= 5 && (numOfPi + numOfSsangPi)>=1) {  // �ǰ� 5�� ������ ���� �ǹ�
          // �� �ǰ� ���嵵 ������ �ǹ��� �ƴ�
          std::cout << player.getName() << "���� �ǹ��Դϴ�." << std::endl;
          std::cout<< player.getName()<< "���� ���ڿ��� ������ �ݾ׿� �ش��ϴ� ������ 2�谡 �˴ϴ�."
              << std::endl;
          players.at(i).setScoreToPay(players.at(i).getScoreToPay()*2);  // ������ 2��
          // �ǹ��� ��� �ݾ����� 2�踦 �����ϹǷ� �ڽ��� ���忡�� ������ ������ 2���
        }
      }
    }
  }
}

EndGameUtil* EndGameUtil::instance_ = NULL;