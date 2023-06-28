#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Car/CCar.h"

TEST_CASE("test engine")
{
	GIVEN("Create car")
	{
		CCar car;

		CHECK(car.GetSpeed() == 0);
		CHECK(car.GetDirection() == CCar::Direction::STAY);
		CHECK(car.GetGear() == CCar::Gear::NEUTRAL);

		WHEN("engine off")
		{
			THEN("check engine")
			{
				CHECK(!car.IsTurnedOn());
			}
		}

		WHEN("engine on")
		{
			car.TurnOnEngine();

			THEN("check engine")
			{
				CHECK(car.IsTurnedOn());
			}
		}
	}
}

TEST_CASE("test neutral gear")
{
	GIVEN("Create car")
	{
		CCar car;

		CHECK(car.GetSpeed() == 0);
		CHECK(car.GetDirection() == CCar::Direction::STAY);
		CHECK(car.GetGear() == CCar::Gear::NEUTRAL);

		WHEN("engine on")
		{
			car.TurnOnEngine();
		    
			THEN("try set speed on neutral gear")
			{
				CHECK(car.SetSpeed(150) == false);

				AND_WHEN("speed > 0")
				{
					car.SetGear(CCar::Gear::FIRST);
					car.SetSpeed(30);

					THEN("try decrease speed on first gear")
					{
						CHECK(car.SetSpeed(20));
						CHECK(car.GetSpeed() == 20);
					}
				}
			}
		}
	}
}

TEST_CASE("test first gear")
{
	GIVEN("Create car")
	{
		CCar car;

		CHECK(car.GetSpeed() == 0);
		CHECK(car.GetDirection() == CCar::Direction::STAY);
		CHECK(car.GetGear() == CCar::Gear::NEUTRAL);

		WHEN("engine on")
		{
			car.TurnOnEngine();

			WHEN("first gear")
			{
				car.SetGear(CCar::Gear::FIRST);
				CHECK(car.GetGear() == CCar::Gear::FIRST);

				THEN("set speed 40")
				{
					CHECK(!car.SetSpeed(40));
					CHECK(car.GetSpeed() == 0);
				}

				THEN("set max speed")
				{
					CHECK(car.SetSpeed(30));
					CHECK(car.GetSpeed() == 30);
				}

				THEN("set speed 15")
				{
					CHECK(car.SetSpeed(15));
					CHECK(car.GetSpeed() == 15);

					AND_THEN("try set second gear")
					{
						car.SetGear(CCar::Gear::SECOND);
						CHECK(car.GetGear() == CCar::Gear::FIRST);
					}
				}
			}
		}
	}
}

TEST_CASE("test second gear")
{
	GIVEN("Create car")
	{
		CCar car;

		CHECK(car.GetSpeed() == 0);
		CHECK(car.GetDirection() == CCar::Direction::STAY);
		CHECK(car.GetGear() == CCar::Gear::NEUTRAL);

		WHEN("engine on")
		{
			car.TurnOnEngine();

			WHEN("second gear")
			{
				car.SetGear(CCar::Gear::FIRST);
				car.SetSpeed(30);
				car.SetGear(CCar::Gear::SECOND);
				CHECK(car.GetGear() == CCar::Gear::SECOND);
				CHECK(car.GetSpeed() == 30);

				THEN("set first gear")
				{
					CHECK(car.SetGear(CCar::Gear::FIRST));
					CHECK(car.GetGear() == CCar::Gear::FIRST);
				}

				THEN("set third gear")
				{
					CHECK(car.SetGear(CCar::Gear::THIRD));
					CHECK(car.GetGear() == CCar::Gear::THIRD);
				}

				THEN("try set speed 15")
				{
					CHECK(!car.SetSpeed(15));
					CHECK(car.GetSpeed() == 30);
				}

				THEN("try set speed 51")
				{
					CHECK(!car.SetSpeed(51));
					CHECK(car.GetSpeed() == 30);
				}

				THEN("try set speed 40")
				{
					CHECK(car.SetSpeed(50));
					CHECK(car.GetSpeed() == 50);

					AND_THEN("set third gear")
					{
						CHECK(car.SetGear(CCar::Gear::THIRD));
						CHECK(car.GetGear() == CCar::Gear::THIRD);
					}
				}
			}
		}
	}
}

TEST_CASE("test third gear")
{
	GIVEN("Create car")
	{
		CCar car;

		CHECK(car.GetSpeed() == 0);
		CHECK(car.GetDirection() == CCar::Direction::STAY);
		CHECK(car.GetGear() == CCar::Gear::NEUTRAL);

		WHEN("engine on")
		{
			car.TurnOnEngine();

			WHEN("third gear")
			{
				car.SetGear(CCar::Gear::FIRST);
				car.SetSpeed(30);
				car.SetGear(CCar::Gear::SECOND);
				CHECK(car.GetGear() == CCar::Gear::SECOND);
				CHECK(car.GetSpeed() == 30);
				car.SetSpeed(50);
				car.SetGear(CCar::Gear::THIRD);

				THEN("set first gear")
				{
					CHECK(!car.SetGear(CCar::Gear::FIRST));
					CHECK(car.GetGear() == CCar::Gear::THIRD);
				}

				THEN("set second gear")
				{
					CHECK(car.SetGear(CCar::Gear::SECOND));
					CHECK(car.GetGear() == CCar::Gear::SECOND);
				}

				THEN("try set speed 29")
				{
					CHECK(!car.SetSpeed(29));
					CHECK(car.GetSpeed() == 50);
				}

				THEN("try set speed 61")
				{
					CHECK(!car.SetSpeed(61));
					CHECK(car.GetSpeed() == 50);
				}

				THEN("try set speed 60")
				{
					CHECK(car.SetSpeed(60));
					CHECK(car.GetSpeed() == 60);

					AND_THEN("set fourth gear")
					{
						CHECK(car.SetGear(CCar::Gear::FOURTH));
						CHECK(car.GetGear() == CCar::Gear::FOURTH);
					}
				}
			}
		}
	}
}

TEST_CASE("test fourth gear")
{
	GIVEN("Create car")
	{
		CCar car;

		CHECK(car.GetSpeed() == 0);
		CHECK(car.GetDirection() == CCar::Direction::STAY);
		CHECK(car.GetGear() == CCar::Gear::NEUTRAL);

		WHEN("engine on")
		{
			car.TurnOnEngine();

			WHEN("fourth gear")
			{
				car.SetGear(CCar::Gear::FIRST);
				car.SetSpeed(30);
				car.SetGear(CCar::Gear::SECOND);
				car.SetSpeed(40);
				car.SetGear(CCar::Gear::FOURTH);
				CHECK(car.GetGear() == CCar::Gear::FOURTH);
				CHECK(car.GetSpeed() == 40);
				car.SetSpeed(80);

				THEN("set second gear")
				{
					CHECK(!car.SetGear(CCar::Gear::SECOND));
					CHECK(car.GetGear() == CCar::Gear::FOURTH);
				}

				THEN("try set speed 39")
				{
					CHECK(!car.SetSpeed(39));
					CHECK(car.GetSpeed() == 80);
				}

				THEN("try set speed 91")
				{
					CHECK(!car.SetSpeed(91));
					CHECK(car.GetSpeed() == 80);
				}

				THEN("try set speed 90")
				{
					CHECK(car.SetSpeed(90));
					CHECK(car.GetSpeed() == 90);

					AND_THEN("set fifth gear")
					{
						CHECK(car.SetGear(CCar::Gear::FIFTH));
						CHECK(car.GetGear() == CCar::Gear::FIFTH);

						AND_THEN("set neutral gear")
						{
							CHECK(car.SetGear(CCar::Gear::NEUTRAL));
							CHECK(car.GetGear() == CCar::Gear::NEUTRAL);

							AND_THEN("increase speed")
							{
								CHECK(!car.SetSpeed(91));
							}

							AND_THEN("decrease speed")
							{
								CHECK(car.SetSpeed(80));
								CHECK(car.SetSpeed(0));
							}
						}
					}
				}
			}
		}
	}
}

TEST_CASE("test fifth gear")
{
	GIVEN("Create car")
	{
		CCar car;

		CHECK(car.GetSpeed() == 0);
		CHECK(car.GetDirection() == CCar::Direction::STAY);
		CHECK(car.GetGear() == CCar::Gear::NEUTRAL);

		WHEN("engine on")
		{
			car.TurnOnEngine();

			WHEN("fifth gear")
			{
				car.SetGear(CCar::Gear::FIRST);
				car.SetSpeed(30);
				car.SetGear(CCar::Gear::SECOND);
				car.SetSpeed(50);
				car.SetGear(CCar::Gear::FIFTH);
				CHECK(car.GetGear() == CCar::Gear::FIFTH);
				CHECK(car.GetSpeed() == 50);
				car.SetSpeed(100);

				THEN("set fourth gear")
				{
					CHECK(!car.SetGear(CCar::Gear::FOURTH));
					CHECK(car.GetGear() == CCar::Gear::FIFTH);
				}

				THEN("try set speed 49")
				{
					CHECK(!car.SetSpeed(49));
					CHECK(car.GetSpeed() == 100);
				}

				THEN("try set speed 151")
				{
					CHECK(!car.SetSpeed(151));
					CHECK(car.GetSpeed() == 100);
				}

				THEN("try set speed 150")
				{
					CHECK(car.SetSpeed(150));
					CHECK(car.GetSpeed() == 150);

					AND_THEN("set neutral gear")
					{
						CHECK(car.SetGear(CCar::Gear::NEUTRAL));
						CHECK(car.GetGear() == CCar::Gear::NEUTRAL);

						AND_THEN("decrease speed")
						{
							CHECK(car.SetSpeed(140));
							CHECK(car.SetSpeed(0));
						}
					}
				}
			}
		}
	}
}

TEST_CASE("test reverse gear")
{
	GIVEN("Create car")
	{
		CCar car;

		CHECK(car.GetSpeed() == 0);
		CHECK(car.GetDirection() == CCar::Direction::STAY);
		CHECK(car.GetGear() == CCar::Gear::NEUTRAL);

		WHEN("engine on")
		{
			car.TurnOnEngine();

			WHEN("first gear")
			{
				car.SetGear(CCar::Gear::FIRST);
				WHEN("speed 30")
				{
					car.SetSpeed(30);

					THEN("try set reverse gear")
					{
						CHECK(!car.SetGear(CCar::Gear::REVERSE));
					}
				}

				WHEN("speed 0")
				{
					THEN("try set reverse gear")
					{
						CHECK(car.SetGear(CCar::Gear::REVERSE));
					}
				}
				
			}
		}
	}
}

TEST_CASE("test direction")
{
	GIVEN("Create car")
	{
		CCar car;

		CHECK(car.GetSpeed() == 0);
		CHECK(car.GetDirection() == CCar::Direction::STAY);
		CHECK(car.GetGear() == CCar::Gear::NEUTRAL);

		WHEN("engine on")
		{
			car.TurnOnEngine();

			THEN("check direction"){
				CHECK(car.GetDirection() == CCar::Direction::STAY);
			}

			WHEN("reverse gear");
			{
				car.SetGear(CCar::Gear::REVERSE);
				THEN("check direction")
				{
					CHECK(car.GetDirection() == CCar::Direction::STAY);
					
					WHEN("set speed 1")
					{
						car.SetSpeed(1);
						THEN("check direction")
						{
							CHECK(car.GetDirection() == CCar::Direction::BACK);
						}
					}
				}
			}

			WHEN("forward gear");
			{
				car.SetGear(CCar::Gear::FIRST);
				THEN("check direction")
				{
					CHECK(car.GetDirection() == CCar::Direction::STAY);

					WHEN("set speed 1")
					{
						car.SetSpeed(1);
						THEN("check direction")
						{
							CHECK(car.GetDirection() == CCar::Direction::FORWARD);
						}
					}
				}
			}
		}
	}
}