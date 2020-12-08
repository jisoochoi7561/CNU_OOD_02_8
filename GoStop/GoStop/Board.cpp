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
#include <cmath>
#include <cstring>

Card Board::gookJinCase(Card card){
  if (card.GetStateOfCard()==열끗&&card.GetMonthOfCard()==9) {
    std::cout
        << "국진을 추가합니다. 국진을 열끗으로 쓸지 쌍피로 쓸지 결정해주세요.\n"
        << "0을 누르면 열끗으로, 다른 수를 누르면 쌍피로 사용합니다."
        << std::endl;
    int c;
    std::cin >> c;
    if (c!=0) {
      card.setState(쌍피);
    }
  }
  return card;
}

//게임판 객체가 필요하다고 생각해서 만들었습니다. 게임판이 주도적으로 게임을 이끌어갑니다.
//게임판은 더미,플레이어,바닥,현재게임의상태(몇고)인지 를 제어합니다.
// --추가-- 고의 상태는 플레이어의 고에 상태에 따라 달라집니다. 그래서 필드에 고를 제거했습니다.
// 고박인 경우에는 종료되고 그 외의 경우에는 고를 외친 플레이어의 고에 따라
// 달라지므로 그냥 플레이어 고를 사용하도록 했습니다.
  Board::Board() : players(), dummy(), badak(), util(EndGameUtil::GetInstance()) {
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
      if (sum == 0) {  //나가리인 경우
        // 모든 플레이어가 손패가 소진된 경우에는 고를 외친 사람이
        // 점수를 내지 못하여 스탑을 하지 못하거나 모든 플레이어가
        // 스탑을 할 수 없는 즉, 게임을 끝낼 수 있는 점수를 획득하지 못한
        // 경우이므로 이 경우에는 나가리로 무효판이 됩니다. 이럴 경우
        // 다음판의 승자의 점수에 2배를 해주어야 합니다. 그러므로
        // 현재판은 단순히 종료시킵니다.
        std::cout << ">> 모든 플레이어의 손패가 소진되었습니다. 나가리입니다.";
        exit(0);
      }

      for (Player& player : players) {
        // 손패가 0이면 그 턴이 마지막 턴이라는 의미입니다. 왜냐하면 더미와 손패가 소진되는 순간이
        // 마지막 플레이어가 마지막 턴(모두 손패가 1장인 경우)에 남은 손패 하나를 내서 더미를 뒤집는 순간이기 때문입니다.
      //  if (player.getHand().GetNumOfCards() != 0) {
          giveTurnToPlayer(player);
      //  }
        /* 여기에 해당하는 경우가 없을 겁니다. 손에 들고있는 패를 내기만 하고 추가를 하지않아서
           최대 7턴만 진행하게 되기 때문입니다. 만약 모두 손패 다 소진해서 끝나면 위에서 종료시켜 줍니다.
        else {
          std::cout << "<< " << player.getName()
                    << " 플레이어의 손패가 소진되어 다음 플레이어에게 차례가 넘어갑니다.\n";
        }*/
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

  // 고를 적용해 점수 계산
  void Board::calcScoreByGo(Player& player) {
    switch (player.getGo()) {
      case 0:   // 고가 없으면 그냥 원점수
        break;
      case 1:  // 고가 1인 경우
        player.setScore(player.getScore() + 1);
        break;
      case 2:  // 고가 2인 경우
        player.setScore(player.getScore() + 2);
        break;
      default:  // 그 외 경우
        player.setScore(player.getScore() * pow(2, player.getGo() - 2));
        break;
    }
  }
  // 나가리가 아닌 게임을 종료하는 함수
  void Board::endGame(std::vector<Player>& players, Player& player) {
    std::vector<Player> defeatedPlayers;  // 패배한 플레이어 벡터
    for (int i = 0; i < players.size(); i++) {
      if (players.at(i).getName() != player.getName()) {
        defeatedPlayers.push_back(players.at(i));  // 패배한 플레이어를 추가
      }
    }

    util->calcByMungBak(player);  // 이긴 사람의 점수를 멍박에 따라 계산(멍박이면 2배)

    // 피박, 광박은 해당하는 사람만 2배로 물어줘야 하는 것이므로
    // 해당 플레이어의 입장에서 승자의 점수를 계산

    // 우선 진 사람의 입장에서 이긴 사람의 점수를 멍박까지 적용한 점수로 초기화
    for (int i = 0; i < defeatedPlayers.size(); i++) {
      defeatedPlayers.at(i).setScoreToPay(player.getScore());
    }

    util->calcByGwangBak(players, player);  // 광박에 해당하는 사람이 지불해야 하는 금액에 해당하는 점수(해당 플레이어 입장에서 승자의 점수)를 2배로
    util->calcByPiBak(players, player);  // 피박에 해당하는 사람이 지불해야 하는 점수(해당 플레이어 입장에서 승자의 점수)를 2배로

    util->checkGoBak(players, player);  // 고박인 사람이 있는지 확인하여 알려준다

    for (int i = 0; i < defeatedPlayers.size(); i++) {
      Player defeatedPlayer = defeatedPlayers.at(i);
      std::cout << defeatedPlayer.getName() << "님 입장에서 "
                << player.getName() << "님에게 지불할 금액에 해당하는 최종 점수는 "
                << defeatedPlayer.getScoreToPay() << "점 입니다." << std::endl;
    }

    exit(0);
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
    std::cout << "-----------------현재 난 패 목록-----------------" << std::endl;
    player.getBadakHand().printCardSet();
    //카드를 낸다.
    std::cout << ">> 인덱스 번호로 카드를 내 주세요" << std::endl;
    int c;
    std::cin>>c;
    Card card = player.getHand().PopIdxCard(c);
    //짝을 맞춘다
    int p1_index = makePair(card, badak);
    if (p1_index==-1) {
      std::cout << ">> 낸 카드를 바닥에 깔아놓습니다" << std::endl;
      badak.AddCard(card);
    } else {
      // 아래에서 뻑인지 판단한 후 추가합니다.
      // std::cout << ">> 페어를 난 패에 추가합니다." << std::endl;
      // player.getBadakHand().AddCard(gookJinCase(card));
      // player.getBadakHand().AddCard(gookJinCase(badak.PopIdxCard(p1_index)));
    }
    // 더미의 패가 소진되었으면 현재 플레이어의 badakHand 패를 가지고 점수를 계산한 다음
    // 최종점수 계산 후 승리자를 선정하도록 처리합니다.
    // --추가-- 여기서 딱히 처리를 해줄 필요는 없습니다. 사람들이 가진 손패가 21장이고
    // 바닥에 처음에 까는게 6장입니다. 그럼 더미에 카드가 21개가 됩니다.
    // 그러면 사람들이 자신의 차례에 카드를 내고 더미에서 카드를 하나씩 뒤집게 되있으므로
    // 딱 맞게 끝나게 됩니다. 만약 마지막 턴(손 패가 모두 하나만 있는 경우)에 점수가 나면 무조건
    // 스탑을 외쳐야하므로 게임이 끝나고 스탑을 하지 못하면 나가리이므로 위의 play에서
    // 처리하게 됩니다.
    // 일단 남겨둡니다. 나중에 삭제하면 될 것 같습니다.
    /*
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
    */
      //카드를 뽑는다
      std::cout << ">> 카드를 뽑겠습니다 " << std::endl;
      Card popped = dummy.PopCard();
      std::cout << ">> 뽑은 카드는 " << popped.toString() << std::endl;
      //짝을 맞춘다
      int p2_index = makePair(popped, badak);
      std::vector<Card> addedCardfromBadak;
      if (p1_index != -1) {
        if (p2_index != -1) { // p1_index != -1 && p2_index != -1 인 경우가 여기서 처리됨
          // 더미에서 젖힌 패와 짝을 맞춘 바닥패가, 내가 낸 패와 짝을 맞췄던 바닥패인 경우(== 뻑)
          if (popped.GetMonthOfCard() == badak.GetCard(p1_index).GetMonthOfCard()
            && p1_index == p2_index) {
            // 3개의 패(더미에서 젖힌 패, 내가 낸 패, 짝을 맞춘 바닥패)는 모두
            // 바닥에 있어야 함. 바닥에 내려놓으면서 각 카드의 isPpuk_ == true로
            // 세팅
            std::cout << ">> 뻑입니다. 세 장의 카드를 모두 바닥에 내려놓습니다."
                      << std::endl;

            // 바닥패 뻑 여부 <= true
            Card temp = badak.PopIdxCard(p2_index);
            temp.setPpuk(true);
            badak.AddCard(temp);

            // 더미에서 젖힌 패
            popped.setPpuk(true);
            badak.AddCard(popped);

            // 내가 낸 패
            card.setPpuk(true);
            badak.AddCard(card);
          }
          // 더미에서 젖힌 패와 짝을 맞춘 바닥패가, 내가 낸 패와 짝을 맞췄던
          // 바닥패와 월은 같지만, 똑같은 패는 아니어서(즉 뻑이 아니라서) 4장을 한꺼번에 가져올 수 있는경우(== 따닥)
          else if (popped.GetMonthOfCard() == badak.GetCard(p1_index).GetMonthOfCard() 
            && p1_index != p2_index) {
            std::cout << ">> 따닥입니다." << std::endl;
            // 4개의 패를 가져오고 다른 참여자로부터 피를 한 장씩 가져온다.
            player.getBadakHand().AddCard(gookJinCase(popped));
            addedCardfromBadak.push_back(badak.GetCard(p1_index));
            addedCardfromBadak.push_back(badak.GetCard(p2_index));
            player.getBadakHand().AddCard(gookJinCase(badak.PopIdxCard(p1_index)));
            if (p1_index < p2_index)
              player.getBadakHand().AddCard(gookJinCase(badak.PopIdxCard(p2_index - 1)));
            else
              player.getBadakHand().AddCard(gookJinCase(badak.PopIdxCard(p2_index)));
            player.getBadakHand().AddCard(gookJinCase(card));

            // 다른 플레이어로부터 피를 한 장씩 받아온다.
            for (Player& p : players) {
              if (p.getName().compare(
                      player.getName())) {  // 이름이 다른 플레이어일 경우
                std::cout << ">> " << p.getName()
                          << " 로부터 피를 한 장 받아옵니다." << std::endl;
                int pi_num = 0;
                for (int i = 0; i < p.getBadakHand().GetNumOfCards(); i++) {
                  if (p.getBadakHand().GetCard(i).GetStateOfCard() == 피) {
                    player.getBadakHand().AddCard(p.getBadakHand().PopIdxCard(
                        i));  // 피를 받아서 난패에 추가
                    pi_num++;
                    break;
                  }
                }
                // 상대방이 피가 없을 경우 쌍피가 있다면 쌍피를 받아온다.
                for (int i = 0; i < p.getBadakHand().GetNumOfCards(); i++) {
                  if (p.getBadakHand().GetCard(i).GetStateOfCard() == 쌍피) {
                    player.getBadakHand().AddCard(p.getBadakHand().PopIdxCard(
                        i));  // 쌍피를 받아서 난패에 추가
                    break;
                  }
                }
              }
            }
          } 
          else {  // 따닥이나 뻑이 아닌 경우
            // 4장의 카드만 가져온다.
            std::cout << ">> 페어를 난 패에 추가합니다." << std::endl;
            player.getBadakHand().AddCard(gookJinCase(popped));
            addedCardfromBadak.push_back(badak.GetCard(p1_index));
            addedCardfromBadak.push_back(badak.GetCard(p2_index));
            player.getBadakHand().AddCard(gookJinCase(badak.PopIdxCard(p1_index)));
            if (p1_index < p2_index)
              player.getBadakHand().AddCard(gookJinCase(badak.PopIdxCard(p2_index - 1)));
            else
              player.getBadakHand().AddCard(gookJinCase(badak.PopIdxCard(p2_index)));
            player.getBadakHand().AddCard(gookJinCase(card));
          }
        } else {  // p1_index != -1 && p2_index == -1 인 경우가 여기서 처리됨
          // 내가 낸 패와, 짝이 맞은 바닥패만 가져온다
          std::cout << ">> 페어를 난 패에 추가합니다." << std::endl;
          player.getBadakHand().AddCard(gookJinCase(card));
          addedCardfromBadak.push_back(badak.GetCard(p1_index));
          Card c = gookJinCase(badak.PopIdxCard(p1_index));
          c.setPpuk(false);
          player.getBadakHand().AddCard(c);
        }
      }

      if (p1_index == -1 && p2_index == -1) { // p1_index == -1 && p2_index == -1 인 경우가 여기서 처리됨
        std::cout << ">> 뽑은 카드를 바닥에 깔아놓습니다." << std::endl;
        badak.AddCard(popped);
      } else if(p1_index == -1 && p2_index != -1) {  // p1_index == -1 && p2_index != -1 인 경우가 여기서 처리됨
          // <쪽>
          // 바닥패와 짝이 되는 카드가 없어서 아무거나 낸 카드를 더미에서 뽑은 카드와
          // 함께 다시 가져오는 경우. 즉 내가 낸 카드를 다시 가져오는 경우
          if (badak.GetCard(p2_index) == card) {
            std::cout << ">> '쪽'입니다. 쪽을 한 두 짝패를 난 패에 추가합니다." << std::endl;
            player.getBadakHand().AddCard(gookJinCase(popped));
            addedCardfromBadak.push_back(badak.GetCard(p2_index));
            player.getBadakHand().AddCard(gookJinCase(badak.PopIdxCard(p2_index)));
            // 다른 플레이어로부터 피를 한 장씩 받아온다.
            for (Player& p : players) {
              if (p.getName().compare(player.getName())) {  // 이름이 다른 플레이어일 경우
                std::cout << ">> " << p.getName()
                          << " 로부터 피를 한 장 받아옵니다." << std::endl;
                int pi_num = 0;
                for (int i = 0; i < p.getBadakHand().GetNumOfCards(); i++) {
                  if (p.getBadakHand().GetCard(i).GetStateOfCard() == 피) {
                    player.getBadakHand().AddCard(p.getBadakHand().PopIdxCard(i));  // 피를 받아서 난패에 추가
                    pi_num++;
                    break;
                  }
                }
                // 상대방이 피가 없을 경우 쌍피가 있다면 쌍피를 받아온다.
                for (int i = 0; i < p.getBadakHand().GetNumOfCards(); i++) {
                  if (p.getBadakHand().GetCard(i).GetStateOfCard() == 쌍피) {
                    player.getBadakHand().AddCard(p.getBadakHand().PopIdxCard(i));  // 쌍피를 받아서 난패에 추가
                    break;
                  }
                }
              }
            }
          } else {
            std::cout << ">> 페어를 난 패에 추가합니다." << std::endl;
            player.getBadakHand().AddCard(gookJinCase(popped));
            addedCardfromBadak.push_back(badak.GetCard(p2_index));
            Card c = gookJinCase(badak.PopIdxCard(p2_index));
            c.setPpuk(false);
            player.getBadakHand().AddCard(c);
          }
      }
      /*
    }*/
    
    // 상대가 뻑낸 카드를 먹었는지 확인하고 그렇다면 피를 한장씩 가져온다.
    if (!addedCardfromBadak.empty()) {
      if (addedCardfromBadak[0].IsPpuk() == true) {
        std::cout << ">> 상대가 뻑을 낸 카드를 먹었습니다. 뻑을 낸 카드 "
                      "3장을 모두 가져옵니다."
                  << std::endl;
        std::vector<int> pcard_index;
        for (int i = 0; i < badak.GetNumOfCards(); i++) {
          if (badak.GetCard(i).GetMonthOfCard() == addedCardfromBadak[0].GetMonthOfCard() &&
              badak.GetCard(i).IsPpuk() == true) {
            pcard_index.push_back(i);
          }
        }
        std::sort(pcard_index.begin(), pcard_index.end());
        std::reverse(pcard_index.begin(), pcard_index.end());
        for (int i : pcard_index) {
          Card c = gookJinCase(badak.PopIdxCard(i));
          c.setPpuk(false);
          player.getBadakHand().AddCard(c);
        }
      }
      if (addedCardfromBadak.size() >= 2 &&
          addedCardfromBadak[1].IsPpuk() == true) {
        std::cout << ">> 상대가 뻑을 낸 카드를 먹었습니다. 뻑을 낸 카드 "
                      "3장을 모두 가져옵니다."
                  << std::endl;
        std::vector<int> pcard_index;
        for (int i = 0; i < badak.GetNumOfCards(); i++) {
          if (badak.GetCard(i).GetMonthOfCard() ==
                  addedCardfromBadak[1].GetMonthOfCard() &&
              badak.GetCard(i).IsPpuk() == true) {
            pcard_index.push_back(i);
          }
        }
        std::sort(pcard_index.begin(), pcard_index.end());
        std::reverse(pcard_index.begin(), pcard_index.end());
        for (int i : pcard_index) {
          Card c = gookJinCase(badak.PopIdxCard(i));
          c.setPpuk(false);
          player.getBadakHand().AddCard(c);
        }
      }
    }
      

    //점수를 계산한다.
    player.getBadakHand().calc(player);
    std::cout << "-----------------현재 난 패 목록-----------------" << std::endl;
    player.getBadakHand().printCardSet();
    std::cout << ">> 지금까지 " << player.getBadakHand().getScore() << "점 획득하셨습니다."
              << std::endl;
    if (player.getBadakHand().getScore() >=3) {  // 바닥패의 계산 점수가 3점 이상인 경우 고 또는 스탑 가능
      int addedScore = player.getBadakHand().getScore() - player.getScore(); // 이번 판에서 추가로 획득한 점수
      if (player.getSayGo() == true) {  // 고를 선언했던 사람인 경우
        if (addedScore != 0) {  // 추가로 점수를 얻은 경우 고 또는 스탑을 할 수 있다
          // 얻지 못했다면 고 또는 스탑을 할 수 없다
          // 점수를 얻은 경우 아래의 내용 수행
          player.setScore(player.getBadakHand().getScore());
          //고 또는 스탑 선택.
          std::cout << ">> " << player.getName() << " 님이 이번에 추가로 "<<addedScore<<"점을  획득!"
                    << std::endl;
          std::cout << ">> 0을 눌러 스탑 또는 1을 눌러 고" << std::endl;
          int willGo;
          std::cin >> willGo;
          while (true) {
            if (willGo != 0 && willGo != 1) {
              std::cout << ">> 제대로 입력해주세요" << std::endl;
              std::cout << ">> 0을 눌러 스탑 또는 1을 눌러 고" << std::endl;
              std::cin >> willGo;
            } else {
              break;
            }
          }
          // 플레이어의 고가 중요해서 보드의 고를 제거하고
          // 플레이어의 고를 이용하도록 수정했습니다.
          switch (willGo) {
            case 0:
              //여기 최종점수 계산 구현 안해놨습니다. 구현해주세요.
              // --부분 구현 완료--
              std::cout << ">> " << player.getName()
                        << " 님의 승리로 게임이 끝났습니다!" << std::endl;
              std::cout << ">> " << player.getName() << " 님은"
                        << player.getScore() << " 점과 ";
              calcScoreByGo(player);  //고로 인한 점수 업데이트
              std::cout << player.getGo() << " 고를 획득하셔서 총"
                        << player.getScore() << " 점으로 승리하셨습니다."
                        << std::endl;
              std::cout << ">> 결산 규칙을 적용하여 최종 점수를 계산합니다."
                        << std::endl;
              endGame(players, player);  // 나가리가 아닌 경우 게임 종료

              break;
            case 1:
              player.setGo(player.getGo() + 1);  //이긴 플레이어의 고를 하나 늘림

              std::cout << ">> " << player.getName() << " 님이 고하셨습니다!"
                        << std::endl;
              std::cout << "현재 " << player.getName() << "님의 고는 "
                        << player.getGo() << "go 입니다." << std::endl;

              break;
          }
        }
      } else {  // 고를 외치지 않았던 사람인 경우 단지 3점만 넘으면 OK
        player.setScore(player.getBadakHand().getScore());
        //고 또는 스탑 선택.
        std::cout << ">> " << player.getName() << " 님이 이번에 추가로 "
                  << addedScore << "점을  획득!" << std::endl;
        std::cout << ">> 0을 눌러 스탑 또는 1을 눌러 고" << std::endl;
        int willGo;
        std::cin >> willGo;
        while (true) {
          if (willGo != 0 && willGo != 1) {
            std::cout << ">> 제대로 입력해주세요" << std::endl;
            std::cout << ">> 0을 눌러 스탑 또는 1을 눌러 고" << std::endl;
            std::cin >> willGo;
          } else {
            break;
          }
        }
        // 플레이어의 고가 중요해서 보드의 고를 제거하고
        // 플레이어의 고를 이용하도록 수정했습니다.
        switch (willGo) {
          case 0:
            //여기 최종점수 계산 구현 안해놨습니다. 구현해주세요.
            // --부분 구현 완료--

            std::cout << ">> " << player.getName()
                      << " 님의 승리로 게임이 끝났습니다!" << std::endl;
            std::cout << ">> " << player.getName() << " 님은" << player.getScore()
                      << " 점과 ";
            calcScoreByGo(player);  //고로 인한 점수 업데이트
            std::cout << player.getGo() << " 고를 획득하셔서 총"
                      << player.getScore() << " 점으로 승리하셨습니다."
                      << std::endl;
            std::cout << ">> 결산 규칙을 적용하여 최종 점수를 계산합니다."
                      << std::endl;
            endGame(players, player);  // 나가리가 아닌 경우 게임 종료

            break;
          case 1:
            player.setGo(player.getGo() + 1);  //이긴 플레이어의 고를 하나 늘림
            player.setSayGo(true);  // 플레이어가 고를 말했다고 변경
            std::cout << ">> " << player.getName() << " 님이 고하셨습니다!"<< std::endl;
            std::cout<<"현재 "<<player.getName()<<"님의 고는 " << player.getGo() << "go 입니다." << std::endl;

            break;
        }
      }
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
