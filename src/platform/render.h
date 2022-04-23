#pragma once

#include <imgui.h>

/// Initializes ImGui using its platform-specific setup code.
int ImGuiPlatformInit();

/// Prepares the system to render an ImGui frame.
int ImGuiOnUpdatePreRender(bool& done);

/// Cleans up the renderer for the next ImGui frame.
int ImGuiOnUpdatePostRender();

/// Cleans up any resources used by ImGui.
int ImGuiPlatformShutdown();