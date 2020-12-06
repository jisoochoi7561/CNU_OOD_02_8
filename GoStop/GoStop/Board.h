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
  void calcScoreByGo(Player& player);  // 추가 함수
  void endGame(std::vector<Player>& players, Player& player);  //추가 함수

 private:
  std::vector<Player> players;
  Dummy dummy;
  CardSet badak;
  EndGameUtil* util;

};
