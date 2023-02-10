/**
 * 1、unique_ptr，独占式指针，和裸指针一样大;
 * 2、shared_ptr，共享式指针，是裸指针的2倍；
 * 3、weak_ptr，辅助shared_ptr，是裸指针的2倍;
 * 4、本质是类模板
 * 5、优先考虑unique_ptr，如果unique_ptr不能满足需求，再考虑shared_ptr
 * 6、优先使用make_shared构造智能指针，编译器内部会有一些针对内存分配的特殊处理
 *    使用make_shared效率更高，如消除重复代码、改进安全性
 * 7、当一个shared_ptr引用计数为0，它会自动释放自己所管理的对象
 * 8、自定义删除器
 * 
 */

#include <iostream>
#include <memory>

using namespace std;

// 裸指针导致的内存泄漏
void funcRaw()
{
    string *ptr = new string("hello world!");
    if (true)   
    {
        // 当某个条件为真，就return，忘记释放内存导致泄漏
        return;
    }
    delete ptr;
    return;
}

// 智能指针解决内存泄漏的问题
void funcSmart()
{
    shared_ptr<string> ptr = make_shared<string>("hello world!");
    if (true)
    {
        return;
    }
    return;
}

class A
{
public:
    void show()
    {
        cout <<"A show() is called"<< endl;
    }
};

shared_ptr<int> createSp(int value)
{
    return make_shared<int>(value);
}

shared_ptr<int> testSp(int value)
{
    shared_ptr<int> tmpSp = createSp(value);
    return tmpSp;
}

int main ()
{
    // 1. 常规初始化
    shared_ptr<A> p1(new A);
    p1->show();
    shared_ptr<A> p2(p1); // 智能指针的复制，p1和p2指向相同的对象，此对象目前有两个引用者
    p2->show();
    cout << p1.get() << ' ' << p2.get() << endl;

    // Returns the number of shared_ptr objects referring to the same managed object.
    cout << p1.use_count() << ' ' << p2.use_count() <<  endl;

    // Relinquishes ownership of p1 on the object and pointer becomes NULL
    p1.reset();
    cout << p1.get() << endl;
    cout << p2.use_count() << ' ' << p2.get() <<  endl;

    // 2.make_shared函数
    shared_ptr<int> p3 = make_shared<int>(100); //p3指向一个值为100的整型的内存
    shared_ptr<string> p4 = make_shared<string>(5, 'a'); 
    cout << *p3 << ' ' << *p4 << endl;

    // 3.使用场景
    auto p5 = testSp(101);
    cout << *p5 << endl;

    return 0;
}