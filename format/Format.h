#ifndef FP_FORMAT_H
#define FP_FORMAT_H

#include <iostream>
#include <sstream>
#include <string>
#include <tuple>

// Prototype de format_tuple
template<typename... Args, size_t... Is>
void format_tuple(std::ostream& os, const std::string& fmt, const std::tuple<Args...>& args, std::index_sequence<Is...>);

// Fonction de formatage récursive
template<typename T>
void format_arg(std::ostream& os, const std::string& fmt, const T& arg) {
  std::cout << "format_arg recursive" << std::endl;
  std::cout << arg << std::endl;
  size_t pos = fmt.find("{}");
  if (pos != std::string::npos) {
    os << fmt.substr(0, pos);
    os << arg;
    format_arg(os, fmt.substr(pos + 2), arg);
  } else {
    os << fmt;
  }
}

// Surcharge pour le cas de tuple
template<typename... Args>
void format_args(std::ostream& os, const std::string& fmt, const std::tuple<Args...>& args) {
  std::cout << "format_args surcharge" << std::endl;
  format_tuple(os, fmt, args, std::index_sequence_for<Args...>{});
}

// Fonction de formatage pour un tuple
template<typename... Args, size_t... Is>
void format_tuple(std::ostream& os, const std::string& fmt, const std::tuple<Args...>& args, std::index_sequence<Is...>) {
  std::cout << "format_tuple" << std::endl;
  (format_arg(os, fmt, std::get<Is>(args)), ...);
}

namespace fp {

  /**
   * @brief Insert all parameters into a formatted string
   */
  template<typename... Args>
  std::string format(const std::string& formatString, const Args&... args) {
    std::cout << "format" << std::endl;
    std::ostringstream oss;
    format_args(oss, formatString, std::make_tuple(args...));
    return oss.str();
  }
}

#endif // FP_FORMAT_H
