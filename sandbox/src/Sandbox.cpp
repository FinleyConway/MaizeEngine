#include "Maize.h"
#include "TestScene.h"

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