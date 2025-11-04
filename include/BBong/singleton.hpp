#ifndef SINGLETON_HPP
#define SINGLETON_HPP

namespace BBong {
template <typename T> class Singleton {
protected:
  Singleton() = default;
  ~Singleton() = default;
  Singleton(const Singleton &) = delete;
  Singleton &operator=(const Singleton &) = delete;

public:
  static T &getInstance() {
    static T instance;
    return instance;
  }
};
}; // namespace BBong

#endif // SINGLETON_HPP