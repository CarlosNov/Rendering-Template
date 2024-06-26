#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <cstdint>
#include <stdint.h>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Core/Core.h"
#include "Core/Log.h"
#include "Core/Assert.h"

#ifdef CORE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif