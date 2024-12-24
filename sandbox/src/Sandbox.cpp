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
		auto* input = state.GetSingleton<Maize::Input>();

		Maize::Vec2f dir;
		float speed = 512.0f;

		if (input->GetButtonHeld(Maize::KeyCode::W))
		{
			dir.y = 1.0f;
		}
		else if (input->GetButtonHeld(Maize::KeyCode::S))
		{
			dir.y = -1.0f;
		}

		if (input->GetButtonHeld(Maize::KeyCode::A))
		{
			dir.x = -1.0f;
		}
		else if (input->GetButtonHeld(Maize::KeyCode::D))
		{
			dir.x = 1.0f;
		}

		p.x += dir.x * speed * state.DeltaTime();
		p.y += dir.y * speed * state.DeltaTime();

		GAME_LOG_INFO("Position: [{}, {}]", p.x, p.y);
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