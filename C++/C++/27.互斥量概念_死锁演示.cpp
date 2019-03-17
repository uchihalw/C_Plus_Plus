/*
 * @file   27.互斥量概念_死锁演示.cpp
 * @date   2019.3.17.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
#include<mutex>
class A
{
public:
	// 把收到的消息（玩家命令）入到一个队列的线程
	void inMsgRecvQueue()
	{
		for (int i = 0; i < 100000; i++)
		{
			cout << "inMstRecvQueue, insert a element" << i << endl;
			my_mutex.lock();
			msgRecvQueue.push_back(i); // 假设数字i就是收到的玩家命令，直接弄到消息队列中去
			my_mutex.unlock();
		}
	}

	bool outMsgLULProc(int &command)
	{
		my_mutex.lock();
		if (!msgRecvQueue.empty())
		{
			// 消息队列不为空
			int command = msgRecvQueue.front();// 返回第一个元素，但是不检查元素是否存在
			msgRecvQueue.pop_front();// 移除第一个元素，但是不返回
		   
			my_mutex.unlock();
			return true;
		}
		my_mutex.unlock();
		return false;
	}

	// 把数据从消息队列取出的线程
	void outMsgRecvQueue()
	{
		int command = 0;
		for (int i = 0; i < 100000; i++)
		{

			bool result = outMsgLULProc(command);
			if (result)
			{
				cout << "取出一个元素成功" << endl;
			}
			
			else
			{
				cout << "outMsgRecvQueu()执行，但目前消息队列为空" << i << endl;
			}
		}
		cout << "END" << endl;
	}
private:
	list<int> msgRecvQueue; // 容器，专门用于代表玩家给咱们发送过来的命令
	mutex my_mutex;//创建一个互斥量
};
void main()
{
	A myobj;
	thread myOutMsg(&A::outMsgRecvQueue, &myobj); // 第二个参数是引用，才能保证线程中使用的对象是obj,如果不是引用，thread会将myobj复制一份
	thread myInMsg(&A::inMsgRecvQueue, &myobj);

	myInMsg.join();
	myOutMsg.join();
}
0. 互斥量的基本概念
	互斥量就是个类对象。理解成一把锁头，多个线程尝试用lock()成员函数来加锁这把锁头，
	只有一个线程可以锁定成功(成功的标标志是lock()函数返回)
	如果没锁成功，那么线程的执行流程就卡在lock()这里不断的尝试去锁这把锁头

1. 互斥量的用法
	先lock()，操作共享数据，再unlock()
	lock()和unclock()要成对使用
	为了防止大家忘记unlock(),引入一个lock_guard的类模板，在你忘记unlock()的时候，替你unlock()
	lock_guard类模板：直接取代lock()和unlock()；
					 也就是你用了lock_guard之后，再不能使用lock()和unlock()

	lock_guard的构造函数里执行了lock()；lock_guard()的析构函数里执行了unlock()（析构只有return的时候才执行），也可以通过作用域使得析构提前执行
	bool outMsgLULProc(int &command)
	{
		lock_guard<mutex> sbguard(my_mutex);
		if (!msgRecvQueue.empty())
		{
			// 消息队列不为空
			int command = msgRecvQueue.front();// 返回第一个元素，但是不检查元素是否存在
			msgRecvQueue.pop_front();// 移除第一个元素，但是不返回

			//my_mutex.unlock();
			return true;
		}
		//my_mutex.unlock();
		return false;
	}


2. 死锁
	死锁问题由至少两个锁头也就是两个互斥量才能产生。
	金锁(JinLock)、银锁(YinLock)
	/*
	两个线程A、B
		1.线程A执行的时候，这线程先锁金锁，把金锁lock()成功了，然后它去lock()银锁
			// 出现了上下文切换
		2.线程B执行，这个线程先锁银锁因为银锁还没有被锁，所以银锁会lock()成功，线程B要去lock()金锁
			// 此时死锁就产生了
		
	*/


	0.死锁问题的解决:只要调用的多个互斥量的顺序保持一致就行
	// unlock()的顺序无所谓
	void inMsgRecvQueue()
	{
		for (int i = 0; i < 100000; i++)
		{
			cout << "inMstRecvQueue, insert a element" << i << endl;
			my_mutex1.lock();
			my_mutex2.lock();
			msgRecvQueue.push_back(i); // 假设数字i就是收到的玩家命令，直接弄到消息队列中去
			my_mutex1.unlock();
			my_mutex2.unlock();
		}
	}

	bool outMsgLULProc(int &command)
	{
		my_mutex1.lock();
		my_mutex2.lock();
		if (!msgRecvQueue.empty())
		{
			// 消息队列不为空
			int command = msgRecvQueue.front();// 返回第一个元素，但是不检查元素是否存在
			msgRecvQueue.pop_front();// 移除第一个元素，但是不返回

			my_mutex1.unlock();
			my_mutex2.unlock();
			return true;
		}
		my_mutex1.unlock();
		my_mutex2.unlock();
		return false;
	}

	1.std::lock()函数模板:用来处理多个互斥量
		一次锁住两个或者两个以上的互斥量(至少两个，1个不行)
		不存在因为在多个线程中，因为锁的顺序导致死锁的问题
		std::lock():如果互斥量中有一个没锁住，它就在哪里等着，等所有互斥量都锁住，才能往下走(返回)
		// 要么两个都锁住，要么两个都没锁住。如果只锁了一个，另外一个没锁成功，那么它立即把已经锁住的解锁
	void inMsgRecvQueue()
		{
			for (int i = 0; i < 100000; i++)
			{
				cout << "inMstRecvQueue, insert a element" << i << endl;
				std::lock(my_mutex1, my_mutex2); // 相当于每个互斥量都调用了.lock()
				msgRecvQueue.push_back(i); // 假设数字i就是收到的玩家命令，直接弄到消息队列中去
				my_mutex1.unlock();
				my_mutex2.unlock();
			}
		}


	2.std::lock_guard的std::adopt_lock参数,解决不需要自己unlock()问题
	// adopt_lock是个结构体对象，一个标记作用:
	// 作用:表示这个互斥量已经lock()
	// 不需要再lock_guard构造函数里面对mutex对象再次进行lock()
	void inMsgRecvQueue()
	{
		for (int i = 0; i < 100000; i++)
		{
			cout << "inMstRecvQueue, insert a element" << i << endl;
			std::lock(my_mutex1, my_mutex2); 
			lock_guard<mutex> sbguard1(my_mutex1，std::adopt_lock()); // adopt_lock不调用lock_guard的lock()函数
			lock_guard<mutex> sbguard2(my_mutex2，std::adopt_lock());

			msgRecvQueue.push_back(i); // 假设数字i就是收到的玩家命令，直接弄到消息队列中去

		}
	}





