/*
 * @file   34.windows临界区_其他各种mutex互斥量.cpp
 * @date   2019.3.23.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0. windows临界区

#include<windows.h>
#define  _WINDOWSJQ_
class A
{
public:
	void inMsgRecvQueue()
	{
		for (int i = 0; i < 10; i++)
		{
#ifdef _WINDOWSJQ_
			EnterCriticalSection(&my_winsec);
			msgRecvQueue.push_back(i);
			LeaveCriticalSection(&my_winsec);
#else
			my_mutex.lock();
			msgRecvQueue.push_back(i);
			my_mutex.unlock();

#endif
			
		}
	}

	bool outMsgLULProc(int &command)
	{
#ifdef _WINDOWSJQ_
		EnterCriticalSection(&my_winsec);
		if(!msgRecvQueue.empty())
		{
			int command = msgRecvQueue.front();
			msgRecvQueue.pop_front();
			LeaveCriticalSection(&my_winsec);
			return true;
		}

#else // _WINDOWSJQ_

		my_mutex.lock();
		if (!msgRecvQueue.empty())
		{
			int command = msgRecvQueue.front();
			msgRecvQueue.pop_front();
			my_mutex.unlock();
			return true;
		}
#endif
		return false;

	}

	void outMsgRecvQueue()
	{
		int command = 0;
		for (int i = 0; i < 1000; i++)
		{
			bool result = outMsgLULProc(command);
			if (result == true)
			{}
			else
			{}
		}
	}
	A()
	{
	#ifdef  _WINDOWSJQ_
		InitializeCriticalSection(my_winsec); // 用临界区之前要先初始化
	#endif
	}

private:
	mutex my_mutex;
	list<int> msgRecvQueue;

#ifdef  _WINDOWSJQ_
	CRITICAL_SECTION my_winsec; //  windows中的临界区，非常类似于c++11中的mutex，但是这个临界区变量用之前必须初始化
#endif //  _WINDOWSJQ_

};

1. 多次进入临界区
	0. 在同一线程(不同线程就会卡住等待)中，windows中相同的“相同的临界区变量”代表临界区的进入(EnterCriticalSection)可以被多次调用
	   但是你调用了几次EnterCriticalSection，就得调用几次LeaveCriticalSection
	void inMsgRecvQueue()
	{
		for (int i = 0; i < 10; i++)
		{
	#ifdef _WINDOWSJQ_
			EnterCriticalSection(&my_winsec);
			EnterCriticalSection(&my_winsec);
			msgRecvQueue.push_back(i);
			LeaveCriticalSection(&my_winsec);
			LeaveCriticalSection(&my_winsec);

	#else
			my_mutex.lock();  // 报异常，C++11不允许调用两次，与windows有区别
			my_mutex.lock();
			msgRecvQueue.push_back(i);
			my_mutex.unlock();
			my_mutex.unlock();

	#endif

		}
	}


2. 自动析构技术

// 本类用于自动释放windows下的临界区，防止忘记LeaveCriticalSection情况发生，类似于C++11中的lock_guard<mutex>
class CWINLOCK  // RAII类，资源获取及初始化
{
public:
	CWINLOCK(CRITICAL_SECTION *ptr)
	{
		ptr = ptr;
	}
	~CWINLOCK()
	{
		LeaveCriticalSection(ptr);
	}
private:
	CRITICAL_SECTION *ptr;
};

CRITICAL_SECTION my_winsec;
void inMsgRecvQueue()
{
	for (int i = 0; i < 10; i++)
	{
#ifdef _WINDOWSJQ_
		CWINLOCK winlock(&my_winsec);
		msgRecvQueue.push_back(i);


#else
		lock_guard<mutex> sbguard();
		msgRecvQueue.push_back(i);

#endif

	}
}

3. recursive_mutex递归的独占互斥量
// 考虑代码是否有优化空间，效率上比mutex要差一些

// version_0,报错
mutex my_mutex;
void test()
{
	lock_guard<mutex> sbguard(my_mutex);
	test2();
}
void test2()
{
	lock_guard<mutex> sbguard(my_mutex);
}
void main()
{
	lock_guard<mutex> sbguard(my_mutex);
	test();
}

// version_1
// 允许同一个线程，同一个互斥量多次被.lock()
recursive_mutex my_mutex;
void test()
{
	lock_guard<recursive_mutex> sbguard(my_mutex);
	test2();
}
void test2()
{
	lock_guard<recursive_mutex> sbguard(my_mutex);
}
void main()
{
	lock_guard<recursive_mutex> sbguard(my_mutex);
	test();
}


4. 带超时的互斥量 timed_mutex 和 recursive_timed_mutex
// timed_mutex: 是带超时功能的独占互斥量
// recursive_timed_mutex: 带超时功能的递归独占互斥量
// try_lock_for(): 等待一段时间，如果拿到了锁或者等待超过时间没有拿到锁，就走下来
// try_lock_until(): 参数是一个未来的时间点，在未来的时间没到的时间内，如果拿到了锁，那么久走下来。如果没拿到锁，程序流程也走下来
timed_mutex my_mutex;
void inMsgRecvQueue()
{
	for (int i = 0; i < 10; i++)
	{
		chrono::microseconds timeout(100);
		if (my_mutex.try_lock_for(timeout))
		if(my_mutex.try_lock_until(chrono::steady_clock::now() + timeout))
		{
			msgRecvQueue.push_back(i);

			my_mutex.unlock();
		}
		else
		{//没拿到锁头
			chrono::microseconds sleeptime(200);
			this_thread::sleep_for(sleeptime);
		}
		

#endif

	}
}