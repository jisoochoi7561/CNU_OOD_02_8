#include "Player.h"

Player::Player() : hand_(), badakhand_(), name_("Hong Killdong"), score_(0),choice(0),go(0) {}
Player::Player(std::string name)
    : hand_(), badakhand_(), name_(name), score_(0), choice(0),go(0) {}
// 플레이어가 손에 쥐고 있는 패는 나중에 게임 시작할 때 추가하면서
// 초기화하면 될 것 같습니다.
void Player::setChoice(const Card& card) { this->choice = card.GetMonthOfCard(); }
BadakHand& Player::getBadakHand() { return this->badakhand_; }
//플레이어의 스코어는 마지막으로 난 패의 스코어입니다.
//최종점수계산은 따로해주세요.finalscore를 새로 따로만들거나, 어차피 게임끝날 떄 한번 쓰이므로 일회용으로 만들어도 될거같아요.
int Player::score() { return this->score_; }
void Player::setScore(int score) { this->score_ = score; }
CardSet& Player::getHand() { return this->hand_; }
std::string Player::getName() { return this->name_; }
// 정렬을 위한 < operator overloading
bool Player::operator<(const Player& other) {
  return this->choice > other.choice;
}