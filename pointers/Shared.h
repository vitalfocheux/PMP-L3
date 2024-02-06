#ifndef SP_SHARED_H
#define SP_SHARED_H

#include <cstddef>
#include <utility>
#include <map>

namespace sp {

  /**
   * @brief Smart shared pointer class
   */
  template<typename T>
  class Shared {
  public:
    /**
     * @brief Constructor takes a dynamic pointer
     */
    Shared(T* ptr = nullptr) : ptr(ptr), refCount(new std::size_t(1)){
    }

    Shared(const Shared<T>& other) : ptr(other.ptr), refCount(other.refCount){
      // if(ptr != nullptr){
      //   (*refCount)++;
      // }
      (*refCount)++;
    }

    Shared(Shared<T>&& other) noexcept : ptr(std::exchange(other.ptr, nullptr)), refCount(std::exchange(other.refCount, refCount)){
    }

    Shared<T>& operator=(const Shared<T>& other){
      if(this != &other){
        ptr = other.ptr;
        refCount = other.refCount;
        (*refCount)++;
      }
      return *this;
    }

    Shared<T>& operator=(Shared<T>&& other) noexcept{
      std::swap(ptr, other.ptr);
      std::swap(refCount, other.refCount);
      std::cout << "Shared move assignment " << *other.refCount << std::endl;
      return *this;
    }

    ~Shared(){
      std::cout << "Shared destructor " << *refCount << std::endl;
      --(*refCount);
      if(*refCount == 0){
        delete ptr;
        delete refCount;
      }
    }

    /**
     * @brief Get the raw pointer
     */
    T* get() {
      return ptr;
    }

    /**
     * @brief Get a reference on pointed data
     */
    T& operator*() {
      return *ptr;
    }

    /**
     * @brief Get the raw pointer
     */
    T* operator->() {
      return ptr;
    }

    /**
     * @brief Get the number of Shared pointed on the current pointer
     */
    std::size_t count() const {
      return *refCount;
    }

    /**
     * @brief  Check if the raw pointer exists
     */
    bool exists() const {
      return *refCount > 0;
    }

  private:
    T* ptr;
    std::size_t *refCount;
  };
}

#endif // SP_SHARED_H
