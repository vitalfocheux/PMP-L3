#ifndef SP_UNIQUE_H
#define SP_UNIQUE_H

namespace sp {

  /**
   * @brief Smart unique pointer
   */
  template<typename T>
  class Unique {
  public:
    /**
     * @brief Constructor takes a dynamic pointer
     */
    Unique(T* ptr = nullptr) : ptr(ptr){
    }

    Unique(const Unique<T>&) = delete;
    Unique(Unique<T>&& other) noexcept : ptr(std::exchange(other.ptr, nullptr)){ }

    Unique<T>& operator=(const Unique<T>&) = delete;
    Unique<T>& operator=(Unique<T>&& other) noexcept{
      std::swap(ptr, other.ptr);
      return *this;
    }

    ~Unique(){
      if(exists()){
        delete ptr;
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
     * @brief Check if the raw pointer exists
     */
    bool exists() const {
      return ptr != nullptr;
    }

  private:
    T* ptr;
  };
}

#endif // SP_UNIQUE_H
