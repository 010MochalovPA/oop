#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../CDate/Date.h"

constexpr unsigned MAX_TIMESTAMP = 2932896;
constexpr unsigned MAX_YEAR = 9999;
constexpr unsigned START_YEAR = 1970;

SCENARIO("Тест операторов инкремента и декремента")
{
	GIVEN("Некоректный таймстомп")
	{
		Date date(2932897);
		THEN("Дата стала 11 апреля 2023 года")
		{
			CHECK(date.GetDay() == 01);
			CHECK(date.GetMonth() == Month::JANUARY);
			CHECK(date.GetYear() == 1970);
		}
	}

	GIVEN("Дата 10 апреля 2023 года")
	{
		Date date(10, Month::APRIL, 2023);

		WHEN("Используем префиксный инкремент")
		{
			++date;

			THEN("Дата стала 11 апреля 2023 года")
			{
				CHECK(date.GetDay() == 11);
				CHECK(date.GetMonth() == Month::APRIL);
				CHECK(date.GetYear() == 2023);
			}
		}

		WHEN("Используем постфиксный инкремент")
		{
			Date oldDate = date++;

			THEN("Дата осталась прежней, а копия стала 11 апреля 2023 года")
			{
				CHECK(oldDate.GetDay() == 10);
				CHECK(oldDate.GetMonth() == Month::APRIL);
				CHECK(oldDate.GetYear() == 2023);

				CHECK(date.GetDay() == 11);
				CHECK(date.GetMonth() == Month::APRIL);
				CHECK(date.GetYear() == 2023);
			}
		}

		WHEN("Используем префиксный декремент")
		{
			--date;

			THEN("Дата стала 9 апреля 2023 года")
			{
				CHECK(date.GetDay() == 9);
				CHECK(date.GetMonth() == Month::APRIL);
				CHECK(date.GetYear() == 2023);
			}
		}

		WHEN("Используем постфиксный декремент")
		{
			Date oldDate = date--;

			THEN("Дата осталась прежней, а копия стала 9 апреля 2023 года")
			{
				CHECK(oldDate.GetDay() == 10);
				CHECK(oldDate.GetMonth() == Month::APRIL);
				CHECK(oldDate.GetYear() == 2023);

				CHECK(date.GetDay() == 9);
				CHECK(date.GetMonth() == Month::APRIL);
				CHECK(date.GetYear() == 2023);
			}
		}
	}

	GIVEN("Крайние значения")
	{
		Date date(31, Month::DECEMBER, 9999);

		THEN("Дата осталась 31 декабря 9999 года")
		{
			CHECK(date.GetDay() == 31);
			CHECK(date.GetMonth() == Month::DECEMBER);
			CHECK(date.GetYear() == 9999);
		}

		WHEN("Используем префиксный инкремент")
		{
			++date;

			THEN("Дата осталась 31 декабря 9999 года")
			{
				CHECK(date.GetDay() == 31);
				CHECK(date.GetMonth() == Month::DECEMBER);
				CHECK(date.GetYear() == 9999);
			}
		}

		WHEN("Используем оператор сложения")
		{
			date = date + 10;

			THEN("Дата осталась 31 декабря 9999 года")
			{
				CHECK(date.GetDay() == 31);
				CHECK(date.GetMonth() == Month::DECEMBER);
				CHECK(date.GetYear() == 9999);
			}
		}

		WHEN("Используем постфиксный инкремент")
		{
			date++;

			THEN("Дата осталась 31 декабря 9999 года")
			{
				CHECK(date.GetDay() == 31);
				CHECK(date.GetMonth() == Month::DECEMBER);
				CHECK(date.GetYear() == 9999);
			}
		}

		Date date1(01, Month::JANUARY, 1970);
		WHEN("Используем префиксный декремент")
		{
			--date1;

			THEN("Дата осталась 01 января 1970 года")
			{
				CHECK(date1.GetDay() == 01);
				CHECK(date1.GetMonth() == Month::JANUARY);
				CHECK(date1.GetYear() == 1970);
			}
		}

		WHEN("Используем оператор вычитания")
		{
			date1 = date1 - 10;

			THEN("Дата осталась 01 января 1970 года")
			{
				CHECK(date1.GetDay() == 01);
				CHECK(date1.GetMonth() == Month::JANUARY);
				CHECK(date1.GetYear() == 1970);
			}
		}

		WHEN("Используем постфиксный декремент")
		{
			date1--;

			THEN("Дата осталась 01 января 1970 года")
			{
				CHECK(date1.GetDay() == 01);
				CHECK(date1.GetMonth() == Month::JANUARY);
				CHECK(date1.GetYear() == 1970);
			}
		}

	}
}

SCENARIO("Тест операторов сложения и вычитания")
{
	GIVEN("Дата 15 июня 2023 года")
	{
		Date date(15, Month::JUNE, 2023);

		WHEN("Составное выражение")
		{
			date = date + 0 + 1;

			THEN("Дата становится 16 июня 2023 года")
			{
				CHECK(date.GetDay() == 16);
				CHECK(date.GetMonth() == Month::JUNE);
				CHECK(date.GetYear() == 2023);
			}
		}

		WHEN("Прибавляем 0 дней")
		{
			date = date + 0;

			THEN("Дата остается 15 июня 2023 года")
			{
				CHECK(date.GetDay() == 15);
				CHECK(date.GetMonth() == Month::JUNE);
				CHECK(date.GetYear() == 2023);
			}
		}

		WHEN("Прибавляем 0 дней")
		{
			date = 0 + date;

			THEN("Дата остается 15 июня 2023 года")
			{
				CHECK(date.GetDay() == 15);
				CHECK(date.GetMonth() == Month::JUNE);
				CHECK(date.GetYear() == 2023);
			}
		}

		WHEN("Прибавляем 0 дней")
		{
			date = 10 + date;

			THEN("Дата остается 17 июня 2023 года")
			{
				CHECK(date.GetDay() == 25);
				CHECK(date.GetMonth() == Month::JUNE);
				CHECK(date.GetYear() == 2023);
			}
		}

		WHEN("Прибавляем 10 дней")
		{
			date = date + 10;

			THEN("Дата стала 25 июня 2023 года")
			{
				CHECK(date.GetDay() == 25);
				CHECK(date.GetMonth() == Month::JUNE);
				CHECK(date.GetYear() == 2023);
			}
		}

		WHEN("Прибавляем 17 дней (выходим за месяц)")
		{
			date = date + 17;

			THEN("Дата стала 2 июля 2023 года")
			{
				CHECK(date.GetDay() == 2);
				CHECK(date.GetMonth() == Month::JULY);
				CHECK(date.GetYear() == 2023);
			}
		}

		WHEN("Прибавляем 366 + 365 + 365 дней (выходим за год)")
		{
			date = date + 366 + 365 + 365;

			THEN("Дата стала 15 июня 2026 года")
			{
				CHECK(date.GetDay() == 15);
				CHECK(date.GetMonth() == Month::JUNE);
				CHECK(date.GetYear() == 2026);
			}
		}

		WHEN("Прибавляем максимальное количество дней")
		{
			date = date + MAX_TIMESTAMP;

			THEN("Дата остается 15 июня 2023 года")
			{
				CHECK(date.GetDay() == 15);
				CHECK(date.GetMonth() == Month::JUNE);
				CHECK(date.GetYear() == 2023);
			}
		}

		WHEN("Вычитаем 0 дней")
		{
			date = date - 0;

			THEN("Дата остается 15 июня 2023 года")
			{
				CHECK(date.GetDay() == 15);
				CHECK(date.GetMonth() == Month::JUNE);
				CHECK(date.GetYear() == 2023);
			}
		}

		WHEN("Вычитаем 10 дней")
		{
			date = date - 10;

			THEN("Дата стала 5 июня 2023 года")
			{
				CHECK(date.GetDay() == 5);
				CHECK(date.GetMonth() == Month::JUNE);
				CHECK(date.GetYear() == 2023);
			}
		}

		WHEN("Вычитаем 15 дней (выходим за месяц)")
		{
			date = date - 15;

			THEN("Дата стала 31 мая 2023 года")
			{
				CHECK(date.GetDay() == 31);
				CHECK(date.GetMonth() == Month::MAY);
				CHECK(date.GetYear() == 2023);
			}
		}

		WHEN("Вычитаем 365 дней (выходим за год)")
		{
			date = date - 365;

			THEN("Дата стала 15 июне 2022 года")
			{
				CHECK(date.GetDay() == 15);
				CHECK(date.GetMonth() == Month::JUNE);
				CHECK(date.GetYear() == 2022);
			}
		}

		WHEN("Вычитаем максимальное количество дней")
		{
			date = date - MAX_TIMESTAMP;

			THEN("Дата остается 15 июня 2023 года")
			{
				CHECK(date.GetDay() == 15);
				CHECK(date.GetMonth() == Month::JUNE);
				CHECK(date.GetYear() == 2023);
			}
		}

		WHEN("Находим положительную разницу дат")
		{
			const Date date1(10, Month::JUNE, 2023);

			THEN("Разница составляет 5 дней")
			{
				CHECK(date - date1 == 5);
			}
		}

		WHEN("Находим отрицательную разницу дат")
		{
			const Date date1(21, Month::JUNE, 2023);

			THEN("Разница составляет -6 дней")
			{
				CHECK(date - date1 == -6);
			}
		}
	}
}

SCENARIO("Тест операторов += и -=")
{
	GIVEN("Дата 15 июня 2023 года")
	{
		Date date(15, Month::JUNE, 2023);

		WHEN("Прибавляем 0 дней")
		{
			date += 0;

			THEN("Дата остается 15 июня 2023 года")
			{
				CHECK(date.GetDay() == 15);
				CHECK(date.GetMonth() == Month::JUNE);
				CHECK(date.GetYear() == 2023);
			}
		}

		WHEN("Прибавляем максимальное количество дней")
		{
			date += MAX_TIMESTAMP;

			THEN("Дата остается 15 июня 2023 года")
			{
				CHECK(date.GetDay() == 15);
				CHECK(date.GetMonth() == Month::JUNE);
				CHECK(date.GetYear() == 2023);
			}
		}

		WHEN("Вычитаем 0 дней")
		{
			date -= 0;

			THEN("Дата остается 15 июня 2023 года")
			{
				CHECK(date.GetDay() == 15);
				CHECK(date.GetMonth() == Month::JUNE);
				CHECK(date.GetYear() == 2023);
			}
		}

		WHEN("Вычитаем максимальное количество дней")
		{
			date -= MAX_TIMESTAMP;

			THEN("Дата остается 15 июня 2023 года")
			{
				CHECK(date.GetDay() == 15);
				CHECK(date.GetMonth() == Month::JUNE);
				CHECK(date.GetYear() == 2023);
			}
		}
	}
}

SCENARIO("Тест операторов сравнения")
{
	GIVEN("Две даты: 15 июня 2023 года и 20 июня 2023 года")
	{
		Date date1(15, Month::JUNE, 2023);
		Date date2(20, Month::JUNE, 2023);

		WHEN("Сравниваем даты")
		{
			THEN("Дата 20 июня 2023 года больше 15 июня 2023 года")
			{
				CHECK(date2 > date1);
				CHECK(date2 >= date1);
				CHECK_FALSE(date1 > date2);
				CHECK_FALSE(date1 >= date2);
			}

			THEN("Дата 15 июня 2023 года меньше 20 июня 2023 года")
			{
				CHECK(date1 < date2);
				CHECK(date1 <= date2);
				CHECK_FALSE(date2 < date1);
				CHECK_FALSE(date2 <= date1);
			}

			THEN("Дата 15 июня 2023 года равна самой себе")
			{
				CHECK(date1 == date1);
				CHECK_FALSE(date1 != date1);
			}
		}
	}
}

SCENARIO("Тест ввода и вывода")
{
	GIVEN("Дата 25 июля 2023 года")
	{
		Date date(25, Month::JULY, 2023);

		WHEN("Выводим дату")
		{
			std::ostringstream oss; // добавить плохой сценарий ++
			oss << date;

			THEN("Строка вывода должна быть 25.7.2023")
			{
				CHECK(oss.str() == "25.7.2023");
			}
		}

		WHEN("Вводим дату")
		{
			std::istringstream iss("10.12.2022");
			iss >> date;

			THEN("Дата должна быть 10 декабря 2022 года")
			{
				CHECK(date.GetDay() == 10);
				CHECK(date.GetMonth() == Month::DECEMBER);
				CHECK(date.GetYear() == 2022);
			}
		}

		std::istringstream iss("2022-13-10");
		iss >> date;

		THEN("Дата должна остаться неизменной")
		{
			CHECK(date.GetDay() == 25);
			CHECK(date.GetMonth() == Month::JULY);
			CHECK(date.GetYear() == 2023);
		}

		AND_THEN("Установлена ошибка в потоке")
		{
			CHECK(iss.fail());
		}
	}
}