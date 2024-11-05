#include <catch2/catch_test_macros.hpp>
#include <Maize.h>

#include "Maize/Event/EventDispatcher.h"

TEST_CASE("Dispatching events", "[events]")
{
	auto testEvent = Maize::KeyPressedEvent(Maize::KeyCode::A);
	auto dispatcher = Maize::EventDispatcher(testEvent);

	REQUIRE(testEvent.handled == false);

	// test if the dispatcher works
	dispatcher.Dispatch<Maize::KeyPressedEvent>([&](const Maize::KeyPressedEvent& e)
	{
		// test if the values are as expected
		REQUIRE(e.GetEventType() == testEvent.GetEventType());
		REQUIRE(e.GetKeyCode() == testEvent.GetKeyCode());

		return true;
	});

	REQUIRE(testEvent.handled == true);
}

TEST_CASE("Get event without dispatcher", "[events]")
{
	const auto testEvent = Maize::KeyPressedEvent(Maize::KeyCode::A);

	// type check test
	if (testEvent.GetEventType() != Maize::EventType::KeyPressed)
	{
		FAIL();
	}
}