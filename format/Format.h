#ifndef FP_FORMAT_H
#define FP_FORMAT_H

#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <iomanip>

namespace fp {

  // template<typename T, typename U>
  // struct is_pointer_of_type {
  //     static constexpr bool value = std::is_pointer<T>::value && std::is_same<typename std::remove_pointer<T>::type, U>::value;
  // };

  // Prototype de format_tuple
  template<typename... Args, size_t... Is>
  void format_tuple(std::ostringstream& os, std::string& fmt, const std::tuple<Args...>& args, std::index_sequence<Is...>);

  // Fonction de formatage récursive
  template<typename T>
  void format_arg(std::ostringstream& os, std::string& fmt, const T& arg) {
    std::cout << "format_arg recursive" << std::endl;
    using ArgType = std::remove_reference_t<T>;
    std::size_t pos = fmt.find("%");
    std::cout << pos << std::endl;
    if(pos != std::string::npos){
      os << fmt.substr(0, (pos));
      std::cout << fmt << std::endl;
      fmt = fmt.substr((pos+1));
      std::cout << fmt << std::endl;
      char c = fmt.front();
      std::cout << "c = " << c << std::endl;
      switch(c) {
        case 'd':
          if constexpr (std::is_same<ArgType, int>::value){
            os << arg;
          } else {
            throw std::runtime_error("Runtime error: Bad argument type");
          }
          break;
        case 'i':
          if constexpr (std::is_same<ArgType, int>::value){
            os << arg;
          } else {
            throw std::runtime_error("Runtime error: Bad argument type");
          }
          break;
        case 'f':
          if constexpr (std::is_same<ArgType, double>::value){
            os << std::fixed << std::setprecision(6) << arg;
          } else {
            throw std::runtime_error("Runtime error: Bad argument type");
          }
          break;
        case 'b':
          if constexpr (std::is_same<ArgType, bool>::value){
            os << std::boolalpha << arg;
          } else {
            throw std::runtime_error("Runtime error: Bad argument type");
          }
          break;
        case 's':
          if constexpr (std::is_same<ArgType, const char*>::value){
            // std::cout << std::boolalpha << (*arg == '\0') << std::endl;
            if(*arg == '\0'){
              os << "(null)";
            } else {
              os << arg;
            }
          } else {
            throw std::runtime_error("Runtime error: Bad argument type string");
          }
          break;
        case 'c':
          if constexpr (std::is_same<ArgType, char>::value){
            os << arg;
          } else {
            throw std::runtime_error("Runtime error: Bad argument type");
          }
          break;
        case 'p':
          if constexpr (std::is_pointer<ArgType>::value){
            os << arg;
          } else {
            throw std::runtime_error("Runtime error: Bad argument type");
          }
          break;
        case 'x':
          if constexpr (std::is_same<ArgType, int>::value){
            os << "0x" << std::hex << arg;
          } else {
            throw std::runtime_error("Runtime error: Bad argument type");
          }
          break;
        case 'o':
          os << "User implementation. Here: " << arg;
          break;
        case '%':
          os << "%";
          break;
        default:
          break;
      }
      fmt = fmt.substr(1);
    }
  }

  // Surcharge pour le cas de tuple
  template<typename... Args>
  void format_args(std::ostringstream& os, std::string& fmt, const std::tuple<Args...>& args) {
    std::cout << "format_args surcharge " << fmt << std::endl;
    format_tuple(os, fmt, args, std::index_sequence_for<Args...>{});
  }

  // Fonction de formatage pour un tuple
  template<typename... Args, size_t... Is>
  void format_tuple(std::ostringstream& os, std::string& fmt, const std::tuple<Args...>& args, std::index_sequence<Is...>) {
    std::cout << "format_tuple " << fmt << std::endl;
    (format_arg(os, fmt, std::get<Is>(args)), ...);
  }

  std::string echappement(std::string& fmt){
    std::size_t pos = fmt.find("%%");
    // std::cout << fmt << " " << pos << std::endl;
    if(pos != std::string::npos){
      fmt = fmt.substr(0, pos) + fmt.substr((pos+1));
    }
    return fmt;
  }

  /**
   * @brief Insert all parameters into a formatted string
   */
  template<typename... Args>
  std::string format(const std::string& formatString, const Args&... args) {
    // if (sizeof...(args) > 0 && formatString.find("%%") == std::string::npos){
    //   throw std::runtime_error("Runtime error: Too many arguments");
    // }
    std::cout << "format" << std::endl;
    std::ostringstream oss;
    std::string fmt = formatString;
    format_args(oss, fmt, std::make_tuple(args...));
    std::cout << fmt << std::endl;
    if(fmt.find("%%") != std::string::npos){
      fmt = echappement(fmt);
    }
    oss << fmt;
    return oss.str();
  }

  std::string format(const std::string& formatString){
    if (formatString.find("%%") != std::string::npos){
      std::string fmt = formatString;
      return echappement(fmt);
    }
    // throw std::runtime_error("Runtime error: Missing argument");
    return formatString;
  }

  
}

#endif // FP_FORMAT_H
