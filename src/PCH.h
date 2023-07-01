#pragma once

#pragma warning(push)

#include <algorithm>
#include <bitset>
#include <chrono>
#include <cmath>
#include <compare>
#include <concepts>
#include <ctime>
#include <filesystem>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <ranges>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "F4SE/F4SE.h"
#include "RE/Fallout.h"

#ifdef NDEBUG
#	include <spdlog/sinks/basic_file_sink.h>
#else
#	include <spdlog/sinks/msvc_sink.h>
#endif
#pragma warning(pop)

#define DLLEXPORT __declspec(dllexport)

namespace logger = F4SE::log;

using namespace std::literals;

#include "Common.h"
#include "Version.h"
