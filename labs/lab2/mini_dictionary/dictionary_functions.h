#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <algorithm> 
#include <windows.h>
#include <optional>

typedef std::set<std::string> Translations;
typedef std::map<std::string, Translations> Dictionary;

std::string StringToLowerCase(const std::string& str);
std::string Trim(std::string str);
void SaveDictionary(const std::string& dictionaryPath, const Dictionary& dictionary);
void CopyDictionaryToFile(std::ofstream& outputFile,const Dictionary& dictionary);
void RunDictionary(std::istream& input, std::ostream& output, std::string dictionaryPath);
void OutputChatMessage(std::ostream& output, const std::string message);
void StartChat(std::istream& input, std::ostream& output, Dictionary& dictionary, bool& dictionaryChanged);
void PrintTranslations(const Dictionary& dictionary, std::ostream& output, const std::string& word);
void InsertInDictionary(Dictionary& dictionary, const std::string& word, const Translations& translations);
void AddTranslation(Dictionary& dictionary, const std::string& word, const std::string& translations);
Dictionary GetDictionaryFromFile(std::ifstream& input);
Translations SplitStringIntoTranstations(const std::string str, char separator);
