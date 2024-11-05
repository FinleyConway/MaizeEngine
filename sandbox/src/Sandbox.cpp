#include "Maize.h"

class SandBox final : public Maize::Application
{
public:
	SandBox(std::string_view title, uint32_t windowWidth, uint32_t windowHeight)
		: Application(title, windowWidth, windowHeight)
	{
	}
};

MAIZE_ENGINE(SandBox, "Sandbox", 1280, 720);