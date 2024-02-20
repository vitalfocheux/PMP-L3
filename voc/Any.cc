#include "Any.h"

namespace voc {

  Any::Any() {
  }

  Any::Any(const Any& other) {
  }

  Any::Any(Any&& other) {
  }

  Any& Any::operator=(const Any& other) {
    return *this;
  }

  Any& Any::operator=(Any&& other) {
    return *this;
  }

  Any::~Any() {
    delete content;
  }

  bool Any::hasValue() const {
    return false;
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
