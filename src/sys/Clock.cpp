#include "Clock.h"

#include <chrono>
#include <thread>

Clock::Clock()
{
	std::thread loop(&Clock::Start, this);
	loop.detach();
}

Clock::~Clock()
{
	shutdown = true;
}

void Clock::Wait(int cycles)
{
	for (auto i = 0; i < cycles; i++)
	{
		std::unique_lock lock(state);
	}
}

void Clock::Start()
{
	using namespace std::chrono_literals;
	while (!shutdown)
	{
		// Clock speed = 4.194304MHz
		std::this_thread::sleep_for(0.000238418579ms);
		Wait();
	}
}
