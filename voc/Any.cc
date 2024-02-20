#include "Any.h"

namespace voc {

  Any::Any() {
  }

  Any::Any(const Any& other) : content(other.content->clone()) {
    std::cout << "Copy constructor" << std::endl;
  }

  Any::Any(Any&& other) : content(other.content) {
    std::cout << "Move constructor" << std::endl;
  }

  Any& Any::operator=(const Any& other) {
    std::cout << "Copy assignment" << std::endl;
    return *this;
  }

  Any& Any::operator=(Any&& other) {
    std::cout << "Move assignment" << std::endl;
    return *this;
  }

  Any::~Any() {
    delete content;
  }

  bool Any::hasValue() const {
    return content != nullptr;
  }

  Any::operator bool() const {
    return false;
  }

  void Any::clear() {
  }

  const std::type_info& Any::getType() const {
    return (content != nullptr) ? content->getType() : typeid(void);
  }

}
