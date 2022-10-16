/**
 * C++11新特性  本文件学习这些新特性的小知识点。智能指针、lambda表达式、右值引用、类、模板，这些分别新开一个目录。
 * 1、可以使用 {}、()在定义变量时进行初始化。
 * 2、auto  自动类型推导是发生在编译期，所以并不会造成程序运行时效率的降低。
 * 3、&  引用为变量起一个别名，修改引用，即修改原变量；可以理解为，引用与原变量占用的是同一块内存；  
 *    定义引用类型时，必须要初始化，而且要以变量或对象初始化（不能是常量），而且类型要相同；
 *    引用在=的左侧，取址符在=的右侧。
 * 4、constexpr  常量  是在编译时求值，能够提升运行时的性能；
 *    编译阶段就知道值，也会带来其他好处，比如更利于做一些系统优化工作等。
 * 5、范围for循环
 *    一个容器只要其内部支持begin和end成员函数用于返回一个迭代器，能够指向容器的第一个元素和末端元素的后面；
 *    这种容器就支持范围for语句。
 * 6、new/delete   与malloc/free的区别；
 *    new 类型标识符
 *    new 类型标识符(初始值)
 *    new 类型标识符[内存单元个数]；开辟一个数组
 *    new不但分配内存，还会做一些初始化工作；delete不但释放内存，还会做一些清理工作。
 * 7、nullptr  对于指针的初始化，能用nullptr就用nullptr;
 *    NULL nullptr两者的类型是不同的。
 * 8、类和结构体的区别主要有两点：访问级别，继承权限。class都是private，struct都是public。
 * 9、
 *   
 * 
 */



#include <iostream>
#include <string.h>
using namespace std;

void funRef(int &_a, int &_b)
{
    _a = 1;
    _b = 2; 
}

struct Student
{
    char name[95];
    int number;
};

void createOneStu(Student *stu)
{
    stu->number = 33017;
    strcpy(stu->name, "baiyang");
}

int main ()
{
    //1
    auto a {10};
    int b(20);
    cout << a << " " << b << endl;

    int &refVal = a;
    int *p = &a;
    refVal = 100;
    cout << a << " " << *p << endl; 
    funRef(a, b);
    cout << a << " " << b << endl;

    //2
    int arrA[] {1,2,3};
    int arrB[] = {7,5,6};
    for (auto &i : arrA)
    {
        cout << i << endl;   // 1 2 3 
        //cout << arrA[i] << endl; // 2 3 7  这两者的区别？
    }

    //3-1
    char *point = nullptr;
    point = (char *)malloc(sizeof(char)*100);
    cout << sizeof("hello world!") << endl;
    strcpy(point, "hello world!");
    cout << point << endl;
    free(point);

    //3-2
    int *myInt1 = new int;
    int *myInt2 = new int(11);
    int *myInt3 = new int[12];

    int *pInt3 = myInt3;
    *pInt3++ = 8;
    *pInt3++ = 9;
    // *pInt3 = 8;     //两组是等价的
    // *(++pInt3) = 9;
    cout << *myInt3 << " " << *(myInt3 + 1) << endl;
    cout << myInt3[0] << " " << myInt3[1] << endl;

    delete myInt1;
    delete myInt2;
    delete[] myInt3;  // myInt3是new出来的，而pInt3是在栈区，所以只delete myInt3即可

    //4
    cout << "sizeof(Student):" << sizeof(Student) << endl;
    Student stu;
    createOneStu(&stu);
    cout << stu.number << endl;
    cout << stu.name << endl;
    cout << "sizeof(stu):" << sizeof(stu) << endl;

    return 0;
}