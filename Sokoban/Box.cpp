#include "Box.h"

Box::Box() : iX(0), iY(0), x(0), y(0) { }
Box::Box(float _iX, float _iY, bool _isOnDestination) : iX(_iX), iY(_iY), x(_iX), y(_iY), isOnDestination(_isOnDestination) { }

void Box::setIX(float _iX) { iX = _iX; }
void Box::setIY(float _iY) { iY = _iY; }
void Box::setX(float _x) { x = _x; }
void Box::setY(float _y) { y = _y; }
void Box::setIsOnDestination(bool _isOnDestination) { isOnDestination = _isOnDestination; }

float Box::getIX() const { return iX; }
float Box::getIY() const { return iY; }
float Box::getX() const { return x; }
float Box::getY() const { return y; }
bool Box::getIsOnDestination() const { return isOnDestination; }
