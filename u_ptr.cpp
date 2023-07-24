#include <iostream>
#include <utility>

template <typename T>
class UniquePtr{
public:
    explicit UniquePtr(T *ptr = nullptr): raw_ptr_(ptr){}

    UniquePtr(UniquePtr &&other) noexcept : raw_ptr_(other.release()){}

    auto operator=(UniquePtr other) noexcept -> UniquePtr&{
        other.swap(*this);
        return *this;
    }

    template<typename U>
    UniquePtr(UniquePtr<U> &&other) noexcept: raw_ptr_(other.release()){}

    auto operator->() -> T*{
        return raw_ptr_;
    }

    auto operator*() -> T{
        return *raw_ptr_;
    }

    explicit operator bool()  {
        return raw_ptr_ != nullptr;
    }

    auto release() -> T*{
        auto res = raw_ptr_;
        raw_ptr_ = nullptr;
        return res;
    }

    void swap(UniquePtr &other){
        std::swap(other.raw_ptr_,raw_ptr_);
    }
private:
    T *raw_ptr_;
};

// Example usage:
class Base {
public:
    virtual void foo() const {
        std::cout << "Base::foo()" << std::endl;
    }
};

class Derived : public Base {
public:
    void foo() const override {
        std::cout << "Derive111::foo()" << std::endl;
    }
};

class Derived2 :public  Base{
public:
    void foo() const override{
        std::cout << "Derived222::foo()" << std::endl;
    }
};

int main() {
    UniquePtr<Base> basePtr;
    UniquePtr<Derived> derived(new Derived);
    basePtr = std::move(derived);
    basePtr->foo(); // Output: Derived::foo()

    UniquePtr<Base> anotherBasePtr;
    anotherBasePtr = std::move(basePtr);
    anotherBasePtr->foo(); // Output: Derived::foo()

    return 0;
}
