#pragma once

#include <cstddef>
#include <sstream>
#include <string>
#include <utility>

namespace sr {
template <typename T>
inline std::string to_string_any(const T &value) {
	std::ostringstream out;
	out << value;

	return out.str();
}

inline void format_impl(std::string &out, const std::string &fmt) {
	out += fmt;
}

template <typename T, typename... Args>
inline void format_impl(std::string &out, const std::string &fmt, T &&value,
						Args &&...args) {
	const size_t pos = fmt.find("{}");

	if (pos == std::string::npos) {
		throw std::runtime_error("Format error: too many arguments!");
	}

	out.append(fmt, 0, pos);
	out += to_string_any(std::forward<T>(value));
	format_impl(out, fmt.substr(pos + 2), std::forward<Args>(args)...);
}

template <typename... Args>
inline std::string format(const std::string &fmt, Args &&...args) {
	std::string result;
	result.reserve(fmt.size() + 32);
	format_impl(result, fmt, std::forward<Args>(args)...);
	return result;
}
}; // namespace sr