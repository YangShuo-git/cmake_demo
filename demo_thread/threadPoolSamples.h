#ifndef _THREADPOOLSAMPLES_H_
#define _THREADPOOLSAMPLES_H_

#include <string>
#include <thread>
#include <vector>
#include <iostream>
#include <msgQueue.h>
#include <mutexSafe.h>
using namespace std;

struct CustomerTask
{
    string task;
    float money;
    CustomerTask(){}
    CustomerTask(const CustomerTask& cp):task(cp.task),money(cp.money){}
    void ExecuteTask()
    {
        if(money>0)
            cout<<"Task "<<task<<" is executed at $"<<money<<endl;
        else
            cout<<"Bank closed because the price is $"<<money<<endl;
    }
};

typedef MsgQueue<CustomerTask> TaskQueueType;
typedef MutexSafe<TaskQueueType> TaskQueueSafe;
class ThreadPool
{
private:
    int _limit;
    vector<thread*> _workerThreads;
    TaskQueueType& _taskQueue;
    bool _threadPoolStop=false;
public:
  
    void ExecuteTask()
    {
        while(1)
        {
            CustomerTask task=_taskQueue.Dequeue();
            task.ExecuteTask();
            if(task.money<0)
            {
                _threadPoolStop=true;
                _taskQueue.Enqueue(task);//tell other threads to stop
            }
            if(_threadPoolStop)
            {
                cout<< "thread finshed!"<<endl;
                return;
            }
            //the sleep function simulates that the task takes a while to finish 
            std::this_thread::sleep_for(std::chrono::milliseconds(rand()%100));
        }
    }

    ThreadPool(TaskQueueType& taskQueue,int limit=3):_limit(limit),_taskQueue(taskQueue){
        for(int i=0;i<_limit;++i)
        {
            _workerThreads.push_back(new thread(&ThreadPool::ExecuteTask,this));
        }
    }
    ~ThreadPool(){
        for(auto threadObj: _workerThreads)
        {
            if(threadObj->joinable())
                {
                    threadObj->join();
                    delete threadObj;
                }
        }
    }
};

void TestLeaderFollower()
{
    TaskQueueType taskQueue(5);
    ThreadPool pool(taskQueue,3);
    //the sleep function simulates the situation that all  
    //worker threads are waiting for the empty message queue at the beginning
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    for(int i=0;i<10;i++)
    {
        CustomerTask task;
        task.money= i+1;
        if(task.money >5)
            task.task = "deposit $";
        else
            task.task = "withdraw $";    
        taskQueue.Enqueue(task);
    }
    CustomerTask bankClosedTask;
    bankClosedTask.task="Bank Closed!";
    bankClosedTask.money=-1;
    taskQueue.Enqueue(bankClosedTask);
}




#endif // _THREADPOOLSAMPLES_H_