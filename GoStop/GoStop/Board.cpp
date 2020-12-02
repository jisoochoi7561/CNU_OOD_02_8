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
    std::cout << "���ο� ������ ���� �Ϸ�" << std::endl;
    dummy.reset();
    std::cout << "���ο� ���� ���� �Ϸ�" << std::endl;
    dummy.Shuffle();
    std::cout << "���̸� �������ϴ�." << std::endl;
  }
  
  void Board::addNewPlayer() {
    std::cout << "Player�� �߰��մϴ�." << std::endl;
    std::cout << "Player�� �̸��� �Է��ϼ��� : " << std::endl;
    std::string name;
    std::cin >> name;
    Player player = Player(name);
    players.push_back(player);
    std::cout << name << " player �߰� �Ϸ�" << std::endl;
  }
  
  void Board::giveTurnToPlayer(Player& player) {

    while (true) {
      std::cout << player.getName()
                << " �÷��̾�� �ൿ�� �����Ͽ� �ֽʽÿ�:\n1. �ڽ��� �� ���� "
                   "\n 2.�ٴڿ� ����մ� �� ����"
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
          std::cout << "�ٽ� ����� �������ּ���" << std::endl;
          break;
      }
    }
  
  }
 
  void Board::giveCardToPlayer(Player& player) {
    player.getHand().AddCard(dummy.PopCard());
    std::cout << player.getName()<< " player���� ī�� ���� ���� �Ͽ����ϴ�."
              << std::endl;
  }
  void Board::giveCardToBadak() {
    Card c = dummy.PopCard();
    badak.AddCard(c);
    std::cout  << "�ٴڿ� ī�� ������ ��ҽ��ϴ�."
              << std::endl;
  }
 
  void Board::decideOrder() { 
    std::set<int> s;
    int a;
    for (int i = 0; i < 3; i++) {
      while (true) {
        std::cout << players.at(i).getName()
                  << " �÷��̾�� �ٴ�ī��[0-5]�� ���� ����ֽʽÿ�."
                  << std::endl;
        std::cin >> a;
        if (a > 5 || a < 0) {
          std::cout << "0-5 �� �ƴմϴ�.����� ����ּ���."
                    << std::endl;
          continue;
        } 
        else if (s.find(a)!=s.end()) {
          std::cout << "�ٸ� �÷��̾ ���� ���̽��ϴ�.. ����� ����ּ���." << std::endl;
          continue;
        }
        else {
          s.insert(a);
          std::cout << "����� �� ī��� :" << std::endl;
          std::cout << badak.GetCard(a).toString() << std::endl;
          players.at(i).setChoice(badak.GetCard(a));
          break;
        }
      }
      
    }
    std::sort(players.begin(), players.end());
    std::cout << "������ ������ �����ϴ� : " << std::endl;
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
    std::cout << "�÷��̾�鿡�� 7�徿 ī��й� �Ϸ�.\n�ٴڿ� 6���� ī�� ���ÿϷ�" << std::endl;
  }




