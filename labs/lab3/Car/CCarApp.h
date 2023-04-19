#pragma once

#include "CCar.h"

class CCarApp
{
public:
	CCarApp(CCar& car, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	bool Info(const int args);
	bool EngineOn(const int args);
	bool EngineOff(const int args);
	bool SetGear(const int args);
	bool SetSpeed(const int args);
	int ConvertGearToInt(const CCar::Gear& gear);
	CCar::Gear ConvertIntToGear(const int gear);
	std::string ConvertDirectionToString(const CCar::Direction& d);

	using Handler = std::function<bool(int args)>;

	using ActionMap = std::map<std::string, Handler>;

	CCar& m_car;
	std::istream& m_input;
	std::ostream& m_output;
	const ActionMap m_actionMap;
};