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
      // ptr = nullptr;
      // refCount = nullptr;
      // weakCount = nullptr;
    }

    /**
     * @brief Constructor takes a Shared pointer
     */
    Weak(const Shared<T>& shared) : ptr(shared.ptr), counter(shared.counter) {
      if(counter != nullptr){
        counter->weakCount++;
      }
    }

    Weak(const Weak<T>&  other) : ptr(other.ptr), counter(other.counter){
      if(counter != nullptr){
        counter->weakCount++;
      }
    }

    Weak(Weak<T>&& other) noexcept : ptr(other.ptr), counter(other.counter){
      other.ptr = nullptr;
      other.counter = nullptr;
    }

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
        counter->weakCount++;
      }
      return *this;
    }

    Weak<T>& operator=(Weak<T>&& other) noexcept{
      std::swap(ptr, other.ptr);
      std::swap(counter, other.counter);
      return *this;
    }

    ~Weak(){
      if(counter == nullptr){
        return;
      }

      counter->weakCount--;
      if(counter->weakCount == 0 && counter->sharedCount == 0){
        delete counter;
        counter = nullptr;
      }
    }

    /**
     * @brief Get a Shared pointer from the Weak pointer
     *
     * If the raw pointer still exists, the method
     * initialize a Shared object. Otherwise, the method
     * retrun a non existing Shared pointeur.
     */
    Shared<T> lock() {
      std::cout << (counter == nullptr) << " || " << (counter->sharedCount == 0) << std::endl;
      if(counter != nullptr){
        std::cout << counter->sharedCount << " " << counter->weakCount << std::endl;
      }
      if(counter == nullptr || counter->sharedCount == 0){
        return Shared<T>();
      }
      return Shared<T>(*this);
    }

    /**
     * @brief Clear the reference to the shared pointer
     */
    void reset() {
    }

  private:
    T* ptr = nullptr;
    Counter* counter = nullptr;

    template<typename U> friend class Shared;
  };
}

#endif // SP_WEAK_H
