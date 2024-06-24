#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../CMyString/MyString.h"

SCENARIO("Проверка конструкторов MyString")
{
	WHEN("Создаем пустую строку")
	{
		MyString string;

		THEN("Строка пустая и длина равна 0")
		{
			CHECK(string.GetLength() == 0);
			CHECK(string.GetStringData()[0] == CODE_ZERO_CHAR);
			CHECK(std::strcmp(string.GetStringData(), "") == 0);
		}
	}
	
	GIVEN("Создаем строку из std::string")
	{
		std::string stlString("std::string");

		THEN("Создаем MyString из std::string")
		{
			MyString string(stlString);

			THEN("Строка создалась верно")
			{
				CHECK(string.GetLength() == 11);
				CHECK(string.GetStringData()[string.GetLength()] == CODE_ZERO_CHAR);
				CHECK(std::strcmp(string.GetStringData(), "std::string") == 0);
			}
		}
	}

	GIVEN("Создаем строку const char*")
	{
		WHEN("Создаем строку")
		{
			MyString string("string\0");

			THEN("Строка содержит все необходимые символы")
			{
				CHECK(string.GetLength() == 6);
				CHECK(string.GetStringData()[string.GetLength()] == CODE_ZERO_CHAR);
				CHECK(std::strcmp(string.GetStringData(), "string") == 0);
			}

			THEN("Создаем строку из всей изначальой строки символов")
			{
				MyString string("string\0", 7);

				THEN("Получаем полную изначальную строку")
				{
					CHECK(string.GetLength() == 7);
					CHECK(string.GetStringData()[string.GetLength()] == CODE_ZERO_CHAR);
					CHECK(std::equal(string.GetStringData(), string.GetStringData() + string.GetLength(), "string\0"));
				}
			}
		}
	}
}

SCENARIO("Проверка конструкторов копирования и перемещения")
{
	MyString string1("test1");
	MyString string2("test2");

	WHEN("Выполняем операцию присвоения")
	{
		string2 = string1;

		THEN("Сравниваем строки")
		{
			CHECK((string1 == string2));
		}

		THEN("Прибавляем строку test3")
		{
			MyString string3("test3");
			string2 += string3;

			THEN("Первая строка изменилась, вторая нет")
			{
				CHECK(std::strcmp(string2.GetStringData(), "test1test3") == 0);
				CHECK(std::strcmp(string3.GetStringData(), "test3") == 0);
			}
		}

		THEN("Проверяем на нулевой символ")
		{
			CHECK(string2.GetStringData()[string2.GetLength()] == CODE_ZERO_CHAR);
		}
	}

	WHEN("Создаем строку при помощи конструктора перемещения")
	{
		MyString string3(std::move(string1));

		THEN("Сравниваем строки")
		{
			CHECK(std::strcmp(string3.GetStringData(), "test1") == 0);
		}

		THEN("Проверяем на нулевой символ")
		{
			CHECK(string3.GetStringData()[string3.GetLength()] == CODE_ZERO_CHAR);
		}
	}
}

SCENARIO("Проверка методов MyString")
{
	GIVEN("Новая строка")
	{
		MyString string("string1");

		WHEN("Проверяем SubString")
		{
			MyString subString = string.SubString(0, 3);
			
			THEN("Подстрока взята верно и последний символ - символ с нулевым кодом")
			{
				CHECK(std::strcmp(subString.GetStringData(), "str") == 0);
				CHECK(subString.GetLength() == 3);
				CHECK(subString.GetStringData()[subString.GetLength()] == CODE_ZERO_CHAR);
			}
		}

		THEN("Проверяем начальную позицию в Substring")
		{
			CHECK_THROWS(string.SubString(string.GetLength(), 1));
		}

		WHEN("Проверяем SubString c третьего символа")
		{
			MyString subString = string.SubString(3, 100);

			THEN("Берется только доступное количество символов")
			{
				CHECK(std::strcmp(subString.GetStringData(), "ing1") == 0);
				CHECK(subString.GetLength() == 4);
				CHECK(subString.GetStringData()[subString.GetLength()] == CODE_ZERO_CHAR);
			}
		}

		WHEN("Проверяем SubString c третьего символа без указания размера")
		{
			MyString subString = string.SubString(3);

			THEN("Берется только доступное количество символов")
			{
				CHECK(std::strcmp(subString.GetStringData(), "ing1") == 0);
				CHECK(subString.GetLength() == 4);
				CHECK(subString.GetStringData()[subString.GetLength()] == CODE_ZERO_CHAR);
			}
		}

		WHEN("Проверяем Clear()")
		{
			string.Clear();

			THEN("Строка пустая")
			{
				CHECK(std::strcmp(string.GetStringData(), "") == 0);
				CHECK(string.GetLength() == 0);
				CHECK(string.GetStringData()[0] == CODE_ZERO_CHAR);
			}
		}
	}
}

SCENARIO("Проверка оператора конкатинации")
{
	WHEN("Проверяем MyString + MyString + MyString")
	{
		MyString string1("test");
		MyString string2(" ");
		MyString string3("MyString");
		MyString string = string1 + string2 + string3;

		THEN("Ожидаем корректный результат")
		{
			CHECK(string.GetLength() == 13);
			CHECK(std::strcmp(string.GetStringData(), "test MyString") == 0);
			CHECK(string.GetStringData()[string.GetLength()] == CODE_ZERO_CHAR);
		}
	}

	
	WHEN("Проверяем MyString + const char* + const char*")
	{
		MyString string1("test");
		const char* string2 = " ";
		const char* string3 = "const char*";
		MyString string = string1 + string2 + string3;

		THEN("Ожидаем корректный результат")
		{
			CHECK(string.GetLength() == 16);
			CHECK(std::strcmp(string.GetStringData(), "test const char*") == 0);
			CHECK(string.GetStringData()[string.GetLength()] == CODE_ZERO_CHAR);
		}
	}

	WHEN("Проверяем MyString + std::string")
	{
		std::string stlString1("test");
		MyString string2(" ");
		std::string stlString3("stlString");
		MyString string = stlString1 + string2 + stlString3;

		THEN("Ожидаем корректный результат")
		{
			CHECK(string.GetLength() == 14);
			CHECK(std::strcmp(string.GetStringData(), "test stlString") == 0);
			CHECK(string.GetStringData()[string.GetLength()] == CODE_ZERO_CHAR);
		}
	}
}

SCENARIO("Проверка spaceship оператор")
{
	GIVEN("Создаем строку")
	{
		MyString string1("1");
		MyString string2("2");
		MyString string3("3");

		THEN("Проверяем оператор ==")
		{
			CHECK_FALSE(string1 == string2);
			CHECK(string1 == "1");
		}

		THEN("Проверяем оператор > и <")
		{
			CHECK(string2 > string1);
			CHECK(string2 < string3);
		}

		THEN("Проверяем >= и <=")
		{
			CHECK(string2 >= string1);
			CHECK(string1 <= string2);
			CHECK(string1 <= string3);
			CHECK(string3 >= string3);
		}

		THEN("Проверяем !=")
		{
			CHECK(string1 != string2);
		}
	}
}


SCENARIO("Проверка оператора обращения к символу по индексу []")
{
	GIVEN("Создаем MyString")
	{
		const std::string stlString = "Hello world!";
		MyString string(stlString);

		THEN("Берем элемент для записи")
		{
			char char1 = string[0];

			THEN("Ожидаем корректный результат")
			{
				CHECK(char1 == stlString[0]);
			}

			THEN("Изменяем char")
			{
				char1 = CODE_ZERO_CHAR;
				CHECK(char1 == CODE_ZERO_CHAR);
			}
		}

		WHEN("Берем элемент для чтения")
		{
			const char char1 = string[1];

			THEN("Ожидаем корректный результат")
			{
				CHECK(char1 == stlString[1]);
			}
		}
	}
}

SCENARIO("Проверка операторов ввода вывода в поток")
{
	GIVEN("Cоздаем MyString и stringstream")
	{
		MyString string1("string");
		std::stringstream stream;

		WHEN("Выводим строку в поток")
		{
			stream << string1;

			THEN("Ожидаем корректный результат")
			{
				CHECK(stream.str() == "string");
			}

			THEN("Читаем строку из потока")
			{
				MyString string2;
				stream >> string2;

				THEN("Ожидаем корректный результат")
				{
					CHECK(string2 == string1);
				}
			}
		}
	}
}