#include <iostream>
#include <string>
#include <thread>
#include <condition_variable>
#include "mutexSafe.h"
using namespace std;

struct StockBlackboard
{
    float price;
    const string name;

    StockBlackboard(const string stockName, float stockPrice=0):name(stockName),price(stockPrice){}
};

typedef MutexSafe<StockBlackboard> StockSafe;
void PeterUpdateStock_Notify (StockSafe& safe, condition_variable& condition)
{
    for (int i=0;i<5;i++)
    {
        {
            unique_lock<StockSafe> lock(safe);   // 理解为上保险箱，普通的锁可理解为上锁
            StockBlackboard& stock= safe.Acquire(lock);
            if(i==2)
                stock.price=99;
            else
                stock.price = abs(rand()% 100);
            cout<<"Peter udpated the price to $"<<stock.price<<endl;
            if(stock.price>90)
            {
                lock.unlock(); // unlock的原因：通知Danny线程时，需要解锁，这样Danny线程才有机会获得并上锁
                cout<<"Peter notified Danny at price $"<<stock.price<<", ";
                condition.notify_one();
                // sleep的原因：当生产者通知消费者后，可能需要一些时间来确保消费者线程已经进入阻塞状态并准备好接收数据
                this_thread::sleep_for(std::chrono::milliseconds(10));
                lock.lock();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(rand()%10));
    }
}
void DannyWait_ReadStock(StockSafe & safe, condition_variable& priceCondition)
{
    cout<<"Danny is waiting for the right price to sell..."<<endl;
    unique_lock<mutex> lock(safe.Mutex());
    priceCondition.wait(lock); // 先解锁，然后sleep，被唤醒后立即上锁

    StockBlackboard& stock= safe.Acquire(lock);
    if(stock.price>90)
        cout<<"Danny sell at: $"<<stock.price<<endl;
    else
        {
            cout<<"False alarm at $"<<stock.price<<" wait again..."<<endl;
            priceCondition.wait(lock);
            StockBlackboard& stock= safe.Acquire(lock);
            if(stock.price>90)
            cout<<"Danny sell at: $"<<stock.price<<endl;
        }
}

void TestConditionVariable()
{
    StockSafe safe (new StockBlackboard("APPL",30));
    condition_variable priceCondition;

    thread DannyThread(DannyWait_ReadStock, std::ref(safe), std::ref(priceCondition));
    thread PeterThread(PeterUpdateStock_Notify, std::ref(safe), std::ref(priceCondition));
    PeterThread.join();
    DannyThread.join();
}

