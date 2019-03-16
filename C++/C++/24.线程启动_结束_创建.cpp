/*
 * @file   24.并发基本概念及实现_进程_线程.cpp
 * @date   2019.3.14.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */

 0.程序的运行起来，生成一个进程，该进程所属的主线程开始自动运行
	 //cout << "hello" << endl; 实际上是主线程在执行，主线程从main()函数返回，则整个进程执行完毕
	 // 主线程从main()开始执行，那么我们自己创建的线程，也需要从一个函数开始运行(初始函数)，一旦这个函数运行完毕，就代表我们这个线程运行结束
	 // 整个进程,是否执行完毕的标志是主线程是否执行完毕,如果主线程执行完毕则代表整个进程执行完毕
	 // 如果主线程执行完毕,一般情况下如其他子线程还没有执行完毕,那么这些子线程也会被操作系统强行终止.
	 // 所以一般情况下,如果想保持子线程的运行状态,那么需要让主线程一直保持运行,不要让主线程运行完毕
	 // 异常:detach()

 1. thread：标准库中的类. // 头文件 thread
	 thread myobj(myprint);// 1.创建了线程，线程执行起点(入口)myPrint 2.myprint线程开始执行
	 如果只有thread myobj(myprint);没有其他诸如join或detach等操作，程序将报错

 2. join():加入/汇合. 就是阻塞，让主线程等待子线程执行完毕，然后子线程和主线程汇合
	myobj.join();

 3.detach():分离. 不建议使用
	 0.传统多线程主线程要等待子线程执行完毕，然后自己才会退出
	 1.主线程不和子线程汇合，主线程执行主线程的，子线程执行子线程的。
	    主线程不必等待子线程运行结束，主线程可以先结束，此举并不影响子线程的执行
	 2.为什么引入detach()
		因为我们创建了很多子线程，让主线程逐个等待子线程结束，所以引入detach()
		一旦detach()之后，与这个主线程关联的thread对象就会失去与这个主线程的关联，此时这个子线程就会驻留在后台运行
		此时，这个子线程就相当于被c++运行时刻接管，当子线程执行完毕后，由运行时库负责清理该线程相关的资源(守护线程)。
	 detach()使线程myprint失去我们自己的控制


 4. 一旦调用了detach()，就不能用join(),否则系统会报告异常

 5.joinable()：判断是否可以成功使用join()或者detach()
	 0.如果在没有调用join()或者detach()之前，使用joinable()返回true
	 1.如果在调用join()或者detach()之后，使用joinable()返回false

 // 执行顺序:#1->#3->#2
 void myprint() // #3
 {
 cout << "Thread start" << endl;
 }

 int main()
 {
 thread myobj(myprint); // #1
 if (myobj.joinable()) {}
 //myobj.join();		   // #2
 //myobj.detach();
 cout << "hello" << endl;
 return 0;
 }

 6.其他创建线程的手法
	0. 用类对象(可调用对象)
	 class TA
	 {
	 public:
		 void operator()()
		 {
			 cout << "operator() start" << endl;
		 }
	 }

	 void main1()
	 {
		 Ta ta;
		 thread myobj(ta); // 可调用对象
		 myobj.join();

	 }


	 // 一旦调用了detach()，那主线程结束了，这里用的这个ta对象还在吗？
	 // 这个ta对象实际上是被复制到线程中去。执行完主线程后，ta会被销毁，但是复制的ta对象依旧存在
	 // 只要你这个TA对象里没有引用，没哟指针，那么就不会产生问题
	 class TA
	 {
	 public:
		 int m_i;
		 TA(int i) :m_i(i) {}

		 TA(const TA & ta) :m_i(ta.m_i) {}

		 void operator()()
		 {
			 cout << "operator() start" << endl;
		 }
	 };
	 void main2()
	 {
		 int my = 6;
		 Ta ta(my);
		 thread myobj(ta); // 可调用对象
		 myobj.detach();

	 }
	 1. 用lambda表达式
		 auto mylambda = [] {cout << "start" << endl; }
		thread myobj(mylambda);
