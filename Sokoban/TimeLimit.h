#ifndef TIMELIMIT_H
#define TIMELIMIT_H

class TimeLimit : public GameManager
{
	private:
		int timeLimit;

	public:
		TimeLimit();
		
		~TimeLimit();
	
		bool levelManager(ALLEGRO_DISPLAY *);
		
		void updateGUI(float);
};

#endif
