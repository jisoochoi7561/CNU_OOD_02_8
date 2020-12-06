#include <iostream>

#include "Card.h"
#include "CardSet.h"
#include "Dummy.h"
#include "Player.h"
#include "BadakHand.h"
#include "Board.h"
#include "EndGameUtil.h"

int main() {
  //������ ����
  Board board = Board();
  //���� �� : �� 48��(���ʽ� �� ����)
  //���� ī�� �� 48�� ��� �����Ϸ�.

  //player 3���� �̸��� �Է¹޾Ƽ� ����.
  board.addNewPlayer();
  board.addNewPlayer();
  board.addNewPlayer();


  //ù�и� ������.
  board.TurnHands();


  //���� ���Ѵ�
  board.decideOrder();
  //�����÷���.
  board.play();

  return 0;
}