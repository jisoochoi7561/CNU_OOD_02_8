#pragma once
#include <iostream>
#include "Card.h"
#include "CardSet.h"
#include "Dummy.h"
#include "Player.h"
#include "BadakHand.h"
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
  Player& getIndxPlayer(int i);

 private:
  std::vector<Player> players;
  Dummy dummy;
  CardSet badak;



};
