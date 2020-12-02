#include "Player.h"

Player::Player() : hand_(), badakhand_(), name_("Hong Killdong"), score_(0),choice(0) {}
Player::Player(std::string name)
    : hand_(), badakhand_(), name_(name), score_(0), choice(0) {}
// 플레이어가 손에 쥐고 있는 패는 나중에 게임 시작할 때 추가하면서
// 초기화하면 될 것 같습니다.
void Player::setChoice(const Card& card) { this->choice = card.GetMonthOfCard(); }
BadakHand Player::getBadakHand() { return this->badakhand_; }
int Player::score() { return this->score_; }
void Player::addScore(int score) { this->score_ += score; }
void Player::multScore(int ratio) { this->score_ *= ratio; }
CardSet& Player::getHand() { return this->hand_; }
std::string Player::getName() { return this->name_; }
// 정렬을 위한 < operator overloading
bool Player::operator<(const Player& other) {
  return this->choice > other.choice;
}