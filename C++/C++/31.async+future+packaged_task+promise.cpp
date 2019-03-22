/*
 * @file   31.async+future+packaged_task+promise.cpp
 * @date   2019.3.21.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
#include<future>
1.async、future创建后台任务并返回值
// 希望线程返回一个结果
// async是个函数模板，用启动一个异步任务，启动一个异步任务之后，返回一个future对象。future是一个类对象
// "启动一个异步任务":自动创建一个线程并开始执行对应的线程入口函数，返回一个future对象
// future对象里面含有线程入口函数所返回的结果（线程返回的结果），可以通过调用future对象的成员函数get()来获取结果
// future提供了一种访问异步操作结果的机制(就是结果你可能不能立即就能拿到)，就是说这个结果可能不会马上拿到。
// 在线程执行完毕的时候，你就能够拿到结果了，这个future(对象)里会保存一个值，以供在将来某个时刻拿到
// version_0
int mythread()
{
	cout << "start" <<std:this_thread::get_id() << endl;
	std::chrono::milliseconds dura(5000); // 5s
	std::this_thread::sleep_for(dura);
	cout << "end" <<std:this_thread::get_id() << endl;
	return 5;
}
void main()
{
	cout << "main" << this_thread::get_id() << endl;
	std::future<int> result = async(mythread); // future对象和async绑定在一起
	cout << result.get() << endl; // 卡在这里等待mythread()执行完毕返回结果，拿到结果。get不拿到值誓不罢休，且只能调用一次，调用多次会报异常
	result.wait(); // 也会卡，但是只是等待线程返回，没有返回值。有点像join,
}

// version_1
// 
/* 
通过额外向async传递一个参数，该参数类型时launch类型(枚举类型)，来达到一些特殊目的
	1.launch::deferred:表示线程入口函数调用被延迟到future的wait()或者get()函数调用时才执行
	  延迟调用，并且没有创建线程，是在主线程中调用的线程入口函数
	  future res = async(launch::deferred, &A::mythred, &a, tmp);
	  如果wait()或者get()没有被调用，那么线程不会卡,因为根本就没有创建出来
	  如果wait()或者get()被调用，线程根本就没有创建出来
	2.launch::async:表示调用async函数的时候就开始创建线程。
	  不需要get或者wait线程就会自动启动
	  ERR:async函数默认用的这个参数

	3.async|deferred 不能联合使用

*/

class A {
public:
	int mythread(int x){}
};
void main()
{
	A a;
	int tmp = 10;
	future res = async(&A::mythread, &a,tmp); // 第二个参数是一个引用，如果不传引用的话，就会重新创建一个A对象。引用才能保证线程中用的是同一个对象
	if (1)
	{
		cout << result.get() << endl; 
	}
	else
	{
		如果没有get或者wait也会等待5s
	}
}

2. packaged_task:打包任务，把任务包装起来
// 是个类模板，它的模板参数是各种可调用对象。方便未来作为线程入口函数方便调用
// packaged_task包装起来的可调用对象还可以直接调用。
int mythread()
{
	cout << "start" << std:this_thread::get_id() << endl;
	std::chrono::milliseconds dura(5000); // 5s
	std::this_thread::sleep_for(dura);
	cout << "end" << std:this_thread::get_id() << endl;
	return 5;
}
void main()
{
	packaged_task<int(int)> mypt(mythread); // 把函数mythread通过packaged_task包装起来
	thread t1(ref(mypt), 1);                // 线程开始执行，第二个参数，作为线程入口函数的参数
	t1.join();                              // 等待线程执行完毕
	future<int> res = mypt.get_future();    // future对象里包含有线程入口函数的返回结果，这里result保存mythread的返回结果
	cout << res.get() << endl;

}

3. promise. 类模板
// 能够在某个线程中给它赋值，然后可以再其他线程中，把这个值取出来用
void mythread(promise<int> &tmpp, int calc)
{
	.....
	std::chrono::milliseconds dura(5000); // 5s
	std::this_thread::sleep_for(dura);
	tmpp.set_value((calc); // 结果保存到了tmpp对象中
	return;
}

void mythread2(future<int> &tmpp)
{
	auto res = tmpp.get(); // 线程2中使用线程1中的值
}
void main()
{
	promise<int> mypromise; // 声明一个promise对象。保存的值类型为int
	thread t1(mythread, ref(mypromise), 180);
	t1.join(); // 如果不使用join，会报异常

	// 获取结果值
	future<int> ful = mypromise.get_future(); // promise和future绑定。用于获取线程返回值

	//int res = ful.get();

	threa t2(mythread2(, ref(ful));
	t2.join();


}


4.小结
到底怎么用，什么时候用