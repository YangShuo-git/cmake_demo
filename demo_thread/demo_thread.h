#ifndef _DEMO_THREAD_H_
#define _DEMO_THREAD_H_

#include <thread>
#include <iostream>


void helloTen();
void helloFive();

void testThreadFunc();

class CTimer
{
private:
    std::thread* timeThread = nullptr;
    std::thread* testThread = nullptr;

public:
    CTimer() {}
    virtual ~CTimer() {
        if (timeThread)
        {
            delete timeThread;
            std::cout << "delete timeThread" << std::endl;
        }
        if (testThread)
        {
            delete testThread;
            std::cout << "delete testThread" << std::endl;
        }
        
        std::cout << "~CTimer finished" << std::endl; 
    }

    void start() {
        // 类中成员函数起线程：传类成员函数、传类外函数
        std::cout << "thread start!" << std::endl; 
        timeThread = new std::thread(&CTimer::runThread, this); 
        testThread = new std::thread(testThreadFunc); 
    }

    void runThread() {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "3s time thread run!" << std::endl; 
    }

    void join() {
        if (timeThread->joinable())
        {
            std::cout << "time thread join!" << std::endl; 
            timeThread->join();
        }
        if (testThread->joinable())
        {
            std::cout << "test thread join!" << std::endl; 
            testThread->join();
        }
        
    }
};


#endif // _DEMO_THREAD_H_
