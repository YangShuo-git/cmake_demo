#include <stdio.h>
#include <thread>
#include <demo_thread.h>

int main()
{
    printf("main function!\n");
    std::thread t1(helloFive);
    std::thread t2(helloTen);

    t1.join();
    t2.join();
    return 0;
}