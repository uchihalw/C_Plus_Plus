/*
 * @file   33.atomic续谈_async深入.cpp
 * @date   2019.3.22.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
1. 原子操作atomic续谈
一般atomic原子操作，针对++、--、+=、&=、|=、=是支持的，其他的可能不支持

std::atomic<int> g_mycout_atomic = 0; //相当于封装了一个类型为int的对象；可以像操作int一样操作atomic
void mythread() //线程入口函数 // 7s
{
	for (int i = 0; i < 100000; i++)
	{
		g_mycout_atomic++; // 对应的操作是原子操作，不会被打断
		g_mycout_atomic += 1; // 
		g_mycout_atomic = g_mycout_atomic + 1; // 
	}
}
void main()
{
	thread obj1(mythread);
	thread obj2(mythread);
	obj1.join();
	obj2.join();

}

2. async深入谈

	0. async参数详谈，async用来创建一个异步任务
	launch::deferred :延迟调用
	launch::async : 强制创建一个线程
	// std::thread() 如果系统资源紧张，那么可能创建线程就会失效，那么执行thread()时整个程序可能崩溃
	// std::async() 创建一个异步任务
	// async和thread最明显的不同，就是async有时候并不创建新线程。谁调用get，就在谁所在的线程中运行线程入口函数
	补充如下：
	
		// 0.如果用deferred来调用async会
			future<int> result = async(launch::deferred, mythread);// deferred延迟调用，并不创建新线程，延迟到future对象调用.get或者.wait的时候才执行mythread.
			如果没有调用wait或者wait将不会创建新线程
		// 1.std::launch::async
			future<int> result = async(launch::async, mythread); // 强制这个异步任务在新线程上执行，系统必须创建出新线程运行mythread()函数

		// 2.std::launch::async | std::launch::deferred
			future<int> result = async(std::launch::async | std::launch::deferred, mythread);
			或:意味着async的行为可能是“创建新线程并立即执行” 或者 “没有创建新线程并延迟到调用.get()才开始执行任务入口函数”，两者居其一

		// 3.不带额外参数，只给async函数一个入口函数名
			future<int> result = async(mythread); 
			当你没有指定额外参数的时候，默认值应该是二者取其一.和2的效果一致。系统自行决定运行哪个

	1. async和thread的区别
		0. std::thread() 如果系统资源紧张，那么可能创建线程就会失效，那么执行thread()时整个程序可能崩溃
			// int mythread() { return 1; }
			// thread myobj(mythread);
			// myobj.join();
			// thread创建线程的方式，如果线程返回值，可能需要通过全局变量才能拿到
		1. async创建异步任务。可能创建也可能不创建线程。async调用很容易拿到线程入口函数的返回值
			// 由于系统资源限制：
			// 0.thread创建的线程太多，则可能创建失败，系统报告异常，崩溃
			// 1.用async，一般就不会报异常也不会崩溃。因为如果系统资源紧张导致无法创建新线程的时候，async这种不加额外参数的调用就不会创建新线程
			//   而是后续谁调用了result.get()来请求结果，那么这个异步任务thread就运作在执行get语句的线程上
			// 2.如果强制async一定要创建新线程。就必须使用launch::async
	2. async不确定性问题的解决
		不加额外参数的async调用，让系统自行决定是否创建新线程
		问题的焦点在于 future<int> result = async(mythread);
		这个异步任务到底有没有被推迟执行，


void mythread()
{
	cout << this_thread::get_id() << endl;
}
void main()
{
	cout << this_thread::get_id() << endl;
	future<int> result = async(mythread);
	cout << result.get() << endl;
}