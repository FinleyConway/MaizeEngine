#pragma once

#include "Maize/Core/Macros/PlatformDetection.h"

#ifdef ENABLE_ASSERTS
#define CORE_ASSERT(x, ...) if(!(x)) { CORE_LOG_ERROR("Assertion failed: {0}. Message: {1}.\nAt: {2}, Line: {3}", #x, __VA_ARGS__, __FILE__, __LINE__); DEBUG_BREAK(); }
#define GAME_ASSERT(x, ...) if(!(x)) { GAME_LOG_ERROR("Assertion failed: {0}. Message: {1}.\nAt: {2}, Line: {3}", #x, __VA_ARGS__, __FILE__, __LINE__); DEBUG_BREAK(); }
#else
	#define CORE_ASSERT(x, ...)
	#define GAME_ASSERT(x, ...)
#endif
