/*
 * @file   33.atomic��̸_async����.cpp
 * @date   2019.3.22.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
1. ԭ�Ӳ���atomic��̸
һ��atomicԭ�Ӳ��������++��--��+=��&=��|=��=��֧�ֵģ������Ŀ��ܲ�֧��

std::atomic<int> g_mycout_atomic = 0; //�൱�ڷ�װ��һ������Ϊint�Ķ��󣻿��������intһ������atomic
void mythread() //�߳���ں��� // 7s
{
	for (int i = 0; i < 100000; i++)
	{
		g_mycout_atomic++; // ��Ӧ�Ĳ�����ԭ�Ӳ��������ᱻ���
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

2. async����̸

	0. async������̸��async��������һ���첽����
	launch::deferred :�ӳٵ���
	launch::async : ǿ�ƴ���һ���߳�
	// std::thread() ���ϵͳ��Դ���ţ���ô���ܴ����߳̾ͻ�ʧЧ����ôִ��thread()ʱ����������ܱ���
	// std::async() ����һ���첽����
	// async��thread�����ԵĲ�ͬ������async��ʱ�򲢲��������̡߳�˭����get������˭���ڵ��߳��������߳���ں���
	�������£�
	
		// 0.�����deferred������async��
			future<int> result = async(launch::deferred, mythread);// deferred�ӳٵ��ã������������̣߳��ӳٵ�future�������.get����.wait��ʱ���ִ��mythread.
			���û�е���wait����wait�����ᴴ�����߳�
		// 1.std::launch::async
			future<int> result = async(launch::async, mythread); // ǿ������첽���������߳���ִ�У�ϵͳ���봴�������߳�����mythread()����

		// 2.std::launch::async | std::launch::deferred
			future<int> result = async(std::launch::async | std::launch::deferred, mythread);
			��:��ζ��async����Ϊ�����ǡ��������̲߳�����ִ�С� ���� ��û�д������̲߳��ӳٵ�����.get()�ſ�ʼִ��������ں����������߾���һ

		// 3.�������������ֻ��async����һ����ں�����
			future<int> result = async(mythread); 
			����û��ָ�����������ʱ��Ĭ��ֵӦ���Ƕ���ȡ��һ.��2��Ч��һ�¡�ϵͳ���о��������ĸ�

	1. async��thread������
		0. std::thread() ���ϵͳ��Դ���ţ���ô���ܴ����߳̾ͻ�ʧЧ����ôִ��thread()ʱ����������ܱ���
			// int mythread() { return 1; }
			// thread myobj(mythread);
			// myobj.join();
			// thread�����̵߳ķ�ʽ������̷߳���ֵ��������Ҫͨ��ȫ�ֱ��������õ�
		1. async�����첽���񡣿��ܴ���Ҳ���ܲ������̡߳�async���ú������õ��߳���ں����ķ���ֵ
			// ����ϵͳ��Դ���ƣ�
			// 0.thread�������߳�̫�࣬����ܴ���ʧ�ܣ�ϵͳ�����쳣������
			// 1.��async��һ��Ͳ��ᱨ�쳣Ҳ�����������Ϊ���ϵͳ��Դ���ŵ����޷��������̵߳�ʱ��async���ֲ��Ӷ�������ĵ��þͲ��ᴴ�����߳�
			//   ���Ǻ���˭������result.get()������������ô����첽����thread��������ִ��get�����߳���
			// 2.���ǿ��asyncһ��Ҫ�������̡߳��ͱ���ʹ��launch::async
	2. async��ȷ��������Ľ��
		���Ӷ��������async���ã���ϵͳ���о����Ƿ񴴽����߳�
		����Ľ������� future<int> result = async(mythread);
		����첽���񵽵���û�б��Ƴ�ִ�У�


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