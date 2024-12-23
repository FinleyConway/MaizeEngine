#include <catch2/catch_test_macros.hpp>
#include <Maize.h>

TEST_CASE("Sprite Class Tests", "[Sprite]")
{
	auto texture = std::make_shared<sf::Texture>(sf::Vector2u(100, 100));

	auto pivot = Maize::Vec2f(40, 40);
	auto textureRect = Maize::IntRect(10, 10, 80, 80);
	auto sprite = Maize::Sprite(texture, textureRect, pivot);

	SECTION("Texture is correctly set")
	{
		REQUIRE(sprite.GetTexture().lock() == texture);
	}

	SECTION("Texture Rect is correctly set")
	{
		REQUIRE(sprite.GetTextureRect() == textureRect);
	}

	SECTION("SetTextureRect updates the texture rect correctly")
	{
		auto newRect = Maize::IntRect(20, 20, 60, 60);
		sprite.SetTextureRect(newRect);

		REQUIRE(sprite.GetTextureRect() == newRect);

		const auto& vertices = sprite.GetVertices();

		REQUIRE(vertices.size() == 6);

		REQUIRE(vertices[0].position == sf::Vector2f(0.f, 0.f));
		REQUIRE(vertices[1].position == sf::Vector2f(0.f, 60.f));
		REQUIRE(vertices[2].position == sf::Vector2f(60.f, 0.f));
		REQUIRE(vertices[3].position == sf::Vector2f(0.f, 60.f));
		REQUIRE(vertices[4].position == sf::Vector2f(60.f, 60.f));
		REQUIRE(vertices[5].position == sf::Vector2f(60.f, 0.f));

		REQUIRE(vertices[0].texCoords == sf::Vector2f(20.f, 20.f));
		REQUIRE(vertices[1].texCoords == sf::Vector2f(20.f, 80.f));
		REQUIRE(vertices[2].texCoords == sf::Vector2f(80.f, 20.f));
		REQUIRE(vertices[3].texCoords == sf::Vector2f(20.f, 80.f));
		REQUIRE(vertices[4].texCoords == sf::Vector2f(80.f, 80.f));
		REQUIRE(vertices[5].texCoords == sf::Vector2f(80.f, 20.f));
	}

	SECTION("GetBounds returns correct bounding box")
	{
		REQUIRE(sprite.GetBounds() == textureRect);
	}

	SECTION("Pivot is correct set")
	{
		REQUIRE(sprite.GetPivot() == pivot);
	}

	SECTION("GetVertices returns correct number of vertices")
	{
		REQUIRE(sprite.GetVertices().size() == 6);
	}

	SECTION("Vertices' positions and texCoords are correctly set")
	{
		const auto& vertices = sprite.GetVertices();

		REQUIRE(vertices[0].position == sf::Vector2f(0.f, 0.f));
		REQUIRE(vertices[1].position == sf::Vector2f(0.f, 80.f));
		REQUIRE(vertices[2].position == sf::Vector2f(80.f, 0.f));
		REQUIRE(vertices[3].position == sf::Vector2f(0.f, 80.f));
		REQUIRE(vertices[4].position == sf::Vector2f(80.f, 80.f));
		REQUIRE(vertices[5].position == sf::Vector2f(80.f, 0.f));

		REQUIRE(vertices[0].texCoords == sf::Vector2f(10.f, 10.f));
		REQUIRE(vertices[1].texCoords == sf::Vector2f(10.f, 90.f));
		REQUIRE(vertices[2].texCoords == sf::Vector2f(90.f, 10.f));
		REQUIRE(vertices[3].texCoords == sf::Vector2f(10.f, 90.f));
		REQUIRE(vertices[4].texCoords == sf::Vector2f(90.f, 90.f));
		REQUIRE(vertices[5].texCoords == sf::Vector2f(90.f, 10.f));
	}

	SECTION("Changing the pivot updates the pivot value")
	{
		auto newPivot = Maize::Vec2f(0.0f, 0.0f);
		sprite.SetPivot(newPivot);

		REQUIRE(sprite.GetPivot() == newPivot);
	}
}