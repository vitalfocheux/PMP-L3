#ifndef SP_SHARED_H
#define SP_SHARED_H

#include <cstddef>
#include <utility>
#include <map>

struct Counter {
  std::size_t sharedCount = 1;
  std::size_t weakCount = 0;
};

namespace sp {

  template<class T> class Weak;

  /**
   * @brief Smart shared pointer class
   */
  template<typename T>
  class Shared {
  public:
    /**
     * @brief Constructor takes a dynamic pointer
     */
    Shared(T* ptr = nullptr) : ptr(ptr){
      if(ptr != nullptr){
        counter = new Counter();
      }
    }

    /**
     * @brief Copy constructor
    */
    Shared(const Shared<T>& other) : ptr(other.ptr), counter(other.counter){
      if(ptr != nullptr){
        counter->sharedCount++;
      }
    }

    /**
     * @brief Copy constructor from a weak pointer
    */
    Shared(const Weak<T>& weak) : ptr(weak.ptr), counter(weak.counter) {
      if(counter != nullptr){
        counter->sharedCount++;
      }
    }

    /**
     * @brief Move constructor
     */
    Shared(Shared<T>&& other) noexcept : ptr(other.ptr), counter(other.counter){
      other.ptr = nullptr;
      other.counter = nullptr;
    }

    /**
     * @brief Copy assignment operator
     */
    Shared<T>& operator=(const Shared<T>& other){
      if(this != &other){
        if(ptr != nullptr){
          counter->sharedCount--;
          if(counter->sharedCount == 0){
            delete ptr;
            ptr = nullptr;
            delete counter;
            counter = nullptr;
          }
        }
        ptr = other.ptr;
        counter = other.counter;
        if(counter != nullptr){
          counter->sharedCount++;
        }
      }
      return *this;
    }

    /**
     * @brief Move assignment operator
     */
    Shared<T>& operator=(Shared<T>&& other) noexcept{
      std::swap(ptr, other.ptr);
      std::swap(counter, other.counter);
      return *this;
    }

    /**
     * @brief Destructor
     */
    ~Shared(){
      decrement_counter();
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
      if(ptr == nullptr){
        return 0;
      }
      return counter->sharedCount;
    }

    /**
     * @brief  Check if the raw pointer exists
     */
    bool exists() const {
      return ptr != nullptr;
    }

    /**
     * @brief Check if the raw pointer exists
     */
    operator bool() const {
      return exists();
    }

    /**
     * @brief Release pointer ownership
     */
    void reset() {
      decrement_counter();
      ptr = nullptr;
      counter = nullptr;
    }

  private:
    T* ptr = nullptr;
    Counter *counter = nullptr;

    template<typename U> friend class Weak;

    /**
     * @brief Decrement the shared counter
     */
    void decrement_counter(){
      if(ptr == nullptr){
        return;
      }
      
      counter->sharedCount--;
      if(counter->sharedCount <= 0){
        delete ptr;
        ptr = nullptr;
        if(counter->weakCount == 0){
          delete counter;
          counter = nullptr;
        }
      }
    }
  };

  /**
   * @brief Create a shared pointer
   */
  template<typename T, typename ... Args>
  Shared<T> makeShared(Args&&... args) {
    return Shared<T>(new T(std::forward<Args>(args)...));
  }
}

#endif // SP_SHARED_H
