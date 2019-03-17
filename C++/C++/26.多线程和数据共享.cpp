/*
 * @file   26.多线程和数据共享.cpp
 * @date   2019.3.17.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0. 创建和等待多线程
	创建多个线程，线程入口函数统一使用func.
	多个线程的执行顺序是乱序的，跟操作系统内部对线程的运行调度机制有关
	主线程等待所有子线程结束，最后主线程结束
void func(int num)
{
	cout << "start " << num << endl;
	cout << "end " << num << endl;
}
void main()
{
	vector<thread> mythread;
	for (int = i = 0; i < 10; i++)
		mythread.push_back(thread(func, i);
	for (auto iter = mythread.begin(); iter != mythread.end(); iter++)
		iter->join();
	cout << "main end" << endl;
}

1. 数据共享问题
	0. 只读的数据:是安全稳定的，不需要特别的处理手段，直接读就可以。
	1. 有读有写:读的时候不能写，写的时候不能读
vector<int> g_v = { 1,2,3 }; // 共享数据
void func()
{
	cout << this_thread::get_id() << g_v[0] << g_v[1] << g_v[2] << endl;
}
void main()
{
	vector<thread> mythread;
	for (int = i = 0; i < 10; i++)
		mythread.push_back(thread(func, i);
	for (auto iter = mythread.begin(); iter != mythread.end(); iter++)
		iter->join();
	cout << "main end" << endl;
}

2. 共享数据的保护案例代码
	网络游戏服务器。两个自己创建的线程，一个线程收集玩家命令，并把命令数据写到一个队列
									另一个线程，从队列中取出玩家发送来的命令，解析，然后执行玩家需要的动作
	// 准备用成员函数作为线程函数的方法来写线程
	// 互斥量:解决多线程保护共享数据问题



class A
{
public:
	// 把收到的消息（玩家命令）入到一个队列的线程
	void inMsgRecvQueue()
	{
		for (int i = 0; i < 100000; i++)
		{
			cout << "inMstRecvQueue, insert a element" << i << endl;
			msgRecvQueue.push_back(i); // 假设数字i就是收到的玩家命令，直接弄到消息队列中去
		}
	}

	// 把数据从消息队列取出的线程
	void outMsgRecvQueue()
	{
		for (int i = 0; i < 100000; i++)
		{
			if (!msgRecvQueue.empty())
			{
				// 消息队列不为空
				int command = msgRecvQueue.front();// 返回第一个元素，但是不检查元素是否存在
				msgRecvQueue.pop_front();// 移除第一个元素，但是不返回
				//....考虑处理数据
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
};
void main()
{
	A myobj;
	thread myOutMsg(&A::outMsgRecvQueue, &myobj); // 第二个参数是引用，才能保证线程中使用的对象是obj,如果不是引用，thread会将myobj复制一份
	thread myInMsg(&A::inMsgRecvQueue, &myobj);

	myInMsg.join();
	myOutMsg.join();
}





















