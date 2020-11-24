#pragma once
#ifndef PlayerWinCardSet_h
#define PlayerWinCardSet_h

class Player;
#include "CardSet.h"

// �÷��̾ �̹� ���� Card���� �����˴ϴ�.
class PlayerWinCardSet : public CardSet {
 public:
  PlayerWinCardSet();

  // ���� ��꿡 ���õ� �Լ����� ���⿡ �ۼ��ϸ� �� �� ���׿�

  // ��Ģ ���� �ƽð����� ���� ������� �� ����̰�
  // ���Ŀ� �÷��̾� �� ��ž�� ���� �� ���� �����
  // ���Ŀ� �����ϸ� �� �� �����ϴ�.
  // �ϴ� �и� �� ���� �Ⱦ��� ���� �������� ��������ϴ�.
  // �Ŀ� �и� �� �Ⱦ��� �� ���ǵ��� �����ϸ� �� �� �����ϴ�.
  // ����� ��Ű�ǵ�� ������ �����߽��ϴ�.

  // �� ����
  void calcScoreFromGwang(Player& player);
  // ���� ����
  void calcScoreFromKkeut(Player& player);
  // �� ����
  void calcScoreFromTti(Player& player);
  // �� ����
  void calcScoreFromPi(Player& player);
  // ���� Ȯ��
  bool isGodori(PlayerWinCardSet& cardSet);
  // �ʴ� Ȯ��
  bool isChodan(PlayerWinCardSet& cardSet);

 private:
  int num_of_go;
};

#endif