#ifndef FP_FORMAT_H
#define FP_FORMAT_H

#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <iomanip>

namespace fp {

  /**
   * @brief A class that allows determining whether to_string is overloaded or not
  */
  template <typename T>
  class has_to_string_overload
  {
  private:
    template <typename C>
    static auto test(void*) -> decltype(to_string(std::declval<C>()), std::true_type());

    template <typename C>
    static std::false_type test(...);

  public:
    static constexpr bool value = decltype(test<T>(0))::value;
  };

  std::size_t indice = 0;

  /**
   * @brief Allows counting the number of substitutions
  */
  std::size_t countSubsistution(const std::string& str) {
    if(str.empty()){
      return 0;
    }
    std::size_t res = 0;
    for(std::size_t i = 0; i < str.size() - 1; i++){
      if(str[i] == '%'){
        if(str[i+1] == '%'){
          i++;
        } else if(str[i+1] == 'd' || str[i+1] == 'i' || str[i+1] == 'f' || str[i+1] == 'b' || str[i+1] == 's' || str[i+1] == 'c' || str[i+1] == 'p' || str[i+1] == 'x' || str[i+1] == 'o' || str[i+1] == ' ') {
          res++;
        }else if(isgraph(str[i+1])){
          throw std::runtime_error("Runtime error: Bad format");
        }
      }
    }
    if(str[str.size() - 1] == '%' && str.size() > 2 && str[str.size() - 2] != '%'){
      res++;
    }
    return res;
  }

  /**
   * @brief Prototype of format_tuple
  */
  template<typename... Args, size_t... Is>
  void format_tuple(std::ostringstream& os, std::string& fmt, const std::tuple<Args...>& args, std::index_sequence<Is...>);

  /**
   * @brief Recursive formatting function
  */
  template<typename T>
  void format_arg(std::ostringstream& os, std::string& fmt, const T& arg) {
    if(fmt[fmt.size() - 1] == '%' && fmt.size() > 1 && fmt[fmt.size() - 2] != '%'){
      throw std::runtime_error("Invalid specifier");
    }
    indice = 0;
    bool br = false;
    using ArgType = std::remove_reference_t<T>;
    while(indice < fmt.size()){
      std::size_t pos = fmt.find("%");
      if(pos != std::string::npos && pos != fmt.size() - 1){
        os << fmt.substr(0, (pos));
        fmt = fmt.substr((pos+1));
        char c = fmt.front();
        switch(c) {
          case 'd':
            if constexpr (std::is_integral<ArgType>::value && !std::is_same<ArgType, char>::value && !std::is_same<ArgType, bool>::value){
              os << arg;
            } else {
              throw std::runtime_error("Runtime error: Bad argument type");
            }
            br = true;
            break;
          case 'i':
            if constexpr (std::is_integral<ArgType>::value && !std::is_same<ArgType, char>::value && !std::is_same<ArgType, bool>::value){
              os << arg;
            } else {
              throw std::runtime_error("Runtime error: Bad argument type");
            }
            br = true;
            break;
          case 'f':
            if constexpr (std::is_floating_point<ArgType>::value){
              os << std::fixed << std::setprecision(6) << arg;
            } else {
              throw std::runtime_error("Runtime error: Bad argument type");
            }
            br = true;
            break;
          case 'b':
            if constexpr (std::is_same<ArgType, bool>::value){
              os << std::boolalpha << arg;
            } else {
              throw std::runtime_error("Runtime error: Bad argument type");
            }
            br = true;
            break;
          case 's':
            if constexpr (std::is_same<ArgType, const char*>::value){
              if(*arg == '\0'){
                os << "(null)";
              } else {
                os << arg;
              }
            } else if constexpr (std::is_same<ArgType, std::string>::value){
              if(arg.empty()){
                os << "(null)";
              } else {
                os << arg;
            }
            } else {
              throw std::runtime_error("Runtime error: Bad argument type");
            }
            br = true;
            break;
          case 'c':
            if constexpr (std::is_same<ArgType, char>::value){
              os << arg;
            } else {
              throw std::runtime_error("Runtime error: Bad argument type");
            }
            br = true;
            break;
          case 'p':
            if constexpr (std::is_pointer<ArgType>::value && !std::is_same<ArgType, const char*>::value && !std::is_same<ArgType, std::string>::value){
              if(arg == nullptr){
                os << "0x0";
              } else {
                os << arg;
              }
            } else {
              throw std::runtime_error("Runtime error: Bad argument type");
            }
            br = true;
            break;
          case 'x':
            if constexpr (std::is_integral<ArgType>::value && !std::is_same<ArgType, char>::value && !std::is_same<ArgType, bool>::value){
              os << "0x" << std::hex << arg;
            } else {
              throw std::runtime_error("Runtime error: Bad argument type");
            }
            br = true;
            break;
          case 'o':
            if constexpr (has_to_string_overload<T>::value) {
              os << to_string(arg);
            } else {
              throw std::runtime_error("Runtime error: Bad argument type");
            }
            br = true;
            break;
          case '%':
            os << "%";
            break;
          default:
            throw std::runtime_error("Runtime error: Bad format");
            break;
        }
        fmt = fmt.substr(1);
      }
      indice++;
      if(br){
        break;
      }
    }
    if(fmt.size() >= 2 && !br){
      char c = fmt[1];
      switch(c) {
          case 'd':
            if constexpr (std::is_integral<ArgType>::value && !std::is_same<ArgType, char>::value && !std::is_same<ArgType, bool>::value){
             os << arg;
            } else {
              throw std::runtime_error("Runtime error: Bad argument type");
            }
            br = true;
            break;
          case 'i':
            if constexpr (std::is_integral<ArgType>::value && !std::is_same<ArgType, char>::value && !std::is_same<ArgType, bool>::value){
              os << arg;
            } else {
              throw std::runtime_error("Runtime error: Bad argument type");
            }
            br = true;
            break;
          case 'f':
            if constexpr (std::is_floating_point<ArgType>::value){
              os << std::fixed << std::setprecision(6) << arg;
            } else {
              throw std::runtime_error("Runtime error: Bad argument type");
            }
            br = true;
            break;
          case 'b':
            if constexpr (std::is_same<ArgType, bool>::value){
              os << std::boolalpha << arg;
            } else {
              throw std::runtime_error("Runtime error: Bad argument type");
            }
            br = true;
            break;
          case 's':
            if constexpr (std::is_same<ArgType, const char*>::value){
              if(*arg == '\0'){
                os << "(null)";
              } else {
                os << arg;
              }
            } else if constexpr (std::is_same<ArgType, std::string>::value){
              if(arg.empty()){
                os << "(null)";
              } else {
                os << arg;
            }
            } else {
              throw std::runtime_error("Runtime error: Bad argument type");
            }
            br = true;
            break;
          case 'c':
            if constexpr (std::is_same<ArgType, char>::value){
              os << arg;
            } else {
              throw std::runtime_error("Runtime error: Bad argument type");
            }
            br = true;
            break;
          case 'p':
            if constexpr (std::is_pointer<ArgType>::value && !std::is_same<ArgType, const char*>::value && !std::is_same<ArgType, std::string>::value){
              if(arg == nullptr){
                os << "0x0";
              } else {
                os << arg;
              }
            } else {
              throw std::runtime_error("Runtime error: Bad argument type");
            }
            br = true;
            break;
          case 'x':
            if constexpr (std::is_integral<ArgType>::value && !std::is_same<ArgType, char>::value && !std::is_same<ArgType, bool>::value){
              os << "0x" << std::hex << arg;
            } else {
              throw std::runtime_error("Runtime error: Bad argument type");
            }
            br = true;
            break;
          case 'o':
            if constexpr (has_to_string_overload<T>::value) {
              os << to_string(arg);
            } else {
              throw std::runtime_error("Runtime error: Bad argument type");
            }
            br = true;
            break;
          case '%':
            os << "%";
            break;
          default:
            throw std::runtime_error("Runtime error: Bad format");
            break;
        }
        fmt = fmt.substr(2);
    }
  }

  /**
   * @brief Overloading for the case of tuples
  */
  template<typename... Args>
  void format_args(std::ostringstream& os, std::string& fmt, const std::tuple<Args...>& args) {
    format_tuple(os, fmt, args, std::index_sequence_for<Args...>{});
  }

  /**
   * @brief Formatting function for a tuple
  */
  template<typename... Args, size_t... Is>
  void format_tuple(std::ostringstream& os, std::string& fmt, const std::tuple<Args...>& args, std::index_sequence<Is...>) {
    (format_arg(os, fmt, std::get<Is>(args)), ...);
  }

  /**
   * @brief Allow escaping the characters %%
  */
  std::string escape(std::ostringstream& os, std::string& fmt){
    std::size_t pos = fmt.find("%%");
    if(pos != std::string::npos){
      std::cout << pos << std::endl;
      os << fmt.substr(0, pos) << "%";
      if(pos+2 == fmt.size()){
        std::cout << os.str() << std::endl;
        fmt = "";
        return fmt;
      }
      fmt = fmt.substr((pos+2));
      escape(os, fmt);
    } else {
      os << fmt;
    }
    return os.str();
  }

  /**
   * @brief Allow escaping the characters %%
  */
  std::string escape(std::string& fmt, std::size_t& index){
    std::size_t pos = fmt.find("%%", index);
    fmt = fmt.substr(0, pos) + "%" + fmt.substr(pos+2);
    index = pos + 1;
    return fmt;
  }

  /**
   * @brief Insert all parameters into a formatted string
   */
  template<typename... Args>
  std::string format(const std::string& formatString, const Args&... args) {
    if(countSubsistution(formatString) != sizeof...(args)){
      throw std::runtime_error("Runtime error: Too many arguments");
    }
    std::ostringstream oss;
    std::string fmt = formatString;
    format_args(oss, fmt, std::make_tuple(args...));
    if(fmt.find("%%") != std::string::npos){
      fmt = escape(oss, fmt);
    }
    oss << fmt;
    return oss.str();
  }

  /**
   * @brief Formatted string withour parameters
  */
  std::string format(const std::string& formatString){
    if(countSubsistution(formatString) != 0){
      throw std::runtime_error("Runtime error: Missing argument");
    }
    std::string fmt = formatString;
    std::size_t index = 0;
    while(fmt.find("%%", index) != std::string::npos){
      fmt = escape(fmt, index);
    }
    return fmt;
  }

  
}

#endif // FP_FORMAT_H
