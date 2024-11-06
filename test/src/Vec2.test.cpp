#include <catch2/catch_test_macros.hpp>
#include <Maize.h>

TEST_CASE("Vec2 initialization and conversion", "[Vec2]")
{
	SECTION("Default constructor initializes to zero")
	{
		Maize::Vec2i vec;

		REQUIRE(vec.x == 0);
		REQUIRE(vec.y == 0);
	}

	SECTION("Parameterized constructor initializes to given values")
	{
		auto vec = Maize::Vec2i(3, 4);

		REQUIRE(vec.x == 3);
		REQUIRE(vec.y == 4);
	}

	SECTION("Conversion constructor converts values correctly")
	{
		auto floatVec = Maize::Vec2f(1.5f, 2.5f);
		auto intVec = Maize::Vec2i(floatVec);

		REQUIRE(intVec.x == 1);
		REQUIRE(intVec.y == 2);
	}
}

TEST_CASE("Vec2 operator overloading", "[Vec2]")
{
	SECTION("Equal operator works correctly")
	{
		auto vec1 = Maize::Vec2i(10, 20);
		auto vec2 = Maize::Vec2f(10.0f, 20.0f);
		auto vec3 = Maize::Vec2i(10, 30);

		REQUIRE(vec1 == vec2);
		REQUIRE(vec2 != vec3);
	}
}