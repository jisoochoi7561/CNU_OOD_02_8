#include "Player.h"

Player::Player() : CardSet() { winset_ = PlayerWinCardSet(); }
// �÷��̾ �տ� ��� �ִ� �д� ���߿� ���� ������ �� �߰��ϸ鼭
// �ʱ�ȭ�ϸ� �� �� �����ϴ�.

PlayerWinCardSet Player::getPlayerWinCardSet() { return this->winset_; }
std::vector<Card> Player::getPlayerCard() { return this->player_card_; }
int Player::score() { return this->score_; }
void Player::addScore(int score) { this->score_ += score; }
void Player::multScore(int ratio) { this->score_ *= ratio; }