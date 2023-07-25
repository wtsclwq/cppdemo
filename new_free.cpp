#include <iostream>
#include <string>

class Person {
public:
    // 构造函数，用于初始化Person对象
    Person(std::string *name) : name_(name) {
        std::cout << "Constructing Person: " << *name << std::endl;
    }

    // 析构函数，用于释放资源
    ~Person() {
        if (name_) {
            std::cout << "Destructing Person: " << *name_ << std::endl;
            delete name_;
        }
    }

    // 打印个人信息
    void printInfo() const {
        if (name_) {
            std::cout << "Name: " << *name_ << std::endl;
        } else {
            std::cout << "Name: Unknown" << std::endl;
        }
    }

private:
    std::string* name_; // 动态分配的资源
};

int main() {
    std::string name = "Liwenqiang";
    Person* person1 = new Person(&name); // 使用new分配Person对象

    // 使用person1指针访问Person对象的成员函数
    person1->printInfo();

    // 错误的释放内存，应该使用delete而不是free
    free(person1); // 潜在的未定义行为
    std::cout << "after free: " << name << std::endl;

//    delete person1;
//    std::cout << "after delere: " << name << std::endl;
    return 0;
}
