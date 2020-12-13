#include <iostream>
#include "Card.h"
#include "CardSet.h"
#include "Dummy.h"
#include "Player.h"
#include "BadakHand.h"
#include "Board.h"
#include "EndGameUtil.h"

int main() {
  //게임판 생성
  Board board = Board();
  //고스톱 패 : 총 48장(보너스 패 없음)
  //고스톱 카드 총 48장 모두 생성완료.

  //player 3명의 이름을 입력받아서 생성.
  board.addNewPlayer();
  board.addNewPlayer();
  board.addNewPlayer();

  //첫패를 돌린다.
  board.TurnHands();

  //선을 구한다
  board.decideOrder();
  //게임플레이.
  board.play();

  return 0;
}