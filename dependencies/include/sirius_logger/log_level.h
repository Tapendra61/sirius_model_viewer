#pragma once

namespace sr {
enum class LogLevel { Trace = 0, Info = 1, Warning = 2, Error = 3, Fatal = 4 };
struct LogColors {
	static constexpr const char *red = "\x1b[31m";
	static constexpr const char *bright_red = "\x1b[1;31m";
	static constexpr const char *yellow = "\x1b[33m";
	static constexpr const char *gray = "\x1b[90m";
	static constexpr const char *reset = "\x1b[0m";
};

inline const char *level_to_string(LogLevel level) {
	switch (level) {
	case LogLevel::Trace:
		return "Trace";
	case LogLevel::Info:
		return "Info";
	case LogLevel::Warning:
		return "Warning";
	case LogLevel::Error:
		return "Error";
	case LogLevel::Fatal:
		return "Fatal";
	}
	return "Unknown";
}

inline const char *get_log_color(LogLevel level) {
	switch (level) {
	case LogLevel::Fatal:
		return LogColors::bright_red;
	case LogLevel::Error:
		return LogColors::red;
	case LogLevel::Warning:
		return LogColors::yellow;
	case LogLevel::Info:
		return LogColors::reset;
	case LogLevel::Trace:
		return LogColors::gray;
	}
	return LogColors::reset;
}
} // namespace sr