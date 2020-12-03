#pragma once
#ifndef BadakHand_h
#define BadakHand_h

class Player;
#include "CardSet.h"

// �÷��̾ �̹� ���� Card���� �����˴ϴ�.
class BadakHand : public CardSet {
 public:
  BadakHand();
  // ���� ��꿡 ���õ� �Լ����� ���⿡ �ۼ��ϸ� �� �� ���׿�

  // ��Ģ ���� �ƽð����� ���� ������� �� ����̰�
  // ���Ŀ� �÷��̾� �� ��ž�� ���� �� ���� �����
  // ���Ŀ� �����ϸ� �� �� �����ϴ�.
  // �ϴ� �и� �� ���� �Ⱦ��� ���� �������� ��������ϴ�.
  // �Ŀ� �и� �� �Ⱦ��� �� ���ǵ��� �����ϸ� �� �� �����ϴ�.
  // ����� ��Ű�ǵ�� ������ �����߽��ϴ�.
  void calc();
  int getScore();
  // �� ����
  int calcScoreFromGwang();
  // ���� ����
  int calcScoreFromKkeut();
  // �� ����
  int calcScoreFromTti();
  // �� ����
  int calcScoreFromPi();
  // ���� Ȯ��
  bool isGodori(BadakHand& cardSet);
  // �ʴ� Ȯ��
  bool isChodan(BadakHand& cardSet);

 private:
  int score;
};

#endif