#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Player.cpp"
#include "Box.cpp"
#include "Menu.h"

#include <vector>
#include <random>
#include <iostream>

using namespace std;

enum Type { TREES = 0, WALL, FLOOR, FLOOR_DESTINATION, BOX, PLAYER, BOX_ON_DESTINATION };

class GameManager
{
	protected:
		unsigned currentLevel;
		unsigned lastLevel;
		
		vector<vector<Type>> map;
		unsigned dimRMap;
		unsigned dimCMap;
		
		double bitmapsCurrentLevelW;
		double bitmapsCurrentLevelH;
		
		ALLEGRO_BITMAP * treesBitmap;
		ALLEGRO_BITMAP * wall;
		ALLEGRO_BITMAP * floor;
		ALLEGRO_BITMAP * floorDestination;
		ALLEGRO_BITMAP * playerUp;
		ALLEGRO_BITMAP * playerDown;
		ALLEGRO_BITMAP * playerLeft;
		ALLEGRO_BITMAP * playerRight;
		ALLEGRO_BITMAP * boxNotOnDestination;
		ALLEGRO_BITMAP * boxOnDestination;
		ALLEGRO_BITMAP * GUIBackground;
		ALLEGRO_BITMAP * audioOnNotPressing;
		ALLEGRO_BITMAP * audioOnPressing;
		ALLEGRO_BITMAP * audioOffNotPressing;
		ALLEGRO_BITMAP * audioOffPressing;
		ALLEGRO_BITMAP * resetNotPressing;
		ALLEGRO_BITMAP * resetPressing;
		
		ALLEGRO_FONT * messagesFont;
		ALLEGRO_FONT * GUIFont;
		
		ALLEGRO_SAMPLE_ID gm;
		ALLEGRO_SAMPLE * gameMusic;
		ALLEGRO_SAMPLE * footsteps;
		ALLEGRO_SAMPLE * movingBox;
		
		ALLEGRO_EVENT_QUEUE * eventQueue;
		
		bool isResetPressing;
		bool resetPressed;

		vector<Box> boxes;
		Player * player;
			
		bool audioOn;
		bool isAudioOnPressing;
		bool isAudioOffPressing;
		
		bool returnToMenu;
		
	public:
		//Costruttori
		GameManager();
		GameManager(int);
		
		//Metodi set
		void setCurrentLevel(unsigned);	
		void setLastLevel(unsigned);
		
		//Metodi get
		unsigned getCurrentLevel() const;
		unsigned getLastLevel() const;
		bool getReturnToMenu() const;
		
		//Questi due metodi calcolano il numero di righe e colonne della mappa del livello attuale
	 	unsigned getCurrentLevelMapRows();
	 	unsigned getCurrentLevelMapColumns(); 	
	 	
	 	//Questo metodo genera la mappa per il livello attuale
	 	vector<vector<Type>> generateLevel();
	 	
	 	//Questo metodo inizializza i bitmaps e la musica scelti casualmente
	 	void setBitmapsAndMusic();
	 	
	 	//Questo metodo controlla eventuali errori nel caricamento dei bitmaps, fonts e audio samples
	 	bool checkForErrors();
	 	
	 	//Questo metodo gestisce e coordina il livello attuale (virtual ridefinito dalle sottoclassi)
	 	virtual bool levelManager(ALLEGRO_DISPLAY *) = 0;
	 	
	 	//Questi due metodi calcolano le posizioni x ed y dei vari bitmaps in base alla risoluzione del display
	 	float calculateXPosition(unsigned, int);	 	
	 	float calculateYPosition(unsigned);
	 	
	 	//Questo metodo inizializza/aggiorna la GUI del livello attuale (virtual ridefinito dalle sottoclassi)
	 	virtual void updateGUI(float) = 0;
	 	
	 	//Questo metodo si occupa delle varie collisioni e gestisce gli eventi che accadono quando se ne verificano
	 	void collisionManager(const unsigned &, const unsigned &, bool &, bool &);
	 	
	 	//Questo metodo controlla se lo score finale è diventato l'High Score e, in caso positivo, lo sostituisce
	 	bool setHighScore();
};
		
#endif
