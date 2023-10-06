#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <filesystem>

using namespace std;

class iniParser
{
public:
	map<string, map<string, string>> fileData;

	iniParser() = default;

	bool loadINI(string dir);
	bool saveINI(string dir);
	map<string, map<string, string>> getData();
	bool addKey(string section, string key, string value = "");
	bool addSection(string section);
	bool removeKey(string key, string section = "\0");
	bool removeSection(string section);
	bool editNameOfKey(string key, string name, string section = "\0");
	bool editValueOfKey(string section, string key, string value);
	bool editNameOfSection(string section, string name);
	bool moveKeyToSection(string key, string section);
	void clearSection(string section);
	void clearMap();
	map<string, string> getAllKeysAndValues(string section = "\0");
	map<string, string> getKeyAndValue(string key, string section = "\0");
	vector<string> getAllKeys(string section = "\0");
	vector<string> getAllSections();
	string getKeyValue(string key, string section = "\0");
	void printMap();
};

