#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../FindMaxEx/FindMaxEx.h"

TEST_CASE("FindMaxEx function tests")
{
	SECTION("Empty vector")
	{
		std::vector<int> numbers = {};
		int maxNumber = 0;
		auto result = FindMaxEx(numbers, maxNumber, [](int a, int b) { return a < b; });
		REQUIRE(result == false);
		REQUIRE(maxNumber == 0);
	}

	SECTION("Vector = [5, 3, 9, 1] with max = 9")
	{
		std::vector<int> numbers = { 5, 3, 9, 1 };
		int maxNumber = 0;
		auto result = FindMaxEx(numbers, maxNumber, [](int a, int b) { return a < b; });
		REQUIRE(result == true);
		REQUIRE(maxNumber == 9);
	}

	SECTION("Vector = [2.4, 3.1, 0.9] with max = 3.1")
	{
		std::vector<double> numbers = { 2.4, 3.1, 0.9 };
		double maxNumber;
		auto result = FindMaxEx(numbers, maxNumber, [](double a, double b) { return a < b; });
		REQUIRE(result == true);
		REQUIRE(maxNumber == 3.1);
	}

	SECTION("Vector = [-0.5, -2.3, 3.0] with max = 3.0")
	{
		std::vector<double> numbers = { -0.5, -2.3, 3.0 };
		double maxNumber;
		auto result = FindMaxEx(numbers, maxNumber, [](double a, double b) { return a < b; });
		REQUIRE(result == true);
		REQUIRE(maxNumber == 3.0);
	}

	SECTION("Vector = ['x', 'm', 'a'] with max = 'x'")
	{
		std::vector<char> chars = { 'x', 'm', 'a' };
		char maxChar;
		auto result = FindMaxEx(chars, maxChar, [](char a, char b) { return a < b; });
		REQUIRE(result == true);
		REQUIRE(maxChar == 'x');
	}

	SECTION("Vector = ['def', 'ghi', 'abc'] with max = 'ghi'")
	{
		std::vector<std::string> strings = { "def", "ghi", "abc" };
		std::string maxString;
		auto result = FindMaxEx(strings, maxString, [](const std::string& a, const std::string& b) { return a < b; });
		REQUIRE(result == true);
		REQUIRE(maxString == "ghi");
	}

	SECTION("Vector = [8] with max = 8")
	{
		std::vector<int> numbers = { 8 };
		int maxNumber = 0;
		auto result = FindMaxEx(numbers, maxNumber, [](int a, int b) { return a < b; });
		REQUIRE(result == true);
		REQUIRE(maxNumber == 8);
	}

	SECTION("Vector = [{'Anna', 24}, {'Eve', 28}, {'John', 21}] with max age")
	{
		struct Person
		{
			std::string name;
			int age;
		};
		std::vector<Person> persons = {
			{ "Anna", 24 },
			{ "Eve", 28 },
			{ "John", 21 },
		};
		Person maxPerson;
		auto result = FindMaxEx(persons, maxPerson, [](const Person& a, const Person& b) { return a.age < b.age; });
		REQUIRE(result == true);
		REQUIRE(maxPerson.name == "Eve");
		REQUIRE(maxPerson.age == 28);
	}
}

TEST_CASE("All values are the same")
{
	std::vector<int> numbers = { 7, 7, 7, 7, 7 };
	int maxNumber = 0;
	auto result = FindMaxEx(numbers, maxNumber, [](int a, int b) { return a < b; });
	REQUIRE(result == true);
	REQUIRE(maxNumber == 7);
}

TEST_CASE("Multiple maximum values")
{
	std::vector<int> numbers = { 10, 3, 10, 1, 5, 10 };
	int maxNumber = 0;
	auto result = FindMaxEx(numbers, maxNumber, [](int a, int b) { return a < b; });
	REQUIRE(result == true);
	REQUIRE(maxNumber == 10);
}