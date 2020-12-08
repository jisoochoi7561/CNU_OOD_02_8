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
  if (card.GetStateOfCard()==����&&card.GetMonthOfCard()==9) {
    std::cout
        << "������ �߰��մϴ�. ������ �������� ���� ���Ƿ� ���� �������ּ���.\n"
        << "0�� ������ ��������, �ٸ� ���� ������ ���Ƿ� ����մϴ�."
        << std::endl;
    int c;
    std::cin >> c;
    if (c!=0) {
      card.setState(����);
    }
  }
  return card;
}

//������ ��ü�� �ʿ��ϴٰ� �����ؼ� ��������ϴ�. �������� �ֵ������� ������ �̲���ϴ�.
//�������� ����,�÷��̾�,�ٴ�,��������ǻ���(���)���� �� �����մϴ�.
// --�߰�-- ���� ���´� �÷��̾��� �� ���¿� ���� �޶����ϴ�. �׷��� �ʵ忡 �� �����߽��ϴ�.
// ����� ��쿡�� ����ǰ� �� ���� ��쿡�� �� ��ģ �÷��̾��� �� ����
// �޶����Ƿ� �׳� �÷��̾� �� ����ϵ��� �߽��ϴ�.
  Board::Board() : players(), dummy(), badak(), util(EndGameUtil::GetInstance()) {
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
      if (sum == 0) {  //�������� ���
        // ��� �÷��̾ ���а� ������ ��쿡�� �� ��ģ �����
        // ������ ���� ���Ͽ� ��ž�� ���� ���ϰų� ��� �÷��̾
        // ��ž�� �� �� ���� ��, ������ ���� �� �ִ� ������ ȹ������ ����
        // ����̹Ƿ� �� ��쿡�� �������� ��ȿ���� �˴ϴ�. �̷� ���
        // �������� ������ ������ 2�踦 ���־�� �մϴ�. �׷��Ƿ�
        // �������� �ܼ��� �����ŵ�ϴ�.
        std::cout << ">> ��� �÷��̾��� ���а� �����Ǿ����ϴ�. �������Դϴ�.";
        exit(0);
      }

      for (Player& player : players) {
        // ���а� 0�̸� �� ���� ������ ���̶�� �ǹ��Դϴ�. �ֳ��ϸ� ���̿� ���а� �����Ǵ� ������
        // ������ �÷��̾ ������ ��(��� ���а� 1���� ���)�� ���� ���� �ϳ��� ���� ���̸� ������ �����̱� �����Դϴ�.
      //  if (player.getHand().GetNumOfCards() != 0) {
          giveTurnToPlayer(player);
      //  }
        /* ���⿡ �ش��ϴ� ��찡 ���� �̴ϴ�. �տ� ����ִ� �и� ���⸸ �ϰ� �߰��� �����ʾƼ�
           �ִ� 7�ϸ� �����ϰ� �Ǳ� �����Դϴ�. ���� ��� ���� �� �����ؼ� ������ ������ ������� �ݴϴ�.
        else {
          std::cout << "<< " << player.getName()
                    << " �÷��̾��� ���а� �����Ǿ� ���� �÷��̾�� ���ʰ� �Ѿ�ϴ�.\n";
        }*/
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

  // �� ������ ���� ���
  void Board::calcScoreByGo(Player& player) {
    switch (player.getGo()) {
      case 0:   // �� ������ �׳� ������
        break;
      case 1:  // �� 1�� ���
        player.setScore(player.getScore() + 1);
        break;
      case 2:  // �� 2�� ���
        player.setScore(player.getScore() + 2);
        break;
      default:  // �� �� ���
        player.setScore(player.getScore() * pow(2, player.getGo() - 2));
        break;
    }
  }
  // �������� �ƴ� ������ �����ϴ� �Լ�
  void Board::endGame(std::vector<Player>& players, Player& player) {
    std::vector<Player> defeatedPlayers;  // �й��� �÷��̾� ����
    for (int i = 0; i < players.size(); i++) {
      if (players.at(i).getName() != player.getName()) {
        defeatedPlayers.push_back(players.at(i));  // �й��� �÷��̾ �߰�
      }
    }

    util->calcByMungBak(player);  // �̱� ����� ������ �۹ڿ� ���� ���(�۹��̸� 2��)

    // �ǹ�, ������ �ش��ϴ� ����� 2��� ������� �ϴ� ���̹Ƿ�
    // �ش� �÷��̾��� ���忡�� ������ ������ ���

    // �켱 �� ����� ���忡�� �̱� ����� ������ �۹ڱ��� ������ ������ �ʱ�ȭ
    for (int i = 0; i < defeatedPlayers.size(); i++) {
      defeatedPlayers.at(i).setScoreToPay(player.getScore());
    }

    util->calcByGwangBak(players, player);  // ���ڿ� �ش��ϴ� ����� �����ؾ� �ϴ� �ݾ׿� �ش��ϴ� ����(�ش� �÷��̾� ���忡�� ������ ����)�� 2���
    util->calcByPiBak(players, player);  // �ǹڿ� �ش��ϴ� ����� �����ؾ� �ϴ� ����(�ش� �÷��̾� ���忡�� ������ ����)�� 2���

    util->checkGoBak(players, player);  // ����� ����� �ִ��� Ȯ���Ͽ� �˷��ش�

    for (int i = 0; i < defeatedPlayers.size(); i++) {
      Player defeatedPlayer = defeatedPlayers.at(i);
      std::cout << defeatedPlayer.getName() << "�� ���忡�� "
                << player.getName() << "�Կ��� ������ �ݾ׿� �ش��ϴ� ���� ������ "
                << defeatedPlayer.getScoreToPay() << "�� �Դϴ�." << std::endl;
    }

    exit(0);
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
    std::cout << "-----------------���� �� �� ���-----------------" << std::endl;
    player.getBadakHand().printCardSet();
    //ī�带 ����.
    std::cout << ">> �ε��� ��ȣ�� ī�带 �� �ּ���" << std::endl;
    int c;
    std::cin>>c;
    Card card = player.getHand().PopIdxCard(c);
    //¦�� �����
    int p1_index = makePair(card, badak);
    if (p1_index==-1) {
      std::cout << ">> �� ī�带 �ٴڿ� ��Ƴ����ϴ�" << std::endl;
      badak.AddCard(card);
    } else {
      // �Ʒ����� ������ �Ǵ��� �� �߰��մϴ�.
      // std::cout << ">> �� �� �п� �߰��մϴ�." << std::endl;
      // player.getBadakHand().AddCard(gookJinCase(card));
      // player.getBadakHand().AddCard(gookJinCase(badak.PopIdxCard(p1_index)));
    }
    // ������ �а� �����Ǿ����� ���� �÷��̾��� badakHand �и� ������ ������ ����� ����
    // �������� ��� �� �¸��ڸ� �����ϵ��� ó���մϴ�.
    // --�߰�-- ���⼭ ���� ó���� ���� �ʿ�� �����ϴ�. ������� ���� ���а� 21���̰�
    // �ٴڿ� ó���� ��°� 6���Դϴ�. �׷� ���̿� ī�尡 21���� �˴ϴ�.
    // �׷��� ������� �ڽ��� ���ʿ� ī�带 ���� ���̿��� ī�带 �ϳ��� ������ �������Ƿ�
    // �� �°� ������ �˴ϴ�. ���� ������ ��(�� �а� ��� �ϳ��� �ִ� ���)�� ������ ���� ������
    // ��ž�� ���ľ��ϹǷ� ������ ������ ��ž�� ���� ���ϸ� �������̹Ƿ� ���� play����
    // ó���ϰ� �˴ϴ�.
    // �ϴ� ���ܵӴϴ�. ���߿� �����ϸ� �� �� �����ϴ�.
    /*
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
    */
      //ī�带 �̴´�
      std::cout << ">> ī�带 �̰ڽ��ϴ� " << std::endl;
      Card popped = dummy.PopCard();
      std::cout << ">> ���� ī��� " << popped.toString() << std::endl;
      //¦�� �����
      int p2_index = makePair(popped, badak);
      std::vector<Card> addedCardfromBadak;
      if (p1_index != -1) {
        if (p2_index != -1) { // p1_index != -1 && p2_index != -1 �� ��찡 ���⼭ ó����
          // ���̿��� ���� �п� ¦�� ���� �ٴ��а�, ���� �� �п� ¦�� ����� �ٴ����� ���(== ��)
          if (popped.GetMonthOfCard() == badak.GetCard(p1_index).GetMonthOfCard()
            && p1_index == p2_index) {
            // 3���� ��(���̿��� ���� ��, ���� �� ��, ¦�� ���� �ٴ���)�� ���
            // �ٴڿ� �־�� ��. �ٴڿ� ���������鼭 �� ī���� isPpuk_ == true��
            // ����
            std::cout << ">> ���Դϴ�. �� ���� ī�带 ��� �ٴڿ� ���������ϴ�."
                      << std::endl;

            // �ٴ��� �� ���� <= true
            Card temp = badak.PopIdxCard(p2_index);
            temp.setPpuk(true);
            badak.AddCard(temp);

            // ���̿��� ���� ��
            popped.setPpuk(true);
            badak.AddCard(popped);

            // ���� �� ��
            card.setPpuk(true);
            badak.AddCard(card);
          }
          // ���̿��� ���� �п� ¦�� ���� �ٴ��а�, ���� �� �п� ¦�� �����
          // �ٴ��п� ���� ������, �Ȱ��� �д� �ƴϾ(�� ���� �ƴ϶�) 4���� �Ѳ����� ������ �� �ִ°��(== ����)
          else if (popped.GetMonthOfCard() == badak.GetCard(p1_index).GetMonthOfCard() 
            && p1_index != p2_index) {
            std::cout << ">> �����Դϴ�." << std::endl;
            // 4���� �и� �������� �ٸ� �����ڷκ��� �Ǹ� �� �徿 �����´�.
            player.getBadakHand().AddCard(gookJinCase(popped));
            addedCardfromBadak.push_back(badak.GetCard(p1_index));
            addedCardfromBadak.push_back(badak.GetCard(p2_index));
            player.getBadakHand().AddCard(gookJinCase(badak.PopIdxCard(p1_index)));
            if (p1_index < p2_index)
              player.getBadakHand().AddCard(gookJinCase(badak.PopIdxCard(p2_index - 1)));
            else
              player.getBadakHand().AddCard(gookJinCase(badak.PopIdxCard(p2_index)));
            player.getBadakHand().AddCard(gookJinCase(card));

            // �ٸ� �÷��̾�κ��� �Ǹ� �� �徿 �޾ƿ´�.
            for (Player& p : players) {
              if (p.getName().compare(
                      player.getName())) {  // �̸��� �ٸ� �÷��̾��� ���
                std::cout << ">> " << p.getName()
                          << " �κ��� �Ǹ� �� �� �޾ƿɴϴ�." << std::endl;
                int pi_num = 0;
                for (int i = 0; i < p.getBadakHand().GetNumOfCards(); i++) {
                  if (p.getBadakHand().GetCard(i).GetStateOfCard() == ��) {
                    player.getBadakHand().AddCard(p.getBadakHand().PopIdxCard(
                        i));  // �Ǹ� �޾Ƽ� ���п� �߰�
                    pi_num++;
                    break;
                  }
                }
                // ������ �ǰ� ���� ��� ���ǰ� �ִٸ� ���Ǹ� �޾ƿ´�.
                for (int i = 0; i < p.getBadakHand().GetNumOfCards(); i++) {
                  if (p.getBadakHand().GetCard(i).GetStateOfCard() == ����) {
                    player.getBadakHand().AddCard(p.getBadakHand().PopIdxCard(
                        i));  // ���Ǹ� �޾Ƽ� ���п� �߰�
                    break;
                  }
                }
              }
            }
          } 
          else {  // �����̳� ���� �ƴ� ���
            // 4���� ī�常 �����´�.
            std::cout << ">> �� �� �п� �߰��մϴ�." << std::endl;
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
        } else {  // p1_index != -1 && p2_index == -1 �� ��찡 ���⼭ ó����
          // ���� �� �п�, ¦�� ���� �ٴ��и� �����´�
          std::cout << ">> �� �� �п� �߰��մϴ�." << std::endl;
          addedCardfromBadak.push_back(badak.GetCard(p1_index));
          player.getBadakHand().AddCard(gookJinCase(badak.PopIdxCard(p1_index)));
          player.getBadakHand().AddCard(gookJinCase(card));
        }
      }

      if (p1_index == -1 && p2_index == -1) { // p1_index == -1 && p2_index == -1 �� ��찡 ���⼭ ó����
        std::cout << ">> ���� ī�带 �ٴڿ� ��Ƴ����ϴ�." << std::endl;
        badak.AddCard(popped);
      } else if(p1_index == -1 && p2_index != -1) {  // p1_index == -1 && p2_index != -1 �� ��찡 ���⼭ ó����
          // <��>
          // �ٴ��п� ¦�� �Ǵ� ī�尡 ��� �ƹ��ų� �� ī�带 ���̿��� ���� ī���
          // �Բ� �ٽ� �������� ���. �� ���� �� ī�带 �ٽ� �������� ���
          if (badak.GetCard(p2_index) == card) {
            std::cout << ">> '��'�Դϴ�. ���� �� �� ¦�и� �� �п� �߰��մϴ�." << std::endl;
            player.getBadakHand().AddCard(gookJinCase(popped));
            addedCardfromBadak.push_back(badak.GetCard(p2_index));
            player.getBadakHand().AddCard(gookJinCase(badak.PopIdxCard(p2_index)));
            // �ٸ� �÷��̾�κ��� �Ǹ� �� �徿 �޾ƿ´�.
            for (Player& p : players) {
              if (p.getName().compare(player.getName())) {  // �̸��� �ٸ� �÷��̾��� ���
                std::cout << ">> " << p.getName()
                          << " �κ��� �Ǹ� �� �� �޾ƿɴϴ�." << std::endl;
                int pi_num = 0;
                for (int i = 0; i < p.getBadakHand().GetNumOfCards(); i++) {
                  if (p.getBadakHand().GetCard(i).GetStateOfCard() == ��) {
                    player.getBadakHand().AddCard(p.getBadakHand().PopIdxCard(i));  // �Ǹ� �޾Ƽ� ���п� �߰�
                    pi_num++;
                    break;
                  }
                }
                // ������ �ǰ� ���� ��� ���ǰ� �ִٸ� ���Ǹ� �޾ƿ´�.
                for (int i = 0; i < p.getBadakHand().GetNumOfCards(); i++) {
                  if (p.getBadakHand().GetCard(i).GetStateOfCard() == ����) {
                    player.getBadakHand().AddCard(p.getBadakHand().PopIdxCard(i));  // ���Ǹ� �޾Ƽ� ���п� �߰�
                    break;
                  }
                }
              }
            }
          } else {
            std::cout << ">> �� �� �п� �߰��մϴ�." << std::endl;
            player.getBadakHand().AddCard(gookJinCase(popped));
            addedCardfromBadak.push_back(badak.GetCard(p2_index));
            Card c = gookJinCase(badak.PopIdxCard(p2_index));
            c.setPpuk(false);
            player.getBadakHand().AddCard(c);
          }
      }
      /*
    }*/
    
    // ��밡 ���� ī�带 �Ծ����� Ȯ���ϰ� �׷��ٸ� �Ǹ� ���徿 �����´�.
    if (!addedCardfromBadak.empty()) {
      if (addedCardfromBadak[0].IsPpuk() == true) {
        std::cout << ">> ��밡 ���� �� ī�带 �Ծ����ϴ�. ���� �� ī�� "
                      "3���� ��� �����ɴϴ�."
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
        std::cout << ">> ��밡 ���� �� ī�带 �Ծ����ϴ�. ���� �� ī�� "
                      "3���� ��� �����ɴϴ�."
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
      

    //������ ����Ѵ�.
    player.getBadakHand().calc(player);
    std::cout << "-----------------���� �� �� ���-----------------" << std::endl;
    player.getBadakHand().printCardSet();
    std::cout << ">> ���ݱ��� " << player.getBadakHand().getScore() << "�� ȹ���ϼ̽��ϴ�."
              << std::endl;
    if (player.getBadakHand().getScore() >=3) {  // �ٴ����� ��� ������ 3�� �̻��� ��� �� �Ǵ� ��ž ����
      int addedScore = player.getBadakHand().getScore() - player.getScore(); // �̹� �ǿ��� �߰��� ȹ���� ����
      if (player.getSayGo() == true) {  // �� �����ߴ� ����� ���
        if (addedScore != 0) {  // �߰��� ������ ���� ��� �� �Ǵ� ��ž�� �� �� �ִ�
          // ���� ���ߴٸ� �� �Ǵ� ��ž�� �� �� ����
          // ������ ���� ��� �Ʒ��� ���� ����
          player.setScore(player.getBadakHand().getScore());
          //�� �Ǵ� ��ž ����.
          std::cout << ">> " << player.getName() << " ���� �̹��� �߰��� "<<addedScore<<"����  ȹ��!"
                    << std::endl;
          std::cout << ">> 0�� ���� ��ž �Ǵ� 1�� ���� ��" << std::endl;
          int willGo;
          std::cin >> willGo;
          while (true) {
            if (willGo != 0 && willGo != 1) {
              std::cout << ">> ����� �Է����ּ���" << std::endl;
              std::cout << ">> 0�� ���� ��ž �Ǵ� 1�� ���� ��" << std::endl;
              std::cin >> willGo;
            } else {
              break;
            }
          }
          // �÷��̾��� �� �߿��ؼ� ������ �� �����ϰ�
          // �÷��̾��� �� �̿��ϵ��� �����߽��ϴ�.
          switch (willGo) {
            case 0:
              //���� �������� ��� ���� ���س����ϴ�. �������ּ���.
              // --�κ� ���� �Ϸ�--
              std::cout << ">> " << player.getName()
                        << " ���� �¸��� ������ �������ϴ�!" << std::endl;
              std::cout << ">> " << player.getName() << " ����"
                        << player.getScore() << " ���� ";
              calcScoreByGo(player);  //��� ���� ���� ������Ʈ
              std::cout << player.getGo() << " �� ȹ���ϼż� ��"
                        << player.getScore() << " ������ �¸��ϼ̽��ϴ�."
                        << std::endl;
              std::cout << ">> ��� ��Ģ�� �����Ͽ� ���� ������ ����մϴ�."
                        << std::endl;
              endGame(players, player);  // �������� �ƴ� ��� ���� ����

              break;
            case 1:
              player.setGo(player.getGo() + 1);  //�̱� �÷��̾��� �� �ϳ� �ø�

              std::cout << ">> " << player.getName() << " ���� ���ϼ̽��ϴ�!"
                        << std::endl;
              std::cout << "���� " << player.getName() << "���� ��� "
                        << player.getGo() << "go �Դϴ�." << std::endl;

              break;
          }
        }
      } else {  // �� ��ġ�� �ʾҴ� ����� ��� ���� 3���� ������ OK
        player.setScore(player.getBadakHand().getScore());
        //�� �Ǵ� ��ž ����.
        std::cout << ">> " << player.getName() << " ���� �̹��� �߰��� "
                  << addedScore << "����  ȹ��!" << std::endl;
        std::cout << ">> 0�� ���� ��ž �Ǵ� 1�� ���� ��" << std::endl;
        int willGo;
        std::cin >> willGo;
        while (true) {
          if (willGo != 0 && willGo != 1) {
            std::cout << ">> ����� �Է����ּ���" << std::endl;
            std::cout << ">> 0�� ���� ��ž �Ǵ� 1�� ���� ��" << std::endl;
            std::cin >> willGo;
          } else {
            break;
          }
        }
        // �÷��̾��� �� �߿��ؼ� ������ �� �����ϰ�
        // �÷��̾��� �� �̿��ϵ��� �����߽��ϴ�.
        switch (willGo) {
          case 0:
            //���� �������� ��� ���� ���س����ϴ�. �������ּ���.
            // --�κ� ���� �Ϸ�--

            std::cout << ">> " << player.getName()
                      << " ���� �¸��� ������ �������ϴ�!" << std::endl;
            std::cout << ">> " << player.getName() << " ����" << player.getScore()
                      << " ���� ";
            calcScoreByGo(player);  //��� ���� ���� ������Ʈ
            std::cout << player.getGo() << " �� ȹ���ϼż� ��"
                      << player.getScore() << " ������ �¸��ϼ̽��ϴ�."
                      << std::endl;
            std::cout << ">> ��� ��Ģ�� �����Ͽ� ���� ������ ����մϴ�."
                      << std::endl;
            endGame(players, player);  // �������� �ƴ� ��� ���� ����

            break;
          case 1:
            player.setGo(player.getGo() + 1);  //�̱� �÷��̾��� �� �ϳ� �ø�
            player.setSayGo(true);  // �÷��̾ �� ���ߴٰ� ����
            std::cout << ">> " << player.getName() << " ���� ���ϼ̽��ϴ�!"<< std::endl;
            std::cout<<"���� "<<player.getName()<<"���� ��� " << player.getGo() << "go �Դϴ�." << std::endl;

            break;
        }
      }
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