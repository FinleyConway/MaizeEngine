#include "Maize.h"

class SandBox final : public Maize::Application
{
public:
	SandBox()
	{
	}
};

int main()
{
	SandBox sandBox;
	if (sandBox.Initialise("Sandbox", 500, 500)) sandBox.Run();
}