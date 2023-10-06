#include <iostream>
#include <stdio.h >
#include <stdlib.h>
#include <thread>
#include <string>
#include <chrono>
#include <Windows.h>
#include <sys/stat.h>
#include <vector>
#include <math.h>
#include <filesystem>
#include "iniParser.h"
#include "Settings.h"
#include "utilities.h"
#include "init.cpp"
#include "Graphic.h"

#pragma execution_character_set( "utf-8" )


vector<string> directories = { "./bin" };
int screenResX = 1000, screenResY = 250;

using namespace std::chrono_literals;
using namespace std;


static void startingScreen() {
	std::cout << R"(
 _   _       _   _ _   _          _ 
| | | |     | | (_) | | |        | |
| | | |_ __ | |_ _| |_| | ___  __| |
| | | | '_ \| __| | __| |/ _ \/ _` |
| |_| | | | | |_| | |_| |  __/ (_| |
 \___/|_| |_|\__|_|\__|_|\___|\__,_|
                                    
                                                            
)" << '\n';
	// system("color a");
	PlaySoundW(
		TEXT("bin/sounds/game_start.wav"),
		NULL,
		SND_FILENAME | SND_ASYNC
	);

	std::this_thread::sleep_for(1s);

	typeWrite("a Game made by Dargonrol", 100, true);

	std::this_thread::sleep_for(1.5s);

	system("CLS");
}


static int titleScreen() {
	system("CLS");
	std::cout << R"(
 _   _ _   _                                     
| |_(_) |_| | ___   ___  ___ _ __ ___  ___ _ __  
| __| | __| |/ _ \ / __|/ __| '__/ _ \/ _ \ '_ \ 
| |_| | |_| |  __/ \__ \ (__| | |  __/  __/ | | |
 \__|_|\__|_|\___| |___/\___|_|  \___|\___|_| |_|
	)" << '\n' << std::flush;

	typeWrite("Welcome. Choose an option below by typing a highlighted character and pressing enter.", 40, true);
	std::cout << "\n\n\n\n" << std::flush;
	typeWrite("(n)ew game | (l)oad save file | (o)pen recent save | (s)ettings | (e)xit \n\n", 8, true, false);

	char userInput;

	std::cin >> userInput;
	switch (userInput)
	{
	case 'e':
		exit(0);
		break;

	case 's':
		return 1;
		break;

	default:
		std::cout << userInput << " is not a valid option. Try again!" << std::flush;
		system("PAUSE");
		break;
	}
	return 0;
}


static int settingsScreen() {
	system("CLS");
	std::cout << R"(
               __    __  .__                      
  ______ _____/  |__/  |_|__| ____    ____  ______
 /  ___// __ \   __\   __\  |/    \  / ___\/  ___/
 \___ \\  ___/|  |  |  | |  |   |  \/ /_/  >___ \ 
/____  >\___  >__|  |__| |__|___|  /\___  /____  >
     \/     \/                   \//_____/     \/ 
	)" << '\n' << std::flush;

	typeWrite("This is the options menue", 45, true);
	std::cout << "\n\n\n\n" << std::flush;
	system("PAUSE");
	return 0;
}


int main() {
	cout << "creating Window...\n";

	Window* pWindow = new Window({500, 500}, L"This is a test window");
	pWindow->showWindow(SW_SHOW);
	pWindow->addTextBox(L"name", { 50, 50 }, { 100, 20 });

	bool running = true;
	while (running) {
		if (!pWindow->ProcessMessages()) {
			cout << "closing window...\n";
			running = false;
		}
		// do stuff / render

		Sleep(10);
	}

	delete pWindow;
	return 0;
}




// cursor in einstellungen änderbar: https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences#example
// jegliche dialog animation mit einem Tastendruck skippbar machen
// credits https://www.youtube.com/watch?v=mant83l8-yI
// story maybe dem credit song anpassen?

// character creation, scifi setting -> TosterTier's PnP, character creation Staatsaufseher like