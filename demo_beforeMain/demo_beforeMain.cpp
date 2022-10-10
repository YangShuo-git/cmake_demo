#include <stdio.h>
/*
  在main函数之前执行代码的几种情况
*/

// 全局对象的构造
class A{
public:
    A()
    {
        printf("构造函数:%s\n", __FUNCTION__);

    }
    ~A()
    {
        printf("析构函数:%s\n", __FUNCTION__);
    }
};
A a;

// 全局变量的初始化
int function()
{
    printf("function:%s\n", __FUNCTION__);
    return 1;
}

int ret = function();

// lambda
int target = []{
    printf("lambda: %s\n", __FUNCTION__);
    return 2;
}();


int main ()
{
    printf("main函数:%s\n", __FUNCTION__);
    printf("ret: %d\n", ret);
    printf("target: %d\n", target);

    return 0;
}