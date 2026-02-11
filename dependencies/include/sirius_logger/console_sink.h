#pragma once

#include "log_level.h"
#include "sink.h"
#include "timestamp.h"
#include <ostream>

namespace sr {
class ConsoleSink final : public Sink {
  private:
	std::ostream &out_;

  public:
	explicit ConsoleSink(std::ostream &out) : out_(out) {}
	void write(const LogLevel level, const std::string_view message) override {
		out_ << "[" << get_current_timestamp() << "]" << "["
			 << get_log_color(level) << level_to_string(level)
			 << LogColors::reset << "]" << message << "\n";
	}
};
} // namespace sr