#include "Display.h"


bool Display::isLayersEmpty()
{
	if (this->layers.empty())
		return true;
	else
		return false;
}

void Display::render()
{
	system("CLS");
	static string tempLine;
	tempLine.reserve((SIZE.X * SIZE.Y) + 50);
	for (int y = 0; y != this->SIZE.Y; y++) {
		for (int x = 0; x != this->SIZE.X; x++) {
			if (this->screenBuffer[y][x].character == '\n') {
				tempLine.append("\n");
				break;
			}
			else
				tempLine.append(this->screenBuffer[y][x].attr + this->screenBuffer[y][x].character);
		}
	}
	
}

int Display::update(string layer, bool refresh)
{
	if (layer != "all") {
	}
	else {
		if (isLayersEmpty()) {
			render();
		}
		else {
			for (auto iterLayers = this->layers.begin(); iterLayers != this->layers.end(); iterLayers++) {
				if (!iterLayers->buffer.empty()) {
					for (auto iterBuffer = iterLayers->buffer.begin(); iterBuffer != iterLayers->buffer.end(); iterBuffer++) {
						setChar(iterBuffer->character, iterBuffer->coordinates, iterLayers->layerName, iterBuffer->attr);
					}
				}
			}
			render();
		}
	}
	return 1;
}

int Display::setChar(char character, COORD coord, string layer, string attr)
{
	if (coord.Y >= 0 && coord.Y < screenBuffer.size() && coord.X >= 0 && coord.X < screenBuffer[0].size()) {
		for (auto iterLayer = this->layers.begin(); iterLayer != layers.end(); iterLayer++) {
			if (iterLayer->layerName.data() == layer) {
				for (auto iterBuffer = iterLayer->buffer.begin(); iterBuffer != iterLayer->buffer.end(); iterBuffer++) {
					if (iterBuffer->coordinates.X == coord.X && iterBuffer->coordinates.Y == coord.Y) {
						iterBuffer->attr = attr;
						iterBuffer->character = character;
						return 1;
					}
					else {
						CHAR_INFO2 newChar;
						newChar.attr = attr;
						newChar.character = character;
						newChar.coordinates = coord;
						return 1;
					}
				}
			}
		}
		//throw("no such layer exists!");
		return -1;
	}
	else {
		throw("coordinates out of range");
		return -1;
	}
}

int Display::setAttr(string attr, COORD coord, string layer)
{
	if (coord.Y >= 0 && coord.Y < screenBuffer.size() && coord.X >= 0 && coord.X < screenBuffer[0].size()) {
		for (auto iterLayer = this->layers.begin(); iterLayer != layers.end(); iterLayer++) {
			if (iterLayer->layerName.data() == layer) {
				for (auto iterBuffer = iterLayer->buffer.begin(); iterBuffer != iterLayer->buffer.end(); iterBuffer++) {
					if (iterBuffer->coordinates.X == coord.X && iterBuffer->coordinates.Y == coord.Y) {
						iterBuffer->attr = attr;
						return 1;
					}
					else {
						CHAR_INFO2 newChar;
						newChar.attr = attr;
						newChar.coordinates = coord;
						return 1;
					}
				}
			}
		}
		//throw("no such layer exists!");
		return -1;
	}
	else {
		throw("coordinates out of range");
		return -1;
	}
}


int Display::addLayer(string layerName)
{

	for (auto iterLayer = this->layers.begin(); iterLayer != layers.end(); iterLayer++) {
		if (iterLayer->layerName.data() == layerName) {
			throw("layer already exists");
			return -1;
		}
		else {
			Layer newLayer;
			newLayer.layerName = layerName;
			this->layers.push_back(newLayer);
			return 1;
		}
	}
	return -1;
}


int Display::removeLayer(string layerName)
{
	for (auto iterLayer = this->layers.begin(); iterLayer != layers.end(); iterLayer++) {
		if (iterLayer->layerName.data() == layerName) {
			this->layers.erase(iterLayer);
			return 1;
		}
		else {
			throw("no such layer exists");
			return -1;
		}
	}
}

vector<string> Display::listLayers()
{
	if (isLayersEmpty())
		throw("no layers");

	vector<string> layerList;
	for (auto iter = this->layers.begin(); iter != this->layers.end(); iter++) {
		layerList.push_back(iter->layerName);
	}
	return vector<string>(layerList);
}

int Display::setCharScreenBuffer(char character, COORD coord, string attr)
{
	if (coord.Y >= 0 && coord.Y < screenBuffer.size() && coord.X >= 0 && coord.X < screenBuffer[0].size()) {
		this->screenBuffer[coord.Y][coord.X].character = character;
		this->screenBuffer[coord.Y][coord.X].attr = attr;
		return 1;
	}
	else {
		throw("coordinates out of range");
		return -1;
	}
	return -1;
}

int Display::setAttrScreenBuffer(string attr, COORD coord)
{
	if (coord.Y >= 0 && coord.Y < screenBuffer.size() && coord.X >= 0 && coord.X < screenBuffer[0].size()) {
		this->screenBuffer[coord.Y][coord.X].attr = attr;
		return 1;
	}
	else {
		throw("coordinates out of range");
		return -1;
	}
	return -1;
}

void Display::resetScreenBuffer()
{
	for (int y = 0; y != this->SIZE.Y; y++) {
		for (int x = 0; x != this->SIZE.X; x++) {
			if (x == this->SIZE.X - 1) {
				this->screenBuffer[y][x].character = '\n';
				this->screenBuffer[y][x].attr = "\033[0m";
			}
			else {
				this->screenBuffer[y][x].character = ' ';
				this->screenBuffer[y][x].attr = "\033[0m";
			}
		}
	}
}
