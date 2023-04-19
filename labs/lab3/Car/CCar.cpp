#include "CCar.h"

bool CCar::IsTurnedOn() const
{
	return m_engineState;
}

CCar::Gear CCar::GetGear() const
{
	return m_gear;
}

int CCar::GetSpeed() const 
{
	return m_speed;
}

CCar::Direction CCar::GetDirection() const
{
	return m_direction;
}

bool CCar::TurnOnEngine()
{
	m_engineState = true;
	return m_engineState;
}

bool CCar::TurnOffEngine()
{
	if (m_speed == 0 && m_gear == Gear::NEUTRAL)
	{
		m_engineState = false;
	}

	return !m_engineState;
}

bool CCar::SetGear(const CCar::Gear& gear)
{
	if (gear == Gear::NEUTRAL)
	{
		m_gear = gear;
		return true;
	}

	if (!m_engineState)
	{
		return false;
	}

	if (gear == Gear::REVERSE && m_speed == 0)
	{
		m_gear = gear;
		return true;
	}

	if (m_direction == Direction::FORWARD && gear == Gear::REVERSE)
	{
		return false;
	}

	if (m_direction == Direction::BACK && gear != Gear::REVERSE)
	{
		return false;
	}

	auto it = m_gearRanges.find(gear);

	if (it == m_gearRanges.end())
	{
		return false;
	}

	auto [min, max] = it->second;

	if (m_speed >= min && m_speed <= max)
	{
		m_gear = gear;
		return true;
	}

	return false;
}

void CCar::SetDirection()
{
	if (m_gear == Gear::REVERSE)
	{
		m_direction = Direction::BACK;
		return;
	}

	if (m_speed == 0)
	{
		m_direction = Direction::STAY;
		return;
	}

	m_direction = Direction::FORWARD;
}

bool CCar::SetSpeed(const int speed)
{
	if (!m_engineState)
	{
		return false;
	}

	if (m_gear == Gear::NEUTRAL && speed != 0)
	{
		return false;
	}

	auto it = m_gearRanges.find(m_gear);

	if (it == m_gearRanges.end())
	{
		return false;
	}

	auto [min, max] = it->second;

	if (speed >= min && speed <= max)
	{
		m_speed = speed;
		CCar::SetDirection();
		return true;
	}

	return false;
}