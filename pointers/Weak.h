#ifndef SP_WEAK_H
#define SP_WEAK_H

#include "Shared.h"

namespace sp {

  /**
   * @brief Smart weak pointer
   */
  template<typename T>
  class Weak {
  public:
    /**
     * @brief Default constructor
     */
    Weak() {
    }

    /**
     * @brief Constructor takes a Shared pointer
     */
    Weak(const Shared<T>& shared) : ptr(shared.ptr), counter(shared.counter) {
      if(counter != nullptr){
        counter->weakCount++;
      }
    }

    /**
     * @brief Copy constructor
     */
    Weak(const Weak<T>&  other) : ptr(other.ptr), counter(other.counter){
      if(counter != nullptr){
        counter->weakCount++;
      }
    }

    /**
     * @brief Move constructor
     */
    Weak(Weak<T>&& other) noexcept : ptr(other.ptr), counter(other.counter){
      other.ptr = nullptr;
      other.counter = nullptr;
    }

    /**
     * @brief Copy assignment operator
     */
    Weak<T>& operator=(const Weak<T>& other){
      if(this != &other){
        if(counter != nullptr){
          counter->weakCount--;
          if(counter->weakCount == 0 && counter->sharedCount == 0){
            delete counter;
            counter = nullptr;
          }
        }
        ptr = other.ptr;
        counter = other.counter;
        if(counter != nullptr){
          counter->weakCount++;
        }
      }
      return *this;
    }

    /**
     * @brief Move assignment operator
     */
    Weak<T>& operator=(Weak<T>&& other) noexcept{
      std::swap(ptr, other.ptr);
      std::swap(counter, other.counter);
      other.reset();
      return *this;
    }

    /**
     * @brief Destructor
     */
    ~Weak(){
      decrement_counter();
    }

    /**
     * @brief Get a Shared pointer from the Weak pointer
     *
     * If the raw pointer still exists, the method
     * initialize a Shared object. Otherwise, the method
     * retrun a non existing Shared pointeur.
     */
    Shared<T> lock() {
      // std::cout << (counter == nullptr) << " || " << (counter->sharedCount == 0) << std::endl;
      // if(counter != nullptr){
      //   std::cout << counter->sharedCount << " " << counter->weakCount << std::endl;
      // }
      if(counter == nullptr || counter->sharedCount == 0){
        return Shared<T>();
      }
      return Shared<T>(*this);
    }

    /**
     * @brief Clear the reference to the shared pointer
     */
    void reset() {
      decrement_counter();
      ptr = nullptr;
      counter = nullptr;
    }

  private:
    T* ptr = nullptr;
    Counter* counter = nullptr;

    template<typename U> friend class Shared;

    /**
     * @brief Decrement the weak counter
    */
    void decrement_counter(){
      if(counter == nullptr){
        return;
      }

      counter->weakCount--;
      if(counter->weakCount == 0 && counter->sharedCount == 0){
        delete counter;
        counter = nullptr;
      }
    }
  };
}

#endif // SP_WEAK_H
