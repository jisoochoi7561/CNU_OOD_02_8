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


//������ ��ü�� �ʿ��ϴٰ� �����ؼ� ��������ϴ�. �������� �ֵ������� ������ �̲���ϴ�.
//�������� ����,�÷��̾�,�ٴ�,��������ǻ���(���)���� �� �����մϴ�.
  Board::Board() : players(), dummy(), badak(),go(0) {
    std::cout << ">> ���ο� ������ ���� �Ϸ�" << std::endl;
    dummy.reset();
    std::cout << ">> ���ο� ���� ���� �Ϸ�" << std::endl;
    dummy.Shuffle();
    std::cout << ">> ���̸� �������ϴ�." << std::endl;
  }
  //�÷��� ��� : ��� �� �÷��̾ ������ ���� ������ �÷��̾���� ���� �ݺ��Ѵ�
  void Board::play() {
    while (true) {
      // ��� �÷��̾��� �а� ������ ��츦 üũ�ϰ� ���� �׷��ٸ� �������� ����Ͽ� ����
      int sum = 0;
      for (Player& player : players) {
        sum += player.getHand().GetNumOfCards();
      }
      if (sum == 0) {
        std::cout << "<< ��� �÷��̾��� ���а� �����Ǿ����ϴ�. ";
        // TODO:���������� ����ϰ� �¸��ڸ� �����ϴ� �޼���(�̱��� ����)
        // ex. CalcFinalScoresAndSelectWinner(); <- �� �Լ����� ������ �ݵ�� ���������� �մϴ�. 
        exit(0);  // ����� �׳� ���μ��� �����ϵ��� ó���߽��ϴ�.
      }

      for (Player& player : players) {
        if (player.getHand().GetNumOfCards() != 0) {
          giveTurnToPlayer(player);
        } else {
          std::cout << "<< " << player.getName()
                    << " �÷��̾��� ���а� �����Ǿ� ���� �÷��̾�� ���ʰ� �Ѿ�ϴ�.\n";
        }
      }
    }
    

  }
  //�����ǿ� ���ο� �÷��̾� �߰�
  void Board::addNewPlayer() {
    std::cout << ">> Player�� �߰��մϴ�." << std::endl;
    std::cout << ">> Player�� �̸��� �Է��ϼ��� : " << std::endl;
    std::string name;
    std::cin >> name;
    Player player = Player(name);
    players.push_back(player);
    std::cout << ">> " << name << " player �߰� �Ϸ�" << std::endl;
  }
  
  //�÷��̾�� ���� �Ѱ��ݴϴ�.
  void Board::giveTurnToPlayer(Player& player) {
    std::cout << "\n[ " << player.getName()
              << "�� �����Դϴ�. ]"
              << std::endl;
    std::cout << "-----------------����� ����-----------------" << std::endl;
    player.getHand().printCardSet();  
    std::cout << "-----------------���� �ٴ�-----------------" << std::endl;
    badak.printCardSet();
    //ī�带 ����.
    std::cout << ">> �ε��� ��ȣ�� ī�带 �� �ּ���" << std::endl;
    int c;
    std::cin>>c;
    Card card = player.getHand().PopIdxCard(c);
    //¦�� �����
    int index = makePair(card, badak);
    if (index==-1) {
      std::cout << ">> �� ī�带 �ٴڿ� ��Ƴ����ϴ�" << std::endl;
      badak.AddCard(card);
    } else {
      std::cout << ">> �� �� �п� �߰��մϴ�." << std::endl;
      player.getBadakHand().AddCard(card);
      player.getBadakHand().AddCard(badak.PopIdxCard(index));
    }
    // ������ �а� �����Ǿ����� ���� �÷��̾��� badakHand �и� ������ ������ ����� ����
    // �������� ��� �� �¸��ڸ� �����ϵ��� ó���մϴ�.
    if (dummy.isEmpty()) {
      player.getBadakHand().calc();
      std::cout << "-----------------���� �� �� ���-----------------" << std::endl;
      player.getBadakHand().printCardSet();
      std::cout << ">> " << player.getBadakHand().getScore() << "�� ȹ���ϼ̽��ϴ�."
                << std::endl;
      // ���� �÷��̾ ���� ���� ������Ʈ
      player.setScore(player.getBadakHand().getScore());

      // TODO:���������� ����ϰ� �¸��ڸ� �����ϴ� �޼���(�̱��� ����)
      // ex. CalcFinalScoresAndSelectWinner(); <- �� �Լ����� ������ �ݵ�� ���������� �մϴ�.
    }
    else {
      //ī�带 �̴´�
      std::cout << ">> ī�带 �̰ڽ��ϴ� " << std::endl;
      Card popped = dummy.PopCard();
      std::cout << ">> ���� ī��� " << popped.toString() << std::endl;
      //¦�� �����
      index = makePair(popped, badak);
      if (index == -1) {
        std::cout << ">> ���� ī�带 �ٴڿ� ��Ƴ����ϴ�." << std::endl;
        badak.AddCard(popped);
      } else {
        std::cout << ">> �� �� �п� �߰��մϴ�." << std::endl;
        player.getBadakHand().AddCard(popped);
        player.getBadakHand().AddCard(badak.PopIdxCard(index));
      }
    }
    //������ ����Ѵ�.
    player.getBadakHand().calc();
    std::cout << "-----------------���� �� �� ���-----------------" << std::endl;
    player.getBadakHand().printCardSet();
    std::cout << ">> " << player.getBadakHand().getScore() << "�� ȹ���ϼ̽��ϴ�."
              << std::endl;
    if ((player.score()+3)<=player.getBadakHand().getScore()) {
      //win
      player.setScore(player.getBadakHand().getScore());
      //��Ǵ� ��ž ����.
      std::cout << ">> " << player.getName() << " ���� 3���̻� ȹ��!" << std::endl;
      std::cout << ">> 0�� ���� ��ž �Ǵ� 1�� ���� ��" << std::endl;
      int willGo;
       std::cin>>willGo;
      while (true) {
         if (willGo!=0&&willGo!=1) {
          std::cout << ">> ����� �Է����ּ���" << std::endl;
           std::cout << ">> 0�� ���� ��ž �Ǵ� 1�� ���� ��" << std::endl;
          std::cin >> willGo;
         } else {
           break;
         }
      }
      switch (willGo) {
        case 0:
          //���� �������� ��� ���� ���س����ϴ�. �������ּ���.
          std::cout << ">> " << player.getName() << " ���� �¸��� ������ �������ϴ�!" << std::endl;
          std::cout << ">> " << player.getName() << " ����" << player.score() << " ���� "
                    << go << " �� ȹ���ϼż� ��" << player.score() * (go+1) << " ������ �¸��ϼ̽��ϴ�."
                    << std::endl;
          exit(0);
      
          break;
        case 1:
          go++;
          std::cout << "<< " << player.getName() << " ���� ���ϼ̽��ϴ�! ���� ��� " << go
                    << "go �Դϴ�."
                    << std::endl;
          //
          break;
      }
    } else {
      //notwin
    }
    
  }
  
  //ī��� ī����� ������ ¦�� �� ������������� Ȯ���մϴ�.�� ��������ٸ� ī����� �ε�����, �ȸ�������ٸ� -1�� �����մϴ�
  int Board::makePair(Card& card,CardSet& cardset) { 
    CardSet available = CardSet();
    std::vector<int> index;
    for (int i = 0; i < cardset.GetNumOfCards();i++) {
      if (card == cardset.GetCard(i)) {
        available.AddCard(cardset.GetCard(i));
        index.push_back(i);
      }
    }
    if (available.GetNumOfCards()==0) {
      std::cout << ">> �� ���� �� �����ϴ�." << std::endl;
      return -1;
    } else {
      std::cout << ">> �����Ͻ� ī��� " << card.toString() << std::endl;
      std::cout << ">> ���� �� �ִ� ī��� " << std::endl;
      available.printCardSet();
      int c;
      while (true) {
        std::cout << ">> �ε��� ��ȣ�� ī�带 ��� �ּ���" << std::endl;
        std::cin >> c;
        if (c < 0 || c >= index.size()) {
          std::cout << ">> �������� �ʴ� �ε����Դϴ�.��õ��մϴ�." << std::endl;
        } else {
          break;
        }
      }
      return index.at(c);
    }
  }
 
  //�÷��̾�� ī�带 �Ѱ��ݴϴ�.
  void Board::giveCardToPlayer(Player& player) {
    player.getHand().AddCard(dummy.PopCard());
    std::cout << ">> " << player.getName()<< " player���� ī�� ���� ���� �Ͽ����ϴ�."
              << std::endl;
  }

  //�ٴڿ� ī�带 ���ϴ�.
  void Board::giveCardToBadak() {
    Card c = dummy.PopCard();
    badak.AddCard(c);
    std::cout  << ">> �ٴڿ� ī�� ������ ��ҽ��ϴ�."
              << std::endl;
  }
 
  //�ʹݿ� ���� ���ϴ� �Լ��Դϴ�.
  //���ǿ����� �ð�ݴ����������,
  //�̰��ӿ����� �ϴ� ������ ���� ������� ���̶�� ���߽��ϴ�.
  void Board::decideOrder() { 
    std::set<int> s;
    int a;
    for (int i = 0; i < 3; i++) {
      while (true) {
        std::cout << ">> " << players.at(i).getName()
                  << " �÷��̾�� �ٴ�ī��[0-5]�� ���� ����ֽʽÿ�."
                  << std::endl;
        std::cin >> a;
        if (a > 5 || a < 0) {
          std::cout << ">> 0-5 �� �ƴմϴ�.����� ����ּ���."
                    << std::endl;
          continue;
        } 
        else if (s.find(a)!=s.end()) {
          std::cout << ">> �ٸ� �÷��̾ ���� ���̽��ϴ�.. ����� ����ּ���." << std::endl;
          continue;
        }
        else {
          s.insert(a);
          std::cout << ">> ����� �� ī��� :" << std::endl;
          std::cout << badak.GetCard(a).toString() << std::endl;
          players.at(i).setChoice(badak.GetCard(a));
          break;
        }
      }
      
    }
    std::sort(players.begin(), players.end());
    std::cout << ">> ������ ������ �����ϴ� : " << std::endl;
    for (Player& player : players) {
      std::cout << player.getName() << " ";
    }
    std::cout << std::endl;
  
   

  }
  
  //i��° �÷��̾ ���ϴ�(�� = 0)
  Player& Board::getIndxPlayer(int i) { 

    return this->players.at(i);
  }


  //�ʹݿ� �÷��̾�鿡�� �и� ������, �ٴڿ� 6���� ���ϴ�.
  void Board::TurnHands() {
    for (int i = 0; i < 7; i++) {
      for (Player& player : players) {
        giveCardToPlayer(player);
      }
    }
    for (int i = 0; i < 6; i++) {
      giveCardToBadak();
    }
    std::cout << ">> �÷��̾�鿡�� 7�徿 ī��й� �Ϸ�.\n>> �ٴڿ� 6���� ī�� ���ÿϷ�" << std::endl;
  }




