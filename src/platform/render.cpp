#include "render.h"

#ifdef WIN32
#include "render/win32_dx11.h"
#endif

int ImGuiPlatformInit()
{
	return NativePlatformInit();
}

int ImGuiOnUpdatePreRender(bool &done)
{
	return NativeOnUpdatePreRender(done);
}

int ImGuiOnUpdatePostRender()
{
	return NativeOnUpdatePostRender();
}

int ImGuiPlatformShutdown()
{
	return NativePlatformShutdown();
}