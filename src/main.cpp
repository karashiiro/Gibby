#include <imgui.h>

#include "core/Application.h"
#include "platform/render.h"

int main(int, char**)
{
	// Initialize imgui with any platform-specific setup code
	if (ImGuiPlatformInit() != 0)
		return 1;

	Application app;
	app.Initialize();

	// Main loop
	bool done = false;
	while (!done)
	{
		if (ImGuiOnUpdatePreRender(done) != 0)
			return 1;

		app.PreRender();

		app.Render();
		ImGui::Render();

		if (ImGuiOnUpdatePostRender() != 0)
			return 1;
	}

	app.Shutdown();

	// Perform platform-specific cleanup
	if (ImGuiPlatformShutdown() != 0)
		return 1;

	return 0;
}