#ifndef VOC_OPTIONAL_H
#define VOC_OPTIONAL_H

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


    /*
     * Create an object thanks to a value
     */
    Optional(T value) : value(new T(value)) {
    }

    /*
     * Create an object in place with the arguments of a constructor of T
     */
    template<typename ... Args>
    Optional(InPlaceStruct inPlace, Args&& ... args) : value(new T(std::forward<Args>(args)...)) {
    }

    /*
     * Affectation from an value
     */
    template<typename U>
    Optional& operator=(U&& value) {
      clear();
      value = new T(std::forward<U>(value));
      return *this;
    }

    /*
     * Affectation from another compatible Optional
     */
    template<typename U>
    Optional& operator=(const Optional<U>& other) {
      clear();
      value = new T(other.value);
      return *this;
    }

    /*
     * Affectation from another compatible Optional
     */
    template<typename U>
    Optional& operator=(Optional<U>&& other) {
      std::swap(value, other.value);
      return *this;
    }

    ~Optional(){
      std::cout << "Destructor" << std::endl;
      clear();
    }

    /*
     * Tell if the object has a value, or is empty
     */
    bool hasValue() const {
      return value != nullptr;
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
      return *value;
    }

    /*
     * Return a const reference to the object, or std::runtime_error if the object is empty
     */
    const T& getValue() const {
      if(!hasValue()){
        throw std::runtime_error("Optional is empty");
      }
      return static_cast<const T&>(*value);
    }

    /*
     * Return a pointer to the stored data. If the value was initialized, the behaviour is undefined.
     */
    T* operator->() {
      return value;    
    }

    /*
     * Return a const pointer to the stored data. If the value was initialized, the behaviour is undefined.
     */
    const T* operator->() const {
      return static_cast<const T*>(value);
    }

    /*
     * Return a reference to the stored data. If the value was initialized, the behaviour is undefined.
     */
    T& operator*() {
      return *value;
    }

    /*
     * Return a reference to the stored data. If the value was initialized, the behaviour is undefined.
     */
    const T& operator*() const {
      return static_cast<const T&>(*value);
    }

    /*
     * Return the stored object T or forward the default value
     */
    template<typename U>
    T getValueOr(U&& defaultValue) const {
      if(hasValue()){
        return *value;
      }
      return std::forward<U>(defaultValue);
    }

    /*
     * Clear the stored value
     */
    void clear() {
      if(hasValue()){
        delete value;
        value = nullptr;
      }
    }

  private:
    T* value = nullptr;
  };

  template<typename T, typename... Args>
  Optional<T> makeOptional(Args&&... args) {
    return Optional<T>(InPlace, std::forward<Args>(args)...);
  }

  #if 0

  /*
   * The comparaison operator could take any instance of Optional with compatible type and
   * must works with non initalized Optional.
   * Furthermore we can compare an Option directly with a value.
   *
   * See https://en.cppreference.com/w/cpp/utility/optional/operator_cmp for more details.
   */
  template<typename T, typename U>
  bool operator==(const Optional<T> lhs, const Optional<U> rhs) {
    return false;
  }

  template<typename T, typename U>
  bool operator!=(const Optional<T> lhs, const Optional<U> rhs) {
    if(lhs.hasValue() && rhs.hasValue()){
      return *lhs != *rhs;
    }
    if((!lhs.hasValue && rhs.hasValue) || (lhs.hasValue && !rhs.hasValue)){
      return true;
    }
    return false;
  }

  template<typename T, typename U>
  bool operator< (const Optional<T> lhs, const Optional<U> rhs) {
    if(lhs.hasValue() && rhs.hasValue()){
      return *lhs < *rhs;
    }
    if(!lhs.hasValue() && rhs.hasValue()){
      return true;
    }
    return false;
  }

  template<typename T, typename U>
  bool operator<=(const Optional<T> lhs, const Optional<U> rhs) {
    if(lhs.hasValue() && rhs.hasValue()){
      return *lhs <= *rhs;
    }
    if((!lhs.hasValue() && rhs.hasValue()) || (lhs == rhs)){
      return true;
    }
    return false;
  }

  template<typename T, typename U>
  bool operator> (const Optional<T> lhs, const Optional<U> rhs) {
    if(lhs.hasValue() && rhs.hasValue()){
      return *lhs > *rhs;
    }
    if(lhs.hasValue() && !rhs.hasValue()){
      return true;
    }
    return false;
  }

  template<typename T, typename U>
  bool operator>=(const Optional<T> lhs, const Optional<U> rhs) {
    if(lhs.hasValue() && rhs.hasValue()){
      return *lhs > *rhs;
    }
    if((lhs.hasValue() && !rhs.hasValue()) || (lhs == rhs)){
      return true;
    }
    return false;
  }

  #endif

}

#endif // VOC_OPTIONAL_H
