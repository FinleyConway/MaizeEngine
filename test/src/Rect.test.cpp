#include <catch2/catch_test_macros.hpp>
#include <Maize.h>

TEST_CASE("Rect construction and type conversion", "[Rect]")
{
	SECTION("Default constructor initializes to zero values")
	{
		Maize::IntRect rect;

		REQUIRE(rect.x == 0);
		REQUIRE(rect.y == 0);
		REQUIRE(rect.width == 0);
		REQUIRE(rect.height == 0);
	}

	SECTION("Parameterized constructor sets correct values")
	{
		auto rect = Maize::IntRect(10, 20, 30, 40);

		REQUIRE(rect.x == 10);
		REQUIRE(rect.y == 20);
		REQUIRE(rect.width == 30);
		REQUIRE(rect.height == 40);
	}

	SECTION("Type conversion constructor works correctly")
	{
		auto rectDouble = Maize::FloatRect(10.5f, 20.5f, 30.5f, 40.5f);
		auto rectInt = Maize::IntRect(rectDouble);

		REQUIRE(rectInt.x == 10);
		REQUIRE(rectInt.y == 20);
		REQUIRE(rectInt.width == 30);
		REQUIRE(rectInt.height == 40);
	}
}
