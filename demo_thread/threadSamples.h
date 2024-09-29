#include <iostream>
#include <string>
#include <thread>
#include "mutexSafe.h"
using namespace std;

/***************************version1 无锁********************************/
void DannyWrite(string &blackboard)
{
    blackboard =+ "My";
    this_thread::sleep_for(std::chrono::milliseconds(rand()%3));
    blackboard += " name";
    this_thread::sleep_for(std::chrono::milliseconds(rand()%3));
    blackboard +=" is";
    this_thread::sleep_for(std::chrono::milliseconds(rand()%3));
    blackboard += " Danny\n";
}
void PeterWrite(string& blackboard)
{
    blackboard +="My";
    this_thread::sleep_for(std::chrono::milliseconds(rand()%3));
    blackboard += " name";
    this_thread::sleep_for(std::chrono::milliseconds(rand()%3));
    blackboard +=" is";
    this_thread::sleep_for(std::chrono::milliseconds(rand()%3));
    blackboard += " Peter\n";
}
void DemoResouceConflict()
{
    string blackboard;
    thread DannyThread(DannyWrite, std::ref(blackboard));
    thread PeterThread(PeterWrite, std::ref(blackboard));
    DannyThread.join();
    PeterThread.join();
    cout<<blackboard<<endl;
}
/***************************version1********************************/


/***************************version2 智能锁********************************/
void PeterWriteWithMutex(mutex& amutex, string& blackboard )
{
    unique_lock<std::mutex> lk(amutex);
    PeterWrite(blackboard);
}
void DannywriteWithMutex(mutex& amutex, string& blackboard)
{
    unique_lock<std::mutex> lk(amutex);
    DannyWrite(blackboard);
}
void TestNomalSafeLock()
{
    string blackboard;
    std::mutex amutex;
    thread DannyThread(DannywriteWithMutex, std::ref(amutex), std::ref(blackboard));
    thread PeterThread(PeterWriteWithMutex, std::ref(amutex), std::ref(blackboard));
    DannyThread.join();
    PeterThread.join();
    cout<<blackboard<<endl;
}
/***************************version2********************************/


/***************************version3 保险箱********************************/
typedef MutexSafe<string>  Safe;
void SafeDannyWrite(Safe& safe)
{
    unique_lock<Safe> lock(safe);
    string& blackboard = safe.Acquire(lock);
    DannyWrite(blackboard);
}
void SafePeterWrite(Safe& safe)
{
    unique_lock<Safe> lock(safe);
    string& blackboard = safe.Acquire(lock);
    PeterWrite(blackboard);
}
void TestSafeSmartlock()
{
    Safe safe(new string());

    thread DannyThread(SafeDannyWrite, ref(safe));
    thread PeterThread(SafePeterWrite, ref(safe));
    DannyThread.join();
    PeterThread.join();

    unique_lock<Safe> lock(safe);
    string& blackboard = safe.Acquire(lock);
    cout<<blackboard<<endl;
}
/***************************version3********************************/
