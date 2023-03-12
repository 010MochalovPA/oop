#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

const size_t LABYRINTH_ROWS = 100;
const size_t LABYRINTH_COLS = 100;
const std::set<char> AVALIBLE_CHARS = { ' ', 'A', 'B', '#' };

struct LabField
{
	char value;
	int wave;
};

using Fields = std::array<std::array<LabField, LABYRINTH_COLS>, LABYRINTH_ROWS>;

struct Point
{
	int row;
	int col;
};
// labyrinth
struct Labyrinth
{
	Fields fields;
	Point start;
	Point end;
	bool hasStart;
	bool hasEnd;
	bool hasPath;
};

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

bool IsStartField(char ch)
{
	return (ch == 'A');
}

bool IsEndField(char ch)
{
	return (ch == 'B');
}

bool IsDirectionLeft(const Point& field)
{
	return field.col != 0;
}

bool IsDirectionRight(const Point& field)
{
	return field.col != LABYRINTH_COLS - 1;
}

bool IsDirectionTop(const Point& field)
{
	return field.row != 0;
}

bool IsDirectionBottom(const Point& field)
{
	return field.row != LABYRINTH_ROWS - 1;
}

void SetStartField(Labyrinth& labyrinth,const Point& point)
{
	if (labyrinth.hasStart)
	{
		throw std::runtime_error("Invalid Labyrinth.");
	}

	labyrinth.start = { point.row, point.col };
	labyrinth.fields[point.row][point.col].wave = 1;
	labyrinth.hasStart = true;
}

void SetEndField(Labyrinth& labyrinth, const Point& point)
{
	if (labyrinth.hasEnd)
	{
		throw std::runtime_error("Invalid Labyrinth.");
	}

	labyrinth.end = { point.row, point.col };
	labyrinth.hasEnd = true;
}

Labyrinth GetLabyrinthFromFile(const std::string& inputFileName)
{
	std::ifstream input;
	input.open(inputFileName);

	if (!input.is_open()) // использовать runtime_error
	{
		throw std::runtime_error("Failed to open <input file> for reading");
	}

	std::string line;
		
	Labyrinth labyrinth{};
	int row = 0;
	int col = 0;

	while (std::getline(input, line))
	{
		for (char ch : line)
		{
			if (AVALIBLE_CHARS.find(ch) == AVALIBLE_CHARS.end())
			{
				throw std::runtime_error("Invalid Labyrinth.");
			}

			LabField field = { ch };

			labyrinth.fields[row][col] = field;

			if (IsStartField(labyrinth.fields[row][col].value))
			{
				SetStartField(labyrinth, { row, col });
			}

			if (IsEndField(labyrinth.fields[row][col].value))
			{
				SetEndField(labyrinth, { row, col });
			}

			col++;
		}
		row++;
		col = 0;
	}

	if (!labyrinth.hasStart || !labyrinth.hasEnd)
	{
		throw std::runtime_error("Invalid Labyrinth.");
	}

	return labyrinth;
}

Args ParseArgs(const int& argc, char* argv[])
{
	if (argc != 3)
	{
		throw std::runtime_error("Invalid argument count");
	}

	Args args{};

	args.inputFileName = argv[1];
	args.outputFileName = argv[2];

	if (args.inputFileName.empty() || args.outputFileName.empty())
	{
		throw std::invalid_argument("Invalid argument");
	}

	return args;
}

std::vector<Point> GetCheckableFiedls(const Point& field)
{
	std::vector<Point> checkableFields{};

	if (IsDirectionLeft(field))
	{
		checkableFields.push_back({ field.row, field.col - 1 });
	}

	if (IsDirectionRight(field))
	{
		checkableFields.push_back({ field.row, field.col + 1 });
	}

	if (IsDirectionTop(field))
	{
		checkableFields.push_back({ field.row - 1, field.col});
	}

	if (IsDirectionBottom(field))
	{
		checkableFields.push_back({ field.row + 1, field.col });
	}

	return checkableFields;
}

bool IsAvalibleLabyrinthField(const Labyrinth& labyrinth, const Point& field)
{
	bool isNotBorder = labyrinth.fields[field.row][field.col].value != '#';
	bool notHasWave = !labyrinth.fields[field.row][field.col].wave;
	return isNotBorder && notHasWave;
}

bool IsFieldСontainWave(const Labyrinth& labyrinth, const Point& field)
{
	return labyrinth.fields[field.row][field.col].wave;
}

std::vector<Point> GetAvalibleLabyrinthFieldsAround(const Labyrinth& labyrinth, const Point& field)
{
	std::vector<Point> checkableFields = GetCheckableFiedls(field);

	std::vector<Point> avalibleFields{};

	for (Point field : checkableFields)
	{
		if (IsAvalibleLabyrinthField(labyrinth, field))
		{
			avalibleFields.push_back(field);
		}
	}

	return avalibleFields;
}

std::vector<Point> GetAvalibleWavesFieldsNearby(const Labyrinth& labyrinth, const Point& field)
{
	std::vector<Point> checkableFields = GetCheckableFiedls(field);

	std::vector<Point> avalibleFields{};

	for (Point field : checkableFields)
	{
		if (IsFieldСontainWave(labyrinth, field))
		{
			avalibleFields.push_back(field);
		}
	}

	return avalibleFields;
}

bool IsSameFieds(const Point& cur, const Point& dif)
{
	return cur.row == dif.row && cur.col == dif.col;
}

void DrawDotsToPath(Labyrinth& labyrinth)
{
	Point curField = labyrinth.end;

	while (!IsSameFieds(curField, labyrinth.start))
	{
		Point minField = curField;
		
		std::vector<Point> avalibleFields = GetAvalibleWavesFieldsNearby(labyrinth, minField);

		for (Point field : avalibleFields)
		{
			int currentWavePointValue = labyrinth.fields[field.row][field.col].wave;
			int minWavePointValue = labyrinth.fields[minField.row][minField.col].wave;

			if (currentWavePointValue == 1)
			{
				return;
			}

			if (currentWavePointValue < minWavePointValue)
			{
				minField = field;
			}
		}

		labyrinth.fields[minField.row][minField.col].value = '.';
		curField = minField;
	}
}

bool FindPathToEnd(Labyrinth& labyrinth)
{
	int step = 1;

	Point start = labyrinth.start;
	Point end = labyrinth.end;

	std::queue<Point> queue;
	queue.push(labyrinth.start);

	while (!IsFieldСontainWave(labyrinth, end))
	{
		labyrinth.hasPath = false;
		std::vector<Point> nextFields{};
		step++;

		while (!queue.empty())
		{
			Point field = queue.front();
			queue.pop();
			std::vector<Point> nextAvalibleFields = GetAvalibleLabyrinthFieldsAround(labyrinth, field);
			nextFields.insert(nextFields.end(), nextAvalibleFields.begin(), nextAvalibleFields.end());
		}

		if (!nextFields.empty())
		{
			for (Point field : nextFields)
			{
				labyrinth.fields[field.row][field.col].wave = step;

				labyrinth.hasPath = true;
				queue.push(field);

				if (labyrinth.fields[end.row][end.col].wave)
				{
					std::queue<Point>().swap(queue);
					return true;
				}
			}
		}

		if (!labyrinth.hasPath)
		{
			return false;
		}
	}
	return true;
}

void FindPathInLabyrinth(Labyrinth& labyrinth)
{
	if (FindPathToEnd(labyrinth))
	{
		DrawDotsToPath(labyrinth);
		return;
	}

	throw std::runtime_error("Impossible to find a path");
};

void PrintLabyrinthToFile(std::string& outputFileName, const Labyrinth& labyrinth)
{
	std::ofstream output;
	output.open(outputFileName);

	if (!output.is_open())
	{
		throw std::invalid_argument("Failed to open <output file> for reading");
	}

	for (int row = 0; row < LABYRINTH_ROWS; row++)
	{
		for (int col = 0; col < LABYRINTH_COLS; col++)
		{
			output << labyrinth.fields[row][col].value;
		}

		output << std::endl;
	}
}



int main(int argc, char* argv[])
{
	try
	{
		Args args = ParseArgs(argc, argv);

		Labyrinth labyrinth = GetLabyrinthFromFile(args.inputFileName);
		
		FindPathInLabyrinth(labyrinth);

		PrintLabyrinthToFile(args.outputFileName, labyrinth);

		return 0;
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl
				  << "Usage: labyrinth.exe <input file> <output file>" << std::endl;

		return 1;
	}
}