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


//게임판 객체가 필요하다고 생각해서 만들었습니다. 게임판이 주도적으로 게임을 이끌어갑니다.
//게임판은 더미,플레이어,바닥,현재게임의상태(몇고)인지 를 제어합니다.
  Board::Board() : players(), dummy(), badak(),go(0) {
    std::cout << ">> 새로운 게임판 세팅 완료" << std::endl;
    dummy.reset();
    std::cout << ">> 새로운 더미 세팅 완료" << std::endl;
    dummy.Shuffle();
    std::cout << ">> 더미를 섞었습니다." << std::endl;
  }
  //플레이 방식 : 어느 한 플레이어가 게임을 끝낼 때까지 플레이어들의 턴을 반복한다
  void Board::play() {
    while (true) {
      // 모든 플레이어의 패가 소진된 경우를 체크하고 만약 그렇다면 최종점수 계산하여 종료
      int sum = 0;
      for (Player& player : players) {
        sum += player.getHand().GetNumOfCards();
      }
      if (sum == 0) {
        std::cout << "<< 모든 플레이어의 손패가 소진되었습니다. ";
        // TODO:최종점수를 계산하고 승리자를 선정하는 메서드(미구현 상태)
        // ex. CalcFinalScoresAndSelectWinner(); <- 이 함수에서 게임을 반드시 종료시켜줘야 합니다. 
        exit(0);  // 현재는 그냥 프로세스 종료하도록 처리했습니다.
      }

      for (Player& player : players) {
        if (player.getHand().GetNumOfCards() != 0) {
          giveTurnToPlayer(player);
        } else {
          std::cout << "<< " << player.getName()
                    << " 플레이어의 손패가 소진되어 다음 플레이어에게 차례가 넘어갑니다.\n";
        }
      }
    }
    

  }
  //게임판에 새로운 플레이어 추가
  void Board::addNewPlayer() {
    std::cout << ">> Player를 추가합니다." << std::endl;
    std::cout << ">> Player의 이름을 입력하세요 : " << std::endl;
    std::string name;
    std::cin >> name;
    Player player = Player(name);
    players.push_back(player);
    std::cout << ">> " << name << " player 추가 완료" << std::endl;
  }
  
  //플레이어에게 턴을 넘겨줍니다.
  void Board::giveTurnToPlayer(Player& player) {
    std::cout << "\n[ " << player.getName()
              << "의 차례입니다. ]"
              << std::endl;
    std::cout << "-----------------당신의 손패-----------------" << std::endl;
    player.getHand().printCardSet();  
    std::cout << "-----------------현재 바닥-----------------" << std::endl;
    badak.printCardSet();
    //카드를 낸다.
    std::cout << ">> 인덱스 번호로 카드를 내 주세요" << std::endl;
    int c;
    std::cin>>c;
    Card card = player.getHand().PopIdxCard(c);
    //짝을 맞춘다
    int index = makePair(card, badak);
    if (index==-1) {
      std::cout << ">> 낸 카드를 바닥에 깔아놓습니다" << std::endl;
      badak.AddCard(card);
    } else {
      std::cout << ">> 페어를 난 패에 추가합니다." << std::endl;
      player.getBadakHand().AddCard(card);
      player.getBadakHand().AddCard(badak.PopIdxCard(index));
    }
    // 더미의 패가 소진되었으면 현재 플레이어의 badakHand 패를 가지고 점수를 계산한 다음
    // 최종점수 계산 후 승리자를 선정하도록 처리합니다.
    if (dummy.isEmpty()) {
      player.getBadakHand().calc();
      std::cout << "-----------------현재 난 패 목록-----------------" << std::endl;
      player.getBadakHand().printCardSet();
      std::cout << ">> " << player.getBadakHand().getScore() << "점 획득하셨습니다."
                << std::endl;
      // 현재 플레이어가 얻은 점수 업데이트
      player.setScore(player.getBadakHand().getScore());

      // TODO:최종점수를 계산하고 승리자를 선정하는 메서드(미구현 상태)
      // ex. CalcFinalScoresAndSelectWinner(); <- 이 함수에서 게임을 반드시 종료시켜줘야 합니다.
    }
    else {
      //카드를 뽑는다
      std::cout << ">> 카드를 뽑겠습니다 " << std::endl;
      Card popped = dummy.PopCard();
      std::cout << ">> 뽑은 카드는 " << popped.toString() << std::endl;
      //짝을 맞춘다
      index = makePair(popped, badak);
      if (index == -1) {
        std::cout << ">> 뽑은 카드를 바닥에 깔아놓습니다." << std::endl;
        badak.AddCard(popped);
      } else {
        std::cout << ">> 페어를 난 패에 추가합니다." << std::endl;
        player.getBadakHand().AddCard(popped);
        player.getBadakHand().AddCard(badak.PopIdxCard(index));
      }
    }
    //점수를 계산한다.
    player.getBadakHand().calc();
    std::cout << "-----------------현재 난 패 목록-----------------" << std::endl;
    player.getBadakHand().printCardSet();
    std::cout << ">> " << player.getBadakHand().getScore() << "점 획득하셨습니다."
              << std::endl;
    if ((player.score()+3)<=player.getBadakHand().getScore()) {
      //win
      player.setScore(player.getBadakHand().getScore());
      //고또는 스탑 선택.
      std::cout << ">> " << player.getName() << " 님이 3점이상 획득!" << std::endl;
      std::cout << ">> 0을 눌러 스탑 또는 1을 눌러 고" << std::endl;
      int willGo;
       std::cin>>willGo;
      while (true) {
         if (willGo!=0&&willGo!=1) {
          std::cout << ">> 제대로 입력해주세요" << std::endl;
           std::cout << ">> 0을 눌러 스탑 또는 1을 눌러 고" << std::endl;
          std::cin >> willGo;
         } else {
           break;
         }
      }
      switch (willGo) {
        case 0:
          //여기 최종점수 계산 구현 안해놨습니다. 구현해주세요.
          std::cout << ">> " << player.getName() << " 님의 승리로 게임이 끝났습니다!" << std::endl;
          std::cout << ">> " << player.getName() << " 님은" << player.score() << " 점과 "
                    << go << " 고를 획득하셔서 총" << player.score() * (go+1) << " 점으로 승리하셨습니다."
                    << std::endl;
          exit(0);
      
          break;
        case 1:
          go++;
          std::cout << "<< " << player.getName() << " 님이 고하셨습니다! 현재 고는 " << go
                    << "go 입니다."
                    << std::endl;
          //
          break;
      }
    } else {
      //notwin
    }
    
  }
  
  //카드와 카드셋을 가지고 짝이 페어가 만들어지는지를 확인합니다.페어가 만들어진다면 카드셋의 인덱스를, 안만들어진다면 -1을 리턴합니다
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
      std::cout << ">> 페어를 만들 수 없습니다." << std::endl;
      return -1;
    } else {
      std::cout << ">> 선택하신 카드는 " << card.toString() << std::endl;
      std::cout << ">> 고르실 수 있는 카드는 " << std::endl;
      available.printCardSet();
      int c;
      while (true) {
        std::cout << ">> 인덱스 번호로 카드를 골라 주세요" << std::endl;
        std::cin >> c;
        if (c < 0 || c >= index.size()) {
          std::cout << ">> 존재하지 않는 인덱스입니다.재시도합니다." << std::endl;
        } else {
          break;
        }
      }
      return index.at(c);
    }
  }
 
  //플레이어에게 카드를 넘겨줍니다.
  void Board::giveCardToPlayer(Player& player) {
    player.getHand().AddCard(dummy.PopCard());
    std::cout << ">> " << player.getName()<< " player에게 카드 한장 지급 하였습니다."
              << std::endl;
  }

  //바닥에 카드를 깝니다.
  void Board::giveCardToBadak() {
    Card c = dummy.PopCard();
    badak.AddCard(c);
    std::cout  << ">> 바닥에 카드 한장을 깔았습니다."
              << std::endl;
  }
 
  //초반에 선을 정하는 함수입니다.
  //현실에서는 시계반대방향이지만,
  //이게임에서는 일단 높은걸 뽑은 순서대로 선이라고 정했습니다.
  void Board::decideOrder() { 
    std::set<int> s;
    int a;
    for (int i = 0; i < 3; i++) {
      while (true) {
        std::cout << ">> " << players.at(i).getName()
                  << " 플레이어는 바닥카드[0-5]를 한장 골라주십시오."
                  << std::endl;
        std::cin >> a;
        if (a > 5 || a < 0) {
          std::cout << ">> 0-5 가 아닙니다.제대로 골라주세요."
                    << std::endl;
          continue;
        } 
        else if (s.find(a)!=s.end()) {
          std::cout << ">> 다른 플레이어가 고른걸 고르셨습니다.. 제대로 골라주세요." << std::endl;
          continue;
        }
        else {
          s.insert(a);
          std::cout << ">> 당신이 고른 카드는 :" << std::endl;
          std::cout << badak.GetCard(a).toString() << std::endl;
          players.at(i).setChoice(badak.GetCard(a));
          break;
        }
      }
      
    }
    std::sort(players.begin(), players.end());
    std::cout << ">> 순서는 다음과 같습니다 : " << std::endl;
    for (Player& player : players) {
      std::cout << player.getName() << " ";
    }
    std::cout << std::endl;
  
   

  }
  
  //i번째 플레이어를 고릅니다(선 = 0)
  Player& Board::getIndxPlayer(int i) { 

    return this->players.at(i);
  }


  //초반에 플레이어들에게 패를 돌리고, 바닥에 6장을 깝니다.
  void Board::TurnHands() {
    for (int i = 0; i < 7; i++) {
      for (Player& player : players) {
        giveCardToPlayer(player);
      }
    }
    for (int i = 0; i < 6; i++) {
      giveCardToBadak();
    }
    std::cout << ">> 플레이어들에게 7장씩 카드분배 완료.\n>> 바닥에 6장의 카드 세팅완료" << std::endl;
  }




