#include "demo_class.h"


DemoClass::DemoClass()
{
}

DemoClass::~DemoClass()
{
    // delete m_data[];
}

DemoClass::DemoClass(int _a)
{
    m_a = _a;
    m_data = new int[10];
    cout << "构造函数" << "\n";
}
DemoClass::DemoClass(const DemoClass &_instance)
{
    m_a = _instance.m_a;
    m_data = new int[10];

    memcpy(m_data, _instance.m_data, sizeof(int)*10);
    cout << "拷贝构造函数" << "\n";
}
DemoClass& DemoClass::operator= (DemoClass &_instance)
{
    m_a = _instance.m_a;
    if (m_data) delete[] m_data;
    m_data = new int[10];
    memcpy(m_data, _instance.m_data, 10 * sizeof(int));
    cout << "赋值构造函数" << "\n";
    return *this;  //可以连等 
}

int main()
{
    DemoClass dc1(20);
    DemoClass dc2(dc1);
    DemoClass dc3 = dc1;
    dc2 = dc3;
}