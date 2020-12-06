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
      scoredByPi_(false), scoreToPay_(0) {}
Player::Player(std::string name)
    : hand_(),
      badakhand_(),
      name_(name),
      score_(0),
      choice(0),
      go(0),
      sayGo_(false), scoredByGwang_(false),
      scoredByPi_(false),
      scoreToPay_(0) {}
// �÷��̾ �տ� ��� �ִ� �д� ���߿� ���� ������ �� �߰��ϸ鼭
// �ʱ�ȭ�ϸ� �� �� �����ϴ�.
void Player::setChoice(const Card& card) {
  this->choice = card.GetMonthOfCard();
}
BadakHand& Player::getBadakHand() { return this->badakhand_; }
//�÷��̾��� ���ھ�� ���������� �� ���� ���ھ��Դϴ�.
//������������� �������ּ���.finalscore�� ���� ���θ���ų�, ������ ���ӳ��� ��
//�ѹ� ���̹Ƿ� ��ȸ������ ���� �ɰŰ��ƿ�.
int Player::getScore() { return this->score_; }
void Player::setScore(int score) { this->score_ = score; }
CardSet& Player::getHand() { return this->hand_; }
std::string Player::getName() { return this->name_; }
// ������ ���� < operator overloading
bool Player::operator<(const Player& other) {
  return this->choice > other.choice;
}

// getter and setter
bool Player::getSayGo() { return this->sayGo_; }             // �߰� �Լ�. �� ��ģ ����� �Ǻ��ϱ� ���� ���
void Player::setSayGo(bool sayGo) { this->sayGo_ = sayGo; }  // �߰� �Լ�
int Player::getGo() { return this->go; }                     // �߰� �Լ�  ���� Ƚ���� �������� ���� ���
void Player::setGo(int go) { this->go = go; }                // �߰� �Լ�
bool Player::getScoredByGwang() { return this->scoredByGwang_; }
void Player::setScoredByGwang(bool flag) {
  this->scoredByGwang_ = flag;
}  // ������ ������ ������ Ȯ���ϱ� ���� ���
bool Player::getScoredByPi() { return this->scoredByPi_; }
void Player::setScoredByPi(bool flag) {
  this->scoredByPi_ = flag;
}  // �Ƿ� ������ ������ Ȯ���ϱ� ���� ���
// ���, �۹� �� ��� �� �ʿ�
int Player::getScoreToPay() { return this->scoreToPay_; }  // ���� �÷��̾� ���忡�� ������ ����(��, ������ �ݾ��� �����ϴ� ����)�� �������� �Լ�
void Player::setScoreToPay(int score) { this->scoreToPay_ = score; }  // ���� �÷��̾� ���忡�� ������ ����(��, ������ �ݾ��� �����ϴ� ����)�� �����ϴ� �Լ�
