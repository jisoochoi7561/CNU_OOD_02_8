#include "Player.h"

Player::Player() : hand_(), badakhand_(), name_("Hong Killdong"), score_(0),choice(0),go(0) {}
Player::Player(std::string name)
    : hand_(), badakhand_(), name_(name), score_(0), choice(0),go(0) {}
// �÷��̾ �տ� ��� �ִ� �д� ���߿� ���� ������ �� �߰��ϸ鼭
// �ʱ�ȭ�ϸ� �� �� �����ϴ�.
void Player::setChoice(const Card& card) { this->choice = card.GetMonthOfCard(); }
BadakHand& Player::getBadakHand() { return this->badakhand_; }
//�÷��̾��� ���ھ�� ���������� �� ���� ���ھ��Դϴ�.
//������������� �������ּ���.finalscore�� ���� ���θ���ų�, ������ ���ӳ��� �� �ѹ� ���̹Ƿ� ��ȸ������ ���� �ɰŰ��ƿ�.
int Player::score() { return this->score_; }
void Player::setScore(int score) { this->score_ = score; }
CardSet& Player::getHand() { return this->hand_; }
std::string Player::getName() { return this->name_; }
// ������ ���� < operator overloading
bool Player::operator<(const Player& other) {
  return this->choice > other.choice;
}