/**
 * C++11新特性 
 * 1、可以使用 {}、()在定义变量时进行初始化。
 * 2、auto  自动类型推导是发生在编译期，所以并不会造成程序运行时效率的降低。
 * 3、&  引用为变量起一个别名，修改引用，即修改原变量；可以理解为，引用与原变量占用的是同一块内存；  
 *    定义引用类型时，必须要初始化，而且要以变量或对象初始化（不能是常量），而且类型要相同；
 *    引用在=的左侧，取址符在=的右侧。
 * 4、常量 constexpr 是在编译时求值，能够提升运行时的性能；
 *    编译阶段就知道值，也会带来其他好处，比如更利于做一些系统优化工作等。
 * 5、for循环 范围for语句
 *    一个容器只要其内部支持begin和end成员函数用于返回一个迭代器，能够指向容器的第一个元素和末端元素的后面；
 *    这种容器就支持范围for语句。
 * 6、new/delete   与malloc/free的区别
 *   
 * 
 */

#include <iostream>
#include <string.h>
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
    cout << a << " " << b << endl;

    int &refVal = a;
    int *p = &a;
    refVal = 100;
    cout << a << " " << *p << endl; 
    funcRef(a, b);
    cout << a << " " << b << endl;

    int arrA[] {1,2,3};
    int arrB[] = {11,5,6};
    for (auto &i : arrA)
    {
        cout << i << endl;
    }

    char *point = nullptr;
    point = (char *)malloc(sizeof(char)*100);
    cout << sizeof("hello world!") << endl;
    strcpy(point, "hello world!");
    cout << point << endl;
    free(point);

    int *pInt = (int*)malloc(sizeof(int)*100);
    int *pNew = pInt;
    *pNew++ = 1;
    *pNew++ = 5;
    // *pNew = 5;
    // *(++pNew) = 1;
    cout << *pInt << " " << *(pInt+1) << " "<< *(pInt + 2) << endl;

    return 0;
}