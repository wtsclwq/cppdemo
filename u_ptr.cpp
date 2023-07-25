#include <iostream>

template<typename T>
class UniquePtr{
public:
    // default constructor
    explicit UniquePtr(T *ptr = nullptr): raw_ptr_(ptr){}

    // mark copy constructor deleted
    UniquePtr(const UniquePtr &) = delete;

    UniquePtr(UniquePtr && other)  noexcept : raw_ptr_(other.release()){}

    ~UniquePtr(){
        delete raw_ptr_;
    }

    // assign operator using copy and swap
    auto operator=(UniquePtr other) -> UniquePtr &{
        other.swap(*this);
        return *this;
    }

//    template<typename U>
    template<typename U,
            std::enable_if_t<std::is_convertible_v<U*, T*>, int> = 0>
    UniquePtr(UniquePtr<U>&& other) noexcept: raw_ptr_(other.release()) {}

    void swap(UniquePtr &other){
        using std::swap;
        swap(other.raw_ptr_, raw_ptr_);
    }

    auto release() -> T*{
        auto res = raw_ptr_;
        raw_ptr_ = nullptr;
        return res;
    }

    void reset(T* ptr = nullptr){
        delete raw_ptr_;
        raw_ptr_ = ptr;
    }

    auto get() -> T*{
        return raw_ptr_;
    }

    auto operator->() -> T*{
        return raw_ptr_;
    }

    auto operator*() -> T{
        return *raw_ptr_;
    }

    explicit operator bool(){
        return raw_ptr_ != nullptr;
    }

private:
    T *raw_ptr_;
};

class MyClass {
public:
    MyClass(int val) : value(val) {}
    void print() const {
        std::cout << "Value: " << value << std::endl;
    }
private:
    int value;
};

class BaseClass {
public:
    virtual void print() const {
        std::cout << "BaseClass" << std::endl;
    }
};

class DerivedClass : public BaseClass {
public:
    void print() const override {
        std::cout << "DerivedClass" << std::endl;
    }
};

int main() {
    // Test basic usage with built-in types
    UniquePtr<int> intPtr(new int(42));
    std::cout << *intPtr << std::endl; // Output: 42

    // Test usage with custom class
    UniquePtr<MyClass> ptr(new MyClass(100));
    ptr->print(); // Output: Value: 100

    // Test resource ownership transfer
    UniquePtr<int> ptr1(new int(42));
    UniquePtr<int> ptr2(new int(111));

    ptr2 = std::move(ptr1);

    if (!ptr1) {
        std::cout << "ptr1 is null" << std::endl; // Output: ptr1 is null
    }

    if (ptr2) {
        std::cout << *ptr2 << std::endl; // Output: 42
    }

    // Test converting derived class pointer to base class pointer
    UniquePtr<DerivedClass> derivedPtr(new DerivedClass());
    UniquePtr<BaseClass> basePtr = std::move(derivedPtr);
    basePtr->print(); // Output: DerivedClass

    return 0;
}