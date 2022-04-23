#pragma once

#include "audio_registers.h"

class Audio
{
public:
	explicit Audio(
			sound_mode_1_registers &mapped_sm1,
			sound_mode_2_registers &mapped_sm2,
			sound_mode_3_registers &mapped_sm3,
			sound_mode_4_registers &mapped_sm4,
			sound_control_registers &mapped_ctrl,
			wave_sample_memory &mapped_wave_sample_memory);
private:
	sound_mode_1_registers &sm1;
	sound_mode_2_registers &sm2;
	sound_mode_3_registers &sm3;
	sound_mode_4_registers &sm4;
	sound_control_registers &ctrl;
	wave_sample_memory &samples;
};
