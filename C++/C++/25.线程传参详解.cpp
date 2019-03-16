/*
 * @file   25.线程传参详解.cpp
 * @date   2019.3.16.
 * @author GBW
 * @Description: 线程传参详解，detach()大坑、成员函数做线程函数
 
 * @Note:
 
 */
0. 传递临时对象作为线程函数
	/*
		0. 只要将临时构造的A类对象作为参数传递给线程，就一定能够在主线程执行完毕前把线程函数的第二个参数构建出来，从而
		   确保detach()子线程也安全运行 
	*/

	0. 要避免的陷阱1
		// version_1
		void func(const int &ix)
		{
			cout << ix;

		}
		void main()
		{
			int i = 0;
			int &var = i;
			func(var);
		}
		/* var、i、ix的地址都相等 */

		// version_2
		void func(const int &ix, char *buf)
		{
			cout << ix // 分析, ix并不是var的引用，实际是指传递，所以即使主线程detach了子线程，那么子线程中的ix也可以正常使用
			cout << buf; // 指针在detach子线程时，绝对会有问题
		}
		void main()
		{
			int i = 0;
			int &var = i;
			char buf[] = "hello";
			thread myobj(func,var,buf);
			myobj.detach();
		}
		/* var、i、的地址都相等, 前面两者与ix的地址不相等 */

		// version_3
		void func(const int &ix, const strng & str)
		{
			cout << ix // 分析, ix并不是var的引用，实际是指传递，所以即使主线程detach了子线程，那么子线程中的ix也可以正常使用
			cout << *str; // 
		}
		void main()
		{
			int i = 0;
			int &var = i;
			char buf[] = "hello";
			thread myobj(func, var, buf);
			myobj.detach();
		}
		/* buf与str的地址不相等 */

	1. 要避免的陷阱2
		// version_1
		void func(const int &ix, const strng & str)
		{
			cout << ix // 分析, ix并不是var的引用，实际是指传递，所以即使主线程detach了子线程，那么子线程中的ix也可以正常使用
			cout << *str; // 
		}
		void main()
		{
			int i = 0;
			int &var = i;
			char buf[] = "hello";
			thread myobj(func, var, string(buf)); // buf到底什么时候转成string
										          // 事实上存在，buf都被回收了(main函数执行完了)，系统才用buf去转string
			myobj.detach();                       // 故通过string构造临时buf,直接将buf转换成string对象
		}
		/* buf与str的地址不相等 */


		// version_2
		class A {
		public:
			int _i;
			A(int i) :_i(i) {}
			A(const A& tmp) :_i(tmp._i) {}
			~A() {}
		};
		void func(const int &ix, const A& a)
		{
			cout << ix;
			
		}
		void main()
		{
			int i = 0;
			thread myobj(func, var, A(5));  // 在创建线程的同时构造临时对象的方法传递参数是可行的，此处会调用一次构造和拷贝
			myobj.detach();                    
		}
	2. 总结
		0. 若传递int这种简单类型的参数，建议都是值传递，不要引用
		1. 如果传递类对象，避免隐式类型转换。全部都在创建线程的同时构建出临时对象来，然后在参数函数里用引用来接(如果不用引用，会调用一次构造函数和两次拷贝函数)
		2. 建议不使用detach()，只使用join()。就不存在局部变量导致线程对内存的非法引用问题

1.临时对象作为线程参数继续讲
	0. 线程id概念：可以用std::this_thread::get_id()来获取


2.传递类对象，智能指针作为线程参数
	0. 传递类对象
		// version_1
		class A {
		public:
			mutable int _i;
			A(int i) :_i(i) {}
			A(const A& tmp) :_i(tmp._i) {}
			~A() {}
		};
		void func(const A& buf) // 子线程中编译器会按照拷贝进行接收
		{
			buf._i = 99;
		}
		void main()
		{
			A a(10);
			thread myobj(func, a); // func()中将buf._i更改为99， 但是main()中a._i仍然为10
			myobj.join();
		}
		// version_2
		class A {
		public:
			int _i;
			A(int i) :_i(i) {}
			A(const A& tmp) :_i(tmp._i) {}
			~A() {}
		};
		void func(A& buf) // 子线程中编译器不会按照拷贝进行接收
		{
			buf._i = 99;
		}
		void main()
		{
			A a(10);
			thread myobj(func, ref(a)); // func()中将buf._i更改为99， 但是main()中a._i也变为99
			myobj.join();
		}
	1. 传递智能指针
		void func(unique_ptr<int> ptr){}
		void main()
		{
			unique_ptr<int> my(new int(100));
			thread myobj(func, move(my));
			myobj.join();
		}

3. 用成员函数指针做线程参数
class A {
public:
	mutable int _i;
	A(int i) :_i(i) {}
	A(const A& tmp) :_i(tmp._i) {}
	~A() {}
	void thread_work(int num){}
};
void main()
{
	A myobj(10);
	thread myobj(&A::thread_work, myobj, 15);
	myobj.join();
}