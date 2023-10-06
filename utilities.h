#pragma once
#include "Settings.h"
#include <Windows.h>
#include <thread>
#include <string>
#include <chrono>

// play audio and backround music
// small things like typewriter animation

// audio stuff
extern inline void playAudio(string filename, string command) {

}

// other stuff
// types each letter with the given delay
bool typeWrite(std::string stringToPrint, int delay, bool randomize = false, bool sound = true) {
	try
	{
		for (int x = 0; stringToPrint[x] != '\0'; x++)
		{
			std::cout << stringToPrint[x] << std::flush;
			if (stringToPrint[x] != ' ' && stringToPrint[x] != '\n' && sound) {


				std::wstring strTypewriterSoundFilePath = L"bin/sounds/typewriter-";
				std::wstring ranNum = std::to_wstring(rand() % 3 + 1);
				std::wstring fileSuffix = L".wav";
				strTypewriterSoundFilePath.append(ranNum);
				strTypewriterSoundFilePath.append(fileSuffix);
				const wchar_t* chrTypewriterSoundFilePath = strTypewriterSoundFilePath.data();


				PlaySoundW(
					chrTypewriterSoundFilePath,
					NULL,
					SND_FILENAME | SND_ASYNC
				);
			};
			int newDelay;
			if (randomize) {
				// 50% less or 10% more
				double lowerBound = delay - delay * 0.5;
				int upperBound = std::round(delay + delay * 0.10);
				newDelay = rand() % upperBound + lowerBound;
			}
			else { newDelay = delay; }

			std::this_thread::sleep_for(std::chrono::milliseconds(newDelay));
		};
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
	return false;
}

/*
int stunden = 6414;
	int tage = 0;
	int monate = 0;
	int jahre = 0;

	if (stunden / 24 < 1)
		cout << "Seid: " << stunden << "h auf dem Server" << flush;
	else {
		tage = round(stunden / 24);
		stunden = stunden % 24;
		if (tage / 30 < 1)
			cout << "Seid: " << tage << "d | " << stunden << "h auf dem Server" << flush;
		else {
			monate = round(tage / 30);
			tage = tage % 30;
			if (monate / 12 < 1)
				cout << "Seid: " << monate << "m | " << tage << "d auf dem Server" << flush;
			else {
				jahre = round(monate / 12);
				monate = monate % 12;
				cout << "Seid: " << jahre << "j | " << monate << "m | " << tage << "d auf dem Server" << flush;
			}
		}
	}
	
	*/