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
            static T instance; // T Ÿ�� ��ü�� �Լ� ���� static���� ���� �� Lazy Initialization
            return instance;
        }
    };
}

#endif // SINGLETON_HPP