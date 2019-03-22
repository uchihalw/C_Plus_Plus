/*
 * @file   32.future其他成员函数_atomic.cpp
 * @date   2019.3.22.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0. future的其他成员函数
void mythread()
{
	std::chrono::milliseconds dura(5000);  // 5s
	this_thread::sleep_for(dura);
}

void main()
{
	future<int> result = async(mythread);

	int wait_time;
	// wait_for等待一段时间
	future_status status = result.wait_for(chrono::seconds(wait_time));

	if (status == future_status::timeout) // wait_time < dura(5000)
	{
		// 表示线程还没有执行完，超时
	}
	else if (status == future_status::ready) // wait_time > dura(5000)
	{
		// 表示线程成功返回
		result.get();
	}
	else if (status == future_status::deferred) // 延迟
	{
		 // 如果async的第一个参数被设置为lanuch::deferred,则本条件成立
		result.get();
	}

}

1. shared_future
// 如果多个线程都想使用某个线程的结果，即shared_future:也是个类模板
// share_future的get是将值复制数据
int mythread(int  mypar)
{
	std::chrono::milliseconds dura(5000);  // 5s
	this_thread::sleep_for(dura);
	return 5;
}
int mythread2(shared_future<int> &tmpf)
int mythread2(future<int> &tmpf) 
{
	auto result = tmpf.get(); // 获取值，只能get一次否则会报异常。get相当于将tmpf中的值移走了，再次get会报异常
							  // 为什么第二次get对象，会报异常。主要因为get函数的设计是一个移动语义。
	return 5;
}
void main()
{
	packaged_task<int(int)> mypt(mythread); // 把函数mythread通过packaged_task包装起来
	thread t1(ref(mypt), 1); // 线程直接开始执行，第二个参数作为线程入口函数的参数
	t1.join(); // 我们可以调用这个等待线程执行完毕，不调用这个不太行，会奔溃

	future<int> result = mypt.get_future(); //  future对象里含有线程入口函数
	bool ifcanget = result.valid(); // true
	shared_future<int> result_s(std::move(result));
	thread t2(mythread2, ref(result| result_s)); // == shared_future<int> result_s(result.share())
	bool ifcanget = result.valid(); // false


	t2.join();// 等待线程执行完毕

}


2. 原子操作,一般用于计数和统计
	1. 互斥量:多线程中，保护共享数据。锁：操作共享数据。开锁
	// 有两个线程，对一个变量进行操作，这个线程读该变量值，另一个线程往这个变量中写值

	int atomvalue = 5

	// 读线程A
	int tmpvalue = atomvalue; // atomvalue代表的是多个线程之间要共享的变量

	//写线程B
	atomvalue = 6;

	// 原子操作可以理解成：不需要互斥量加锁(无锁)技术的多线程并发编程方式
	// 原子操作：是在多线程中，不会被打断的程序执行片段，即 g_mycout++; 原子操作，比互斥量效率更高
	// 互斥量的加锁一般是针对一个代码段(几行代码)，而原子操作针对的一般都是一个变量，而不是一个代码段

	// 原子操作，一般都是指不可分割的操作，也就是说这种操作要么是完成的，要么是不完成的，不会出现半成品状态
	// atd::atomic代表原子操作，是个类模板。其实atomic这个东西是来封装某个类型的值的

// version_0
int g_mycout = 0;
mutex g_my_mutex;
void mythread() //线程入口函数 // 7s
{
	for (int i = 0;i<100000;i++)
	{
		g_my_mutex lock();
		g_mycout++;
		g_my_mutex unlock();
	}
}

std::atomic<int> g_mycout_atomic = 0; //相当于封装了一个类型为int的对象；可以像操作int一样操作atomic
void mythread() //线程入口函数 // 7s
{
	for (int i = 0; i < 100000; i++)
	{

		g_mycout_atomic++; // 对应的操作是原子操作，不会被打断
	}
}
void main()
{
	thread obj1(mythread);
	thread obj2(mythread);
	obj1.join();
	obj2.join();

}

// version_1
std::atomic<bool> g_ifend = false;
void mythread()
{
	chrono::milliseconds dura(1000); // 1s
	while (g_ifend == false)
	{
		this_thread::sleep_for(dura);
	}
}

void main()
{
	thread obj1(mythread);
	thread obj2(mythread);
	chrono::milliseconds dura(5000);
	this_thread::sleep_for(dura);

	g_ifend = true;
	obj1.join();
	obj2.join();

}
















