/*
 * @file   30.condition_variable+wait+notify_one+notify_all.cpp
 * @date   2019.3.21.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0. 条件变量condition_variable、wait、notify_one():通知一个线程



queue msgRecvQueu;
mutex my_mutex;
condition_variable my_cond; // 生成一个条件变量对象，需要和互斥量配合使用
void inMsgRecvQueue()
{
	for (int i = 0; i< 5; i++)
	{
		unique_lock<mutex> my_mutex(my_mutex);
		msgRecvQueu.push();

		// 假如outMsgRecvQueue正在处理一个事物，需要一端时间，而不是在卡在wait()那里等待你唤醒，那么此时notify_one()的调用也许没有效果
		my_cond.notify_one(); // 尝试吧wait()的线程唤醒，执行完这行，那么outMsgRecvQueue里面的wait()就会被唤醒
	}
}
void outMsgRecvQueue()
{
	int command = 0;
	while (true)
	{
		unique_lock<mutex> my_guard(my_mutex);


		// wait()用来等一个东西
		// 如果第二个参数lambda表达式的返回值是false,那么wait()将解锁互斥量，并堵塞到本行。
		// 如果第二个参数lambda表达式的返回值是true,那么wait()直接返回
		// 那么堵塞到什么时候为止，堵到其他某个线程调用notify_one()成员函数为止
		// 如果wait()的第二个参数缺省。即my_cond.wait(my_guard),那么就跟第二个参数lambda表达式返回false效果一样。《互斥锁没有获取到》
		// 当其他线程用notify_one()将本wait()唤醒后，wait()就开始恢复干活？
		// a).wait()不断的尝试重新获取互斥量锁，如果获取不到，流程留卡在wait这里等待获取。如果获取到(等于加了锁)，wait()就接着走下去，执行b
		// b).获取到锁，并上锁。
			// b1.)如果wait有第二个参数，就判断这个lambda表达式，如果表达式为false,那么wait又对互斥量解锁，又开始休眠在这里等待再次被notify唤醒
			// b2.)如果表达式为true，那么流程走下来，此时互斥锁被锁着。
			// b3.)如果wait没有第二个参数，那么wait返回，流程走下来？？？？？？？？？？？？？？？？《互斥锁获取到》
		my_cond.wait(my_guard, [this] { // 一个lambda就是一个可调用对象（函数）
			if (!msgRecvQueu.empty())
				return true;
			return false;
		
		});

		// 流程走到这里来，这个互斥锁一定是锁着的。同时可以确定 msgRecvQueu 至少有一条数据
		command = msgRecvQueu.front();
		msgRecvQueu.pop();
		my_guard.unlock(); // 需要手动解锁。以免锁住太长时间

	}
}
A myobj;
thread obj1(&A::outMsgRecvQueue, &myobj);
thread obj3(&A::inMsgRecvQueue, &myobj);


2. notify_all()
A myobj;
thread obj1(&A::outMsgRecvQueue, &myobj);
thread obj2(&A::outMsgRecvQueue, &myobj);
thread obj3(&A::inMsgRecvQueue, &myobj);

// 如果是notify_one()会不确定激活哪一个inMsgRecvQueue，其只能激活一个线程
// 如果两个线程都需要被唤醒，那么notify_all()可以同时唤醒两个线程
