#ifndef MENU_H
#define MENU_H

#include "constants.cpp"

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <random>
#include <fstream>

using namespace std;

class Menu
{
	private:
		ALLEGRO_COLOR backgroundColor;
		ALLEGRO_COLOR sokobanTextColor;
		ALLEGRO_COLOR highScoreTextColor;
		ALLEGRO_COLOR chooseLevelTextColor;
		
		ALLEGRO_FONT * sokobanTextFont;
		ALLEGRO_FONT * highScoreTextFont;
		ALLEGRO_FONT * chooseLevelTextFont;
		
		ALLEGRO_BITMAP * rotatingBox;
		ALLEGRO_BITMAP * manPushingBox;
		ALLEGRO_BITMAP * playNotPressing;
		ALLEGRO_BITMAP * playPressing;
		ALLEGRO_BITMAP * classicNotPressing;
		ALLEGRO_BITMAP * classicPressing;
		ALLEGRO_BITMAP * timeLimitNotPressing;
		ALLEGRO_BITMAP * timeLimitPressing;
		ALLEGRO_BITMAP * backNotPressing;
		ALLEGRO_BITMAP * backPressing;
		ALLEGRO_BITMAP * justALevelNotPressing;
		ALLEGRO_BITMAP * justALevelPressing;
		
		ALLEGRO_EVENT_QUEUE * eventQueue;
		
		ALLEGRO_TIMER * timer;
		
		ALLEGRO_SAMPLE * menuTheme;
		ALLEGRO_SAMPLE * buttonClick;
		
		float boxRotationSpeed;
		
		bool playButtonPressed;
		bool justALevelButtonPressed;
		
		int levelChosen;
		
	public:
		Menu();
		
		~Menu();
		
		void setLevelChosen(int);
		
		int getLevelChosen() const;
		
		bool levelChosenCheck(const char &);
		
		int checkForErrors();
		
		int menuManager(ALLEGRO_DISPLAY *);
		
		void GUIUpdate(bool, bool, bool, bool, bool);
};

#endif
