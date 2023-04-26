#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Car/CCar.h"

CCar car;
// тесты должны быть разбиты на сценарии
TEST_CASE("test1")
{
	CHECK(car.GetSpeed() == 0);
	CHECK(car.GetGear() == CCar::Gear::NEUTRAL);
	CHECK(car.IsTurnedOn() == false);
	CHECK(car.GetDirection() == CCar::Direction::STAY);

	car.TurnOnEngine();

	CHECK(car.IsTurnedOn() == true);

	CHECK(!car.SetGear(CCar::Gear::SECOND));

	CHECK(car.SetGear(CCar::Gear::FIRST));

	CHECK(!car.SetSpeed(45));
	car.SetSpeed(28);

	CHECK(car.GetSpeed() == 28);

	CHECK(car.GetDirection() == CCar::Direction::FORWARD);
	CHECK(!car.SetGear(CCar::Gear::REVERSE));

	car.SetSpeed(0);
	CHECK(car.GetSpeed() == 0);

	CHECK(car.SetGear(CCar::Gear::REVERSE));

	car.SetSpeed(10);
	CHECK(car.GetDirection() == CCar::Direction::BACK);

	CHECK(car.SetGear(CCar::Gear::NEUTRAL));
	CHECK(!car.SetGear(CCar::Gear::FIRST));
	CHECK(!car.TurnOffEngine());
}

TEST_CASE("test2")
{
	car.SetSpeed(0);

	CHECK(car.SetGear(CCar::Gear::FIRST));

	CHECK(!car.SetSpeed(39));

	CHECK(car.SetSpeed(29));

	CHECK(!car.SetGear(CCar::Gear::THIRD));
	CHECK(car.SetGear(CCar::Gear::SECOND));

	CHECK(car.SetSpeed(20));
	CHECK(!car.SetSpeed(19));
	CHECK(car.SetSpeed(50));
	CHECK(!car.SetSpeed(51));

	CHECK(car.SetGear(CCar::Gear::THIRD));
	CHECK(!car.SetGear(CCar::Gear::REVERSE));
	CHECK(!car.SetGear(CCar::Gear::FIRST));
}