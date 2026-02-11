#pragma once

#include "log_level.h"
#include "sink.h"
#include "timestamp.h"
#include <fstream>
#include <string_view>

namespace sr {
class FileSink final : public Sink {
  private:
	std::ofstream file_;

  public:
	explicit FileSink(const std::string &path)
		: file_(path, std::ios::out | std::ios::app) {}

	void write(const LogLevel level, const std::string_view message) override {
		file_ << "[" << get_current_timestamp() << "]" << "["
			  << level_to_string(level) << "]" << message << "\n";
		file_.flush();
	}
};
} // namespace sr