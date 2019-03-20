/*
 * @file   29.�������ģʽ�������ݷ���.cpp
 * @date   2019.3.20.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
1. ���ģʽ���̸
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

2. �������ģʽ��������������������
// ���ٵ�����:��Ҫ�������Լ��������̣߳����������̣߳��д���MyCAS�����ʵ���������߳̿��ܲ�ֹ2��
// getInstance()��Ա������Ҫ����

mutex resource_mutex; // ���廥����
// version_0:Ч��̫�ͣ��̹߳��ࡣΪ�˽���ٽ����⣬ʹ��̫����̵߳ȴ���
MyCAS* MyCAS::getInstance()
{
	unique_lock<mutex> mymutex(resource_mutex); // �Զ��������Զ�����
	if (m_instance == nullptr)
	{
		m_instance = new MyCAS();
		static CCarhuishou c1;
	}
	return m_instance;
}
// version_1:˫�ؼ��
MyCAS* MyCAS::getInstance()
{
	// ���m_instance��Ϊ�գ����ʾm_instance�Ѿ���new���� 
	// ���m_instanceΪ�գ�������m_instanceһ��û��new��
	if (m_instance != nullptr) 
	{ 
		unique_lock<mutex> mymutex(resource_mutex); // �Զ��������Զ�����
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
// call_once�������ܹ���֤����a()ֻ������һ��
// �߱���������������������Ч���ϱȻ��������ĵ���Դ����
// call_once()��Ҫ��һ�����ʹ�á���once_flag����ʵonce_flag��һ���ṹ
// call_once()����ͨ����������������Ӧ�ĺ���function_name�Ƿ�ִ�С�����call_once֮��call_once�ͽ�����������Ϊһ���ѵ���״̬
// �����ٴε���call_once(),ֻҪonce_flag������Ϊ���ѵ��á�����ô�ú����Ͳ����ٱ�����


std::once_flag g_flag;
void mythread()
{
	MyCAS *pa = MyCAS::getInstance();
}

class MyCAS
{
public:
	static void createInstance() // ֻ������һ��
	{
		chrono::microseconds dura(20000); // 20s
		thread::sleep_for(dura);
		m_instance = new MyCAS();
	}

	static MyCAS *getInstance()
	{
		
		std::call_once(g_flag, createInstance); // �����߳�ͬʱִ�е��������һ���߳�Ҫ����һ���߳�ִ�����createInstance

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

