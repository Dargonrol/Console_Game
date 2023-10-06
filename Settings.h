#pragma once
#include <string>
#include <vector>
#include "iniParser.h"

using namespace std;


class Settings {
	string name;
	vector<string> values;
	string currentValue;
	string defaultValue;
	string section;
public:
	Settings(const string& name, const vector<string>& values, const string& defaultValue, string section)
		: name(name), values(values), defaultValue(defaultValue), section(section)
	{
		currentValue = defaultValue;
	}

	void resetSetting();

	void setValue(string value_to_set);
	void setValues(vector<string> values_to_set);
	void setName(string name_to_set);
	void setDefault(string newDefault);
	void addValue(string newvalue);
	void removeValue(string targetValue);
	void setSection(string section);

	iniParser serialize(iniParser obj);

	string getName();
	string getCurrentValue();
	string getDefaultValue();
	string getSection();
	vector<string> getAllValues();

	static vector<Settings> resetSettings(vector<Settings> obj);
	static iniParser serializeVector(vector<Settings>, iniParser obj);

	static vector<Settings> loadINI(vector<Settings> settingsVector, string filePath);
	static iniParser saveINI(vector<Settings> settingsVector, string filePath);

	static vector<Settings> changeNameInVector(vector<Settings> settingsVector, string settingName, string newName);
	static vector<Settings> changeValueInVector(vector<Settings> settingsVector, string settingName, string newValue);
	static vector<Settings> changeValuesInVector(vector<Settings> settingsVector, string settingName, vector<string> newValues);
	static vector<Settings> changeDefaultInVector(vector<Settings> settingsVector, string settingName, string newDefault);
	static vector<Settings> changeSectionInVector(vector<Settings> settingsVector, string settingName, string newSection);
	static vector<Settings> RemoveValueInVector(vector<Settings> settingsVector, string settingName, string oldValue);
	static vector<Settings> AddValueInVector(vector<Settings> settingsVector, string settingName, string newValue);

	// write function to change value of setting if it is in an vector settings
};