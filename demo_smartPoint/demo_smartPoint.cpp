/**
 * 1、unique_ptr，独占式指针;
 * 2、shared_ptr，共享式指针；
 * 3、weak_ptr，辅助shared_ptr;
 * 4、本质是类模板
 * 
 */

#include <iostream>
#include <memory>

using namespace std;

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
    shared_ptr<int> tmpSp = createSp(10);
    return tmpSp;
}

int main ()
{
    // 1. 常规初始化
    shared_ptr<A> p1(new A);
    cout << p1.get() << endl;
    p1->show();
    shared_ptr<A> p2(p1); // 智能指针的复制，p1和p2指向相同的对象，此对象目前有两个引用者
    p2->show();
    cout << p1.get() << ' ' << p2.get() << endl;

    // Returns the number of shared_ptr objects
    // referring to the same managed object.
    cout << p1.use_count() << ' ' << p2.use_count() <<  endl;

    // Relinquishes ownership of p1 on the object and pointer becomes NULL
    p1.reset();
    cout << p1.get() << endl;
    cout << p2.use_count() << ' ' << p2.get() <<  endl;

    // 2.make_shared函数
    shared_ptr<int> p3 = make_shared<int>(100); //p3指向一个值为100的整型的内存
    auto p4 = make_shared<string>(5, 'a'); 
    cout << *p3 << ' ' << *p4 << endl;

    // 3.使用场景
    auto p5 = testSp(101);
    cout << *p5 << endl;

    return 0;
}