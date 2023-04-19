#pragma once
#include "stdafx.h"

class CCar
{
public:
	const enum class Gear {
		REVERSE = -1,
		NEUTRAL,
		FIRST,
		SECOND,
		THIRD,
		FOURTH,
		FIFTH,
	};

	const enum class Direction {
		FORWARD,
		BACK,
		STAY,
	};

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(const Gear& gear);
	bool SetSpeed(const int speed);

	bool IsTurnedOn() const;
	Direction GetDirection() const;
	int GetSpeed() const;
	Gear GetGear() const;

private:
	const struct SpeedRange
	{
		int min;
		int max;
	};

	using GearRanges = std::map<Gear, SpeedRange>;

	int m_speed = 0;
	Gear m_gear = Gear::NEUTRAL;
	bool m_engineState = false;
	Direction m_direction = Direction::STAY;
	void SetDirection();
	GearRanges m_gearRanges = { 
		{ Gear::REVERSE, { 0, 20 } },
		{ Gear::NEUTRAL, { 0, 150 } },
		{ Gear::FIRST, { 0, 30 } },
		{ Gear::SECOND, { 20, 50 } },
		{ Gear::THIRD, { 30, 60 } },
		{ Gear::FOURTH, { 40, 90 } },
		{ Gear::FIFTH, { 50, 150 } }
	};
};