#include "../Car/stdafx.h"
#include "../Car/CCar.h"


struct CarFixture
{
	CCar car;
};
// Телевизор
BOOST_FIXTURE_TEST_SUITE(Car, CarFixture)
	// изначально выключен
	BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
	{
		BOOST_CHECK(!car.IsTurnedOn());
	}

BOOST_AUTO_TEST_SUITE_END()