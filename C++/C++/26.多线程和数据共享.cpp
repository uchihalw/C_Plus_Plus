/*
 * @file   26.���̺߳����ݹ���.cpp
 * @date   2019.3.17.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0. �����͵ȴ����߳�
	��������̣߳��߳���ں���ͳһʹ��func.
	����̵߳�ִ��˳��������ģ�������ϵͳ�ڲ����̵߳����е��Ȼ����й�
	���̵߳ȴ��������߳̽�����������߳̽���
void func(int num)
{
	cout << "start " << num << endl;
	cout << "end " << num << endl;
}
void main()
{
	vector<thread> mythread;
	for (int = i = 0; i < 10; i++)
		mythread.push_back(thread(func, i);
	for (auto iter = mythread.begin(); iter != mythread.end(); iter++)
		iter->join();
	cout << "main end" << endl;
}

1. ���ݹ�������
	0. ֻ��������:�ǰ�ȫ�ȶ��ģ�����Ҫ�ر�Ĵ����ֶΣ�ֱ�Ӷ��Ϳ��ԡ�
	1. �ж���д:����ʱ����д��д��ʱ���ܶ�
vector<int> g_v = { 1,2,3 }; // ��������
void func()
{
	cout << this_thread::get_id() << g_v[0] << g_v[1] << g_v[2] << endl;
}
void main()
{
	vector<thread> mythread;
	for (int = i = 0; i < 10; i++)
		mythread.push_back(thread(func, i);
	for (auto iter = mythread.begin(); iter != mythread.end(); iter++)
		iter->join();
	cout << "main end" << endl;
}

2. �������ݵı�����������
	������Ϸ�������������Լ��������̣߳�һ���߳��ռ�������������������д��һ������
									��һ���̣߳��Ӷ�����ȡ����ҷ����������������Ȼ��ִ�������Ҫ�Ķ���
	// ׼���ó�Ա������Ϊ�̺߳����ķ�����д�߳�
	// ������:������̱߳���������������



class A
{
public:
	// ���յ�����Ϣ���������뵽һ�����е��߳�
	void inMsgRecvQueue()
	{
		for (int i = 0; i < 100000; i++)
		{
			cout << "inMstRecvQueue, insert a element" << i << endl;
			msgRecvQueue.push_back(i); // ��������i�����յ���������ֱ��Ū����Ϣ������ȥ
		}
	}

	// �����ݴ���Ϣ����ȡ�����߳�
	void outMsgRecvQueue()
	{
		for (int i = 0; i < 100000; i++)
		{
			if (!msgRecvQueue.empty())
			{
				// ��Ϣ���в�Ϊ��
				int command = msgRecvQueue.front();// ���ص�һ��Ԫ�أ����ǲ����Ԫ���Ƿ����
				msgRecvQueue.pop_front();// �Ƴ���һ��Ԫ�أ����ǲ�����
				//....���Ǵ�������
			}
			else
			{
				cout << "outMsgRecvQueu()ִ�У���Ŀǰ��Ϣ����Ϊ��" << i << endl;
			}
		}
		cout << "END" << endl;
	}
private:
	list<int> msgRecvQueue; // ������ר�����ڴ�����Ҹ����Ƿ��͹���������
};
void main()
{
	A myobj;
	thread myOutMsg(&A::outMsgRecvQueue, &myobj); // �ڶ������������ã����ܱ�֤�߳���ʹ�õĶ�����obj,����������ã�thread�Ὣmyobj����һ��
	thread myInMsg(&A::inMsgRecvQueue, &myobj);

	myInMsg.join();
	myOutMsg.join();
}





















