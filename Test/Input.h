#pragma once

#include "Window.h"

#define IS_KEY_DOWN(key) ((GetAsyncKeyState(key) & 0x8000) ? 1 : 0)
#define IS_KEY_UP(key) ((GetAsyncKeyState(key) & 0x8000) ? 0 : 1)
