#include <iostream>

// 运行时多态（动态多态）：基类 Animal
class Animal {
public:
    virtual void speak() const {
        std::cout << "Animal makes a sound" << std::endl;
    }
};

class Dog : public Animal {
public:
    void speak() const override {
        std::cout << "Dog barks" << std::endl;
    }
};

// 编译时多态（静态多态）：函数重载
int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

// 模板多态
template <typename T>
T multiply(T a, T b) {
    return a * b;
}

int main() {
    // 运行时多态
    Animal* animal = new Animal;
    Animal* dog = new Dog;
    animal->speak(); // 输出：Animal makes a sound
    dog->speak();    // 输出：Dog barks

    // 编译时多态
    int sum1 = add(1, 2);
    double sum2 = add(1.5, 2.5);
    std::cout << "Sum1: " << sum1 << std::endl; // 输出：Sum1: 3
    std::cout << "Sum2: " << sum2 << std::endl; // 输出：Sum2: 4.0

    // 模板多态
    int result1 = multiply(3, 4);
    double result2 = multiply(1.5, 2.0);
//    std::string result3 = multiply("1.5", "2.0");

    std::cout << "Result1: " << result1 << std::endl; // 输出：Result1: 12
    std::cout << "Result2: " << result2 << std::endl; // 输出：Result2: 3.0

    return 0;
}
