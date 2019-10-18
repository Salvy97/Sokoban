#include "Player.h"

Player::Player() :  iX(0), iY(0), x(0), y(0), direction(2), moves(0) { }
Player::Player(int _score) : iX(0), iY(0), x(0), y(0), score(_score), direction(2), moves(0) { }

void Player::setIX(float _iX) { iX = _iX; }
void Player::setIY(float _iY) { iY = _iY; }
void Player::setX(float _x) { x = _x; }
void Player::setY(float _y) { y = _y; }
void Player::setScore(int _score) { score = _score; }
void Player::setDirection(unsigned _direction) { direction = _direction; }
void Player::setMoves(unsigned _moves) { moves = _moves; }

float Player::getIX() const { return iX; }
float Player::getIY() const { return iY; }
float Player::getX() const { return x; }
float Player::getY() const { return y; }
int Player::getScore() const { return score; }
unsigned Player::getDirection() const { return direction; }
unsigned Player::getMoves() const { return moves; }
