#pragma once

#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

namespace sr {
inline std::string get_current_timestamp() {
	std::ostringstream oss;

	std::chrono::time_point<std::chrono::system_clock> now =
		std::chrono::system_clock::now();
	std::time_t c_time_now = std::chrono::system_clock::to_time_t(now);
	std::tm local_tm;
	localtime_s(&local_tm, &c_time_now);
	oss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S");

	return oss.str();
}
} // namespace sr