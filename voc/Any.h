#ifndef VOC_ANY_H
#define VOC_ANY_H

#include <typeinfo>
#include <utility>
#include <iostream>

namespace voc {

  namespace details {

    class Helper {
      public:
        virtual ~Helper() {
        }
        virtual Helper* clone() const = 0;
        virtual const std::type_info& getType() const = 0;
    };

    template<typename T>
    class HelperGeneric : public details::Helper {

      public:
        HelperGeneric(const T& value) : value(value) {
          // std::cout << this << " " <<"HelperGeneric(const T& value)" << std::endl;
        }

        // HelperGeneric(const voc::Any& other) : value(other.content->clone()) {
        //   std::cout << this << " " <<"HelperGeneric(const T& value) with Any" << std::endl;
        // }

        HelperGeneric(T&& value) : value(value) {
          // std::cout << this << " " <<"HelperGeneric(T&& value)" << std::endl;
        }

        // HelperGeneric(voc::Any&& other) : value(other.content) {
        //   std::cout << this << " " <<"HelperGeneric(T&& value) with Any" << std::endl;
        // }

        HelperGeneric* clone() const override {
          return new HelperGeneric(value);
        }

        const std::type_info& getType() const override {
          return typeid(T);
        }

        T value;
    };
  }

  template<typename T>
  struct InPlaceTypeStruct {
  };

  template<typename T>
  inline constexpr InPlaceTypeStruct<T> InPlaceType = { };

  class Any {
  public:
    /*
     * Create an empty object
     */
    Any();

    Any(const Any& other);

    Any(Any&& other) noexcept;

    /*
     * Create an object thanks to a value
     */
    template<typename T, typename std::enable_if<!std::is_same<std::decay_t<T>, Any>::value>::type* = nullptr>
    Any(T&& value) {
      // std::cout << this << " " << "Any(T&& value)" << std::endl;
      content = new details::HelperGeneric<T>(std::forward<T>(value));
    }

    template<typename U, typename std::enable_if<std::is_same<std::decay_t<U>, Any>::value>::type* = nullptr>
    Any(U&& value) {
      content = value.content ? value.content->clone() : nullptr;
    }

    /*
     * Create an object in place with the arguments of a constructor of T
     */
    template<typename T, typename ... Args>
    Any(InPlaceTypeStruct<T> inPlace [[maybe_unused]], Args&& ... args) : content(new details::HelperGeneric<T>(T(std::forward<Args>(args)...))){
      // std::cout << this << " " << "Any(InPlaceTypeStruct<T> inPlace, Args&& ... args)" << std::endl;
    }

    Any& operator=(const Any& other);

    Any& operator=(Any&& other) noexcept;


    /*
     * Affecte a directly value
     */
    template<typename U, typename std::enable_if<!std::is_same<std::decay_t<U>, Any>::value>::type* = nullptr>
    Any& operator=(U&& value) {
      delete content;
      content = new details::HelperGeneric<U>(std::forward<U>(value));
      return *this;
    }

    /**
     * Affecte a directly value from an Any with SFINAE
    */
    template<typename U, typename std::enable_if<std::is_same<std::decay_t<U>, Any>::value>::type* = nullptr>
    Any& operator=(U&& value) {
      if (this != &value) {
        delete content;
        content = value.content ? value.content->clone() : nullptr;
      }
      return *this;
    }

    ~Any();

    /*
     * Tell if the object has a value or is empty
     */
    bool hasValue() const;

    /*
     * Tell if the object has a value or is empty
     */
    operator bool() const;

    /*
     * Clear the object. After a call to clear, the object is empty.
     */
        void clear();

        /*
         * Return the type_info of the type of the object,
         * or the type_info of void if the object is empty
         */
        const std::type_info& getType() const;

      private:

        // std::unique_ptr<details::Helper> content = nullptr;

        details::Helper* content = nullptr;

        template<typename T>
        friend T anyCast(const Any& any);
        template<typename T>
        friend T anyCast(Any& any);
        template<typename T>
        friend T anyCast(Any&& any);
        template<typename T>
        friend T* anyCast(Any* any);
        template<typename T>
        friend const T* anyCast(const Any* any);
        template<typename T> friend class details::HelperGeneric;
  };

  /*
   * Create an instance of Any with a value of type T
   */
  template<typename T, typename... Args>
  Any makeAny(Args&&... args) {
    return Any(InPlaceType<T>, std::forward<Args>(args)...);
  }

  /*
   * Return a copy of the object, or std::bad_cast if the object is empty or has not the right type
   */
  template<typename T>
  T anyCast(const Any& any) {
    // std::cout << "anyCast(const Any& any)" << std::endl;
    if(!any.hasValue() || any.getType() != typeid(T)){
      throw std::bad_cast();
    }
    return static_cast<details::HelperGeneric<T>*>(any.content)->value;
  }

  /*
   * Return a copy of the object, or std::bad_cast if the object is empty or has not the right type
   */
  template<typename T>
  T anyCast(Any& any) {
    // std::cout << "anyCast(Any& any)" << std::endl;
    if(!any.hasValue() || any.getType() != typeid(T)){
      throw std::bad_cast();
    }
    return static_cast<details::HelperGeneric<T>*>(any.content)->value;
  }

  /*
   * Return a copy of the object, or std::bad_cast if the object is empty or has not the right type
   */
  template<typename T>
  T anyCast(Any&& any) {
    // std::cout << "anyCast(Any&& any)" << std::endl;
    if(!any.hasValue() || any.getType() != typeid(T)){
      throw std::bad_cast();
    }
    return std::move(static_cast<details::HelperGeneric<T>*>(any.content)->value);
  }

  /*
   * Return a pointer to the object, or nullptr if the object is empty or has not the right type
   */
  template<typename T>
  T* anyCast(Any* any) {
    // std::cout << "anyCast(Any* any)" << std::endl;
    if(!any->hasValue() || any->getType() != typeid(T)){
      return nullptr;
    }
    return &static_cast<details::HelperGeneric<T>*>(any->content)->value;
  }

  /*
   * Return a pointer to the object, or nullptr if the object is empty or has not the right type
   */
  template<typename T>
  const T* anyCast(const Any* any) {
    // std::cout << "anyCast(const Any* any)" << std::endl;
    if(!any->hasValue() || any->getType() != typeid(T)){
      return nullptr;
    }
    return &static_cast<details::HelperGeneric<T>*>(any->content)->value;
  }

}

#endif // VOC_ANY_H
