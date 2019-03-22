/*
 * @file   31.async+future+packaged_task+promise.cpp
 * @date   2019.3.21.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
#include<future>
1.async��future������̨���񲢷���ֵ
// ϣ���̷߳���һ�����
// async�Ǹ�����ģ�壬������һ���첽��������һ���첽����֮�󣬷���һ��future����future��һ�������
// "����һ���첽����":�Զ�����һ���̲߳���ʼִ�ж�Ӧ���߳���ں���������һ��future����
// future�������溬���߳���ں��������صĽ�����̷߳��صĽ����������ͨ������future����ĳ�Ա����get()����ȡ���
// future�ṩ��һ�ַ����첽��������Ļ���(���ǽ������ܲ������������õ�)������˵���������ܲ��������õ���
// ���߳�ִ����ϵ�ʱ������ܹ��õ�����ˣ����future(����)��ᱣ��һ��ֵ���Թ��ڽ���ĳ��ʱ���õ�
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
	std::future<int> result = async(mythread); // future�����async����һ��
	cout << result.get() << endl; // ��������ȴ�mythread()ִ����Ϸ��ؽ�����õ������get���õ�ֵ�Ĳ����ݣ���ֻ�ܵ���һ�Σ����ö�λᱨ�쳣
	result.wait(); // Ҳ�Ῠ������ֻ�ǵȴ��̷߳��أ�û�з���ֵ���е���join,
}

// version_1
// 
/* 
ͨ��������async����һ���������ò�������ʱlaunch����(ö������)�����ﵽһЩ����Ŀ��
	1.launch::deferred:��ʾ�߳���ں������ñ��ӳٵ�future��wait()����get()��������ʱ��ִ��
	  �ӳٵ��ã�����û�д����̣߳��������߳��е��õ��߳���ں���
	  future res = async(launch::deferred, &A::mythred, &a, tmp);
	  ���wait()����get()û�б����ã���ô�̲߳��Ῠ,��Ϊ������û�д�������
	  ���wait()����get()�����ã��̸߳�����û�д�������
	2.launch::async:��ʾ����async������ʱ��Ϳ�ʼ�����̡߳�
	  ����Ҫget����wait�߳̾ͻ��Զ�����
	  ERR:async����Ĭ���õ��������

	3.async|deferred ��������ʹ��

*/

class A {
public:
	int mythread(int x){}
};
void main()
{
	A a;
	int tmp = 10;
	future res = async(&A::mythread, &a,tmp); // �ڶ���������һ�����ã�����������õĻ����ͻ����´���һ��A�������ò��ܱ�֤�߳����õ���ͬһ������
	if (1)
	{
		cout << result.get() << endl; 
	}
	else
	{
		���û��get����waitҲ��ȴ�5s
	}
}

2. packaged_task:������񣬰������װ����
// �Ǹ���ģ�壬����ģ������Ǹ��ֿɵ��ö��󡣷���δ����Ϊ�߳���ں����������
// packaged_task��װ�����Ŀɵ��ö��󻹿���ֱ�ӵ��á�
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
	packaged_task<int(int)> mypt(mythread); // �Ѻ���mythreadͨ��packaged_task��װ����
	thread t1(ref(mypt), 1);                // �߳̿�ʼִ�У��ڶ�����������Ϊ�߳���ں����Ĳ���
	t1.join();                              // �ȴ��߳�ִ�����
	future<int> res = mypt.get_future();    // future������������߳���ں����ķ��ؽ��������result����mythread�ķ��ؽ��
	cout << res.get() << endl;

}

3. promise. ��ģ��
// �ܹ���ĳ���߳��и�����ֵ��Ȼ������������߳��У������ֵȡ������
void mythread(promise<int> &tmpp, int calc)
{
	.....
	std::chrono::milliseconds dura(5000); // 5s
	std::this_thread::sleep_for(dura);
	tmpp.set_value((calc); // ������浽��tmpp������
	return;
}

void mythread2(future<int> &tmpp)
{
	auto res = tmpp.get(); // �߳�2��ʹ���߳�1�е�ֵ
}
void main()
{
	promise<int> mypromise; // ����һ��promise���󡣱����ֵ����Ϊint
	thread t1(mythread, ref(mypromise), 180);
	t1.join(); // �����ʹ��join���ᱨ�쳣

	// ��ȡ���ֵ
	future<int> ful = mypromise.get_future(); // promise��future�󶨡����ڻ�ȡ�̷߳���ֵ

	//int res = ful.get();

	threa t2(mythread2(, ref(ful));
	t2.join();


}


4.С��
������ô�ã�ʲôʱ����