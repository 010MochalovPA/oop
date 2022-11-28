#include <iostream>
#include <fstream>

using namespace std;
void CloseStreams(ifstream& input, ofstream& output);

void CloseStreams(ifstream& input, ofstream& output)
{
	input.close();
	output.close();
}

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		cout << "Invalid arguments count" << endl
			<< "Usage: copyfile.exe <input file> <output file>" << endl;
		return 1;
	}

	// Объявили переменную типа ifstream 
	// (input file stream, поток для чтения из файла), проинициализировав его
	// именем входного файла
	
	ifstream input(argv[1]);

	// вызываем метод is_open() у объекта input,
	// который вернет true, если файл был открыт
	if (!input.is_open()) 
	{
		cout << "Failed to open " << argv[1] << " for reading" << endl;
		return 1;
 	}

	// создали поток для записи в выходной файл
	ofstream output(argv[2]);
	if (!output.is_open())
	{
		cout << "Failed to open " << argv[2] << " for writing" << endl;
		input.close();
		return 1;
	}

	char ch;
	// Считываем в переменную ch символ из входного потока
	// возвращаем значение, приводимое к bool, которое сигнализирует об успехе
	while (input.get(ch))
	{
		if (!output.put(ch))
		{
			cout << "Failed to save data on disk" << endl;
			CloseStreams(input, output);
			return 1;
		}
	}

	if (!output.flush()) // Если не удалось сбросить данные на диск
	{
		cout << "Failed to save data on disk" << endl;
		CloseStreams(input, output);
		return 1;
	}

	CloseStreams(input, output);
	return 0;
}
