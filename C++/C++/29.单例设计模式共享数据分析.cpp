/*
 * @file   29.单例设计模式共享数据分析.cpp
 * @date   2019.3.20.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
1. 设计模式大概谈
class MyCAS
{
public:
	static MyCAS *getInstance();
	
/*
	~MyCAS()
	{
		if (m_instance != NULL)
		{
			delete m_instance;
			m_instance = NULL;
		}
	}
*/

	class CCarhuishou
	{
	public:
		~CCarhuishou()
		{
			if (m_instance != NULL)
			{
				delete m_instance;
				m_instance = NULL;
			}
		}
	};

private:
	MyCAS(){}
	static MyCAS* m_instance;
};

MyCAS* MyCAS::m_instance = nullptr;
MyCAS* MyCAS::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new MyCAS();
		static CCarhuishou c1;
	}
	return m_instance;
}


void main()
{
	MyCAS *ptr = MyCAS::getInstance();
}

2. 单例设计模式共享数据问题分析、解决
// 面临的问题:需要在我们自己创建的线程（而不是主线程）中创建MyCAS对象的实例，这种线程可能不止2个
// getInstance()成员函数需要互斥

mutex resource_mutex; // 定义互斥量
// version_0:效率太低，线程过多。为了解决临界问题，使得太多的线程等待。
MyCAS* MyCAS::getInstance()
{
	unique_lock<mutex> mymutex(resource_mutex); // 自动加锁，自动解锁
	if (m_instance == nullptr)
	{
		m_instance = new MyCAS();
		static CCarhuishou c1;
	}
	return m_instance;
}
// version_1:双重检查
MyCAS* MyCAS::getInstance()
{
	// 如果m_instance不为空，则表示m_instance已经被new过了 
	// 如果m_instance为空，不代表m_instance一定没被new过
	if (m_instance != nullptr) 
	{ 
		unique_lock<mutex> mymutex(resource_mutex); // 自动加锁，自动解锁
		if (m_instance == nullptr)
		{
			m_instance = new MyCAS();
			static CCarhuishou c1;
		}
	}
	
	return m_instance;
}


void mythread()
{
	MyCAS *pa = MyCAS::getInstance();
}
void main()
{
	thread obj1(mythread);
	thread obj2(mythread);

	obj1.join();
	obj2.join();
}

3. call_once(, function_name) // C++11
// call_once功能是能够保证函数a()只被调用一次
// 具备互斥量这种能力，而且效率上比互斥量消耗的资源更少
// call_once()需要与一个标记使用。即once_flag，其实once_flag是一个结构
// call_once()就是通过这个标记来决定对应的函数function_name是否执行。调用call_once之后，call_once就将这个标记设置为一种已调用状态
// 后续再次调用call_once(),只要once_flag被设置为“已调用”，那么该函数就不会再被调用


std::once_flag g_flag;
void mythread()
{
	MyCAS *pa = MyCAS::getInstance();
}

class MyCAS
{
public:
	static void createInstance() // 只被调用一次
	{
		chrono::microseconds dura(20000); // 20s
		thread::sleep_for(dura);
		m_instance = new MyCAS();
	}

	static MyCAS *getInstance()
	{
		
		std::call_once(g_flag, createInstance); // 两个线程同时执行到这里。其中一个线程要等另一个线程执行完毕createInstance

		return m_instance;
	}
private:
	MyCAS() {}
	static MyCAS* m_instance;
};
MyCAS* MyCAS::m_instance = nullptr;

void main()
{
	thread obj1(mythread);
	thread obj2(mythread);

	obj1.join();
	obj2.join();
}

