#include <catch2/catch_test_macros.hpp>
#include <Maize.h>

#include "Maize/Scene/SceneManager.h"

class Single { };

class TestScene final : public Maize::Scene
{
public:
	void OnStart() override
	{
		onStartCalled = true;

		CreateSingleton<Single>();

		auto entity = CreateEntity({ 0, 0 }, false, false);

		AddSystem<>("test", flecs::OnStart, [](Maize::SystemState s, Maize::Entity e)
		{
			auto* single = s.GetSingleton<Single>();

			REQUIRE(single != nullptr);
		});

		// check if the entity was created with all essentials
		REQUIRE(entity.IsNull() == false);
		REQUIRE(entity.HasComponent<Maize::Position>());
		REQUIRE(entity.HasComponent<Maize::Active>());
		REQUIRE(entity.TryGetComponent<Maize::Position>() != nullptr);

		// check if you cant remove essential components
		REQUIRE(entity.RemoveComponent<Maize::Position>() == false);
		REQUIRE(entity.RemoveComponent<Maize::Active>() == false);
		REQUIRE(entity.DisableComponent<Maize::Position>() == false);
		REQUIRE(entity.DisableComponent<Maize::Active>() == false);
	}

	void OnEnd() override
	{
		onEndCalled = true;
	}

public:
	bool onStartCalled = false;
	bool onEndCalled = false;
};

class TestScene2 final : public Maize::Scene
{
public:
	void OnStart() override
	{
		AddSystem<>("test", flecs::OnStart, [](Maize::SystemState s, Maize::Entity e)
		{
			auto* single = s.GetSingleton<Single>();

			REQUIRE(single == nullptr);
		});
	}

	void OnEnd() override {}
};

TEST_CASE("Test scene management")
{
	sf::RenderWindow window;
	auto renderer = Maize::Internal::Renderer(window);
	auto sceneManager = Maize::Internal::SceneManager(renderer);

	auto firstScene = std::make_unique<TestScene>();
	TestScene* firstScenePtr = firstScene.get();

	// test if it was loaded and the on start function was called
	REQUIRE(sceneManager.LoadScene(std::move(firstScene)) == true);
	REQUIRE(firstScenePtr->onStartCalled == true);

	// test if transition scene loaded and the on end function was called
	auto secondScene = std::make_unique<TestScene2>();
	REQUIRE(sceneManager.LoadScene(std::move(secondScene)) == true);
	REQUIRE(firstScenePtr->onEndCalled == true);

	sceneManager.Quit();
}
