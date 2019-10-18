struct constants
{
	//GENERAL
	const int resolutionW = 1024;
	const int resolutionH = 768;
	const float FPS = 60;
	const int lastLevelAvaliable = 6;

	//MENU
	const int manPushingBoxW = resolutionW / 1.002;
	const int manPushingBoxH = resolutionH / 2;
	const float manPushingBoxX = resolutionW / 600;
	const float manPushingBoxY = resolutionH / 2;
	
	const float rotatingBoxW = 0.2;
	const float rotatingBoxH = 0.2;
	const float rotatingBoxX = sokobanTextX + 100;
	const float rotatingBoxY = sokobanTextY + 100;
	
	const int sokobanTextSize = 128;
	const float sokobanTextX = resolutionW / 2;
	const float sokobanTextY = 80;
	const char * sokobanText = "SOKOBAN";
	
	const int highScoreTextSize = 32;
	const float highScoreTextX = resolutionW - border - 160;
	const float highScoreTextY = resolutionH - 40;
	const char * highScoreText = "High Score: ";
	
	const float playButtonX = resolutionW / 2 - 90;
	const float playButtonY = sokobanTextY + 150;
	const int playButtonW = 180;
	const int playButtonH = 82;
	
	const float classicButtonX = playButtonX;
	const float classicButtonY = playButtonY;
	const int classicButtonW = playButtonW;
	const int classicButtonH = playButtonH;
	
	const float timeLimitButtonX = playButtonX;
	const float timeLimitButtonY = playButtonY + 100;
	const int timeLimitButtonW = playButtonW;
	const int timeLimitButtonH = playButtonH;
	
	const float justALevelButtonX = playButtonX;
	const float justALevelButtonY = playButtonY + 200;
	const int justALevelButtonW = playButtonW;
	const int justALevelButtonH = playButtonH;
	
	const int chooseLevelTextSize = 64;
	const float chooseLevelTextX = resolutionW / 2;
	const float chooseLevelTextY = resolutionH / 2 - 100;
	const char * chooseLevelText = "Choose a level to play (use the keyboard)";
	
	const float backButtonX = (resolutionW - border) - 100;
	const float backButtonY = 40;
	const int backButtonW = 64;
	const int backButtonH = 64;
	
	//GAME
	const int border = (resolutionW - resolutionH) / 2;
	
	const int messagesTextSize = 72;
	const float messagesTextX = resolutionW / 2;
	const float messagesTextY = resolutionH / 2;
	const char * levelCompleteText = "LEVEL COMPLETE!";
	const char * newHighScoreText = "NEW HIGH SCORE!";
	const char * youLostText = "YOU LOST!";
	
	const int GUITextSize = 24;
	
	const float audioButtonX = (resolutionW - border) - 75;
	const float audioButtonY = 10;
	const int audioButtonW = 64;
	const int audioButtonH = 64;
	
	const int GUIBackground1W = 160;
	const int GUIBackground1H = 50;
	const float GUIBackground1X = border;
	const float GUIBackground1Y = 0;
	
	const int GUIBackground2W = 165;
	const int GUIBackground2H = 148;
	const float GUIBackground2X = border;
	const float GUIBackground2Y = resolutionH - GUIBackground2H;
	
	const float scoreTextX = border + 55;
	const float scoreTextY = 10;
	const char * scoreText = "Score: ";
		
	const float movesTextX = border + 60;
	const float movesTextY = resolutionH - 55;
	const char * movesText = "Moves: ";
	
	const float timeTextX = movesTextX;
	const float timeTextY = movesTextY - 30;
	const char * timeText = "Time: ";
	
	const float levelTextX = timeTextX;
	const float levelTextY = timeTextY - 30;
	const char * levelText = "LEVEL ";		
	
	const float resetX = (resolutionW - border) - 75;
	const float resetY = resolutionH - 75;
	const float resetW = 64;
	const float resetH = 64;
} constants;
