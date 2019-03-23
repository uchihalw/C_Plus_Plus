/*
 * @file   34.windows�ٽ���_��������mutex������.cpp
 * @date   2019.3.23.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0. windows�ٽ���

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
		InitializeCriticalSection(my_winsec); // ���ٽ���֮ǰҪ�ȳ�ʼ��
	#endif
	}

private:
	mutex my_mutex;
	list<int> msgRecvQueue;

#ifdef  _WINDOWSJQ_
	CRITICAL_SECTION my_winsec; //  windows�е��ٽ������ǳ�������c++11�е�mutex����������ٽ���������֮ǰ�����ʼ��
#endif //  _WINDOWSJQ_

};

1. ��ν����ٽ���
	0. ��ͬһ�߳�(��ͬ�߳̾ͻῨס�ȴ�)�У�windows����ͬ�ġ���ͬ���ٽ��������������ٽ����Ľ���(EnterCriticalSection)���Ա���ε���
	   ����������˼���EnterCriticalSection���͵õ��ü���LeaveCriticalSection
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
			my_mutex.lock();  // ���쳣��C++11������������Σ���windows������
			my_mutex.lock();
			msgRecvQueue.push_back(i);
			my_mutex.unlock();
			my_mutex.unlock();

	#endif

		}
	}


2. �Զ���������

// ���������Զ��ͷ�windows�µ��ٽ�������ֹ����LeaveCriticalSection���������������C++11�е�lock_guard<mutex>
class CWINLOCK  // RAII�࣬��Դ��ȡ����ʼ��
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

3. recursive_mutex�ݹ�Ķ�ռ������
// ���Ǵ����Ƿ����Ż��ռ䣬Ч���ϱ�mutexҪ��һЩ

// version_0,����
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
// ����ͬһ���̣߳�ͬһ����������α�.lock()
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


4. ����ʱ�Ļ����� timed_mutex �� recursive_timed_mutex
// timed_mutex: �Ǵ���ʱ���ܵĶ�ռ������
// recursive_timed_mutex: ����ʱ���ܵĵݹ��ռ������
// try_lock_for(): �ȴ�һ��ʱ�䣬����õ��������ߵȴ�����ʱ��û���õ�������������
// try_lock_until(): ������һ��δ����ʱ��㣬��δ����ʱ��û����ʱ���ڣ�����õ���������ô�������������û�õ�������������Ҳ������
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
		{//û�õ���ͷ
			chrono::microseconds sleeptime(200);
			this_thread::sleep_for(sleeptime);
		}
		

#endif

	}
}