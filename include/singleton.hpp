#ifndef SINGLETON_HPP
#define SINGLETON_HPP

namespace Singleton{
    template <typename T>
    class Singleton {
    protected:
        Singleton() = default;
        ~Singleton() = default;
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

    public:
        static T& getInstance() {
            static T instance; // T 타입 객체를 함수 내부 static으로 생성 → Lazy Initialization
            return instance;
        }
    };
}

#endif // SINGLETON_HPP