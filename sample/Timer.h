#pragma once

#include <SDL2/SDL.h>

class Timer {
public:
	struct Time {
	};

	Timer() : before_(SDL_GetPerformanceCounter()), freq_((double)SDL_GetPerformanceFrequency()) {
		now_ = before_;
	}

	double Peek() {
		now_ = SDL_GetPerformanceCounter();
		return double(now_ - before_) / freq_;
	}
	
	double Get() {
		before_ = now_;
		now_ = SDL_GetPerformanceCounter();
		return double(now_ - before_) / freq_;
	}

private:
	Uint64 before_;
	Uint64 now_;
	double freq_;
};
