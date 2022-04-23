#pragma once

#include <shared_mutex>

class Clock
{
public:
	Clock();
	virtual ~Clock();

	void Wait();
private:
	void Start();

	// When the mutex is locked, the clock is off,
	// and vice versa.
	mutable std::shared_mutex state{};
	bool shutdown = false;
};
