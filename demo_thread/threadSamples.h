#include <iostream>
#include <mutex>
#include <string>
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
// 通过保险箱来管理资源，避免不同互斥锁对象之间的资源竞争和错误访问
template <typename T>
class MutexSafe
{
private:
    mutex _mutex;
    T* _resource;
    T* operator ->(){}
    T& operator &(){}
public:
    MutexSafe(T* resource):_resource(resource){}
    ~MutexSafe(){delete _resource;}

    void lock(){
        _mutex.lock();
    }
    void unlock(){
        _mutex.unlock();
    }
    bool try_lock(){
        return _mutex.try_lock();
    }
    mutex& Mutex(){
        return _mutex;
    }
    
    // 要求传入的 lock 参数是 safe 对象本身, 能避免任意锁都可以访问资源的问题
    // 强迫传入lock，不然会有version2的问题
    // 通过传入特定类型的unique_lock对象，可以确保只有持有正确互斥锁的对象才能访问资源
    // 避免不同互斥锁对象之间的资源竞争和错误访问
    T& Acquire(unique_lock<MutexSafe<T>>& lock)
    {
        MutexSafe<T> *_safe = lock.mutex();
        if(&_safe->Mutex()!=&_mutex)
        {
            throw "wrong lock object passed to Acquire function.\n";
        }
        return *_resource;
    }
    T& Acquire(unique_lock<mutex>& lock)
    {
        if(lock.mutex()!=&_mutex)
        {
            throw "wrong lock object passed to Acquire function.\n";
        }
        return *_resource;
    }
};

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
