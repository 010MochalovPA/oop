#include <fstream>
#include <iostream>

using namespace std;

void CloseStreams(ifstream& input, ofstream& output);
int JoinFiles(int argc, char* argv[]);

void CloseStreams(ifstream& input, ofstream& output)
{
	input.close();
	output.close();
}

int JoinFiles(int argc, char* argv[])
{
	ofstream output(argv[argc - 1], ios::binary);

	if (!output.is_open())
	{
		cout << "Failed to open " << argv[argc - 1] << " for writing" << endl;
		return 1;
	}

	for (int indexFileName = 1; indexFileName < argc - 1; ++indexFileName)
	{
		ifstream input(argv[indexFileName], ios::binary);

		if (!input.is_open())
		{
			cout << "Failed to open " << argv[indexFileName] << " for reading" << endl;
			return 1;
		}

		char ch;
		
		while (input.read(&ch, sizeof(ch)))
		{
			output.write(&ch, sizeof(ch));
		}

		if (!output.flush())
		{
			cout << "Failed to save data on disk\n";
			return 1;
		}

		input.close();
		
	}
	output.close();
	return 0;
}

int main(int argc, char* argv[])
{
	if (argc <= 2)
	{
		cout << "Invalid argument count" << endl
			 << "Usage: join.exe <input file1> ... <input file N> <output file>" << endl;
		return 1;
	}
	
	return JoinFiles(argc, argv);

}