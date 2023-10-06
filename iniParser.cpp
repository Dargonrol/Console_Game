#include "iniParser.h"
#include <vector>
#include <string>
#include <map>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool iniParser::loadINI(string dir)
{
	ifstream iniFile;
	iniFile.open(dir, ios::in);
	if (iniFile.is_open())
	{
		string readBuffer;
		string section;
		while (getline(iniFile, readBuffer))
		{
			if (readBuffer[0] == '[' && !readBuffer.empty()) {
				section = readBuffer.substr(1, readBuffer.size() - 2);
				this->addSection(section);
				readBuffer.clear();
			}
			else if (!readBuffer.empty()) {
				auto splitPos = readBuffer.find("=");
				string key = readBuffer.substr(0, splitPos - 1);
				this->addKey(section, key);
				readBuffer.erase(0, splitPos + 2);
				this->editValueOfKey(section, key, readBuffer);
				readBuffer.clear();
			}
		}
		iniFile.close();
	}
	return true;
}

bool iniParser::saveINI(string dir)
{
	ofstream iniFile;
	iniFile.open(dir, ios::out | ios::trunc);

	for (auto iterSection = this->fileData.begin(); iterSection != this->fileData.end(); iterSection++) {
		iniFile << "[" << iterSection->first << "]" << endl;
		for (auto iterKey = iterSection->second.begin(); iterKey != iterSection->second.end(); iterKey++) {
			iniFile << iterKey->first << " = " << iterKey->second << endl;
		}
	}
	iniFile.close();
	return true;
}

map<string, map<string, string>> iniParser::getData()
{
	return map<string, map<string, string>>(this->fileData);
}

bool iniParser::addKey(string section, string key, string value)
{
	this->fileData[section][key] = value;
	return true;
}

bool iniParser::addSection(string section)
{
	try
	{
		map<string, string> innerMap;
		this->fileData.insert({ section, innerMap });
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
	return false;
}

bool iniParser::removeKey(string key, string section)
{
	try
	{
		if (section.data() != "\0") {
			auto iter = this->fileData.at(section).find(key);
			this->fileData.at(section).erase(iter);
		}
		else {
			// /0 detection doesn't work
			for (auto i = this->fileData.begin(); i != this->fileData.end(); i++) {
				auto iter = i->second.find(key);
				i->second.erase(iter);
			}
		}
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
	return false;
}

bool iniParser::removeSection(string section)
{
	try
	{
		auto iter = this->fileData.find(section);
		this->fileData.erase(iter); // wierd error, if we use iter to erase when iter points to an non exixtent place. When using section directly in erase, error does not happen.
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

// wierd error I cannot yet fix! NOTE: same error as the thing above!
bool iniParser::editNameOfKey(string key, string name, string section)
{
	if (section != "\0") {
		cout << "test" << flush;
		const auto iterSection = this->fileData.find(section);
		cout << "test0.5" << flush;
		const auto iterKey = iterSection->second.find(key);
		cout << "test2" << flush;
		string value = iterKey->second;
		cout << "test3" << flush;
		iterSection->second.erase(iterKey);
		iterSection->second.insert(pair<string, string>(key, value));
		return true;
	}
	else {
		// /0 detection doesn't work
		for (auto iterSection = this->fileData.begin(); iterSection != this->fileData.end(); iterSection++) {
			auto iterKey = iterSection->second.find(key);
			string value = iterKey->second;
			iterSection->second.erase(iterKey);
			iterSection->second.insert(pair<string, string>(key, value));
		}
		return true;
	}
	return false;
}

bool iniParser::editValueOfKey(string section, string key, string value)
{
	auto iterSection = this->fileData.find(section);
	auto iterKey = iterSection->second.find(key);
	iterKey->second = value;
	return true;
}

bool iniParser::editNameOfSection(string section, string name)
{
	auto iterSection = this->fileData.find(section);
	map<string, string> innerMap = iterSection->second;
	this->fileData.erase(section);
	this->fileData.insert({ name, innerMap });
	return false;
}

void iniParser::clearSection(string section)
{
	map<string, string> emptyInnerMap;
	auto iterSection = this->fileData.find(section);
	iterSection->second = emptyInnerMap;
}

void iniParser::clearMap()
{
	this->fileData.clear();
}

vector<string> iniParser::getAllKeys(string section)
{
	vector<string> buffer;
	if (section != "\0") {
		auto iterSections = this->fileData.find(section);
		for (auto iterKeys = iterSections->second.begin(); iterKeys != iterSections->second.end(); iterKeys++) {
			buffer.push_back(iterKeys->first);
		}
	}
	else {
		// /0 detection doesn't work
		for (auto iterSections = this->fileData.begin(); iterSections != this->fileData.end(); iterSections++) {
			for (auto iterKeys = iterSections->second.begin(); iterKeys != iterSections->second.end(); iterKeys++) {
				buffer.push_back(iterKeys->first);
			}
		}
	}
	return vector<string>(buffer);
}

vector<string> iniParser::getAllSections()
{
	vector<string> buffer;
	for (auto iterSections = this->fileData.begin(); iterSections != this->fileData.end(); iterSections++) {
		buffer.push_back(iterSections->first);
	}
	return vector<string>(buffer);
}

string iniParser::getKeyValue(string key, string section)
{
	auto iterSection = this->fileData.find(section);
	if (iterSection != this->fileData.end()) {
		auto iterKey = iterSection->second.find(key);
		if (iterKey != iterSection->second.end()) {
			return string(iterKey->second);
		}
	}
	return string("");
}

void iniParser::printMap()
{
	for (auto iterSections = this->fileData.begin(); iterSections != this->fileData.end(); iterSections++) {
		cout << "[" << iterSections->first << "]\n" << flush;
		for (auto iterKeys = iterSections->second.begin(); iterKeys != iterSections->second.end(); iterKeys++) {
			cout << "\t" << iterKeys->first << "\t=  {" << iterKeys->second << "}\n" << flush;
		}
	}
}
