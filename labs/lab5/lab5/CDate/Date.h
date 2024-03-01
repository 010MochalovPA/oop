#pragma once

#include <iomanip>
#include <iostream>
#include <map>

enum class Month
{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

enum class WeekDay
{
	SUNDAY = 0,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
};

struct DateStruct
{
	unsigned int day;
	Month month;
	unsigned int year;
};

class Date
{
public:
	explicit Date(unsigned int day, Month month, unsigned int year);
	explicit Date(unsigned int timestamp);

	unsigned int GetDay() const;
	Month GetMonth() const;
	unsigned int GetYear() const;
	WeekDay GetWeekDay() const;
	bool IsValid() const;
	DateStruct TimestampToDate(unsigned int timestamp) const;
	unsigned int GetTimestamp() const;

	Date operator++();
	Date operator++(int);
	Date operator--();
	Date operator--(int);
	Date operator+(int days) const;
	Date operator-(int days) const;
	int operator-(const Date& date) const;
	Date& operator+=(int days);
	Date& operator-=(int days);
	
	auto operator<=>(Date const& date) const = default;

	friend std::ostream& operator<<(std::ostream& stream, const Date& date);
	friend std::istream& operator>>(std::istream& stream, Date& date);
	friend Date operator+(int days, const Date& date);

private:
	unsigned int m_timestamp;
};

// Операцию находящую разницу двух дат ++
// Прибавлять к дням дату ++