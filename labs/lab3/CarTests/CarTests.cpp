#include "../Car/stdafx.h"
#include "../Car/CCar.h"


struct CarFixture
{
	CCar car;
};

BOOST_FIXTURE_TEST_SUITE(Car, CarFixture)
	
	BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
	{
		BOOST_CHECK(!car.IsTurnedOn());
	}

	BOOST_AUTO_TEST_CASE(gear_check)
	{
		BOOST_CHECK(!car.SetGear(CCar::Gear::FIRST));
		BOOST_CHECK_EQUAL(car.GetGear(), CCar::Gear::NEUTRAL);
	}

BOOST_AUTO_TEST_SUITE_END()