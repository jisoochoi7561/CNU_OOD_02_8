#include <iostream>

#include "Card.h"
#include "CardSet.h"
#include "Dummy.h"
#include "Player.h"
#include "BadakHand.h"
#include "Board.h"
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


  
  board.decideOrder();

  Player& a = board.getIndxPlayer(0);
  board.giveTurnToPlayer(a);

  return 0;
}