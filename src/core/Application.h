#pragma once

#include <imgui.h>

class Application
{
public:
	void Initialize();
	void PreRender();
	void Render();
	void Shutdown();

private:
	bool show_demo_window = true;
	bool show_another_window = false;
	bool done = false;
	float float_test = 0.0f;
	int counter = 0;
};