/*
 * @file   28.unique_lock.cpp
 * @date   2019.3.18.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
1. unique_lock 取代 lock_guard
	0. unique_lock是个类模板，工作中，一般lock_guard（推荐使用）
	1. lock_guard 取代了mutex的lock()和unlock()
	2. unique_lock比lock_guard灵活很多，效率上差一点，内存占用多一点 

bool outMsgLULProc(int &command)
{
	unique_lock<mutex> sbguard(my_mutex);
	//lock_guard<mutex> sbguard(my_mutex);
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

2. unique_lock的第二个参数
	0. lock_guard可以带第二个参数
	// lock_guard<mutex> guard(mu_mutex, adopt_lock);
	1.adopt_lock:表示互斥量已经被lock，故必须把互斥量提前lock，否则会报异常
	// 假设调用方线程已经拥有了互斥的所有权(已经lock成功了)，才可以使用adopt_lock
	// 通知lock_guard不要在构造函数中lock这个互斥量
	// unique_lock也可以带adopt_lock标记，含义相同
	/* 
		std::chrono::milliseconds dura(20000) // 20s
		this_thread::sleep_for(dura)
	*/
	2.try_to_lock
	// 尝试用mutex的lock（）去锁定这个mutex,但如果没有锁定成功，我也会立即返回，并不会阻塞在那里
	// try_to_lock的前提是你自己不能先去lock
	bool outMsgLULProc(int &command)
	{
		// lock()，不能提前lock
		unique_lock<mutex> sbguard(my_mutex, try_to_lock);
		if (my_mutex.owns_lock())
		{ // 成功拿到锁 }
		else
		{ }
		//lock_guard<mutex> sbguard(my_mutex);
		if (!msgRecvQueue.empty())
		{
			// 消息队列不为空
			int command = msgRecvQueue.front();// 返回第一个元素，但是不检查元素是否存在

			return true;
		}
		//my_mutex.unlock();
		return false;
	}

	3. defer_lock
	// 用defer_lock的前提是你不能自己去先lock,否则会报异常
	// 意思就是并没有给mutex加锁：初始化了一个没有加锁的mutex
	unique_lock<mutex> sbguard(my_mutex, defer_lock);
	sbguard.lock(); // 不用自己unlock
	// 处理共享代码
	sbguard.unlock(); // 锁住之后，想灵活一点，希望unlock后去处理一些非共享代码
	// 处理非共享代码
	sbguard.lock();
	// 处理共享代码

3. unique_lock的成员函数
	0. unlock,解锁
	1. lock，加锁
	2. try_lock，// 尝试加锁，成功返回true,不是阻塞的
	3. release,//返回它所管理的mutex对象指针，并释放所有权，也就是说，这个unique_lock和mutex不再有联系
	// 如果原来mutex对象处于加锁状态，你有责任接管过来并负责解锁
	bool outMsgLULProc(int &command)
	{
		// lock()，不能提前lock
		unique_lock<mutex> sbguard(my_mutex);
		mutex *ptx = sbguard.release(); // ptx接管过啦，故有责任自己解锁

		// 消息队列不为空
		int command = msgRecvQueue.front();// 返回第一个元素，但是不检查元素是否存在

		ptx->unlock();
		
		return false;
	}
	4.为什么有时候需要unlock()，因为lock锁住的代码越少，执行越快，整个程序运行效率越高
	 // 锁头锁住的代码的多少，称为锁的粒度
	 // 粒度太细，容易错过共享数据
	 // 粒度太粗，容易降低效率

4. unique_lock的值传递 // 不要把同一个mutex邦定到两个unique_lock
unique_lock<mutex> sbguard(my_mutex); 
// sbguard拥有my_mutex的所有权
// sbguard可以将自己的所有权转移给其他unique_lock对象
// unique_lock对象这个mutex的所有权是属于可以转移，但是不能复制
	unique_lock<mutex> sbguard1(my_mutex);
	unique_lock<mutex> sbguard2(sbguard1);  // 报错，不能复制
	unique_lock<mutex> sbguard2(move(sbguard1)); // 相当于sbguard2和my_mutex绑定到一起了，现在sbguard1指向空，sbguard2执行my_mutex

	class A
	{
	public:
		unique_lock<mutex> rtn_unique_lock()
		{
			unique_lock<mutex> tmpguard(my_mutex1);
			return tmpguard;
		}
	private:
		mutex my_mutex1;
	}