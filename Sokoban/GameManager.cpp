#include "GameManager.h"

GameManager::GameManager() : currentLevel(1), lastLevel(constants.lastLevelAvaliable), resetPressed(false), returnToMenu(false)
{	 	
	al_set_new_bitmap_flags(ALLEGRO_MIPMAP);										
	treesBitmap = al_load_bitmap("Bitmaps/Game/trees.png");
	playerUp = al_load_bitmap("Bitmaps/Game/playerUp.png");
	playerDown = al_load_bitmap("Bitmaps/Game/playerDown.png");
	playerLeft = al_load_bitmap("Bitmaps/Game/playerLeft.png");
	playerRight = al_load_bitmap("Bitmaps/Game/playerRight.png");
	boxNotOnDestination = al_load_bitmap("Bitmaps/Game/box.png");
	boxOnDestination = al_load_bitmap("Bitmaps/Game/boxOnDestination.png");
	GUIBackground = al_load_bitmap("Bitmaps/Game/GUIBackground.png");
	audioOnNotPressing = al_load_bitmap("Bitmaps/Game/audioOnNotPressing.png");
	audioOnPressing = al_load_bitmap("Bitmaps/Game/audioOnPressing.png");
	audioOffNotPressing = al_load_bitmap("Bitmaps/Game/audioOffNotPressing.png");
	audioOffPressing = al_load_bitmap("Bitmaps/Game/audioOffPressing.png");
	resetNotPressing = al_load_bitmap("Bitmaps/Game/resetNotPressing.png");
	resetPressing = al_load_bitmap("Bitmaps/Game/resetPressing.png");
	
	messagesFont = al_load_font("Fonts/messagesFont.otf", constants.messagesTextSize, 0);
	GUIFont = al_load_font("Fonts/GUIFont.otf", constants.GUITextSize, 0);
	
	eventQueue = al_create_event_queue();
	
	footsteps = al_load_sample("Audio/footsteps.ogg");
	movingBox = al_load_sample("Audio/movingBox.ogg");
}

GameManager::GameManager(int _currentLevel) : currentLevel(_currentLevel), lastLevel(_currentLevel), resetPressed(false), returnToMenu(false)
{
	al_set_new_bitmap_flags(ALLEGRO_MIPMAP);										
	treesBitmap = al_load_bitmap("Bitmaps/Game/trees.png");
	playerUp = al_load_bitmap("Bitmaps/Game/playerUp.png");
	playerDown = al_load_bitmap("Bitmaps/Game/playerDown.png");
	playerLeft = al_load_bitmap("Bitmaps/Game/playerLeft.png");
	playerRight = al_load_bitmap("Bitmaps/Game/playerRight.png");
	boxNotOnDestination = al_load_bitmap("Bitmaps/Game/box.png");
	boxOnDestination = al_load_bitmap("Bitmaps/Game/boxOnDestination.png");
	GUIBackground = al_load_bitmap("Bitmaps/Game/GUIBackground.png");
	audioOnNotPressing = al_load_bitmap("Bitmaps/Game/audioOnNotPressing.png");
	audioOnPressing = al_load_bitmap("Bitmaps/Game/audioOnPressing.png");
	audioOffNotPressing = al_load_bitmap("Bitmaps/Game/audioOffNotPressing.png");
	audioOffPressing = al_load_bitmap("Bitmaps/Game/audioOffPressing.png");
	resetNotPressing = al_load_bitmap("Bitmaps/Game/resetNotPressing.png");
	resetPressing = al_load_bitmap("Bitmaps/Game/resetPressing.png");
	
	messagesFont = al_load_font("Fonts/messagesFont.otf", constants.messagesTextSize, 0);
	GUIFont = al_load_font("Fonts/GUIFont.otf", constants.GUITextSize, 0);
	
	eventQueue = al_create_event_queue();
	
	footsteps = al_load_sample("Audio/footsteps.ogg");
	movingBox = al_load_sample("Audio/movingBox.ogg");
}

void GameManager::setCurrentLevel(unsigned _currentLevel) { currentLevel = _currentLevel; }

void GameManager::setLastLevel(unsigned _lastLevel) { lastLevel = _lastLevel; }

unsigned GameManager::getCurrentLevel() const { return currentLevel; }

unsigned GameManager::getLastLevel() const { return lastLevel; }

bool GameManager::getReturnToMenu() const { return returnToMenu; }

unsigned GameManager::getCurrentLevelMapRows()
{
	ifstream mapFile;
	mapFile.open("Levels/level" + to_string(currentLevel) + "Map.txt");
	string dimR;
	unsigned dimRMap = 0;
	if (mapFile.is_open())
		while (getline(mapFile, dimR))
			dimRMap++;
	mapFile.close();
	return dimRMap;
}

unsigned GameManager::getCurrentLevelMapColumns()
{
	ifstream mapFile;
	mapFile.open("Levels/level" + to_string(currentLevel) + "Map.txt");
	string dimR;
	unsigned dimCMap = 0;
	if (mapFile.is_open())
	{
		getline(mapFile, dimR);
		dimCMap = dimR.size();
	}
	mapFile.close();
	dimCMap = (dimCMap + 1) / 2;
	return dimCMap;
}

vector<vector<Type>> GameManager::generateLevel()
{
	unsigned dimRMap = getCurrentLevelMapRows();
	unsigned dimCMap = getCurrentLevelMapColumns();
	vector<vector<Type>> map(dimRMap, vector<Type>(dimCMap));
	int object;
	unsigned actualI = 0, actualJ = 0;
	ifstream mapFile;
	mapFile.open("Levels/level" + to_string(currentLevel) + "Map.txt");
	if (mapFile.is_open())
	{
		while (mapFile >> object)
		{
			switch (object)
			{
				case 0: map[actualI][actualJ] = TREES;
						break;
				case 1: map[actualI][actualJ] = WALL;
						break;
				case 2: map[actualI][actualJ] = FLOOR;
						break;
				case 3: map[actualI][actualJ] = FLOOR_DESTINATION;
						break;
				case 4: map[actualI][actualJ] = BOX;
						break;
				case 5: map[actualI][actualJ] = PLAYER;
						break;
				case 6: map[actualI][actualJ] = BOX_ON_DESTINATION;
						break;	
			}
			actualJ++;
			if (actualJ == dimCMap)
			{
				actualI++;
				actualJ = 0;
			}
		}
	}
	mapFile.close();
	return map;
}

void GameManager::setBitmapsAndMusic()
{
	random_device rd;
	mt19937 e2(rd());
	uniform_int_distribution<unsigned> range1(1, 2);
	unsigned choice = range1(e2);
	
	wall = al_load_bitmap(("Bitmaps/Game/wall" + to_string(choice) + ".png").c_str());
	floor = al_load_bitmap(("Bitmaps/Game/floor" + to_string(choice) + ".png").c_str());
	floorDestination = al_load_bitmap(("Bitmaps/Game/floor" + to_string(choice) + "Destination.png").c_str());
	
	uniform_int_distribution<unsigned> range2(1, 4);
	choice = range2(e2);
	
	gameMusic = al_load_sample(("Audio/gameMusic" + to_string(choice) + ".ogg").c_str());
}

bool GameManager::checkForErrors()
{
	bool error = false;	
	
	if (!wall || !floor || !floorDestination || !playerUp || !playerDown || !playerLeft || !playerRight || !boxNotOnDestination || !boxOnDestination || !GUIBackground || !messagesFont || !GUIFont || !resetNotPressing || !resetPressing || !gameMusic || !footsteps || !movingBox || !audioOnNotPressing || !audioOnPressing || !audioOffNotPressing || !audioOffPressing)
		error = true;
		
	if (!wall)
		cout<<"Failed to initialize wall bitmap!"<<endl;
	if (!floor)
		cout<<"Failed to initialize floor bitmap!"<<endl;
	if (!floorDestination)
		cout<<"Failed to initialize floor_destination bitmap!"<<endl;
	if (!playerUp)
		cout<<"Failed to initialize player_up bitmap!"<<endl;
	if (!playerDown)
		cout<<"Failed to initialize player_down bitmap!"<<endl;
	if (!playerLeft)
		cout<<"Failed to initialize player_left bitmap!"<<endl;
	if (!playerRight)
		cout<<"Failed to initialize player_right bitmap!"<<endl;
	if (!boxOnDestination)
		cout<<"Failed to initialize box_on_destination bitmap!"<<endl;
	if (!GUIBackground)
		cout<<"Failed to initialize GUI_background bitmap!"<<endl;
	if (!messagesFont)
		cout<<"Failed to initialize messages_font font!"<<endl;
	if (!GUIFont)
		cout<<"Failed to initialize GUI_font bitmap!"<<endl;
	if (!resetNotPressing)
		cout<<"Failed to initialize reset_not_pressing bitmap!"<<endl;
	if (!resetPressing)
		cout<<"Failed to initialize reset_pressing bitmap!"<<endl;
	if (!gameMusic)
		cout<<"Failed to initialize game_music audio!"<<endl;
	if (!footsteps)
		cout<<"Failed to initialize footsteps audio!"<<endl;
	if (!movingBox)
		cout<<"Failed to initialize moving_box audio!"<<endl;
	if (!audioOnNotPressing)
		cout<<"Failed to initialize audio_on_not_pressing bitmap!"<<endl;
	if (!audioOnPressing)
		cout<<"Failed to initialize audio_on_pressing bitmap!"<<endl;
	if (!audioOffNotPressing)
		cout<<"Failed to initialize audio_off_not_pressing bitmap!"<<endl;
	if (!audioOffPressing)
		cout<<"Failed to initialize audio_off_pressing bitmap!"<<endl;
		
	return error;
}

float GameManager::calculateXPosition(unsigned pos, int border)
{
	return ((constants.resolutionW - (constants.border * 2)) / getCurrentLevelMapRows()) * pos + constants.border;
}

float GameManager::calculateYPosition(unsigned pos)
{
	return (constants.resolutionH / getCurrentLevelMapColumns()) * pos;
}

void GameManager::collisionManager(const unsigned &posI, const unsigned &posJ, bool &wasADestination, bool &hittedAWall)
{
	if (player->getDirection() == 1)
	{
		if (map[posI - 1][posJ] == FLOOR)
		{	  
			player->setY(player->getY() - bitmapsCurrentLevelW);
			if (wasADestination)
				map[posI][posJ] = FLOOR_DESTINATION;
			else
				map[posI][posJ] = FLOOR;
			map[posI - 1][posJ] = PLAYER;
	    	wasADestination = false;
	    	al_play_sample(footsteps, 16, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
		else if (map[posI - 1][posJ] == FLOOR_DESTINATION)
		{    
			player->setY(player->getY() - bitmapsCurrentLevelW);
			if (wasADestination)
				map[posI][posJ] = FLOOR_DESTINATION;
	   	 	else
				map[posI][posJ] = FLOOR;
			map[posI - 1][posJ] = PLAYER;
			wasADestination = true;
			al_play_sample(footsteps, 16, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
    	else if (map[posI - 1][posJ] == BOX)
		{
			unsigned boxPos;    
			for (unsigned i = 0; i < boxes.size(); i++)
			{
				if (boxes[i].getX() == calculateXPosition(posJ, constants.border) && boxes[i].getY() == calculateYPosition(posI - 1))
				{
					boxPos = i;
					break;
				}
			}
			if (map[posI - 2][posJ] == FLOOR)
			{
				bool boxWasOnADestination = boxes[boxPos].getIsOnDestination();
				boxes[boxPos].setIsOnDestination(false);
				boxes[boxPos].setY(boxes[boxPos].getY() - bitmapsCurrentLevelW);
				player->setY(player->getY() - bitmapsCurrentLevelW);
				map[posI - 2][posJ] = BOX;
				map[posI - 1][posJ] = PLAYER;
				if (wasADestination)
					map[posI][posJ] = FLOOR_DESTINATION;
				else
					map[posI][posJ] = FLOOR;
				wasADestination = boxWasOnADestination;
				al_play_sample(movingBox, 16, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
			else if (map[posI - 2][posJ] == FLOOR_DESTINATION)
			{
				bool boxWasOnADestination = boxes[boxPos].getIsOnDestination();
				boxes[boxPos].setY(boxes[boxPos].getY() - bitmapsCurrentLevelW);
				boxes[boxPos].setIsOnDestination(true);
				player->setY(player->getY() - bitmapsCurrentLevelW);
				map[posI - 2][posJ] = BOX;
				map[posI - 1][posJ] = PLAYER;
				if (wasADestination)
					map[posI][posJ] = FLOOR_DESTINATION;
				else
					map[posI][posJ] = FLOOR;
				wasADestination = boxWasOnADestination;
				al_play_sample(movingBox, 16, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
			else if (map[posI - 2][posJ] == WALL || map[posI - 2][posJ] == BOX)
				hittedAWall = true;
		}
		else if (map[posI - 1][posJ] == WALL)
			hittedAWall = true;
	}
	else if (player->getDirection() == 2)
	{
		if (map[posI + 1][posJ] == FLOOR)
		{	  
			player->setY(player->getY() + bitmapsCurrentLevelW);
			if (wasADestination)
				map[posI][posJ] = FLOOR_DESTINATION;
			else
				map[posI][posJ] = FLOOR;
			map[posI + 1][posJ] = PLAYER;
	    	wasADestination = false;
	    	al_play_sample(footsteps, 16, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
		else if (map[posI + 1][posJ] == FLOOR_DESTINATION)
		{    
			player->setY(player->getY() + bitmapsCurrentLevelW);
			if (wasADestination)
				map[posI][posJ] = FLOOR_DESTINATION;
	   	 	else
				map[posI][posJ] = FLOOR;
			map[posI + 1][posJ] = PLAYER;
			wasADestination = true;
			al_play_sample(footsteps, 16, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
    	else if (map[posI + 1][posJ] == BOX)
		{
			unsigned boxPos;    
			for (unsigned i = 0; i < boxes.size(); i++)
			{
				if (boxes[i].getX() == calculateXPosition(posJ, constants.border) && boxes[i].getY() == calculateYPosition(posI + 1))
				{
					boxPos = i;
					break;
				}
			}
			if (map[posI + 2][posJ] == FLOOR)
			{
				bool boxWasOnADestination = boxes[boxPos].getIsOnDestination();
				boxes[boxPos].setIsOnDestination(false);
				boxes[boxPos].setY(boxes[boxPos].getY() + bitmapsCurrentLevelW);
				player->setY(player->getY() + bitmapsCurrentLevelW);
				map[posI + 2][posJ] = BOX;
				map[posI + 1][posJ] = PLAYER;
				if (wasADestination)
					map[posI][posJ] = FLOOR_DESTINATION;
				else
					map[posI][posJ] = FLOOR;
				wasADestination = boxWasOnADestination;
				al_play_sample(movingBox, 16, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
			else if (map[posI + 2][posJ] == FLOOR_DESTINATION)
			{
				bool boxWasOnADestination = boxes[boxPos].getIsOnDestination();
				boxes[boxPos].setY(boxes[boxPos].getY() + bitmapsCurrentLevelW);
				boxes[boxPos].setIsOnDestination(true);
				player->setY(player->getY() + bitmapsCurrentLevelW);
				map[posI + 2][posJ] = BOX;
				map[posI + 1][posJ] = PLAYER;
				if (wasADestination)
					map[posI][posJ] = FLOOR_DESTINATION;
				else
					map[posI][posJ] = FLOOR;
				wasADestination = boxWasOnADestination;
				al_play_sample(movingBox, 16, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
			else if (map[posI + 2][posJ] == WALL || map[posI + 2][posJ] == BOX)
				hittedAWall = true;
		}
		else if (map[posI + 1][posJ] == WALL)
			hittedAWall = true;
	}
	else if (player->getDirection() == 3)
	{
		if (map[posI][posJ - 1] == FLOOR)
		{	  
			player->setX(player->getX() - bitmapsCurrentLevelW);
			if (wasADestination)
				map[posI][posJ] = FLOOR_DESTINATION;
			else
				map[posI][posJ] = FLOOR;
			map[posI][posJ - 1] = PLAYER;
	    	wasADestination = false;
	    	al_play_sample(footsteps, 16, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
		else if (map[posI][posJ - 1] == FLOOR_DESTINATION)
		{    
			player->setX(player->getX() - bitmapsCurrentLevelW);
			if (wasADestination)
				map[posI][posJ] = FLOOR_DESTINATION;
	   	 	else
				map[posI][posJ] = FLOOR;
			map[posI][posJ - 1] = PLAYER;
			wasADestination = true;
			al_play_sample(footsteps, 16, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
    	else if (map[posI][posJ - 1] == BOX)
		{
			unsigned boxPos;    
			for (unsigned i = 0; i < boxes.size(); i++)
			{
				if (boxes[i].getX() == calculateXPosition(posJ - 1, constants.border) && boxes[i].getY() == calculateYPosition(posI))
				{
					boxPos = i;
					break;
				}
			}
			if (map[posI][posJ - 2] == FLOOR)
			{
				bool boxWasOnADestination = boxes[boxPos].getIsOnDestination();
				boxes[boxPos].setIsOnDestination(false);
				boxes[boxPos].setX(boxes[boxPos].getX() - bitmapsCurrentLevelW);
				player->setX(player->getX() - bitmapsCurrentLevelW);
				map[posI][posJ - 2] = BOX;
				map[posI][posJ - 1] = PLAYER;
				if (wasADestination)
					map[posI][posJ] = FLOOR_DESTINATION;
				else
					map[posI][posJ] = FLOOR;
				wasADestination = boxWasOnADestination;
				al_play_sample(movingBox, 16, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
			else if (map[posI][posJ - 2] == FLOOR_DESTINATION)
			{
				bool boxWasOnADestination = boxes[boxPos].getIsOnDestination();
				boxes[boxPos].setX(boxes[boxPos].getX() - bitmapsCurrentLevelW);
				boxes[boxPos].setIsOnDestination(true);
				player->setX(player->getX() - bitmapsCurrentLevelW);
				map[posI][posJ - 2] = BOX;
				map[posI][posJ - 1] = PLAYER;
				if (wasADestination)
					map[posI][posJ] = FLOOR_DESTINATION;
				else
					map[posI][posJ] = FLOOR;
				wasADestination = boxWasOnADestination;
				al_play_sample(movingBox, 16, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
			else if (map[posI][posJ - 2] == WALL || map[posI][posJ - 2] == BOX)
				hittedAWall = true;
		}
		else if (map[posI][posJ - 1] == WALL)
			hittedAWall = true;
	}
	else if (player->getDirection() == 4)
	{
		if (map[posI][posJ + 1] == FLOOR)
		{	  
			player->setX(player->getX() + bitmapsCurrentLevelW);
			if (wasADestination)
				map[posI][posJ] = FLOOR_DESTINATION;
			else
				map[posI][posJ] = FLOOR;
			map[posI][posJ + 1] = PLAYER;
	    	wasADestination = false;
	    	al_play_sample(footsteps, 16, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
		else if (map[posI][posJ + 1] == FLOOR_DESTINATION)
		{    
			player->setX(player->getX() + bitmapsCurrentLevelW);
			if (wasADestination)
				map[posI][posJ] = FLOOR_DESTINATION;
	   	 	else
				map[posI][posJ] = FLOOR;
			map[posI][posJ + 1] = PLAYER;
			wasADestination = true;
			al_play_sample(footsteps, 16, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
    	else if (map[posI][posJ + 1] == BOX)
		{
			unsigned boxPos;    
			for (unsigned i = 0; i < boxes.size(); i++)
			{
				if (boxes[i].getX() == calculateXPosition(posJ + 1, constants.border) && boxes[i].getY() == calculateYPosition(posI))
				{
					boxPos = i;
					break;
				}
			}
			if (map[posI][posJ + 2] == FLOOR)
			{
				bool boxWasOnADestination = boxes[boxPos].getIsOnDestination();
				boxes[boxPos].setIsOnDestination(false);
				boxes[boxPos].setX(boxes[boxPos].getX() + bitmapsCurrentLevelW);
				player->setX(player->getX() + bitmapsCurrentLevelW);
				map[posI][posJ + 2] = BOX;
				map[posI][posJ + 1] = PLAYER;
				if (wasADestination)
					map[posI][posJ] = FLOOR_DESTINATION;
				else
					map[posI][posJ] = FLOOR;
				wasADestination = boxWasOnADestination;
				al_play_sample(movingBox, 16, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
			else if (map[posI][posJ + 2] == FLOOR_DESTINATION)
			{
				bool boxWasOnADestination = boxes[boxPos].getIsOnDestination();
				boxes[boxPos].setX(boxes[boxPos].getX() + bitmapsCurrentLevelW);
				boxes[boxPos].setIsOnDestination(true);
				player->setX(player->getX() + bitmapsCurrentLevelW);
				map[posI][posJ + 2] = BOX;
				map[posI][posJ + 1] = PLAYER;
				if (wasADestination)
					map[posI][posJ] = FLOOR_DESTINATION;
				else
					map[posI][posJ] = FLOOR;
				wasADestination = boxWasOnADestination;
				al_play_sample(movingBox, 16, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
			else if (map[posI][posJ + 2] == WALL || map[posI][posJ + 2] == BOX)
				hittedAWall = true;
		}
		else if (map[posI][posJ + 1] == WALL)
			hittedAWall = true;
	}
}

/*void GameManager::collisionManager(const unsigned &posI, const unsigned &posJ, bool &wasADestination, bool &hittedAWall)
{
	unsigned IValue1, IValue2, JValue1, JValue2;
	switch (player->getDirection())
	{
		case 1: IValue1 = posI - 1;
				IValue2 = posI - 2;
				JValue1 = posJ;
				JValue2 = posJ;
				break;
		case 2: IValue1 = posI + 1;
				IValue2 = posI + 2;
				JValue1 = posJ;
				JValue2 = posJ;
				break;
		case 3: IValue1 = posI;
				IValue2 = posI;
				JValue1 = posJ - 1;
				JValue2 = posJ - 2;
				break;
		case 4: IValue1 = posI;
				IValue2 = posI;
				JValue1 = posJ + 1;
				JValue2 = posJ + 2;
				break;
	}

	if (map[IValue1][JValue1] == FLOOR)
	{	  
		player->setY(player->getY() - bitmapsCurrentLevelW);
		if (wasADestination)
			map[IValue1][JValue1] = FLOOR_DESTINATION;
		else
			map[IValue1][JValue1] = FLOOR;
		map[IValue1][JValue1] = PLAYER;
	    wasADestination = false;
	    al_play_sample(footsteps, 16, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
	else if (map[IValue1][JValue1] == FLOOR_DESTINATION)
	{    
		player->setY(player->getY() - bitmapsCurrentLevelW);
		if (wasADestination)
			map[IValue1][JValue1] = FLOOR_DESTINATION;
	   	 else
			map[IValue1][JValue1] = FLOOR;
		map[IValue1][JValue1] = PLAYER;
		wasADestination = true;
		al_play_sample(footsteps, 16, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
    else if (map[IValue2][JValue2] == BOX)
	{
		unsigned boxPos;    
		for (unsigned i = 0; i < boxes.size(); i++)
		{
			if (boxes[i].getX() == calculateXPosition(JValue1, constants.border) && boxes[i].getY() == calculateYPosition(IValue1))
			{
				boxPos = i;
				break;
			}
		}
		if (map[IValue2][JValue2] == FLOOR)
		{
			bool boxWasOnADestination = boxes[boxPos].getIsOnDestination();
			boxes[boxPos].setIsOnDestination(false);
			boxes[boxPos].setY(boxes[boxPos].getY() - bitmapsCurrentLevelW);
			player->setY(player->getY() - bitmapsCurrentLevelW);
			map[IValue2][JValue2] = BOX;
			map[IValue1][JValue1] = PLAYER;
			if (wasADestination)
				map[IValue1][JValue1] = FLOOR_DESTINATION;
			else
				map[IValue1][JValue1] = FLOOR;
			wasADestination = boxWasOnADestination;
			al_play_sample(movingBox, 16, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
		else if (map[IValue2][JValue2] == FLOOR_DESTINATION)
		{
			bool boxWasOnADestination = boxes[boxPos].getIsOnDestination();
			boxes[boxPos].setY(boxes[boxPos].getY() - bitmapsCurrentLevelW);
			boxes[boxPos].setIsOnDestination(true);
			player->setY(player->getY() - bitmapsCurrentLevelW);
			map[IValue2][JValue2] = BOX;
			map[IValue1][JValue1] = PLAYER;
			if (wasADestination)
				map[IValue1][JValue1] = FLOOR_DESTINATION;
			else
				map[IValue1][JValue1] = FLOOR;
			wasADestination = boxWasOnADestination;
			al_play_sample(movingBox, 16, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
		else if (map[IValue2][JValue2] == WALL || map[IValue2][JValue2] == BOX)
			hittedAWall = true;
	}
	else if (map[IValue1][JValue1] == WALL)
		hittedAWall = true;
}*/

bool GameManager::setHighScore()
{
	fstream highScoreFile;
	highScoreFile.open("HighScore.txt");
	int highScore;
	if (highScoreFile.is_open())
	{
		while (highScoreFile >> highScore)
		{
			if (player->getScore() > highScore)
			{
				highScoreFile.close();
				highScoreFile.open("HighScore.txt", fstream::out | fstream::trunc);
				highScoreFile.close();
				highScoreFile.open("HighScore.txt");
				highScoreFile << player->getScore();	
			}
			else
				return false;
		}	
	}
	highScoreFile.close();
	return true;
}
