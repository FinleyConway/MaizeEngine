#include <catch2/catch_test_macros.hpp>
#include <Maize.h>

TEST_CASE("Renderer Class Test", "[Renderer]")
{
	sf::RenderWindow window;
	auto renderer = Maize::Internal::Renderer(window);

	SECTION("Current View matching")
	{
		auto view = sf::View({ 0, 0 }, { 100, 100 });

		renderer.SetCurrentView(view);

		REQUIRE(renderer.GetCurrentView().getTransform() == view.getTransform());
	}

	SECTION("drawing cycle")
	{
		// both should be accepted
		std::vector<sf::Vertex> empty;
		std::array<sf::Vertex, 6> vertices;

		renderer.BeginDrawing();

		// when the draw call count should refresh
		REQUIRE(renderer.GetDrawCalls() == 0);

		// this should discard as there is nothing to draw
		renderer.Draw(empty, {});
		REQUIRE(renderer.GetDrawCalls() == 0);

		renderer.Draw(vertices, {});
		renderer.Draw(vertices, {});

		renderer.EndDrawing();

		// all rendering details should all still be logged
		REQUIRE(renderer.GetDrawCalls() == 2);
	}
}
