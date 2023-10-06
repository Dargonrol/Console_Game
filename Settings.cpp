#pragma once
#include "Settings.h"
#include <string>
#include <vector>

using namespace std;

void Settings::resetSetting()
{
	this->currentValue = this->defaultValue;
}

void Settings::setValue(string value_to_set)
{
	this->currentValue = value_to_set;
}

void Settings::setValues(vector<string> values_to_set)
{
	this->values = values_to_set;
}

void Settings::setName(string name_to_set)
{
	this->name = name_to_set;
}

void Settings::setDefault(string newDefault)
{
	this->defaultValue = newDefault;
}

void Settings::addValue(string newvalue)
{
	this->values.push_back(newvalue);
}

void Settings::removeValue(string targetValue)
{
	auto iter = find(this->values.begin(), this->values.end(), targetValue);
	if (iter != this->values.end())
		this->values.erase(iter);
}

void Settings::setSection(string newSection)
{
	this->section = newSection;
}

iniParser Settings::serialize(iniParser obj)
{
	string section = this->section;

	if (obj.fileData.find(section) != obj.fileData.end()) {
		// section found therefore key could exist too so check if key exists
		auto iterSection = obj.fileData.find(section);
		// check if key already exists
		if (iterSection->second.find(this->name) != iterSection->second.end()) {
			// key does exist, edit value
			obj.editValueOfKey(section, this->name, this->currentValue);
			return obj;
		}
		else {
			// key does not exist, create new one
			obj.addKey(section, this->name, this->currentValue);
			return obj;
		}
	}
	else {
		// section not found so key cannot already exist therefore add new section, then key
		obj.addSection(section);
		obj.addKey(section, this->name, this->currentValue);
		return obj;
	}
}

string Settings::getName()
{
	return string(this->name);
}

string Settings::getCurrentValue()
{
	return string(this->currentValue);
}

string Settings::getDefaultValue()
{
	return string(this->defaultValue);
}

string Settings::getSection()
{
	return string(this->section);
}

vector<string> Settings::getAllValues()
{
	return vector<string>(this->values);
}

vector<Settings> Settings::resetSettings(vector<Settings> obj)
{
	for (unsigned int i = 0; i < obj.size(); i++) {
		obj[i].resetSetting();
	}
	return vector<Settings>(obj);
}

iniParser Settings::serializeVector(vector<Settings> settingsVector, iniParser parsObj)
{
	for (int i = 0; i != settingsVector.size(); i++) {
		string section = settingsVector[i].getSection();

		if (parsObj.fileData.find(section) != parsObj.fileData.end()) {
			// section found therefore key could exist too so check if key exists
			auto iterSection = parsObj.fileData.find(section);
			// check if key already exists
			if (iterSection->second.find(settingsVector[i].getName()) != iterSection->second.end()) {
				// key does exist, edit value
				parsObj.editValueOfKey(section, settingsVector[i].getName(), settingsVector[i].getCurrentValue());
			}
			else {
				// key does not exist, create new one
				parsObj.addKey(section, settingsVector[i].getName(), settingsVector[i].getCurrentValue());
			}
		}
		else {
			// section not found so key cannot already exist therefore add new section, then key
			parsObj.addSection(section);
			parsObj.addKey(section, settingsVector[i].getName(), settingsVector[i].getCurrentValue());
		}
	}
	return parsObj;
}

vector<Settings> Settings::loadINI(vector<Settings> settingsVector, string filePath)
{
	iniParser iniObj;
	iniObj.loadINI(filePath);
	for (int i = 0; i != settingsVector.size(); i++) {
		settingsVector[i].setValue(iniObj.getKeyValue(settingsVector[i].getName(), settingsVector[i].getSection()));
		if (settingsVector[i].getCurrentValue().empty()) {
			settingsVector[i].resetSetting();
		}
	}
	return vector<Settings>(settingsVector);
}

iniParser Settings::saveINI(vector<Settings> settingsVector, string filePath)
{
	iniParser iniObj;
	iniObj = Settings::serializeVector(settingsVector, iniObj);
	iniObj.saveINI(filePath);
	return iniParser(iniObj);
}

vector<Settings> Settings::changeNameInVector(vector<Settings> settingsVector, string settingName, string newName)
{
	const int bufferSize = 200;
	for (int i = 0; i != settingsVector.size(); i++) {
		char chr_settingsVector[bufferSize];
		strcpy_s(chr_settingsVector, settingsVector[i].getName().c_str());
		const char* chr_settingName = settingName.c_str();

		if (strcmp(chr_settingsVector, chr_settingName) == 0) {
			settingsVector[i].setName(newName);
			break;
		}
	}
	return vector<Settings>(settingsVector);
}

vector<Settings> Settings::changeValueInVector(vector<Settings> settingsVector, string settingName, string newValue)
{
	const int bufferSize = 200;
	for (int i = 0; i != settingsVector.size(); i++) {
		char chr_settingsVector[bufferSize];
		strcpy_s(chr_settingsVector, settingsVector[i].getName().c_str());
		const char* chr_settingName = settingName.c_str();

		if (strcmp(chr_settingsVector, chr_settingName) == 0) {
			settingsVector[i].setValue(newValue);
			break;
		}
	}
	return vector<Settings>(settingsVector);
}

vector<Settings> Settings::changeValuesInVector(vector<Settings> settingsVector, string settingName, vector<string> newValues)
{
	const int bufferSize = 200;
	for (int i = 0; i != settingsVector.size(); i++) {
		char chr_settingsVector[bufferSize];
		strcpy_s(chr_settingsVector, settingsVector[i].getName().c_str());
		const char* chr_settingName = settingName.c_str();

		if (strcmp(chr_settingsVector, chr_settingName) == 0) {
			settingsVector[i].setValues(newValues);
			break;
		}
	}
	return vector<Settings>(settingsVector);
}

vector<Settings> Settings::changeDefaultInVector(vector<Settings> settingsVector, string settingName, string newDefault)
{
	const int bufferSize = 200;
	for (int i = 0; i != settingsVector.size(); i++) {
		char chr_settingsVector[bufferSize];
		strcpy_s(chr_settingsVector, settingsVector[i].getName().c_str());
		const char* chr_settingName = settingName.c_str();

		if (strcmp(chr_settingsVector, chr_settingName) == 0) {
			settingsVector[i].setDefault(newDefault);
			break;
		}
	}
	return vector<Settings>(settingsVector);
}

vector<Settings> Settings::changeSectionInVector(vector<Settings> settingsVector, string settingName, string newSection)
{
	const int bufferSize = 200;
	for (int i = 0; i != settingsVector.size(); i++) {
		char chr_settingsVector[bufferSize];
		strcpy_s(chr_settingsVector, settingsVector[i].getName().c_str());
		const char* chr_settingName = settingName.c_str();
		if (strcmp(chr_settingsVector, chr_settingName) == 0) {
			settingsVector[i].setSection(newSection);
			break;
		}
	}
	return vector<Settings>(settingsVector);
}

vector<Settings> Settings::RemoveValueInVector(vector<Settings> settingsVector, string settingName, string oldValue)
{
	const int bufferSize = 200;
	for (int i = 0; i != settingsVector.size(); i++) {
		char chr_settingsVector[bufferSize];
		strcpy_s(chr_settingsVector, settingsVector[i].getName().c_str());
		const char* chr_settingName = settingName.c_str();

		if (strcmp(chr_settingsVector, chr_settingName) == 0) {
			settingsVector[i].removeValue(oldValue);
			break;
		}
	}
	return vector<Settings>(settingsVector);
}

vector<Settings> Settings::AddValueInVector(vector<Settings> settingsVector, string settingName, string newValue)
{
	const int bufferSize = 200;
	for (int i = 0; i != settingsVector.size(); i++) {
		char chr_settingsVector[bufferSize];
		strcpy_s(chr_settingsVector, settingsVector[i].getName().c_str());
		const char* chr_settingName = settingName.c_str();

		if (strcmp(chr_settingsVector, chr_settingName) == 0) {
			settingsVector[i].addValue(newValue);
			break;
		}
	}
	return vector<Settings>(settingsVector);
}
