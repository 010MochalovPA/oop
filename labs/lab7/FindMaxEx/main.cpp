#include "./FindMaxEx.h"
#include <iostream>
#include <string>

struct Athlete
{
	std::string name;
	float height = 0.f;
	float weight = 0.f;
};

int main()
{
	std::vector<Athlete> athletes = {
		{ "first athlete", 1, 2 },
		{ "second athlete", 2, 3 },
		{ "third athlete", 3, 4 },
		{ "fourth athlete", 2, 5 }
	};
	
	Athlete heaviestAthlete;

	auto weightLess = [](const Athlete& a, const Athlete& b) {
		return a.weight < b.weight;
	};

	if (FindMaxEx(athletes, heaviestAthlete, weightLess))
	{
		std::cout << "Heaviest athlete: " << heaviestAthlete.name << ", Weight: " << heaviestAthlete.weight << std::endl;
	}
	else
	{
		std::cout << "No athletes to compare." << std::endl;
	}

	
	Athlete tallestAthlete;

	auto heightLess = [](const Athlete& a, const Athlete& b) {
		return a.height < b.height;
	};

	if (FindMaxEx(athletes, tallestAthlete, heightLess))
	{
		std::cout << "Tallest athlete: " << tallestAthlete.name << ", Height: " << tallestAthlete.height << std::endl;
	}
	else
	{
		std::cout << "No athletes to compare." << std::endl;
	}

	return 0;
}