##ifndef _MSGQUEUE_H_
#define _MSGQUEUE_H_

// 任何时候，只能有一个线程访问这个消息队列
// 队列满了，生产者被阻塞；队列空了，消费者被阻塞

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename MsgType>
class MsgQueue
{
private:
    queue<MsgType> _queue; 
    mutex _mutex;
    condition_variable _enqCv;
    condition_variable _deqCv;
    int _limit;

public:
    MsgQueue(int limit=3):_limit(limit){}

    void Enqueue(MsgType& msg)
    {
        unique_lock<mutex> lock(_mutex);
        if(_queue.size()>=_limit)
        {
            cout<<"queue is full, wait()..."<<endl;
            _enqCv.wait(lock, [this]{return _queue.size()<_limit;});
        }
        _queue.push(msg);
        _deqCv.notify_one();
    }
    MsgType Dequeue()
    {
        unique_lock<mutex> lock(_mutex);
        if(_queue.size()<=0)
        {
            cout<<"queue is empty, wait()..."<<endl;
            _deqCv.wait(lock, [this]{return _queue.size()>0;});
        }
        MsgType& msg = _queue.front();
        _queue.pop();
        _enqCv.notify_one();
        return msg;
    }
    
    int Size()
    {
        unique_lock<mutex> lock(_mutex);
        return _queue.size();
    }
};

#endif // _MSGQUEUE_H_