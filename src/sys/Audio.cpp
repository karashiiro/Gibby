#include "Audio.h"

Audio::Audio(
		sound_mode_1_registers& mapped_sm1,
		sound_mode_2_registers& mapped_sm2,
		sound_mode_3_registers& mapped_sm3,
		sound_mode_4_registers& mapped_sm4,
		sound_control_registers& mapped_ctrl,
		wave_sample_memory& mapped_wave_sample_memory)
	: sm1(mapped_sm1), sm2(mapped_sm2), sm3(mapped_sm3),
	  sm4(mapped_sm4), ctrl(mapped_ctrl), samples(mapped_wave_sample_memory)
{
}
