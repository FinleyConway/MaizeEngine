#include <catch2/catch_test_macros.hpp>
#include <Maize.h>

class Test final : public Maize::Application
{
public:
	Test()
	{
	}
};

TEST_CASE("Creating application", "[Application]")
{
	Test test;

	REQUIRE(test.Initialise("Test", 0, 0) == false);
	REQUIRE(test.Initialise("Test", 1, 1) == true);
}