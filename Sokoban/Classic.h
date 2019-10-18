#ifndef CLASSIC_H
#define CLASSIC_H

class Classic : public GameManager
{
	private:
		int score;
		bool isJustALevel;
		 
	public:	
		Classic();
		Classic(int);
		
		~Classic();
		
		bool levelManager(ALLEGRO_DISPLAY *);
		
		void updateGUI(float);
};

#endif
