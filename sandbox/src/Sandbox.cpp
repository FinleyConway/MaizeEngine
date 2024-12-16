#include "Maize.h"

class TestScene final : public Maize::Scene
{
public:
	virtual void OnStart() override
	{
		CreateEntity(Maize::Vec2f(0, 0), false, false);

		AddSystem<Maize::Position>("Move Entity", flecs::OnUpdate, OnMove);
	}

	virtual void OnEnd() override {}

private:
	static void OnMove(Maize::SystemState state, Maize::Entity e, Maize::Position& p)
	{
		float speed = 128.0f;

		p.x += speed * state.DeltaTime();
		p.y += speed * state.DeltaTime();

		GAME_LOG_INFO("X: {}, Y: {}", p.x, p.y);
	}
};

class SandBox final : public Maize::Application
{
public:
	SandBox(std::string_view title, uint32_t width, uint32_t height) : Application(title, width, height)
	{
		LoadScene(std::make_unique<TestScene>());
	}
};

int main()
{
	auto sandBox = SandBox("Sandbox", 800, 600);
	sandBox.Run();
}