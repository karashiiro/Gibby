#pragma once

#include <imgui.h>

int NativePlatformInit();
int NativeOnUpdatePreRender(bool& done);
int NativeOnUpdatePostRender();
int NativePlatformShutdown();