#include <catch2/catch_test_macros.hpp>
#include <Maize.h>

/**
 * Since this is not getting created by the world, this is testing if the null entity has been handled.
 **/

TEST_CASE("Null Entity Class Test", "[Null Entity]")
{
	Maize::Entity e;

	SECTION("Adding components")
	{
		REQUIRE(e.AddOrReplaceComponent<Maize::Position>() == false);
		REQUIRE(e.AddOrReplaceComponent(Maize::Position(0, 0)) == false);

		REQUIRE(e.TryGetComponent<Maize::Position>() == nullptr);
		REQUIRE(e.HasComponent<Maize::Position>() == false);
	}

	SECTION("Getting components")
	{
		REQUIRE(e.TryGetComponent<Maize::Position>() == nullptr);
		REQUIRE(e.TryGetMutComponent<Maize::Position>() == nullptr);
	}

	SECTION("Checking components")
	{
		REQUIRE(e.HasComponent<Maize::Position>() == false);
	}

	SECTION("Is null")
	{
		REQUIRE(e.IsNull() == true);
		REQUIRE(e.ID() == flecs::entity::null().id());
	}

	SECTION("Handling State")
	{
		REQUIRE(e.Enable() == false);
		REQUIRE(e.Disable() == false);
		REQUIRE(e.Destroy() == false);

		REQUIRE(e.DisableComponent<Maize::Position>() == false);
		REQUIRE(e.EnableComponent<Maize::Position>() == false);
	}
}