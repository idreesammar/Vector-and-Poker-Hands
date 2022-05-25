#include <iostream>
#include <ctime>

#include "Play.h"
#include "ITPVector.hpp"

int main(int argc, const char* argv[])
{
	playPoker(std::cin, std::cout, time(nullptr));

	return 0;
}
