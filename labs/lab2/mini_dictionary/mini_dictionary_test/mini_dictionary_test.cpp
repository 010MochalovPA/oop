#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../mini_dictionary.h"

TEST_CASE("Testing trim function")
{
	std::string test1 = "   test";
	CHECK(Trim(test1) == "test");

	std::string test2 = "test  ";
	CHECK(Trim(test2) == "test");

	std::string test3 = "   test  ";
	CHECK(Trim(test3) == "test");
}

TEST_CASE("Testing translation")
{
	Translations translation = SplitStringIntoTranstations("машина, , автомобиль, авто", ',');
	
	CHECK(translation == std::set<std::string>{ "машина", "автомобиль", "авто" });
	CHECK(translation.size() == 3);
}

TEST_CASE("Testing adding retranslations")
{
	Dictionary dictionary = {};
	AddTranslation(dictionary, "car", "машина, автомобиль");
	AddTranslation(dictionary, "car", "автомобиль, автомашина");
	AddTranslation(dictionary, "cat", "кот, кошка");

	auto result = dictionary.find("car");
	CHECK(result->second == std::set<std::string>{ "машина", "автомобиль", "автомашина" });
	CHECK(result->second.size() == 3);
}


