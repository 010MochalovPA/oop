#pragma once
#include "stdafx.h"

const int MAX_SPEED = 150;
const int MIN_SPEED = 0;

class CCar
{
public:
	enum class Gear {
		REVERSE = -1,
		NEUTRAL,
		FIRST,
		SECOND,
		THIRD,
		FOURTH,
		FIFTH,
	};

	enum class Direction {
		FORWARD,
		BACK,
		STAY,
	};

	// можно присвоить значения полям ++

	bool TurnOnEngine();
	bool TurnOffEngine();
	// не использовать конст ++
	// enum передаем по знгачению ++
	bool SetGear(const Gear gear);
	bool SetSpeed(const int speed);

	bool IsTurnedOn();
	Direction GetDirection();
	int GetSpeed();
	Gear GetGear();

private:
	const struct SpeedRange
	{
		int min;
		int max;
	};

	using GearRanges = std::map<Gear, SpeedRange>;

	// поля класса лучше перекинуть вниз ++
	// сделать поле статическим и константным ++
	const static inline CCar::GearRanges m_gearRanges = { 
		{ Gear::REVERSE, { 0, 20 } },
		{ Gear::NEUTRAL, { 0, 150 } },
		{ Gear::FIRST, { 0, 30 } },
		{ Gear::SECOND, { 20, 50 } },
		{ Gear::THIRD, { 30, 60 } },
		{ Gear::FOURTH, { 40, 90 } },
		{ Gear::FIFTH, { 50, 150 } }
	};

	int m_speed = 0;
	Gear m_gear = Gear::NEUTRAL;
	bool m_engineState = false;
};