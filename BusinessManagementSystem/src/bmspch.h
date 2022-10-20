#pragma once

#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <filesystem>
#include <time.h>

// MySQL Database
#include <mysql/jdbc.h>

// Logging
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

// JSON
#include <nlohmann/json.hpp>

#include "Core.h"