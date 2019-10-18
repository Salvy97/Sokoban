#include "Menu.h"

Menu::Menu() : playButtonPressed(false), justALevelButtonPressed(false)
{
	ALLEGRO_COLOR backgroundColor1 = al_map_rgb(13, 58, 0);
	ALLEGRO_COLOR backgroundColor2 = al_map_rgb(157, 1, 9);
	ALLEGRO_COLOR backgroundColor3 = al_map_rgb(255, 200, 0);
	
	random_device rd;
	mt19937 e2(rd());
	uniform_int_distribution<unsigned> dist(1, 3);
	
	unsigned backgroundChoice = dist(e2);
	
	switch (backgroundChoice)
	{
		case 1: backgroundColor = backgroundColor1;
				break;
		case 2: backgroundColor = backgroundColor2;
				break;			
		case 3: backgroundColor = backgroundColor3;
				break;
	}
	
	rotatingBox = al_load_bitmap("Bitmaps/Game/box.png");	
	manPushingBox = al_load_bitmap("Bitmaps/Menu/manPushingBox.png");
	playNotPressing = al_load_bitmap("Bitmaps/Menu/playNotPressing.png");
	playPressing = al_load_bitmap("Bitmaps/Menu/playPressing.png");
	classicNotPressing = al_load_bitmap("Bitmaps/Menu/classicNotPressing.png");
	classicPressing = al_load_bitmap("Bitmaps/Menu/classicPressing.png");
	timeLimitNotPressing = al_load_bitmap("Bitmaps/Menu/timeLimitNotPressing.png");
	timeLimitPressing = al_load_bitmap("Bitmaps/Menu/timeLimitPressing.png");
	backNotPressing = al_load_bitmap("Bitmaps/Menu/backNotPressing.png");
	backPressing = al_load_bitmap("Bitmaps/Menu/backPressing.png");
	justALevelNotPressing = al_load_bitmap("Bitmaps/Menu/justALevelNotPressing.png");
	justALevelPressing = al_load_bitmap("Bitmaps/Menu/justALevelPressing.png");
	
	sokobanTextFont = al_load_font("Fonts/sokoban.ttf", constants.sokobanTextSize, 0);
	highScoreTextFont = al_load_font("Fonts/GUIFont.otf", constants.highScoreTextSize, 0);
	chooseLevelTextFont = highScoreTextFont;
	
	sokobanTextColor = al_map_rgb(0, 17, 255);
	highScoreTextColor = al_map_rgb(255, 255, 0);
	chooseLevelTextColor = al_map_rgb(255, 255, 0);
	
	boxRotationSpeed = 0.003;
	
	eventQueue = al_create_event_queue();
	
	timer = al_create_timer(1 / constants.FPS);
	
	menuTheme = al_load_sample("Audio/menuTheme.ogg");
	buttonClick = al_load_sample("Audio/buttonClick.ogg");
}

void Menu::setLevelChosen(int _levelChosen) { levelChosen = _levelChosen; }

int Menu::getLevelChosen() const { return levelChosen; }

int Menu::checkForErrors()
{
	bool error = false;

	if (!rotatingBox || !manPushingBox || !playNotPressing || !playPressing || !sokobanTextFont || !eventQueue || !timer || !classicNotPressing || !classicPressing || !timeLimitNotPressing || !timeLimitPressing || !menuTheme || !justALevelNotPressing || !justALevelPressing)
		error = true;
		
	if (!rotatingBox)
		cout<<"Failed to initialize rotating_box bitmap!"<<endl;
	if (!manPushingBox)
		cout<<"Failed to initialize man_pushing_box bitmap!"<<endl;
	if (!playNotPressing)
		cout<<"Failed to initialize play_not_pressing bitmap!"<<endl;
	if (!playPressing)
		cout<<"Failed to initialize play_pressing bitmap!"<<endl;
	if (!sokobanTextFont)
		cout<<"Failed to initialize sokoban_text font!"<<endl;
	if (!eventQueue)
		cout<<"Failed to initialize event_queue!"<<endl;
	if (!timer)
		cout<<"Failed to initialize timer!"<<endl;
	if (!classicNotPressing)
		cout<<"Failed to initialize classic_not_pressing bitmap!"<<endl;
	if (!classicPressing)
		cout<<"Failed to initialize classic_pressing bitmap!"<<endl;
	if (!timeLimitNotPressing)
		cout<<"Failed to initialize time_limit_not_pressing bitmap!"<<endl;
	if (!timeLimitPressing)
		cout<<"Failed to initialize time_limit_pressing bitmap!"<<endl;
	if (!justALevelNotPressing)
		cout<<"Failed to initialize just_a_level_not_pressing bitmap!"<<endl;
	if (!justALevelPressing)
		cout<<"Failed to initialize just_a_level_pressing bitmap!"<<endl;
	if (!menuTheme)
		cout<<"Failed to initialize menu_theme audio!"<<endl;
		
	return error;
}

int Menu::menuManager(ALLEGRO_DISPLAY * display)
{
	if (checkForErrors())
		return -1;

	al_set_window_title(display, "Sokoban");
	
	al_flip_display();
	al_install_mouse();
	al_install_keyboard();
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_mouse_event_source());
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	
	al_start_timer(timer);
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	
	al_play_sample(menuTheme, 2, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);

	bool done = false;
	
	bool isPlayPressing = false;
	bool isClassicPressing = false;
	bool isTimeLimitPressing = false;
	bool isJustALevelPressing = false;
	bool isBackPressing = false;
	
	bool draw = false;
	
	unsigned whatNext;
	
	while (!done)
	{
		float mouseX, mouseY;
		
		do
		{
			ALLEGRO_EVENT events;
			al_wait_for_event(eventQueue, &events);
		
			if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				done = true;
				whatNext = 0;
			}
			else if (events.type == ALLEGRO_EVENT_MOUSE_AXES)
			{
				mouseX = events.mouse.x;
				mouseY = events.mouse.y;
			}
			if (playButtonPressed && !justALevelButtonPressed)
			{	
				if (mouseX < constants.classicButtonX + 185 && mouseX > constants.classicButtonX && mouseY < constants.classicButtonY + 100 && mouseY > constants.classicButtonY)
				{
					isClassicPressing = true;
					if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && events.mouse.button == 1)
					{
						al_play_sample(buttonClick, 2, 0, 2, ALLEGRO_PLAYMODE_ONCE, NULL);
						whatNext = 1;
						done = true;
					}
				}
				else
					isClassicPressing = false;		
				if (mouseX < constants.timeLimitButtonX + 185 && mouseX > constants.timeLimitButtonX && mouseY < constants.timeLimitButtonY + 100 && mouseY > constants.timeLimitButtonY)
				{
					isTimeLimitPressing = true;
					if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && events.mouse.button == 1)
					{
						al_play_sample(buttonClick, 2, 0, 2, ALLEGRO_PLAYMODE_ONCE, NULL);
						whatNext = 2;
						done = true;
					}	
				}
				else
					isTimeLimitPressing = false;
				if (mouseX < constants.justALevelButtonX + 185 && mouseX > constants.justALevelButtonX && mouseY < constants.justALevelButtonY + 100 && mouseY > constants.justALevelButtonY)
				{
					isJustALevelPressing = true;
					if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && events.mouse.button == 1)
					{
						al_play_sample(buttonClick, 2, 0, 2, ALLEGRO_PLAYMODE_ONCE, NULL);
						justALevelButtonPressed = true;
						playButtonPressed = false;
					}	
				}
				else
					isJustALevelPressing = false;
				if (mouseX < constants.backButtonX + 185 && mouseX > constants.backButtonX && mouseY < constants.backButtonY + 100 && mouseY > constants.backButtonY)
				{
					isBackPressing = true;
					if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && events.mouse.button == 1)
					{
						al_play_sample(buttonClick, 2, 0, 4, ALLEGRO_PLAYMODE_ONCE, NULL);
						playButtonPressed = false;
					}
				}
				else
					isBackPressing = false;
			}
			else if (!playButtonPressed && !justALevelButtonPressed)
			{
				if (mouseX < constants.playButtonX + 185 && mouseX > constants.playButtonX && mouseY < constants.playButtonY + 100 && mouseY > constants.playButtonY)
				{
					isPlayPressing = true;
					if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && events.mouse.button == 1)
					{
						al_play_sample(buttonClick, 2, 0, 2, ALLEGRO_PLAYMODE_ONCE, NULL);
						playButtonPressed = true;
					}
				}
				else
					isPlayPressing = false;
			}
			if (justALevelButtonPressed)
			{
				if (events.type == ALLEGRO_EVENT_KEY_CHAR)
				{
					if (levelChosenCheck(events.keyboard.unichar))
					{
						whatNext = 3;
						done = true;
					}
				}
				if (mouseX < constants.backButtonX + 185 && mouseX > constants.backButtonX && mouseY < constants.backButtonY + 100 && mouseY > constants.backButtonY)
				{
					isBackPressing = true;
					if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && events.mouse.button == 1)
					{
						al_play_sample(buttonClick, 2, 0, 4, ALLEGRO_PLAYMODE_ONCE, NULL);
						justALevelButtonPressed = false;
						playButtonPressed = true;
					}
				}
				else
					isBackPressing = false;
			}
			
			draw = true;	
				
		} while (!al_is_event_queue_empty(eventQueue));
		
	if (draw)
		GUIUpdate(isPlayPressing, isClassicPressing, isTimeLimitPressing, isJustALevelPressing, isBackPressing);
		
	al_flip_display();
	al_clear_to_color(backgroundColor);
		
	}
	
	return whatNext;
}

void Menu::GUIUpdate(bool isPlayPressing, bool isClassicPressing, bool isTimeLimitPressing, bool isJustALevelPressing, bool isBackPressing)
{
	al_draw_scaled_bitmap(manPushingBox, 0, 0, al_get_bitmap_width(manPushingBox), al_get_bitmap_height(manPushingBox), constants.manPushingBoxX, constants.manPushingBoxY, constants.manPushingBoxW, constants.manPushingBoxH, 0);
	al_draw_scaled_rotated_bitmap(rotatingBox, constants.rotatingBoxX, constants.rotatingBoxY, constants.rotatingBoxX, constants.rotatingBoxY, constants.rotatingBoxW, constants.rotatingBoxH, boxRotationSpeed, 0);
	boxRotationSpeed += 0.003;
	al_draw_text(sokobanTextFont, sokobanTextColor, constants.sokobanTextX, constants.sokobanTextY, ALLEGRO_ALIGN_CENTRE, constants.sokobanText);
	if (!playButtonPressed && !justALevelButtonPressed)
	{
		if (!isPlayPressing)
			al_draw_scaled_bitmap(playNotPressing, 0, 0, al_get_bitmap_width(playNotPressing), al_get_bitmap_height(playNotPressing), constants.playButtonX, constants.playButtonY, constants.playButtonW, constants.playButtonH, 0);
		else
			al_draw_scaled_bitmap(playPressing, 0, 0, al_get_bitmap_width(playPressing), al_get_bitmap_height(playPressing), constants.playButtonX, constants.playButtonY, constants.playButtonW, constants.playButtonH, 0);
	}
	else if (playButtonPressed && !justALevelButtonPressed)
	{
		if (!isClassicPressing)
			al_draw_scaled_bitmap(classicNotPressing, 0, 0, al_get_bitmap_width(classicNotPressing), al_get_bitmap_height(classicNotPressing), constants.classicButtonX, constants.classicButtonY, constants.classicButtonW, constants.classicButtonH, 0);
		else
			al_draw_scaled_bitmap(classicPressing, 0, 0, al_get_bitmap_width(classicPressing), al_get_bitmap_height(classicPressing), constants.classicButtonX, constants.classicButtonY, constants.classicButtonW, constants.classicButtonH, 0);
		if (!isTimeLimitPressing)
			al_draw_scaled_bitmap(timeLimitNotPressing, 0, 0, al_get_bitmap_width(timeLimitNotPressing), al_get_bitmap_height(timeLimitNotPressing), constants.timeLimitButtonX, constants.timeLimitButtonY, constants.timeLimitButtonW, constants.timeLimitButtonH, 0);
		else
			al_draw_scaled_bitmap(timeLimitPressing, 0, 0, al_get_bitmap_width(timeLimitPressing), al_get_bitmap_height(timeLimitPressing), constants.timeLimitButtonX, constants.timeLimitButtonY, constants.timeLimitButtonW, constants.timeLimitButtonH, 0);
		if (!isJustALevelPressing)
			al_draw_scaled_bitmap(justALevelNotPressing, 0, 0, al_get_bitmap_width(justALevelNotPressing), al_get_bitmap_height(justALevelNotPressing), constants.justALevelButtonX, constants.justALevelButtonY, constants.justALevelButtonW, constants.justALevelButtonH, 0);
		else
			al_draw_scaled_bitmap(justALevelPressing, 0, 0, al_get_bitmap_width(justALevelPressing), al_get_bitmap_height(justALevelPressing), constants.justALevelButtonX, constants.justALevelButtonY, constants.justALevelButtonW, constants.justALevelButtonH, 0);
		if (!isBackPressing)
			al_draw_scaled_bitmap(backNotPressing, 0, 0, al_get_bitmap_width(backNotPressing), al_get_bitmap_height(backNotPressing), constants.backButtonX, constants.backButtonY, constants.backButtonW, constants.backButtonH, 0);
		else
			al_draw_scaled_bitmap(backPressing, 0, 0, al_get_bitmap_width(backPressing), al_get_bitmap_height(backPressing), constants.backButtonX, constants.backButtonY, constants.backButtonW, constants.backButtonH, 0);
	}
	else if (!playButtonPressed && justALevelButtonPressed)
	{
		al_draw_text(chooseLevelTextFont, chooseLevelTextColor, constants.chooseLevelTextX, constants.chooseLevelTextY, ALLEGRO_ALIGN_CENTRE, constants.chooseLevelText);
		if (!isBackPressing)
			al_draw_scaled_bitmap(backNotPressing, 0, 0, al_get_bitmap_width(backNotPressing), al_get_bitmap_height(backNotPressing), constants.backButtonX, constants.backButtonY, constants.backButtonW, constants.backButtonH, 0);
		else
			al_draw_scaled_bitmap(backPressing, 0, 0, al_get_bitmap_width(backPressing), al_get_bitmap_height(backPressing), constants.backButtonX, constants.backButtonY, constants.backButtonW, constants.backButtonH, 0);
	}
	al_draw_text(highScoreTextFont, highScoreTextColor, constants.highScoreTextX, constants.highScoreTextY, ALLEGRO_ALIGN_CENTRE, constants.highScoreText);
	ifstream highScoreFile;
	highScoreFile.open("HighScore.txt");
	int highScore;
	if (!highScoreFile)
		highScore = 0;
	if (highScoreFile.is_open())
		highScoreFile >> highScore;
	al_draw_textf(highScoreTextFont, highScoreTextColor, constants.highScoreTextX + 110, constants.highScoreTextY, ALLEGRO_ALIGN_CENTRE, "%i", highScore);
	highScoreFile.close();	
}

bool Menu::levelChosenCheck(const char &c)
{		
	if ((int)(c - 48) <= constants.lastLevelAvaliable && (int)(c - 48) > 0)
	{
		setLevelChosen(((int)(c - 48)));
		return true;
	}
	return false;
}

Menu::~Menu()
{
	al_destroy_timer(timer);
	al_destroy_bitmap(rotatingBox);
	al_destroy_bitmap(manPushingBox);
	al_destroy_bitmap(playNotPressing);
	al_destroy_bitmap(playPressing);
	al_destroy_bitmap(classicNotPressing);
	al_destroy_bitmap(classicPressing);
	al_destroy_bitmap(timeLimitNotPressing);
	al_destroy_bitmap(timeLimitPressing);
	al_destroy_event_queue(eventQueue);
	al_destroy_font(sokobanTextFont);
	al_destroy_sample(menuTheme);
	al_destroy_sample(buttonClick);
}
