//
// Created by wtsclwq on 2023/7/24.
//

#include <iostream>

class A{

};


void func(const A& a){
    std::cout << "xxxx" << std::endl;
}

void func(A &&a){
    std::cout << "yyyy" << std::endl;
}

A&& mock_move(A &a){
    return reinterpret_cast<A&>(a);
}

int main(){
    A a{};
    func(a);
    func(mock_move(a));
}