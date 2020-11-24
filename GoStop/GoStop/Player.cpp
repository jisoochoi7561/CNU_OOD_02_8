#include "Player.h"

Player::Player() : CardSet() { winset_ = PlayerWinCardSet(); }
// 플레이어가 손에 쥐고 있는 패는 나중에 게임 시작할 때 추가하면서
// 초기화하면 될 것 같습니다.

PlayerWinCardSet Player::getPlayerWinCardSet() { return this->winset_; }
std::vector<Card> Player::getPlayerCard() { return this->player_card_; }
int Player::score() { return this->score_; }
void Player::addScore(int score) { this->score_ += score; }
void Player::multScore(int ratio) { this->score_ *= ratio; }