/*
 * @file   32.future������Ա����_atomic.cpp
 * @date   2019.3.22.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0. future��������Ա����
void mythread()
{
	std::chrono::milliseconds dura(5000);  // 5s
	this_thread::sleep_for(dura);
}

void main()
{
	future<int> result = async(mythread);

	int wait_time;
	// wait_for�ȴ�һ��ʱ��
	future_status status = result.wait_for(chrono::seconds(wait_time));

	if (status == future_status::timeout) // wait_time < dura(5000)
	{
		// ��ʾ�̻߳�û��ִ���꣬��ʱ
	}
	else if (status == future_status::ready) // wait_time > dura(5000)
	{
		// ��ʾ�̳߳ɹ�����
		result.get();
	}
	else if (status == future_status::deferred) // �ӳ�
	{
		 // ���async�ĵ�һ������������Ϊlanuch::deferred,����������
		result.get();
	}

}

1. shared_future
// �������̶߳���ʹ��ĳ���̵߳Ľ������shared_future:Ҳ�Ǹ���ģ��
// share_future��get�ǽ�ֵ��������
int mythread(int  mypar)
{
	std::chrono::milliseconds dura(5000);  // 5s
	this_thread::sleep_for(dura);
	return 5;
}
int mythread2(shared_future<int> &tmpf)
int mythread2(future<int> &tmpf) 
{
	auto result = tmpf.get(); // ��ȡֵ��ֻ��getһ�η���ᱨ�쳣��get�൱�ڽ�tmpf�е�ֵ�����ˣ��ٴ�get�ᱨ�쳣
							  // Ϊʲô�ڶ���get���󣬻ᱨ�쳣����Ҫ��Ϊget�����������һ���ƶ����塣
	return 5;
}
void main()
{
	packaged_task<int(int)> mypt(mythread); // �Ѻ���mythreadͨ��packaged_task��װ����
	thread t1(ref(mypt), 1); // �߳�ֱ�ӿ�ʼִ�У��ڶ���������Ϊ�߳���ں����Ĳ���
	t1.join(); // ���ǿ��Ե�������ȴ��߳�ִ����ϣ������������̫�У��ᱼ��

	future<int> result = mypt.get_future(); //  future�����ﺬ���߳���ں���
	bool ifcanget = result.valid(); // true
	shared_future<int> result_s(std::move(result));
	thread t2(mythread2, ref(result| result_s)); // == shared_future<int> result_s(result.share())
	bool ifcanget = result.valid(); // false


	t2.join();// �ȴ��߳�ִ�����

}


2. ԭ�Ӳ���,һ�����ڼ�����ͳ��
	1. ������:���߳��У������������ݡ����������������ݡ�����
	// �������̣߳���һ���������в���������̶߳��ñ���ֵ����һ���߳������������дֵ

	int atomvalue = 5

	// ���߳�A
	int tmpvalue = atomvalue; // atomvalue������Ƕ���߳�֮��Ҫ����ı���

	//д�߳�B
	atomvalue = 6;

	// ԭ�Ӳ����������ɣ�����Ҫ����������(����)�����Ķ��̲߳�����̷�ʽ
	// ԭ�Ӳ��������ڶ��߳��У����ᱻ��ϵĳ���ִ��Ƭ�Σ��� g_mycout++; ԭ�Ӳ������Ȼ�����Ч�ʸ���
	// �������ļ���һ�������һ�������(���д���)����ԭ�Ӳ�����Ե�һ�㶼��һ��������������һ�������

	// ԭ�Ӳ�����һ�㶼��ָ���ɷָ�Ĳ�����Ҳ����˵���ֲ���Ҫô����ɵģ�Ҫô�ǲ���ɵģ�������ְ��Ʒ״̬
	// atd::atomic����ԭ�Ӳ������Ǹ���ģ�塣��ʵatomic�������������װĳ�����͵�ֵ��

// version_0
int g_mycout = 0;
mutex g_my_mutex;
void mythread() //�߳���ں��� // 7s
{
	for (int i = 0;i<100000;i++)
	{
		g_my_mutex lock();
		g_mycout++;
		g_my_mutex unlock();
	}
}

std::atomic<int> g_mycout_atomic = 0; //�൱�ڷ�װ��һ������Ϊint�Ķ��󣻿��������intһ������atomic
void mythread() //�߳���ں��� // 7s
{
	for (int i = 0; i < 100000; i++)
	{

		g_mycout_atomic++; // ��Ӧ�Ĳ�����ԭ�Ӳ��������ᱻ���
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
















