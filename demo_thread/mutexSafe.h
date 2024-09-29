#ifndef _MUTEXSAFE_H_
#define _MUTEXSAFE_H_

#include <mutex>
using namespace std;

// 只有通过保险箱才能获取共享资源，避免不同互斥锁对象之间的资源竞争和错误访问
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


#endif // _MUTEXSAFE_H_