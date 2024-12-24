#include <numeric>

#include "Maize.h"
#include "Maize/Scene/Components/Rendering/SpriteRenderer.h"

class TestScene final : public Maize::Scene
{
public:
	virtual void OnStart() override
	{
		m_Texture = std::make_shared<sf::Texture>(sf::Vector2u(64, 64));

		std::vector<uint8_t> data;
		data.assign(64 * 64 * 4, 255);

		m_Texture->update(data.data());

		auto sprite = Maize::Sprite(m_Texture, { 0, 0, 64, 64 });


		CreateEntity(Maize::Vec2f(0, 0), false, false, Maize::Camera());
		CreateEntity(Maize::Vec2f(0, 0), false, false, Maize::SpriteRenderer(sprite));

		AddSystem<Maize::Position, Maize::SpriteRenderer>("Move Entity", flecs::OnUpdate, OnMove);
	}

	virtual void OnEnd() override {}

private:
	static void OnMove(Maize::SystemState state, Maize::Entity e, Maize::Position& p, Maize::SpriteRenderer&)
	{
		float speed = 10000.0f;

		p.x += speed * state.DeltaTime();
		p.y += speed * state.DeltaTime();

		if (p.x >= 230 && p.y >= 230)
		{
			//p.x = 0;
			//p.y = 0;
			e.AddOrReplaceComponent(Maize::Position(0, 0));
		}
	}

private:
	std::shared_ptr<sf::Texture> m_Texture;
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