#include "Date.h"

constexpr unsigned int DAYS_IN_NON_LEAP_YEAR = 365;
constexpr unsigned int DAYS_IN_LEAP_YEAR = 366;
constexpr unsigned int START_YEAR = 1970;
constexpr unsigned int MAX_YEAR = 9999;
constexpr unsigned int MAX_TIMESTAMP = 2932896;
constexpr unsigned int DAYS_IN_WEEK = 7;

namespace
{
	bool IsLeapYear(unsigned int year)
	{
		return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
	}

	unsigned int DaysInMonth(Month month, unsigned int year)
	{
		switch (month)
		{
		case Month::JANUARY:
		case Month::MARCH:
		case Month::MAY:
		case Month::JULY:
		case Month::AUGUST:
		case Month::OCTOBER:
		case Month::DECEMBER:
			return 31;

		case Month::APRIL:
		case Month::JUNE:
		case Month::SEPTEMBER:
		case Month::NOVEMBER:
			return 30;

		case Month::FEBRUARY:
			return IsLeapYear(year) ? 29 : 28;

		default:
			return 0;
		}
	}
}

Date::Date(unsigned int timestamp)
	: m_timestamp(0)
{
	if (timestamp > 0 && timestamp < MAX_TIMESTAMP)
	{
		m_timestamp = timestamp;
	} 
}

Date::Date(unsigned int day, Month month, unsigned int year)
	: m_timestamp(0)
{
	if (year >= START_YEAR && year <= MAX_YEAR)
	{
		for (unsigned int i = START_YEAR; i < year; i++)
		{
			m_timestamp += IsLeapYear(i) ? DAYS_IN_LEAP_YEAR : DAYS_IN_NON_LEAP_YEAR;
		}

		for (int i = 1; i < static_cast<int>(month); i++)
		{
			m_timestamp += DaysInMonth(static_cast<Month>(i), year);
		}

		m_timestamp += day - 1;
	}
}

WeekDay Date::GetWeekDay() const
{
	unsigned int timestampAdjusted = (m_timestamp + 2) % DAYS_IN_WEEK;
	return static_cast<WeekDay>((timestampAdjusted + 5) % DAYS_IN_WEEK);
}

bool Date::IsValid() const
{
	return m_timestamp > 0 && m_timestamp < MAX_TIMESTAMP;
}

int countLeapYears(int startYear, int endYear)
{
	// Функция для расчета количества високосных лет в диапазоне
	auto leapYearsInRange = [](int year) {
		return year / 4 - year / 100 + year / 400;
	};

	// Вызываем функцию для начального и конечного года и находим разницу
	int leapYearsStart = leapYearsInRange(startYear - 1);
	int leapYearsEnd = leapYearsInRange(endYear);

	// Возвращаем разницу, чтобы получить количество високосных лет в диапазоне
	return leapYearsEnd - leapYearsStart;
}

DateStruct Date::TimestampToDate(unsigned int timestamp) const
{
	auto leapYearsInRange = [](unsigned int year) {
		return year / 4 - year / 100 + year / 400;
	};

	unsigned int days = timestamp ;

	unsigned int year = START_YEAR + ((days - (leapYearsInRange(days / DAYS_IN_NON_LEAP_YEAR))) / DAYS_IN_NON_LEAP_YEAR);
	
	const unsigned int countLeapYears = leapYearsInRange(year) - leapYearsInRange(START_YEAR);

	days -= (year - START_YEAR) * DAYS_IN_NON_LEAP_YEAR + countLeapYears - (IsLeapYear(year) ? 1 : 0);
	
	unsigned int month = 1;
	// посчитать без циклов
	unsigned int daysInMonth = DaysInMonth(static_cast<Month>(month), year);
	while (month <= 12 && days >= DaysInMonth(static_cast<Month>(month), year))
	{
		days -= daysInMonth;
		if (days > 0)
		{
			month++;
			daysInMonth = DaysInMonth(static_cast<Month>(month), year);
		}
	}
	return { days + 1, static_cast<Month>(month), year };
}

unsigned int Date::GetTimestamp() const
{
	return m_timestamp;
}

unsigned int Date::GetDay() const
{
	DateStruct date = TimestampToDate(m_timestamp);
	return date.day;
}

Month Date::GetMonth() const
{
	DateStruct date = TimestampToDate(m_timestamp);
	return date.month;
}

unsigned int Date::GetYear() const
{
	DateStruct date = TimestampToDate(m_timestamp);
	return date.year;
}

Date Date::operator++()
{
	if (IsValid())
	{
		m_timestamp++;
	}
	return *this;
}

Date Date::operator++(int)
{
	Date date = *this;
	if (IsValid())
	{
		m_timestamp++;
	}
	return date;
}

Date Date::operator--()
{
	if (IsValid())
	{
		m_timestamp--;
	}
	return *this;
}

Date Date::operator--(int)
{
	Date date = *this;
	if (IsValid())
	{
		m_timestamp--;
	}
	return date;
}

Date Date::operator+(int days) const
{
	if (IsValid() && m_timestamp <= MAX_TIMESTAMP - days)
	{
		return Date(m_timestamp + days);
	}

	return *this;
}


Date Date::operator-(int days) const
{
	if (IsValid() && m_timestamp >= static_cast<unsigned int>(days))
	{
		return Date(m_timestamp - days);
	}

	return *this;
}

int Date::operator-(const Date& date) const
{
	return this->GetTimestamp() - date.GetTimestamp();
}

Date& Date::operator+=(int days)
{
	return *(this + days);
}

Date& Date::operator-=(int days)
{
	return *(this - days);
}

std::ostream& operator<<(std::ostream& stream, const Date& date)
{
	return stream << date.GetDay() << '.' << static_cast<int>(date.GetMonth()) << '.' << date.GetYear();
}

std::istream& operator>>(std::istream& stream, Date& date)
{
	unsigned int day;
	unsigned int year;
	int month;
	char delimiter;

	if (stream >> day >> delimiter && delimiter == '.' && stream >> month >> delimiter && delimiter == '.' && stream >> year)
	{
		date = Date(day, static_cast<Month>(month), year);
	}
	else
	{
		stream.setstate(std::ios::failbit);
	}

	return stream;
}

Date operator+(int days, const Date& date)
{
	return Date(days + date.GetTimestamp());
}