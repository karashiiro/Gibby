#include "Graphics.h"

Graphics::Graphics(Memory* external_memory)
{
	vram = external_memory->GetVideoMemory();
}
