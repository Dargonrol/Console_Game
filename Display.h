#pragma once
#include <vector>
#include <string>
#include <Windows.h>
#include <iostream>
#include <sys/stat.h>
#include <map>

using namespace std;

class Display
{
private:
	// creates an construct which saves the character as well as possible attributes like color
	typedef struct _CHAR_INFO {
		char character = ' ';
		string attr = "\033[0m";
	} CHAR_INFO;

	// saves character, attributes as well as coordinates
	typedef struct _CHAR_INFO2 {
		char character = ' ';
		string attr = "\033[0m";
		COORD coordinates;
	} CHAR_INFO2;

	// a construct to store the layerName as well as an CHAR_INFO2-buffer
	typedef struct _Layer {
		string layerName;
		vector<CHAR_INFO2> buffer;
	} Layer;

	// initialize space to save layers
	vector<Layer> layers;

	// creates the main ScreenBuffer
	vector<vector<CHAR_INFO>> screenBuffer;
	CHAR_INFO defaultChar;

	// debug layer to display debug information
	Layer debugLayer;

	bool isLayersEmpty();
	void render();
public:
	// basically screen resolution -> every Layer and ScreenBuffer will have this Size
	COORD SIZE;

	// initializes a ScreenBuffer and fills it with emtpy spaces 
	Display(COORD coords) : SIZE{ coords.X + 1, coords.Y }, screenBuffer(coords.Y, vector<CHAR_INFO>(coords.X + 1, defaultChar)) {
		for (int y = 0; y != SIZE.Y; y++) {
			for (int x = 0; x != SIZE.X; x++) {
				if (x == SIZE.X - 1) {
					this->screenBuffer[y][x].character = '\n';
					this->screenBuffer[y][x].attr = "\033[0m";
				}
				else {
					this->screenBuffer[y][x].character = ' ';
					this->screenBuffer[y][x].attr = "\033[1;31m";
				}
			}
		}
	}

	// updates all or a specific Layer / copies content to screenBuffer and prints it
	int update(string layer = "all", bool refresh = true);
	// set a Character on a specific or base layer
	int setChar(char character, COORD coord, string layer, string attr = "\033[0m");
	// set an attribute on a specific layer
	int setAttr(string attr, COORD coord, string layer);

	// adds a new Layer on top
	int addLayer(string layerName);
	// removes a Layer
	int removeLayer(string layerName);
	// returns a vector<string> of all Layers from top to bottom
	vector<string> listLayers();

	// directly manipulates screenBuffer: sets a character, attr optional
	int setCharScreenBuffer(char character, COORD coord, string attr = "\033[0m");
	// directly manipulates screenBuffer: sets an attribute on a specific coordinate
	int setAttrScreenBuffer(string attr, COORD coord);
	// clears screenBuffer
	void resetScreenBuffer();
	
};

// add function to add additional buffers / support additional buffers in general

// clears a Layer ["layername"] or all layers: ["all"]

// vecotor<char_info> layer