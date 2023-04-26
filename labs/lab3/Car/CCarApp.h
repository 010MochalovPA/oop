#pragma once

#include "CCar.h"

class CCarApp
{
public:
	CCarApp(CCar& car, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	bool Info(const int arg);
	bool EngineOn(const int arg);
	bool EngineOff(const int arg);
	bool SetGear(const int arg);
	bool SetSpeed(const int arg);
	int ConvertGearToInt(const CCar::Gear& gear);
	CCar::Gear ConvertIntToGear(const int gear);
	std::string ConvertDirectionToString(const CCar::Direction& d);

	using Handler = std::function<bool(int arg)>;
	using ActionMap = std::map<std::string, Handler>;
	const ActionMap m_actionMap;

	CCar& m_car;
	std::istream& m_input;
	std::ostream& m_output;
};