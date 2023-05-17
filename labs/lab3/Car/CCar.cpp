#include "CCar.h"
// не стоит хранить m_direction ++
// TurnOff разобраться почему Unknown command ++
bool CCar::IsTurnedOn()
{
	return m_engineState;
}

CCar::Gear CCar::GetGear()
{
	return m_gear;
}

int CCar::GetSpeed() 
{
	return m_speed;
}

CCar::Direction CCar::GetDirection()
{
	if (m_speed < 0)
	{
		return CCar::Direction::BACK;
	}

	if (m_speed > 0)
	{
		return CCar::Direction::FORWARD;
	}

	return CCar::Direction::STAY;
}

bool CCar::TurnOnEngine()
{
	//TODO: лучше проверять состояние включенности и в случае включенного двигаетля выходить
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
// попробовать сделать метод покороче (получилось не сильно короче)
bool CCar::SetGear(const Gear gear)
{//TODO: разделить на методы
	if (gear == Gear::NEUTRAL)
	{
		m_gear = gear;
		return true;
	}

	if (!m_engineState)
	{
		return false;
	}

	if (gear != Gear::REVERSE && GetDirection() == Direction::BACK)
	{
		return false;
	}

	if (gear == Gear::REVERSE)
	{
		if (m_speed == 0 || m_gear == Gear::REVERSE)
		{
			m_gear = gear;
			return true;
		}
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

bool CCar::SetSpeed(const int speed)
{
	if (!m_engineState)
	{
		return false;
	}

	if (m_gear == Gear::NEUTRAL && speed != 0)
	{
		if (m_speed > speed && speed >= MIN_SPEED)
		{
			m_speed = speed;
			return true;
		}
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
		if (m_gear == CCar::Gear::REVERSE)
		{
			m_speed = -speed;
			return true;
		}
		
		m_speed = speed;
		return true;
	}

	return false;
}