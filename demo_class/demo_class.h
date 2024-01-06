/**
 * 1、operator是C++的关键字，它和运算符一起使用，表示一个运算符函数，理解时应将operator=整体上视为一个函数名。
 * 2、赋值构造函数
 *    首先是要有 “=”；然后等号两边都是已初始化的实例。
 * 3、构造函数不能是虚函数，基类析构函数必须是虚函数
 * 
 * 
 * 
 * 
 * 
 */

#include <iostream>
#include <memory.h>

using std::cout;

class DemoClass
{
public:
    DemoClass();
    DemoClass(int _a);
    DemoClass(const DemoClass &_instance);
    DemoClass& operator=(DemoClass &_instance);
    ~DemoClass();

private:
    int m_a;
    int *m_data;
};


class Test
{
public:
    Test(/* args */);
    ~Test();

    void func1(){
        int a;
    };

private:
    int a;
};

Test::Test(/* args */)
{
}

Test::~Test()
{
}

