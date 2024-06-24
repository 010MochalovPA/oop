#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../CMyString/MyString.h"

SCENARIO("�������� ������������� MyString")
{
	WHEN("������� ������ ������")
	{
		MyString string;

		THEN("������ ������ � ����� ����� 0")
		{
			CHECK(string.GetLength() == 0);
			CHECK(string.GetStringData()[0] == CODE_ZERO_CHAR);
			CHECK(std::strcmp(string.GetStringData(), "") == 0);
		}
	}
	
	GIVEN("������� ������ �� std::string")
	{
		std::string stlString("std::string");

		THEN("������� MyString �� std::string")
		{
			MyString string(stlString);

			THEN("������ ��������� �����")
			{
				CHECK(string.GetLength() == 11);
				CHECK(string.GetStringData()[string.GetLength()] == CODE_ZERO_CHAR);
				CHECK(std::strcmp(string.GetStringData(), "std::string") == 0);
			}
		}
	}

	GIVEN("������� ������ const char*")
	{
		WHEN("������� ������")
		{
			MyString string("string\0");

			THEN("������ �������� ��� ����������� �������")
			{
				CHECK(string.GetLength() == 6);
				CHECK(string.GetStringData()[string.GetLength()] == CODE_ZERO_CHAR);
				CHECK(std::strcmp(string.GetStringData(), "string") == 0);
			}

			THEN("������� ������ �� ���� ���������� ������ ��������")
			{
				MyString string("string\0", 7);

				THEN("�������� ������ ����������� ������")
				{
					CHECK(string.GetLength() == 7);
					CHECK(string.GetStringData()[string.GetLength()] == CODE_ZERO_CHAR);
					CHECK(std::equal(string.GetStringData(), string.GetStringData() + string.GetLength(), "string\0"));
				}
			}
		}
	}
}

SCENARIO("�������� ������������� ����������� � �����������")
{
	MyString string1("test1");
	MyString string2("test2");

	WHEN("��������� �������� ����������")
	{
		string2 = string1;

		THEN("���������� ������")
		{
			CHECK((string1 == string2));
		}

		THEN("���������� ������ test3")
		{
			MyString string3("test3");
			string2 += string3;

			THEN("������ ������ ����������, ������ ���")
			{
				CHECK(std::strcmp(string2.GetStringData(), "test1test3") == 0);
				CHECK(std::strcmp(string3.GetStringData(), "test3") == 0);
			}
		}

		THEN("��������� �� ������� ������")
		{
			CHECK(string2.GetStringData()[string2.GetLength()] == CODE_ZERO_CHAR);
		}
	}

	WHEN("������� ������ ��� ������ ������������ �����������")
	{
		MyString string3(std::move(string1));

		THEN("���������� ������")
		{
			CHECK(std::strcmp(string3.GetStringData(), "test1") == 0);
		}

		THEN("��������� �� ������� ������")
		{
			CHECK(string3.GetStringData()[string3.GetLength()] == CODE_ZERO_CHAR);
		}
	}
}

SCENARIO("�������� ������� MyString")
{
	GIVEN("����� ������")
	{
		MyString string("string1");

		WHEN("��������� SubString")
		{
			MyString subString = string.SubString(0, 3);
			
			THEN("��������� ����� ����� � ��������� ������ - ������ � ������� �����")
			{
				CHECK(std::strcmp(subString.GetStringData(), "str") == 0);
				CHECK(subString.GetLength() == 3);
				CHECK(subString.GetStringData()[subString.GetLength()] == CODE_ZERO_CHAR);
			}
		}

		THEN("��������� ��������� ������� � Substring")
		{
			CHECK_THROWS(string.SubString(string.GetLength(), 1));
		}

		WHEN("��������� SubString c �������� �������")
		{
			MyString subString = string.SubString(3, 100);

			THEN("������� ������ ��������� ���������� ��������")
			{
				CHECK(std::strcmp(subString.GetStringData(), "ing1") == 0);
				CHECK(subString.GetLength() == 4);
				CHECK(subString.GetStringData()[subString.GetLength()] == CODE_ZERO_CHAR);
			}
		}

		WHEN("��������� SubString c �������� ������� ��� �������� �������")
		{
			MyString subString = string.SubString(3);

			THEN("������� ������ ��������� ���������� ��������")
			{
				CHECK(std::strcmp(subString.GetStringData(), "ing1") == 0);
				CHECK(subString.GetLength() == 4);
				CHECK(subString.GetStringData()[subString.GetLength()] == CODE_ZERO_CHAR);
			}
		}

		WHEN("��������� Clear()")
		{
			string.Clear();

			THEN("������ ������")
			{
				CHECK(std::strcmp(string.GetStringData(), "") == 0);
				CHECK(string.GetLength() == 0);
				CHECK(string.GetStringData()[0] == CODE_ZERO_CHAR);
			}
		}
	}
}

SCENARIO("�������� ��������� ������������")
{
	WHEN("��������� MyString + MyString + MyString")
	{
		MyString string1("test");
		MyString string2(" ");
		MyString string3("MyString");
		MyString string = string1 + string2 + string3;

		THEN("������� ���������� ���������")
		{
			CHECK(string.GetLength() == 13);
			CHECK(std::strcmp(string.GetStringData(), "test MyString") == 0);
			CHECK(string.GetStringData()[string.GetLength()] == CODE_ZERO_CHAR);
		}
	}

	
	WHEN("��������� MyString + const char* + const char*")
	{
		MyString string1("test");
		const char* string2 = " ";
		const char* string3 = "const char*";
		MyString string = string1 + string2 + string3;

		THEN("������� ���������� ���������")
		{
			CHECK(string.GetLength() == 16);
			CHECK(std::strcmp(string.GetStringData(), "test const char*") == 0);
			CHECK(string.GetStringData()[string.GetLength()] == CODE_ZERO_CHAR);
		}
	}

	WHEN("��������� MyString + std::string")
	{
		std::string stlString1("test");
		MyString string2(" ");
		std::string stlString3("stlString");
		MyString string = stlString1 + string2 + stlString3;

		THEN("������� ���������� ���������")
		{
			CHECK(string.GetLength() == 14);
			CHECK(std::strcmp(string.GetStringData(), "test stlString") == 0);
			CHECK(string.GetStringData()[string.GetLength()] == CODE_ZERO_CHAR);
		}
	}
}

SCENARIO("�������� spaceship ��������")
{
	GIVEN("������� ������")
	{
		MyString string1("1");
		MyString string2("2");
		MyString string3("3");

		THEN("��������� �������� ==")
		{
			CHECK_FALSE(string1 == string2);
			CHECK(string1 == "1");
		}

		THEN("��������� �������� > � <")
		{
			CHECK(string2 > string1);
			CHECK(string2 < string3);
		}

		THEN("��������� >= � <=")
		{
			CHECK(string2 >= string1);
			CHECK(string1 <= string2);
			CHECK(string1 <= string3);
			CHECK(string3 >= string3);
		}

		THEN("��������� !=")
		{
			CHECK(string1 != string2);
		}
	}
}


SCENARIO("�������� ��������� ��������� � ������� �� ������� []")
{
	GIVEN("������� MyString")
	{
		const std::string stlString = "Hello world!";
		MyString string(stlString);

		THEN("����� ������� ��� ������")
		{
			char char1 = string[0];

			THEN("������� ���������� ���������")
			{
				CHECK(char1 == stlString[0]);
			}

			THEN("�������� char")
			{
				char1 = CODE_ZERO_CHAR;
				CHECK(char1 == CODE_ZERO_CHAR);
			}
		}

		WHEN("����� ������� ��� ������")
		{
			const char char1 = string[1];

			THEN("������� ���������� ���������")
			{
				CHECK(char1 == stlString[1]);
			}
		}
	}
}

SCENARIO("�������� ���������� ����� ������ � �����")
{
	GIVEN("C������ MyString � stringstream")
	{
		MyString string1("string");
		std::stringstream stream;

		WHEN("������� ������ � �����")
		{
			stream << string1;

			THEN("������� ���������� ���������")
			{
				CHECK(stream.str() == "string");
			}

			THEN("������ ������ �� ������")
			{
				MyString string2;
				stream >> string2;

				THEN("������� ���������� ���������")
				{
					CHECK(string2 == string1);
				}
			}
		}
	}
}