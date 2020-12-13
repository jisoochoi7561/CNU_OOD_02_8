#include "Player.h"

Player::Player()
    : hand_(),
      badakhand_(),
      name_("Hong Killdong"),
      score_(0),
      choice(0),
      go(0),
      sayGo_(false),
      scoredByGwang_(false),
      scoredByPi_(false), scoreToPay_(0), isPresident_(false) {}
Player::Player(std::string name)
    : hand_(),
      badakhand_(),
      name_(name),
      score_(0),
      choice(0),
      go(0),
      sayGo_(false), scoredByGwang_(false),
      scoredByPi_(false),
      scoreToPay_(0),
      isPresident_(false) {}
// 플레이어가 손에 쥐고 있는 패는 나중에 게임 시작할 때 추가하면서
// 초기화하면 될 것 같습니다.
void Player::setChoice(const Card& card) {
  this->choice = card.GetMonthOfCard();
}
BadakHand& Player::getBadakHand() { return this->badakhand_; }
//플레이어의 스코어는 마지막으로 난 패의 스코어입니다.
//최종점수계산은 따로해주세요.finalscore를 새로 따로만들거나, 어차피 게임끝날 떄
//한번 쓰이므로 일회용으로 만들어도 될거같아요.
int Player::getScore() { return this->score_; }
void Player::setScore(int score) { this->score_ = score; }
CardSet& Player::getHand() { return this->hand_; }
std::string Player::getName() { return this->name_; }
// 정렬을 위한 < operator overloading
bool Player::operator<(const Player& other) {
  return this->choice > other.choice;
}

// getter and setter
bool Player::getSayGo() { return this->sayGo_; }             // 추가 함수. 고를 외친 사람을 판별하기 위해 사용
void Player::setSayGo(bool sayGo) { this->sayGo_ = sayGo; }  // 추가 함수
int Player::getGo() { return this->go; }                     // 추가 함수  고의 횟수를 가져오기 위해 사용
void Player::setGo(int go) { this->go = go; }                // 추가 함수
bool Player::getScoredByGwang() { return this->scoredByGwang_; }
void Player::setScoredByGwang(bool flag) {
  this->scoredByGwang_ = flag;
}  // 광으로 점수가 났는지 확인하기 위해 사용
bool Player::getScoredByPi() { return this->scoredByPi_; }
void Player::setScoredByPi(bool flag) {
  this->scoredByPi_ = flag;
}  // 피로 점수가 났는지 확인하기 위해 사용
// 고박, 멍박 등 결산 시 필요
int Player::getScoreToPay() { return this->scoreToPay_; }  // 현재 플레이어 입장에서 승자의 점수(즉, 지불할 금액을 결정하는 점수)를 가져오는 함수
void Player::setScoreToPay(int score) { this->scoreToPay_ = score; }  // 현재 플레이어 입장에서 승자의 점수(즉, 지불할 금액을 결정하는 점수)를 설정하는 함수

void Player::setIsPresident(bool isPresident) {
  this->isPresident_ = isPresident;
}

bool Player::getIsPresident() { return this -> isPresident_; }

void Player::getPiFromPlayer(std::vector<Player>& players) {
  // 다른 플레이어로부터 피를 한 장씩 받아온다.
  for (Player& p : players) {
    if (p.getName().compare(this->getName())) {  // 이름이 다른 플레이어일 경우
      std::cout << ">> " << p.getName() << " 로부터 피를 한 장 받아옵니다."
                << std::endl;
      int pi_num = 0;
      for (int i = 0; i < p.getBadakHand().GetNumOfCards(); i++) {
        if (p.getBadakHand().GetCard(i).GetStateOfCard() == pi) {
          this->getBadakHand().AddCard(
              p.getBadakHand().PopIdxCard(i));  // 피를 받아서 난패에 추가
          pi_num++;
          break;
        }
      }
      // 상대방이 피가 없을 경우 쌍피가 있다면 쌍피를 받아온다.
      for (int i = 0; i < p.getBadakHand().GetNumOfCards(); i++) {
        if (p.getBadakHand().GetCard(i).GetStateOfCard() == ssangpi) {
          this->getBadakHand().AddCard(
              p.getBadakHand().PopIdxCard(i));  // 쌍피를 받아서 난패에 추가
          break;
        }
      }
    }
  }
}