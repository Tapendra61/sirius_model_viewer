#pragma once
#include "console_sink.h"
#include "file_sink.h"
#include "logger.h"
#include <iostream>
#include <memory>

inline sr::Logger g_logger{};

namespace sr {

inline void init_logger(LogLevel level = LogLevel::Trace,
						const std::string &file_path = "") {
	g_logger.set_level(level);
	g_logger.add_sink(std::make_unique<ConsoleSink>(std::cout));

	if (!file_path.empty()) {
		g_logger.add_sink(std::make_unique<FileSink>(file_path));
	}
}

template <typename... Args>
inline void log_trace(const std::string &fmt, Args &&...args) {
	g_logger.log(LogLevel::Trace, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
inline void log_info(const std::string &fmt, Args &&...args) {
	g_logger.log(LogLevel::Info, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
inline void log_warn(const std::string &fmt, Args &&...args) {
	g_logger.log(LogLevel::Warning, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
inline void log_error(const std::string &fmt, Args &&...args) {
	g_logger.log(LogLevel::Error, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
inline void log_fatal(const std::string &fmt, Args &&...args) {
	g_logger.log(LogLevel::Fatal, fmt, std::forward<Args>(args)...);
}
}; // namespace sr