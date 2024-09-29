#include <stdio.h>
#include <demo_thread.h>
#include "conditionVariableSample.h"

int main()
{
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

#if 0
    CTimer timerTest;
    timerTest.start();
    timerTest.join();
#endif

    // DemoResouceConflict();
    // TestNomalSafeLock();
    // TestSafeSmartlock();

    TestConditionVariable();

    return 0;
}