#include <stdio.h>
#include <demo_thread.h>

int main()
{
    printf("main function!\n");
#if 0
    std::thread t2(helloTen);
    std::thread t1(helloFive);
    t1.join();
    t2.join();

    std::thread t3([](){
        printf("t3 function!\n");
        std::this_thread::sleep_for(std::chrono::seconds(10));
    });
#endif
    CTimer timerTest;
    timerTest.start();
    timerTest.join();

    return 0;
}