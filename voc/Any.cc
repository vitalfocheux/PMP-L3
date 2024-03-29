#include "Any.h"

namespace voc {

  Any::Any() {
    // std::cout << "Default constructor" << std::endl;
  }

  Any::Any(const Any& other) : content(other.content->clone()) {
    // std::cout << "Copy constructor" << std::endl;
  }

  Any::Any(Any&& other) noexcept : content(std::exchange(other.content, nullptr)){
    // std::cout << "Move constructor" << std::endl;
  }

  Any& Any::operator=(const Any& other) {
    // std::cout << "Copy assignment" << std::endl;
    clear();
    if (other.content != nullptr) {
      content = other.content->clone();
    }
    return *this;
  }

  Any& Any::operator=(Any&& other) noexcept {
    // std::cout << "Move assignment" << std::endl;
    std::swap(content, other.content);
    return *this;
  }

  Any::~Any() {
    if(content != nullptr){
      delete content;
      content = nullptr;  
    }
  }

  bool Any::hasValue() const {
    return content != nullptr;
  }

  Any::operator bool() const {
    return hasValue();
  }

  void Any::clear() {
    delete content;
    content = nullptr;
  }

  const std::type_info& Any::getType() const {
    return (content != nullptr) ? content->getType() : typeid(void);
  }

}
