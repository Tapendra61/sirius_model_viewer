#pragma once

#include "formatter.h"
#include "log_level.h"
#include "sink.h"
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

namespace sr {

class Logger {
  private:
	std::vector<std::unique_ptr<Sink>> sinks_;
	LogLevel level_ = LogLevel::Trace;
	std::mutex mtx_;

  public:
	void set_level(LogLevel level) { level_ = level; }

	template <typename... Args>
	void log(LogLevel level, const std::string &fmt, Args &&...args) {
		if (level < level_)
			return;

		std::lock_guard<std::mutex> lock(mtx_);

		std::string message = format(fmt, std::forward<Args>(args)...);

		for (auto &sink : sinks_) {
			sink->write(level, message);
		}
	}

	void add_sink(std::unique_ptr<Sink> sink) {
		sinks_.push_back(std::move(sink));
	}
};
} // namespace sr