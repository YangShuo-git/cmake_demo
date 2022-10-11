/**
 * C++11新特性 
 * 1、可以使用 {}、()在定义变量时进行初始化;
 * 2、auto  自动类型推导是发生在编译期，所以并不会造成程序运行时效率的降低
 * 3、&  引用为变量起一个别名，修改引用，即修改原变量；可以理解为，引用与原变量占用的是同一块内存  
 *   定义引用类型时，必须要初始化，而且要以变量或对象初始化（不能是常量），而且类型要相同
 *   引用在=的左侧，取址符在=的右侧
 * 4、常量 
 *   
 * 
 */
#include <iostream>
using namespace std;

void funcRef(int &_a, int &_b)
{
    _a = 1;
    _b = 2; 
}

int main ()
{
    auto a {10};
    int b(20);
    int arrA[] {1,2,3};
    int arrB[] = {4,5,6};

    cout << a << " " << b << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << arrA[i] << endl;
    }

    int &refVal = a;
    int *p = &a;
    refVal = 100;
    cout << a << " " << *p << endl; 
    funcRef(a, b);
    cout << a << " " << b << endl;
    
    return 0;
}