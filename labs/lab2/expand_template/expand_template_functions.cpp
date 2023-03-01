#include "expand_template.h"

std::optional<Args> GetArgs(const int& argc, char* argv[])
{
	if (argc < 5)
	{
		return std::nullopt;
	}

	if ((argc - 1) % 2 != 0)
	{
		return std::nullopt;
	}

	Args args = {};

	args.inputFileName = argv[1];
	args.outputFileName = argv[2];

	for (int i = 3; i < argc; i += 2)
	{
		std::string first = argv[i];
		std::string second = argv[i + 1];

		if (first.empty() || second.empty() || !ValidateValue(first) || !ValidateValue(second))
		{
			return std::nullopt;
		}

		args.params.emplace(first, second);
	}

	return args;
}

// не используется pos
// size_t
void ReplaceSubString(std::string& str,const std::string& newString, int length, int pos)
{
	str.erase(str.length() - length, length);

	str = str + newString;
}

// Add 
void AddNodeBohr(std::vector<Node>& bohr, const std::string& str)
{
	int vert = 0;

	for (int i = 0; i < str.length(); ++i)
	{
		char ch;
		if (str[i] == ' ')
		{
			ch = str[i] - ' ' + MAX_COUNT_CHARS - 1;
		}
		else
		{
			ch = str[i] - 'a';
		}

		if (bohr[vert].to[ch] == -1)
		{
			// emplace_back(bohr[vert].value + str[i])
			bohr.push_back(Node(bohr[vert].value + str[i]));
			bohr[vert].to[ch] = (int)(bohr.size()) - 1;
		}

		vert = bohr[vert].to[ch];
	}

	bohr[vert].isTerm = true;
	bohr[vert].length = (int)(str.length());
}

void InitLinksOnBohr(std::vector<Node>& bohr)
{
	bohr[0].link = 0;

	for (int ch = 0; ch < MAX_COUNT_CHARS; ch++)
	{
		if (bohr[0].to[ch] != -1)
		{
			continue;
		}

		bohr[0].to[ch] = 0;
	}

	std::queue<int> queueVert;
	queueVert.push(0);

	while (!queueVert.empty())
	{
		int vert = queueVert.front();
		queueVert.pop();

		for (int c = 0; c < MAX_COUNT_CHARS; c++)
		{
			int child = bohr[vert].to[c];

			if (bohr[child].link != -1)
			{
				continue;
			}

			bohr[child].link = (vert == 0) ? 0 : bohr[bohr[vert].link].to[c];

			for (int d = 0; d < MAX_COUNT_CHARS; d++)
			{
				if (bohr[child].to[d] != -1)
				{
					continue;
				}

				bohr[child].to[d] = bohr[bohr[child].link].to[d];
			}

			queueVert.push(child);
		}
	}
}

void Bohr_init(std::vector<Node>& bohr)// неверное название
{
	bohr.push_back(Node(""));
}

bool ValidateValue(const std::string str)
{
	for (char ch : str)
	{
		if ('a' > ch || 'z' < ch)
		{
			if (ch == ' ')
			{
				continue;
			}
			return false;
		}
	}
	return true;
}

void AddNodesFromMap(std::vector<Node>& bohr, const std::map<std::string, std::string>& params)
{
	for (auto& param : params)
	{
		AddNodeBohr(bohr, param.first);
	}
}

std::string ExpandTemplate(const std::vector<Node>& bohr, const std::string& tpl, std::map<std::string, std::string> params)
{
	int v = 0;
	std::string result;
	for (int i = 0; i < tpl.length(); ++i)
	{
		result = result + tpl[i];

		char ch;
		if (tpl[i] == ' ')
		{
			ch = tpl[i] - ' ' + MAX_COUNT_CHARS - 1;
		}
		else
		{
			ch = tpl[i] - 'a';
		}

		v = bohr[v].to[ch];

		if (bohr[v].isTerm == true)
		{
			if (i + 1 < tpl.length())
			{
				char next;

				if (tpl[i + 1] == ' ')
				{
					next = tpl[i + 1] - ' ' + MAX_COUNT_CHARS - 1;
				}
				else
				{
					next = tpl[i + 1] - 'a';
				}
				
				if (bohr[v].value + tpl[i + 1] == bohr[bohr[v].to[next]].value)
				{
					continue;
				}
			}
			
			ReplaceSubString(result, params.find(bohr[v].value)->second, bohr[v].length, (i - bohr[v].length) + 1);
		}
	}
	return result;
}