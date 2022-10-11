/**
 * C++11新特性 
 * 1、可以使用 {}、()在定义变量时进行初始化;
 * 2、auto的自动类型推导是发生在编译器，所以并不会造成程序运行时效率的降低
 * 
 * 
 */
#include <iostream>
using namespace std;

int main ()
{
    auto a {10};
    int b(20);
    int arrA[] {1,2,3};
    int arrB[] = {4,5,6};

    cout << a << " " << b <<  endl;
    for (int i = 0; i < 3; i++)
    {
        cout << arrA[i] << endl;
    }
    
    return 0;
}