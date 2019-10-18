#include "GameManager.cpp"
#include "Menu.cpp"
#include "Classic.cpp"
#include "TimeLimit.cpp"

int main()
{
	if(!al_init())
	{
		cout<<"Failed to initialize Allegro!"<<endl;
		return 0;
	}
	if (!al_init_font_addon())
	{
		cout<<"Failed to initialize al_init_font_addon!"<<endl;
		return 0;
	}
	if (!al_init_ttf_addon())
	{
		cout<<"Failed to initialize al_init_ttf_addon!"<<endl;
		return 0;
	}
	if (!al_init_image_addon())
	{
		cout<<"Failed to initialize al_init_image_addon!"<<endl;
		return 0;
	}
	if (!al_install_audio())
	{
		cout<<"Failed to initialize al_install_audio!"<<endl;
		return 0;
	}
	if (!al_init_acodec_addon())
	{
		cout<<"Failed to initialize al_init_acodec_addon!"<<endl;
		return 0;
	}
	if (!al_reserve_samples(8))
	{
		cout<<"Failed to reserve samples!"<<endl;
		return 0;
	}
	
	ALLEGRO_DISPLAY * display = al_create_display(constants.resolutionW, constants.resolutionH);
	if (!display)
	{
		cout<<"Failed to create a display!"<<endl;
		return 0;
	}
	
	bool isMenu = true;
		
	while (isMenu)	
	{
		Menu * menu = new Menu();

		switch (menu->menuManager(display))
		{
			case -1: {
					  	cout<<"Error!"<<endl;
				  	 	delete menu;
				  	 	isMenu = false;
				 	 	break;
				 	 }
			case 0:	 {
						delete menu;
						isMenu = false;
			    	 	break;
			    	 }
			case 1:	 {
						delete menu;
						GameManager * classic = new Classic();
						if (!classic->levelManager(display))
							cout<<"Error!"<<endl;
						else
						{
							if (classic->getReturnToMenu())
								isMenu = true;
							else
								isMenu = false;
							delete classic;
						}
						break;
					 }
			case 2:	 {
						delete menu;
						GameManager * timeLimit = new TimeLimit();
						if (!timeLimit->levelManager(display))
							cout<<"Error!"<<endl;
						else
						{
							if (timeLimit->getReturnToMenu())
								isMenu = true;
							else
								isMenu = false;
							delete timeLimit;
						}
						break;
					 }
			case 3: {
						int levelChosen = menu->getLevelChosen();
			 			delete menu;
			 			GameManager * classic = new Classic(levelChosen);
			 			if (!classic->levelManager(display))
							cout<<"Error!"<<endl;
						else
						{
							if (classic->getReturnToMenu())
								isMenu = true;
							else
								isMenu = false;
							delete classic;
						}
						break;
					 }
		}
	}
	
	al_destroy_display(display);
	
	return 0;
}
