#include <iostream>

class A {
public:
    A(){
        std::cout<< "default constructor" << std::endl;
    }

    A(const A& other){
        std::cout<< "copy constructor" << std::endl;
    }

    A& operator=(const A& other)= default;

    A(A &&other) noexcept {
        std::cout<< "move constructor" << std::endl;
    }

    A& operator=(A &&other) = default;

    ~A(){
        std::cout<< "destructor" << std::endl;
    }

private:
    int a{};
    int b{};
};

A func1(){
    return A();
}

int main() {
    auto a =func1();
    return 0;
}
