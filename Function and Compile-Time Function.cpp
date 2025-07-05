#include <iostream>
#include <functional>
#include <string>
#include <memory>
#include <exception>


// not compile-time version
struct OwnException : public std::runtime_error {
    OwnException(std::string msg) : std::runtime_error(msg) {}
};

template<typename T>
struct function1;

template<typename T, typename... Args>
class function1<T(Args...)> {
public:

    constexpr function1() : smartPtr(nullptr) {}
    constexpr function1(T(*ptr1)(Args...))
    {
        smartPtr = std::make_unique<T(*)(Args...)>(ptr1); 
    }
    ~function1() = default;

    constexpr function1(const function1& otherptr) noexcept
    {
        if (otherptr.smartPtr == nullptr) 
            smartPtr = nullptr;
        else
            smartPtr = std::make_unique<T(*)(Args...)>(*otherptr.smartPtr);
    }
    constexpr function1& operator =(const function1& otherptr) noexcept {
        if (this == &otherptr)
            return *this;
        if (otherptr.smartPtr == nullptr)
            smartPtr = nullptr;

        smartPtr = std::make_unique<T(*)(Args...)>(*otherptr.smartPtr);
        return *this;
    }

    constexpr function1(function1&& otherptr) noexcept {
        smartPtr = std::move(std::make_unique<T(*)(Args...)>(*otherptr.smartPtr));
        otherptr.smartPtr = nullptr;
    }
    constexpr function1& operator =(function1&& otherptr) noexcept {
        if (this == &otherptr)
            return *this;

        smartPtr = std::move(std::make_unique<T(*)(Args...)>(*otherptr.smartPtr));
        otherptr.smartPtr = nullptr;
        return *this;
    }

    constexpr decltype(auto) operator()(Args... args) const {
        if (smartPtr == nullptr) {
            throw OwnException("Your function is NULL!");
        }
        if (smartPtr != nullptr) {
            return (*smartPtr.get())(args...);
        }
        return T();
    }
    
private:
    std::unique_ptr<T(*)(Args...)> smartPtr;

};

// compile time version
template<typename T>
struct functionCompileTime;

template<typename T, typename... Args>
class functionCompileTime<T(Args...)> {
public:

    consteval functionCompileTime() : ptr(nullptr) {}
    consteval functionCompileTime(T(*ptr1)(Args...))
        : ptr(ptr1)
    {
    }
    ~functionCompileTime() = default;

    consteval functionCompileTime(const functionCompileTime& otherptr) noexcept
    {
        if (otherptr.ptr == nullptr)
            ptr = nullptr;
        else
            ptr = *otherptr.ptr;
    }
    consteval functionCompileTime& operator =(const functionCompileTime& otherptr) noexcept {
        if (this == &otherptr)
            return *this;
        if (otherptr.ptr == nullptr)
            ptr = nullptr;

        ptr = *otherptr.ptr;
        return *this;
    }

    consteval functionCompileTime(functionCompileTime&& otherptr) noexcept {
        ptr = std::move(*otherptr.ptr);
        otherptr.ptr = nullptr;
    }
    consteval functionCompileTime& operator =(functionCompileTime&& otherptr) noexcept {
        if (this == &otherptr)
            return *this;

        ptr = std::move(*otherptr.ptr);
        otherptr.ptr = nullptr;
        return *this;
    }

    constexpr decltype(auto) operator()(const Args... args) const {
        if (ptr == nullptr)
            return T();
        if (ptr != nullptr) {
            T i = [&](T(*)(Args... args)) -> T {
                return ptr(args...);
                }(ptr);
            return i;
        }
        return T();
    }

private:
    T(*ptr)(Args...);
};

static constexpr int foo2(const int e, const int e2) {
    return e - e2;
}

int main()
{

    constexpr functionCompileTime<int(int, int)> f2 = foo2;
    constexpr functionCompileTime<int(int, int)> f = f2;
    constexpr int i = f(1, 2);
}
