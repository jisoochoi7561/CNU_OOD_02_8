#pragma once
#include <iostream>
#include "Card.h"
#include "CardSet.h"
#include "Dummy.h"
#include "Player.h"
#include "BadakHand.h"
#include "EndGameUtil.h"
#include <vector>

class Board {
 public:
  Board();
  void addNewPlayer();
  void giveTurnToPlayer(Player& player);
  void giveCardToPlayer(Player& player);
  void TurnHands();
  void giveCardToBadak();
  void decideOrder();
  int makePair(Card& card, CardSet& cardset);
  Player& getIndxPlayer(int i);
  void play();
  Card gookJinCase(Card card);
  void endGame(std::vector<Player>& players, Player& player);  //추가 함수
  void checkPresident(Player& player);
  void setLastTurn(bool lastTurn);
  bool getLastTurn();
  void setExistPresident(bool flag);
  bool getExistPresident();


 private:
  std::vector<Player> players;
  Dummy dummy;
  CardSet badak;
  EndGameUtil* util;
  bool isLastTurn;
  bool existPresident;

};
