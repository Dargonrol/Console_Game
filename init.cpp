#include "init.h"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"

#define ANSI_COLOR_BRIGHT  "\x1b[1m"
#define ANSI_COLOR_RESET   "\x1b[0m"

vector<Settings> initializeGame(int screenResX, int screenResY, vector<string> directories) {
	std::cout << ANSI_COLOR_RED "Hello World\n" ANSI_COLOR_RESET;

	// implement proper settings.ini corruption test
	string source = directories[0];
	directories.push_back(source + "/sounds");
	string settingsPath = source + "/settings.ini";
	string saveGameLocation = source + "/saves";

	// create Settings
	Settings sound_option("sound", { "on", "off" }, "on", "Options");
	Settings style_option("style", { "modern", "cyberpunk", "sci-fi", "nostalgic" }, "modern", "Options");
	Settings framerate_option("framerate", { "5 fps", "10 fps", "15 fps", "30 fps" "60 fps", "unlimited" }, "30 fps", "Options");
	Settings saveGame_location("saveGame-location", { saveGameLocation }, saveGameLocation, "Options");

	vector<Settings> allSettings = {
		sound_option,
		style_option,
		framerate_option,
		saveGame_location
	};

	iniParser parsedSettings;
	if (filesystem::exists(settingsPath)) {
		allSettings = Settings::loadINI(allSettings, settingsPath);
	}
	else {
		parsedSettings = Settings::saveINI(allSettings, settingsPath);
	}

	initializeDirectories(directories);

	return vector<Settings>(allSettings);
}

void initializeDirectories(vector<string> dirs)
{
	for (int i = 0; i < dirs.size(); i++) {
		if (filesystem::exists(dirs[i])) {
			//exists

		}
		else {
			//does not exist
		}

	}
}

