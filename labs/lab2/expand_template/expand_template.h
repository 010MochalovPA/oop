#pragma once

#include <iostream>
#include <fstream>
#include <iostream>
#include <fstream>
#include <optional>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <string>

const int MAX_COUNT_CHARS = 27;

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::map<std::string, std::string> params;
};

struct Node
{
	int to[MAX_COUNT_CHARS];
	int length;
	bool isTerm;
	int link;
	std::string value;

	Node(const std::string& v)
	{
		memset(to, -1, sizeof(to));
		length = 0;
		isTerm = false;
		link = -1;
		value = v;
	}
};

void ReplaceSubString(std::string& str, std::string& newString, int length, int pos);
void AddNodeBohr(std::vector<Node>& bohr, const std::string& str);
void InitLinksOnBohr(std::vector<Node>& bohr);
void Bohr_init(std::vector<Node>& bohr);
bool ValidateValue(const std::string str);
void AddNodesFromMap(std::vector<Node>& bohr, const std::map<std::string, std::string>& params);
std::string ExpandTemplate(const std::vector<Node>& bohr, const std::string& tpl, std::map<std::string, std::string> params);
std::optional<Args> GetArgs(const int& argc, char* argv[]);