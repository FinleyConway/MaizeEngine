#include "Maize.h"

class SandBox final : public Maize::Application
{
public:
	bool Initialise() override
	{
		return true;
	}
};

MAIZE_ENGINE(SandBox);