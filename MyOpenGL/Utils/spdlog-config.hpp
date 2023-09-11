#pragma once

#ifndef NDEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#else
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_ERROR
#endif

#ifdef _MSC_VER
#define LOG_STRING(string) L##string
#else
#define  LOG_STRING(string) string
#endif

#include <spdlog/spdlog.h>
