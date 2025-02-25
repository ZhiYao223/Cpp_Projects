#include <iostream>
#include <functional>

void f(int i){
    std::cout << "f is called, i = "<< i << ".\n";    
}

int main()
{
    //回调基本函数
    std::function<void(int)> callback = std::bind(f,std::placeholders::_1);

    callback(2);
    return 0;
}