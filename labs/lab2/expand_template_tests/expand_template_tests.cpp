#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../expand_template/expand_template.h"

TEST_CASE("Testing case 1")
{
	
	std::vector<Node> bohr;
	std::map<std::string, std::string> params;

	params.emplace("a"," a ");
	params.emplace("aa", " bb ");
	params.emplace("b", " c ");
	params.emplace("bb", " cc ");
	params.emplace("c", " x ");
	params.emplace("cc", " xx ");
	const std::string tpl = "aabbcc";

	Bohr_init(bohr);

	AddNodesFromMap(bohr, params);

	InitLinksOnBohr(bohr);

	CHECK(ExpandTemplate(bohr, tpl, params) == " bb  cc  xx ");
}

TEST_CASE("Testing case 2")
{
	std::map<std::string, std::string> params;

	params.emplace("m", "a");
	params.emplace("a", "m");
	params.emplace("ma", "mama");
	const std::string tpl = "mama";

	std::vector<Node> bohr;
	Bohr_init(bohr);

	AddNodesFromMap(bohr, params);

	InitLinksOnBohr(bohr);

	CHECK(ExpandTemplate(bohr, tpl, params) == "mamamama");
}

TEST_CASE("Testing case 3")
{
	std::map<std::string, std::string> params;

	params.emplace("ma", "mama");
	params.emplace("mama", "mother");
	const std::string tpl = "mama";

	std::vector<Node> bohr;
	Bohr_init(bohr);

	AddNodesFromMap(bohr, params);

	InitLinksOnBohr(bohr);

	CHECK(ExpandTemplate(bohr, tpl, params) == "mother");
}