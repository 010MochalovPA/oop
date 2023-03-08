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

using Lab = std::array<std::array<char, LABYRINTH_COLS>, LABYRINTH_ROWS>;
using Waves = std::array<std::array<int, LABYRINTH_COLS>, LABYRINTH_ROWS>;
// labyrinth

class Point
{

public:
	int row;
	int col;
	Point()
	{
		this->row = 0;
		this->col = 0;
	}

	Point(int row, int col)
	{
		this->SetRow(row);
		this->SetCol(col);
	}

	bool isDirectionLeft() const
	{
		return this->col != 0;
	}

	bool isDirectionRight() const
	{
		return this->col != LABYRINTH_COLS - 1;
	}

	bool isDirectionTop() const
	{
		return this->row != 0;
	}

	bool isDirectionBottom() const
	{
		return this->row != LABYRINTH_ROWS - 1;
	}

	int GetRow() const
	{
		return this->row;
	}

	void SetRow(int row)
	{
		this->row = row;
	}

	int GetCol() const
	{
		return this->col;
	}

	void SetCol(int col)
	{
		this->col = col;
	}

	Point GetValue() const
	{
		return { this->row, this->col };
	}
};

class Labyrinth
{
private:
	Lab labyrinth{};
	Waves waves{};
	Point start{};
	Point end{};
	bool hasStart = false;
	bool hasEnd = false;

	std::vector<Point> GetAvalibleNearbyLabyrinthField(const Point& field)
	{
		std::vector<Point> avalibleFields{};

		int row = field.GetRow();
		int col = field.GetCol();

		if (field.isDirectionLeft() && this->labyrinth[row][col - 1] != '#' && !this->waves[row][col - 1])
		{
			Point leftField(row, col - 1);
			avalibleFields.push_back(leftField);
		}

		if (field.isDirectionRight() && this->labyrinth[row][col + 1] != '#' && !this->waves[row][col + 1])
		{
			Point rightField(row, col + 1);
			avalibleFields.push_back(rightField);
		}

		if (field.isDirectionTop() && this->labyrinth[row - 1][col] != '#' && !this->waves[row - 1][col])
		{
			Point topField(row - 1, col);
			avalibleFields.push_back(topField);
		}

		if (field.isDirectionBottom() && this->labyrinth[row + 1][col] != '#' && !this->waves[row + 1][col])
		{
			Point bottomField(row + 1, col);
			avalibleFields.push_back(bottomField);
		}

		return avalibleFields;
	}

	std::vector<Point> GetAvalibleNearbyWavesField(const Point& field)
	{
		std::vector<Point> avalibleFields{};

		int row = field.GetRow();
		int col = field.GetCol();

		if (field.isDirectionLeft() && this->waves[row][col - 1])
		{
			Point leftField(row, col - 1);
			avalibleFields.push_back(leftField);
		}

		if (field.isDirectionRight() && this->waves[row][col + 1])
		{
			Point rightField(row, col + 1);
			avalibleFields.push_back(rightField);
		}

		if (field.isDirectionTop() && this->waves[row - 1][col])
		{
			Point topField(row - 1, col);
			avalibleFields.push_back(topField);
		}

		if (field.isDirectionBottom() && this->waves[row + 1][col])
		{
			Point bottomField(row + 1, col);
			avalibleFields.push_back(bottomField);
		}

		return avalibleFields;
	}

	void SetStartPoint(const Point& point)
	{
		if (this->hasStart)
		{
			throw std::runtime_error("Invalid Labyrinth.");
		}

		this->start = point;
	}

	void SetEndPoint(const Point& point)
	{
		if (this->hasEnd)
		{
			throw std::runtime_error("Invalid Labyrinth.");
		}

		this->end = point;
	}

	void SetWavesFieldValue(const Point& point, int value)
	{
		int row = point.GetRow();
		int col = point.GetCol();

		this->waves[row][col] = value;
	}

	char GetLabyrinthFieldValue(const Point& point)
	{
		int row = point.GetRow();
		int col = point.GetCol();
		return this->labyrinth[row][col];
	}

	char GetWavesFieldValue(const Point& point)
	{
		int row = point.GetRow();
		int col = point.GetCol();
		return this->waves[row][col];
	}

	bool isStartPoint(char ch)
	{
		return (ch == 'A');
	}

	bool isEndPoint(char ch)
	{
		return (ch == 'B');
	}

	void AddNextStepWave(std::vector<Point>& nextPoints, const Point& field, int step, bool& hasPath)
	{
		std::vector<Point> avalibleFields = GetAvalibleNearbyLabyrinthField(field);

		if (avalibleFields.empty())
		{
			return;
		}

		for (Point point : avalibleFields)
		{
			char labyrinthFieldValue = GetLabyrinthFieldValue(point);

			SetWavesFieldValue(point, step);

			if (isEndPoint(labyrinthFieldValue))
			{
				nextPoints.clear();
				return;
			}

			hasPath = true;
			nextPoints.push_back(point);
		}
	}

	bool FindPathToEnd()
	{
		int step = 1;
		std::queue<Point> queue;
		queue.push(this->start);
		while (this->waves[this->end.row][this->end.col] == 0)
		{
			bool hasPath = false;
			step++;
			std::vector<Point> nextPoints{};

			while (!queue.empty())
			{
				Point field = queue.front();
				queue.pop();

				AddNextStepWave(nextPoints, field, step, hasPath);
			}

			if (!nextPoints.empty())
			{
				for (Point point : nextPoints)
				{
					queue.push(point);
				}
			}

			if (!hasPath) // вернуть булевое значение
			{
				return false;
			}
		}
		return true;
	}

	void GetLabyrinthFromFile(const std::string& inputFileName)
	{
		std::ifstream input;
		input.open(inputFileName);

		if (!input.is_open()) // использовать runtime_error
		{
			throw std::runtime_error("Failed to open <input file> for reading");
		}

		std::string line;
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

				this->labyrinth[row][col] = ch;

				if (isStartPoint(this->labyrinth[row][col]))
				{
					SetStartPoint({ row, col });
					this->hasStart = true;
				}

				if (isEndPoint(this->labyrinth[row][col]))
				{
					SetEndPoint({ row, col });
					this->hasEnd = true;
				}

				col++;
			}
			row++;
			col = 0;
		}

		if (!this->hasStart || !this->hasEnd)
		{
			throw std::runtime_error("Invalid Labyrinth.");
		}
	}

public:
	Labyrinth()
	{
		Lab labyrinth{};
	}

	Labyrinth(const std::string& inputFileName)
	{
		GetLabyrinthFromFile(inputFileName);
	}

	void DrawPointsToPath()
	{
		Point curPoint = this->end.GetValue();

		while (curPoint.row != this->start.row || curPoint.col != this->start.col)
		{
			Point minField = curPoint;

			int currentValue = GetWavesFieldValue(minField);

			std::vector<Point> avaliblePoints = GetAvalibleNearbyWavesField(minField);

			for (Point point : avaliblePoints)
			{
				if (waves[point.row][point.col] == 1)
				{
					return;
				}

				if (waves[point.row][point.col] < waves[minField.row][minField.col])
				{
					minField = point;
				}
			}

			labyrinth[minField.row][minField.col] = '.';
			curPoint = minField;
		}
	}

	void GetLabyrinthWithPath()
	{
		int startRow = this->start.GetRow();
		int startCol = this->start.GetCol();

		this->waves[startRow][startCol] = 1;

		if (FindPathToEnd())
		{
			DrawPointsToPath();
		}
		else
		{
			throw std::runtime_error("Invalid Labyrinth.");
		}
	}

	void PrintLabyrinthToFile(std::string& outputFileName)
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
				output << labyrinth[row][col];
			}

			output << std::endl;
		}
	}

	void PrintWaves(std::string& outputFileName) // удалить
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
				output << waves[row][col];
			}

			output << std::endl;
		}
	}
};

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

Args ParseArgs(const int& argc, char* argv[])
{
	if (argc != 3)
	{
		throw std::invalid_argument("Invalid argument count");
	}

	Args args = {};

	args.inputFileName = argv[1];
	args.outputFileName = argv[2];

	if (args.inputFileName.empty() || args.outputFileName.empty())
	{
		throw std::invalid_argument("Invalid argument");
	}

	return args;
}

int main(int argc, char* argv[])
{
	try
	{
		Args args = ParseArgs(argc, argv);

		Labyrinth labyrinth(args.inputFileName);

		labyrinth.GetLabyrinthWithPath();

		labyrinth.PrintLabyrinthToFile(args.outputFileName);

		return 0;
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl
				  << "Usage: labyrinth.exe <input file> <output file>" << std::endl;

		return 1;
	}
}