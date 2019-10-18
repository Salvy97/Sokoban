#include "Classic.h"

Classic::Classic() : GameManager(), score(0), isJustALevel(false) { }

Classic::Classic(int level) : GameManager(level), score(0), isJustALevel(true) { }

bool Classic::levelManager(ALLEGRO_DISPLAY * display)
{	
	if (!resetPressed)	
		setBitmapsAndMusic();

	if (checkForErrors())
		return false;	

	map = generateLevel();
	dimRMap = getCurrentLevelMapRows();
	dimCMap = getCurrentLevelMapColumns();
			
	bitmapsCurrentLevelW = constants.resolutionH / dimRMap;
	bitmapsCurrentLevelH = constants.resolutionH / dimCMap;
	
	player = new Player(score);
	
	for (unsigned i = 0; i < dimRMap; i++)
	{
		for (unsigned j = 0; j < dimCMap; j++)
		{
			if (map[i][j] == 4)
			{
				Box b(calculateXPosition(j, constants.border), calculateYPosition(i), false);
				boxes.push_back(b);
			}
			if (map[i][j] == 6)
			{
				Box b(calculateXPosition(j, constants.border), calculateYPosition(i), true);
				boxes.push_back(b);
				map[i][j] = BOX;
			}
			if (map[i][j] == 5)
			{
				player->setIX(calculateXPosition(j, constants.border));
				player->setX(calculateXPosition(j, constants.border));
				player->setIY(calculateYPosition(i));
				player->setY(calculateYPosition(i));
			}
		}		
	}
	
	al_install_keyboard();
	al_install_mouse();
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_mouse_event_source());
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	
	ALLEGRO_TIMER * timer = al_create_timer(1 / constants.FPS);
	al_start_timer(timer);
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	
	al_play_sample(gameMusic, 2, 0, 1, ALLEGRO_PLAYMODE_LOOP, &gm);
	
	bool levelDone = false;
	bool wasADestination = false;
	bool displayClosed = false;
	isResetPressing = false;	
	isAudioOnPressing = false;
	isAudioOffPressing = false;
	
	audioOn = true;
	
	float seconds = 0;
	
	while (!levelDone)
	{		
		float mouseX, mouseY;
		
		do 
		{
			ALLEGRO_EVENT event;
			al_wait_for_event(eventQueue, &event);
		
			levelDone = true;
			for (unsigned i = 0; i < boxes.size(); i++)
				if (!boxes[i].getIsOnDestination())
					levelDone = false;
					
			if (levelDone)
			{
				score += (player->getMoves() / seconds) * 100;
				player->setScore(score);
				updateGUI(seconds);
				al_draw_text(messagesFont, al_map_rgb(255, 255, 0), constants.messagesTextX, constants.messagesTextY, ALLEGRO_ALIGN_CENTRE, constants.levelCompleteText);
				if (currentLevel == lastLevel)
					if (!isJustALevel)
						if (setHighScore())
							al_draw_text(messagesFont, al_map_rgb(255, 255, 0), constants.messagesTextX, constants.messagesTextY + 100, ALLEGRO_ALIGN_CENTRE, constants.newHighScoreText);
				al_flip_display();			
				al_rest(4);
				currentLevel++;
				boxes.clear();
				delete player;
				al_flush_event_queue(eventQueue);
				al_destroy_timer(timer);
				al_stop_sample(&gm);
				resetPressed = false;
				if (currentLevel > lastLevel)
				{
					returnToMenu = true;
					return true;
				}
			}		
					
			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				displayClosed = true;
				levelDone = true;
			}
			else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				unsigned posI, posJ;
				bool hittedAWall = false;
				for (unsigned i = 0; i < dimRMap; i++)
				{
					for (unsigned j = 0; j < dimCMap; j++)
					{
						if (map[i][j] == PLAYER)
						{
							posI = i;
							posJ = j;
						}
					}
				}
				switch (event.keyboard.keycode)
				{
					case ALLEGRO_KEY_UP:	 player->setDirection(1);
											 collisionManager(posI, posJ, wasADestination, hittedAWall);
											 break;										
					case ALLEGRO_KEY_DOWN:	 player->setDirection(2);
											 collisionManager(posI, posJ, wasADestination, hittedAWall);										 
									  		 break;
					case ALLEGRO_KEY_LEFT:	 player->setDirection(3);
											 collisionManager(posI, posJ, wasADestination, hittedAWall);
								  	  		 break;
					case ALLEGRO_KEY_RIGHT:	 player->setDirection(4);
											 collisionManager(posI, posJ, wasADestination, hittedAWall);
									   		 break;
					case ALLEGRO_KEY_ESCAPE: returnToMenu = true;
											 levelDone = true;
											 boxes.clear();
											 delete player;
				 							 al_flush_event_queue(eventQueue);
											 al_destroy_timer(timer);
											 al_stop_sample(&gm);
											 break;
				}
				if (!hittedAWall && !returnToMenu)
					player->setMoves(player->getMoves() + 1);
			}
			else if (event.type == ALLEGRO_EVENT_TIMER)
				seconds += 1 / constants.FPS;
			else if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
			{
				mouseX = event.mouse.x;
				mouseY = event.mouse.y;
			}
			if (mouseX < constants.resetX + constants.resetW && mouseX > constants.resetX && mouseY < constants.resetY + constants.resetH && mouseY > constants.resetY)
			{
				isResetPressing = true;
				if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1)
				{
					al_stop_sample(&gm);
					resetPressed = true;
					boxes.clear();
					delete player;
					al_flush_event_queue(eventQueue);
					al_destroy_timer(timer);
					levelDone = true;
				}
			}
			else
				isResetPressing = false;
			if (!audioOn)
			{
				if (mouseX < constants.audioButtonX + constants.audioButtonW && mouseX > constants.audioButtonX && mouseY < constants.audioButtonY + constants.audioButtonH && mouseY > constants.audioButtonY)
				{
					isAudioOffPressing = true;
					if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1)
					{
						al_play_sample(gameMusic, 2, 0, 1, ALLEGRO_PLAYMODE_LOOP, &gm);
						audioOn = true;				
					}
				}
				else
					isAudioOffPressing = false;
			}
			else
			{
				if (mouseX < constants.audioButtonX + constants.audioButtonW && mouseX > constants.audioButtonX && mouseY < constants.audioButtonY + constants.audioButtonH && mouseY > constants.audioButtonY)
				{
					isAudioOnPressing = true;
					if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1)
					{
						al_stop_sample(&gm);
						audioOn = false;				
					}
				}
				else
					isAudioOnPressing = false;
			}
			
		} while (!al_is_event_queue_empty(eventQueue));
		
		updateGUI(seconds);
			
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	
	if (!displayClosed && !returnToMenu)
		levelManager(display);
	else
		return true;
}

void Classic::updateGUI(float GUITimer)
{
	for (unsigned i = 0; i < dimCMap; i++)
	{
		for (unsigned j = 0; j < dimRMap; j++)
		{
			switch (map[i][j])
			{
				case 0: al_draw_scaled_bitmap(treesBitmap, 0, 0, al_get_bitmap_width(treesBitmap), al_get_bitmap_height(treesBitmap), calculateXPosition(j, constants.border), calculateYPosition(i), bitmapsCurrentLevelW, bitmapsCurrentLevelH, 0);
						break;
				case 1: al_draw_scaled_bitmap(wall, 0, 0, al_get_bitmap_width(wall), al_get_bitmap_height(wall), calculateXPosition(j, constants.border), calculateYPosition(i), bitmapsCurrentLevelW, bitmapsCurrentLevelH, 0);
						break;
				case 2: al_draw_scaled_bitmap(floor, 0, 0, al_get_bitmap_width(floor), al_get_bitmap_height(floor), calculateXPosition(j, constants.border), calculateYPosition(i), bitmapsCurrentLevelW, bitmapsCurrentLevelH, 0);
						break;
				case 3: al_draw_scaled_bitmap(floorDestination, 0, 0, al_get_bitmap_width(floorDestination), al_get_bitmap_height(floorDestination), calculateXPosition(j, constants.border), calculateYPosition(i), bitmapsCurrentLevelW, bitmapsCurrentLevelH, 0);
						break;
				case 4: al_draw_scaled_bitmap(floor, 0, 0, al_get_bitmap_width(floor), al_get_bitmap_height(floor), calculateXPosition(j, constants.border), calculateYPosition(i), bitmapsCurrentLevelW, bitmapsCurrentLevelH, 0);
						break;
				case 5: al_draw_scaled_bitmap(floor, 0, 0, al_get_bitmap_width(floor), al_get_bitmap_height(floor), calculateXPosition(j, constants.border), calculateYPosition(i), bitmapsCurrentLevelW, bitmapsCurrentLevelH, 0);
						break;
			}
		}
	}
	
	for (unsigned i = 0; i < boxes.size(); i++)
	{
		if (!boxes[i].getIsOnDestination())
			al_draw_scaled_bitmap(boxNotOnDestination, 0, 0, al_get_bitmap_width(boxNotOnDestination), al_get_bitmap_height(boxNotOnDestination), boxes[i].getX(), boxes[i].getY(), bitmapsCurrentLevelW, bitmapsCurrentLevelH, 0);
		else
			al_draw_scaled_bitmap(boxOnDestination, 0, 0, al_get_bitmap_width(boxOnDestination), al_get_bitmap_height(boxOnDestination), boxes[i].getX(), boxes[i].getY(), bitmapsCurrentLevelW, bitmapsCurrentLevelH, 0);
	}
	
	switch (player->getDirection())
	{
		case 1:	al_draw_scaled_bitmap(playerUp, 0, 0, al_get_bitmap_width(playerUp), al_get_bitmap_height(playerUp), player->getX(), player->getY(), bitmapsCurrentLevelW, bitmapsCurrentLevelH, 0);
				break;
		case 2:	al_draw_scaled_bitmap(playerDown, 0, 0, al_get_bitmap_width(playerDown), al_get_bitmap_height(playerDown), player->getX(), player->getY(), bitmapsCurrentLevelW, bitmapsCurrentLevelH, 0);
				break;
		case 3:	al_draw_scaled_bitmap(playerLeft, 0, 0, al_get_bitmap_width(playerLeft), al_get_bitmap_height(playerLeft), player->getX(), player->getY(), bitmapsCurrentLevelW, bitmapsCurrentLevelH, 0);
				break;
		case 4:	al_draw_scaled_bitmap(playerRight, 0, 0, al_get_bitmap_width(playerRight), al_get_bitmap_height(playerRight), player->getX(), player->getY(), bitmapsCurrentLevelW, bitmapsCurrentLevelH, 0);
				break;				
	}
	
	if (audioOn)
	{
		if (!isAudioOnPressing)
			al_draw_scaled_bitmap(audioOnNotPressing, 0, 0, al_get_bitmap_width(audioOnNotPressing), al_get_bitmap_height(audioOnNotPressing), constants.audioButtonX, constants.audioButtonY, constants.audioButtonW, constants.audioButtonH, 0);
		else
			al_draw_scaled_bitmap(audioOnPressing, 0, 0, al_get_bitmap_width(audioOnPressing), al_get_bitmap_height(audioOnPressing), constants.audioButtonX, constants.audioButtonY, constants.audioButtonW, constants.audioButtonH, 0);
	}
	else
	{
		if (!isAudioOffPressing)
			al_draw_scaled_bitmap(audioOffNotPressing, 0, 0, al_get_bitmap_width(audioOffNotPressing), al_get_bitmap_height(audioOffNotPressing), constants.audioButtonX, constants.audioButtonY, constants.audioButtonW, constants.audioButtonH, 0);
		else
			al_draw_scaled_bitmap(audioOffPressing, 0, 0, al_get_bitmap_width(audioOffPressing), al_get_bitmap_height(audioOffPressing), constants.audioButtonX, constants.audioButtonY, constants.audioButtonW, constants.audioButtonH, 0);
	}
		
	al_draw_scaled_bitmap(GUIBackground, 0, 0, al_get_bitmap_width(GUIBackground), al_get_bitmap_height(GUIBackground), constants.GUIBackground1X, constants.GUIBackground1Y, constants.GUIBackground1W, constants.GUIBackground1H, 0);	
		
	al_draw_text(GUIFont, al_map_rgb(255, 255, 0), constants.scoreTextX, constants.scoreTextY, ALLEGRO_ALIGN_CENTRE, constants.scoreText);
	al_draw_textf(GUIFont, al_map_rgb(255, 0, 0), constants.scoreTextX + 60, constants.scoreTextY, ALLEGRO_ALIGN_CENTRE, "%i", player->getScore());
	
	al_draw_scaled_bitmap(GUIBackground, 0, 0, al_get_bitmap_width(GUIBackground), al_get_bitmap_height(GUIBackground), constants.GUIBackground2X, constants.GUIBackground2Y, constants.GUIBackground2W, constants.GUIBackground2H, 0);
	
	al_draw_text(GUIFont, al_map_rgb(255, 255, 0), constants.levelTextX, constants.levelTextY, ALLEGRO_ALIGN_CENTRE, constants.levelText);
	al_draw_textf(GUIFont, al_map_rgb(255, 255, 0), constants.levelTextX + 60, constants.levelTextY, ALLEGRO_ALIGN_CENTRE, "%i", currentLevel);
	
	al_draw_text(GUIFont, al_map_rgb(255, 255, 0), constants.timeTextX, constants.timeTextY, ALLEGRO_ALIGN_CENTRE, constants.timeText);
	al_draw_textf(GUIFont, al_map_rgb(255, 255, 0), constants.timeTextX + 60, constants.timeTextY, ALLEGRO_ALIGN_CENTRE, "%i", (unsigned)GUITimer);
	
	al_draw_text(GUIFont, al_map_rgb(255, 255, 0), constants.movesTextX, constants.movesTextY, ALLEGRO_ALIGN_CENTRE, constants.movesText);
	al_draw_textf(GUIFont, al_map_rgb(255, 255, 0), constants.movesTextX + 60, constants.movesTextY, ALLEGRO_ALIGN_CENTRE, "%i", player->getMoves());
	
	if (!isResetPressing)
		al_draw_scaled_bitmap(resetNotPressing, 0, 0, al_get_bitmap_width(resetNotPressing), al_get_bitmap_height(resetNotPressing), constants.resetX, constants.resetY, constants.resetW, constants.resetH, 0);
	else
		al_draw_scaled_bitmap(resetPressing, 0, 0, al_get_bitmap_width(resetPressing), al_get_bitmap_height(resetPressing), constants.resetX, constants.resetY, constants.resetW, constants.resetH, 0);
}

Classic::~Classic() 
{
	al_destroy_event_queue(eventQueue);
	al_destroy_font(messagesFont);
	al_destroy_font(GUIFont);
	al_destroy_bitmap(treesBitmap);
	al_destroy_bitmap(wall);
	al_destroy_bitmap(floor);
	al_destroy_bitmap(floorDestination);
	al_destroy_bitmap(playerDown);
	al_destroy_bitmap(boxNotOnDestination);
	al_destroy_bitmap(resetNotPressing);
	al_destroy_bitmap(resetPressing);
	al_destroy_sample(gameMusic);
	al_destroy_sample(footsteps);
	al_destroy_sample(movingBox);
	al_destroy_bitmap(audioOnNotPressing);
	al_destroy_bitmap(audioOnPressing);
	al_destroy_bitmap(audioOffNotPressing);
	al_destroy_bitmap(audioOffPressing);
}
