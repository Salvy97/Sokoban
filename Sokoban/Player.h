#ifndef PLAYER_H
#define PLAYER_H

class Player
{
	private:
		float iX;
		float iY;
		float x;
		float y;
		int score;
		unsigned direction;
		unsigned moves;

	public:
		Player();
		Player(int);

		void setIX(float);
		void setIY(float);
		void setX(float);
		void setY(float);
		void setScore(int);
		void setDirection(unsigned);
		void setMoves(unsigned);

		float getIX() const;
		float getIY() const;
		float getX() const;
		float getY() const;
		int getScore() const;
		unsigned getDirection() const;
		unsigned getMoves() const;
};

#endif
