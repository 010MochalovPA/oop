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
const char START_CHAR = 'A';
const char END_CHAR = 'B';
const char BORDER_CHAR = '#';
const char DOT_CHAR = '.';

struct Field
{
	char value;
	int wave;
};

using Fields = std::array<std::array<Field, LABYRINTH_COLS>, LABYRINTH_ROWS>;

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
	return (ch == START_CHAR);
}

bool IsEndField(char ch)
{
	return (ch == END_CHAR);
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

	if (!input.is_open())
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

			labyrinth.fields[row][col] = { ch };

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

std::vector<Point> GetCheckableFiedlsAround(const Point& field)
{
	std::vector<Point> checkableFields{};

	for (int row = -1; row <= 1; row++)
	{
		for (int col = -1; col <= 1; col++)
		{
			if ((row == 0 && col == 0) || (row != 0 && col != 0))
			{
				continue;
			}

			checkableFields.push_back({ field.row + row, field.col + col });
		}
	}

	return checkableFields;
}

bool IsAvalibleLabyrinthField(const Labyrinth& labyrinth, const Point& field)
{
	bool isNotBorder = labyrinth.fields[field.row][field.col].value != BORDER_CHAR;
	bool hasWave = labyrinth.fields[field.row][field.col].wave;
	return isNotBorder && !hasWave;
}

bool IsFieldСontainWave(const Labyrinth& labyrinth, const Point& field)
{
	return labyrinth.fields[field.row][field.col].wave != 0;
}

std::vector<Point> GetAvalibleWavesFieldsAround(const Labyrinth& labyrinth, const Point& field)
{
	std::vector<Point> checkableFields = GetCheckableFiedlsAround(field);

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

bool IsSameFields(const Point& cur, const Point& dif)
{
	return cur.row == dif.row && cur.col == dif.col;
}

void DrawDotsToPath(Labyrinth& labyrinth)
{
	Point curField = labyrinth.end;

	while (!IsSameFields(curField, labyrinth.start))
	{
		Point minField = curField;
		
		std::vector<Point> avalibleFields = GetAvalibleWavesFieldsAround(labyrinth, minField);

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

		labyrinth.fields[minField.row][minField.col].value = DOT_CHAR;
		curField = minField;
	}
}

std::vector<Point> MarkAndGetAvalibleLabyrinthFieldsAround(Labyrinth& labyrinth, const Point& field, int step)
{
	std::vector<Point> checkableFields = GetCheckableFiedlsAround(field);

	std::vector<Point> avalibleFields{};

	for (Point field : checkableFields)
	{
		if (IsAvalibleLabyrinthField(labyrinth, field))
		{
			labyrinth.fields[field.row][field.col].wave = step;
			labyrinth.hasPath = true;
			avalibleFields.push_back(field);
		}
	}

	return avalibleFields;
}

std::vector<Point> MarkAndGetNextFieldsOnCurrentLevel(std::queue<Point>& queue, Labyrinth& labyrinth, int step)
{
	std::vector<Point> nextFields{};
	while (!queue.empty())
	{
		// как будто многократно попадают одни и теже координаты ++
		std::vector<Point> nextAvalibleFields = MarkAndGetAvalibleLabyrinthFieldsAround(labyrinth, queue.front(), step);
		queue.pop();
		nextFields.insert(nextFields.end(), nextAvalibleFields.begin(), nextAvalibleFields.end());
	}

	return nextFields;
}

bool FindPathToEnd(Labyrinth& labyrinth)
{
	int step = 1;

	std::queue<Point> queue;
	queue.push(labyrinth.start);

	while (!IsFieldСontainWave(labyrinth, labyrinth.end))
	{
		step++;
		labyrinth.hasPath = false;

		// вынести в отдельную функцию ++
		std::vector<Point> nextFields = MarkAndGetNextFieldsOnCurrentLevel(queue, labyrinth, step);

		if (!nextFields.empty())
		{
			for (Point field : nextFields)
			{
				queue.push(field);
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

	throw std::runtime_error("Can't find the path");
};

void PrintLabyrinthToFile(std::string& outputFileName, const Labyrinth& labyrinth)
{
	std::ofstream output;
	output.open(outputFileName);

	if (!output.is_open())
	{
		throw std::invalid_argument("Failed to open <output file> for reading");
	}

	// использоват range-based for ++
	for (const auto& row : labyrinth.fields)
	{
		for (const auto& field : row)
		{
			output << field.value;
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