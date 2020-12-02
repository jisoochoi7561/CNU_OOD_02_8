#include "Board.h"
#include <iostream>
#include "Card.h"
#include "CardSet.h"
#include "Dummy.h"
#include "Player.h"
#include "BadakHand.h"
#include <vector>
#include <set>
#include <algorithm>


  Board::Board() : players(), dummy(), badak() {
    std::cout << "새로운 게임판 세팅 완료" << std::endl;
    dummy.reset();
    std::cout << "새로운 더미 세팅 완료" << std::endl;
    dummy.Shuffle();
    std::cout << "더미를 섞었습니다." << std::endl;
  }
  
  void Board::addNewPlayer() {
    std::cout << "Player를 추가합니다." << std::endl;
    std::cout << "Player의 이름을 입력하세요 : " << std::endl;
    std::string name;
    std::cin >> name;
    Player player = Player(name);
    players.push_back(player);
    std::cout << name << " player 추가 완료" << std::endl;
  }
  
  void Board::giveTurnToPlayer(Player& player) {

    while (true) {
      std::cout << player.getName()
                << " 플레이어는 행동을 선택하여 주십시오:\n1. 자신의 패 보기 "
                   "\n 2.바닥에 깔려잇는 패 보기"
                << std::endl;
      int choice;
      std::cin >> choice;
      switch (choice) {
        case 1:
          player.getHand().printCardSet();  
          break;
        case 2:
          badak.printCardSet();
          break;
        default:
          std::cout << "다시 제대로 선택해주세요" << std::endl;
          break;
      }
    }
  
  }
 
  void Board::giveCardToPlayer(Player& player) {
    player.getHand().AddCard(dummy.PopCard());
    std::cout << player.getName()<< " player에게 카드 한장 지급 하였습니다."
              << std::endl;
  }
  void Board::giveCardToBadak() {
    Card c = dummy.PopCard();
    badak.AddCard(c);
    std::cout  << "바닥에 카드 한장을 깔았습니다."
              << std::endl;
  }
 
  void Board::decideOrder() { 
    std::set<int> s;
    int a;
    for (int i = 0; i < 3; i++) {
      while (true) {
        std::cout << players.at(i).getName()
                  << " 플레이어는 바닥카드[0-5]를 한장 골라주십시오."
                  << std::endl;
        std::cin >> a;
        if (a > 5 || a < 0) {
          std::cout << "0-5 가 아닙니다.제대로 골라주세요."
                    << std::endl;
          continue;
        } 
        else if (s.find(a)!=s.end()) {
          std::cout << "다른 플레이어가 고른걸 고르셨습니다.. 제대로 골라주세요." << std::endl;
          continue;
        }
        else {
          s.insert(a);
          std::cout << "당신이 고른 카드는 :" << std::endl;
          std::cout << badak.GetCard(a).toString() << std::endl;
          players.at(i).setChoice(badak.GetCard(a));
          break;
        }
      }
      
    }
    std::sort(players.begin(), players.end());
    std::cout << "순서는 다음과 같습니다 : " << std::endl;
    for (Player& player : players) {
      std::cout << player.getName() << " ";
    }
    std::cout << std::endl;
  
   

  }
  
  Player& Board::getIndxPlayer(int i) { 

    return this->players.at(i);
  }



  void Board::TurnHands() {
    for (int i = 0; i < 7; i++) {
      for (Player& player : players) {
        giveCardToPlayer(player);
      }
    }
    for (int i = 0; i < 6; i++) {
      giveCardToBadak();
    }
    std::cout << "플레이어들에게 7장씩 카드분배 완료.\n바닥에 6장의 카드 세팅완료" << std::endl;
  }




