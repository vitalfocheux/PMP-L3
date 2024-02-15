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

    /**
     * @brief Move constructor
     */
    Unique(Unique<T>&& other) noexcept : ptr(std::exchange(other.ptr, nullptr)){ }

    Unique<T>& operator=(const Unique<T>&) = delete;

    /**
     * @brief Move assignment operator
     */
    Unique<T>& operator=(Unique<T>&& other) noexcept{
      std::swap(ptr, other.ptr);
      return *this;
    }

    ~Unique(){
      if(exists()){
        delete ptr;
        ptr = nullptr;
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
      if(exists()){
        delete ptr;
        ptr = nullptr;
      }
    }

  private:
    T* ptr = nullptr;
  };

  /**
   * @brief Create a unique pointer
   */
  template<typename T, typename ... Args>
  Unique<T> makeUnique(Args&&... args) {
    return Unique<T>(new T(std::forward<Args>(args)...));
  }
}

#endif // SP_UNIQUE_H
