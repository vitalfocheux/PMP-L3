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
    Weak(const Shared<T>& shared) {
      ptr = shared.get();
      *refCount = shared.count();
    }

    Weak(const Weak<T>&  other){

    }

    Weak(Weak<T>&& other) noexcept{

    }

    Weak<T>& operator=(const Weak<T>& other){
      return *this;
    }

    Weak<T>& operator=(Weak<T>&& other) noexcept{
      return *this;
    }

    ~Weak(){
      
    }

    /**
     * @brief Get a Shared pointer from the Weak pointer
     *
     * If the raw pointer still exists, the method
     * initialize a Shared object. Otherwise, the method
     * retrun a non existing Shared pointeur.
     */
    Shared<T> lock() {
      if(ptr != nullptr){
        return Shared<T>();
      }
      return Shared<T>(ptr);
    }

  private:
    T* ptr;
    std::size_t* refCount;
    std::size_t* weakCount;
  };
}

#endif // SP_WEAK_H
