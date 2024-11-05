#pragma once

#include <iostream>
#include <memory>

int main();

namespace Maize {

	class Application
	{
	public:
		virtual ~Application() = default;

		virtual bool Initialise() = 0;

	private:
		friend int ::main();

		bool Run()
		{
			std::cout << "hello world\n";
			return true;
		}
	};

	std::unique_ptr<Application> CreateApplication();

	#define MAIZE_ENGINE(type)										\
	std::unique_ptr<Maize::Application> Maize::CreateApplication()	\
	{																\
		return std::make_unique<type>();							\
	}

} // Maize
