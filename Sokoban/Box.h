class Box
{
	private:
		float iX;
		float iY;
		float x;
		float y;
		bool isOnDestination;
		
	public:
		Box();
		Box(float, float, bool);

		void setIX(float);
		void setIY(float);
		void setX(float);
		void setY(float);
		void setIsOnDestination(bool);

		float getIX() const;
		float getIY() const;
		float getX() const;
		float getY() const;
		bool getIsOnDestination() const;
};
