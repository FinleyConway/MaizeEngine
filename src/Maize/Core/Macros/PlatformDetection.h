#pragma once

// platform detection
#if defined(_WIN64)
	#define PLATFORM_WIN
#elif defined(__linux__)
	#define PLATFORM_LINUX
#else
	#error "Unsupported platform!"
#endif


// debug macro platform specific macro
#if defined(PLATFORM_WIN)
	#define DEBUG_BREAK() __debugbreak()
#elif defined(PLATFORM_LINUX)
	#include <csignal>
	#define DEBUG_BREAK() raise(SIGTRAP)
#else
		#error "Platform doesn't support debugbreak!"
#endif