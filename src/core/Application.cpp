#include "Application.h"

void Application::Initialize()
{
}

void Application::PreRender()
{
}

void Application::Render()
{
	// Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
	{
		// Create a window called "Hello, world!" and append into it.
		ImGui::Begin("Hello, world!");

		// Display some text (you can use a format strings too)
		ImGui::Text("This is some useful text.");

		// Edit booleans storing our window open/close state
		ImGui::Checkbox("Demo Window", &show_demo_window);
		ImGui::Checkbox("Another Window", &show_another_window);

		// Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat("float", &float_test, 0.0f, 1.0f);

		// Buttons return true when clicked (most widgets return true when edited/activated)
		if (ImGui::Button("Button"))
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}
}

void Application::Shutdown()
{
	done = true;
}