#ifndef VOC_OPTIONAL_H
#define VOC_OPTIONAL_H

#define cmp

namespace voc {

  struct InPlaceStruct {
  };

  inline constexpr InPlaceStruct InPlace = { };

  template<typename T>
  class Optional {
  public:
    /*
     * Create an empty object
     */
    Optional()
    {
    }

    Optional(const Optional& other) : content(new T(*other.content)) {
    }

    Optional(Optional&& other) noexcept : content(std::exchange(other.content, nullptr)){
    }


    /*
     * Create an object thanks to a value
     */
    Optional(T value) : content(new T(value)) {
    }

    /*
     * Create an object in place with the arguments of a constructor of T
     */
    template<typename ... Args>
    Optional(InPlaceStruct inPlace [[maybe_unused]], Args&& ... args) : content(new T(std::forward<Args>(args)...)) {
    }

    /*
     * Affectation from an value
     */
    template<typename U, typename std::enable_if<!std::is_same<std::decay_t<U>, Optional<T>>::value>::type* = nullptr>
    Optional& operator=(U&& value) {
      clear();
      content = new T(std::forward<U>(value));
      return *this;
    }

    template<typename U, typename std::enable_if<std::is_same<std::decay_t<U>, Optional<T>>::value>::type* = nullptr>
    Optional& operator=(U&& value) {
      clear();
      content = new T(*value.content);
      return *this;
    }

    /*
     * Affectation from another compatible Optional
     */
    template<typename U>
    Optional& operator=(const Optional<U>& other) {
      clear();
      content = new T(other.content);
      return *this;
    }

    /*
     * Affectation from another compatible Optional
     */
    template<typename U>
    Optional& operator=(Optional<U>&& other) {
      std::swap(content, other.content);
      return *this;
    }

    ~Optional(){
      // std::cout << "Destructor" << std::endl;
      clear();      
    }

    /*
     * Tell if the object has a value, or is empty
     */
    bool hasValue() const {
      return content != nullptr;
    }

    /*
     * Tell if the object has a value, or is empty
     */
    explicit operator bool() const {
      return hasValue();
    }

    /*
     * Return a reference to the object, or std::runtime_error if the object is empty
     */
    T& getValue() {
      if(!hasValue()){
        throw std::runtime_error("Optional is empty");
      }
      return *content;
    }

    /*
     * Return a const reference to the object, or std::runtime_error if the object is empty
     */
    const T& getValue() const {
      if(!hasValue()){
        throw std::runtime_error("Optional is empty");
      }
      return static_cast<const T&>(*content);
    }

    /*
     * Return a pointer to the stored data. If the value was initialized, the behaviour is undefined.
     */
    T* operator->() {
      return content;    
    }

    /*
     * Return a const pointer to the stored data. If the value was initialized, the behaviour is undefined.
     */
    const T* operator->() const {
      return static_cast<const T*>(content);
    }

    /*
     * Return a reference to the stored data. If the value was initialized, the behaviour is undefined.
     */
    T& operator*() {
      return *content;
    }

    /*
     * Return a reference to the stored data. If the value was initialized, the behaviour is undefined.
     */
    const T& operator*() const {
      return static_cast<const T&>(*content);
    }

    /*
     * Return the stored object T or forward the default value
     */
    template<typename U>
    T getValueOr(U&& defaultValue) const {
      if(hasValue()){
        return *content;
      }
      return std::forward<U>(defaultValue);
    }

    /*
     * Clear the stored value
     */
    void clear() {
      if(hasValue()){
        delete content;
        content = nullptr;
      }
    }

  private:
    T* content = nullptr;
  };

  template<typename T, typename... Args>
  Optional<T> makeOptional(Args&&... args) {
    return Optional<T>(InPlace, std::forward<Args>(args)...);
  }

  #ifdef cmp

  /*
   * The comparaison operator could take any instance of Optional with compatible type and
   * must works with non initalized Optional.
   * Furthermore we can compare an Option directly with a value.
   *
   * See https://en.cppreference.com/w/cpp/utility/optional/operator_cmp for more details.
   */
  template<typename T, typename U>
  bool operator==(const Optional<T>& lhs, const Optional<U>& rhs) {
    if(bool(lhs) != bool(rhs)){
      return false;
    }
    if(bool(lhs) == false && bool(rhs) == false){
      return true;
    }
    return *lhs == *rhs;
  }

  // template<typename T>
  // bool operator==(const Optional<T>& lhs, std::nullopt_t) {
  //   return !lhs;
  // }

  // template<typename T>
  // bool operator==(std::nullopt_t, const Optional<T>& rhs) {
  //   return !rhs;
  // }

  template<typename T, typename U>
  bool operator==(const Optional<T>& lhs, const U& rhs) {
    return bool(lhs) ? *lhs == rhs : false;
  }

  template<typename T, typename U>
  bool operator==(const T& lhs, const Optional<U>& rhs) {
    return bool(rhs) ? lhs == *rhs : false;
  }

  template<typename T, typename U>
  bool operator!=(const Optional<T>& lhs, const Optional<U>& rhs) {
    if(bool(lhs) != bool(rhs)){
      return true;
    }
    if(bool(lhs) == false && bool(rhs) == false){
      return false;
    }
    return *lhs != *rhs;
  }

  // template<typename T>
  // bool operator!=(const Optional<T>& lhs, std::nullopt_t) {
  //   return lhs;
  // }

  // template<typename T>
  // bool operator!=(std::nullopt_t, const Optional<T>& rhs) {
  //   return rhs;
  // }

  template<typename T, typename U>
  bool operator!=(const Optional<T>& lhs, const U& rhs) {
    return bool(lhs) ? *lhs != rhs : true;
  }

  template<typename T, typename U>
  bool operator!=(const T& lhs, const Optional<U>& rhs) {
    return bool(rhs) ? lhs != *rhs : true;
  }

  template<typename T, typename U>
  bool operator< (const Optional<T>& lhs, const Optional<U>& rhs) {
    if(bool(rhs) == false){
      return false;
    }
    if(bool(lhs) == false){
      return true;
    }
    return *lhs < *rhs;
  }

  // template<typename T>
  // bool operator< (const Optional<T>& lhs, std::nullopt_t) {
  //   return false;
  // }

  // template<typename T>
  // bool operator< (std::nullopt_t, const Optional<T>& rhs) {
  //   return rhs;
  // }

  template<typename T, typename U>
  bool operator< (const Optional<T>& lhs, const U& rhs) {
    return bool(lhs) ? *lhs < rhs : true;
  }

  template<typename T, typename U>
  bool operator< (const T& lhs, const Optional<U>& rhs) {
    return bool(rhs) ? lhs < *rhs : false;
  }

  template<typename T, typename U>
  bool operator<=(const Optional<T>& lhs, const Optional<U>& rhs) {
    if(bool(lhs) == false){
      return true;
    }
    if(bool(rhs) == false){
      return false;
    }
    return *lhs <= *rhs;
  }

  // template<typename T>
  // bool operator<=(const Optional<T>& lhs, std::nullopt_t) {
  //   return !lhs;
  // }

  // template<typename T>
  // bool operator<=(std::nullopt_t, const Optional<T>& rhs) {
  //   return true;
  // }

  template<typename T, typename U>
  bool operator<=(const Optional<T>& lhs, const U& rhs) {
    return bool(lhs) ? *lhs <= rhs : true;
  }

  template<typename T, typename U>
  bool operator<=(const T& lhs, const Optional<U>& rhs) {
    return bool(rhs) ? lhs <= *rhs : false;
  }

  template<typename T, typename U>
  bool operator> (const Optional<T>& lhs, const Optional<U>& rhs) {
    if(bool(lhs) == false){
      return false;
    }
    if(bool(rhs) == false){
      return true;
    }
    return *lhs > *rhs;
  }

  // template<typename T>
  // bool operator> (const Optional<T>& lhs, std::nullopt_t) {
  //   return lhs;
  // }

  // template<typename T>
  // bool operator> (std::nullopt_t, const Optional<T>& rhs) {
  //   return false;
  // }

  template<typename T, typename U>
  bool operator> (const Optional<T>& lhs, const U& rhs) {
    return bool(lhs) ? *lhs > rhs : false;
  }

  template<typename T, typename U>
  bool operator> (const T& lhs, const Optional<U>& rhs) {
    return bool(rhs) ? lhs > *rhs : true;
  }

  template<typename T, typename U>
  bool operator>=(const Optional<T>& lhs, const Optional<U>& rhs) {
    if(bool(rhs) == false){
      return true;
    }
    if(bool(lhs) == false){
      return false;
    }
    return *lhs >= *rhs;
  }

  // template<typename T>
  // bool operator>=(const Optional<T>& lhs, std::nullopt_t) {
  //   return true;
  // }

  // template<typename T>
  // bool operator>=(std::nullopt_t, const Optional<T>& rhs) {
  //   return !rhs;
  // }

  template<typename T, typename U>
  bool operator>=(const Optional<T>& lhs, const U& rhs) {
    return bool(lhs) ? *lhs >= rhs : false;
  }

  template<typename T, typename U>
  bool operator>=(const T& lhs, const Optional<U>& rhs) {
    return bool(rhs) ? lhs >= *rhs : true;
  }

  #endif

}

#endif // VOC_OPTIONAL_H
