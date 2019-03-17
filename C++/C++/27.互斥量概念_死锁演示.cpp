/*
 * @file   27.����������_������ʾ.cpp
 * @date   2019.3.17.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
#include<mutex>
class A
{
public:
	// ���յ�����Ϣ���������뵽һ�����е��߳�
	void inMsgRecvQueue()
	{
		for (int i = 0; i < 100000; i++)
		{
			cout << "inMstRecvQueue, insert a element" << i << endl;
			my_mutex.lock();
			msgRecvQueue.push_back(i); // ��������i�����յ���������ֱ��Ū����Ϣ������ȥ
			my_mutex.unlock();
		}
	}

	bool outMsgLULProc(int &command)
	{
		my_mutex.lock();
		if (!msgRecvQueue.empty())
		{
			// ��Ϣ���в�Ϊ��
			int command = msgRecvQueue.front();// ���ص�һ��Ԫ�أ����ǲ����Ԫ���Ƿ����
			msgRecvQueue.pop_front();// �Ƴ���һ��Ԫ�أ����ǲ�����
		   
			my_mutex.unlock();
			return true;
		}
		my_mutex.unlock();
		return false;
	}

	// �����ݴ���Ϣ����ȡ�����߳�
	void outMsgRecvQueue()
	{
		int command = 0;
		for (int i = 0; i < 100000; i++)
		{

			bool result = outMsgLULProc(command);
			if (result)
			{
				cout << "ȡ��һ��Ԫ�سɹ�" << endl;
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
	mutex my_mutex;//����һ��������
};
void main()
{
	A myobj;
	thread myOutMsg(&A::outMsgRecvQueue, &myobj); // �ڶ������������ã����ܱ�֤�߳���ʹ�õĶ�����obj,����������ã�thread�Ὣmyobj����һ��
	thread myInMsg(&A::inMsgRecvQueue, &myobj);

	myInMsg.join();
	myOutMsg.join();
}
0. �������Ļ�������
	���������Ǹ����������һ����ͷ������̳߳�����lock()��Ա���������������ͷ��
	ֻ��һ���߳̿��������ɹ�(�ɹ��ı��־��lock()��������)
	���û���ɹ�����ô�̵߳�ִ�����̾Ϳ���lock()���ﲻ�ϵĳ���ȥ�������ͷ

1. ���������÷�
	��lock()�������������ݣ���unlock()
	lock()��unclock()Ҫ�ɶ�ʹ��
	Ϊ�˷�ֹ�������unlock(),����һ��lock_guard����ģ�壬��������unlock()��ʱ������unlock()
	lock_guard��ģ�壺ֱ��ȡ��lock()��unlock()��
					 Ҳ����������lock_guard֮���ٲ���ʹ��lock()��unlock()

	lock_guard�Ĺ��캯����ִ����lock()��lock_guard()������������ִ����unlock()������ֻ��return��ʱ���ִ�У���Ҳ����ͨ��������ʹ��������ǰִ��
	bool outMsgLULProc(int &command)
	{
		lock_guard<mutex> sbguard(my_mutex);
		if (!msgRecvQueue.empty())
		{
			// ��Ϣ���в�Ϊ��
			int command = msgRecvQueue.front();// ���ص�һ��Ԫ�أ����ǲ����Ԫ���Ƿ����
			msgRecvQueue.pop_front();// �Ƴ���һ��Ԫ�أ����ǲ�����

			//my_mutex.unlock();
			return true;
		}
		//my_mutex.unlock();
		return false;
	}


2. ����
	��������������������ͷҲ�����������������ܲ�����
	����(JinLock)������(YinLock)
	/*
	�����߳�A��B
		1.�߳�Aִ�е�ʱ�����߳������������ѽ���lock()�ɹ��ˣ�Ȼ����ȥlock()����
			// �������������л�
		2.�߳�Bִ�У�����߳�����������Ϊ������û�б���������������lock()�ɹ����߳�BҪȥlock()����
			// ��ʱ�����Ͳ�����
		
	*/


	0.��������Ľ��:ֻҪ���õĶ����������˳�򱣳�һ�¾���
	// unlock()��˳������ν
	void inMsgRecvQueue()
	{
		for (int i = 0; i < 100000; i++)
		{
			cout << "inMstRecvQueue, insert a element" << i << endl;
			my_mutex1.lock();
			my_mutex2.lock();
			msgRecvQueue.push_back(i); // ��������i�����յ���������ֱ��Ū����Ϣ������ȥ
			my_mutex1.unlock();
			my_mutex2.unlock();
		}
	}

	bool outMsgLULProc(int &command)
	{
		my_mutex1.lock();
		my_mutex2.lock();
		if (!msgRecvQueue.empty())
		{
			// ��Ϣ���в�Ϊ��
			int command = msgRecvQueue.front();// ���ص�һ��Ԫ�أ����ǲ����Ԫ���Ƿ����
			msgRecvQueue.pop_front();// �Ƴ���һ��Ԫ�أ����ǲ�����

			my_mutex1.unlock();
			my_mutex2.unlock();
			return true;
		}
		my_mutex1.unlock();
		my_mutex2.unlock();
		return false;
	}

	1.std::lock()����ģ��:����������������
		һ����ס���������������ϵĻ�����(����������1������)
		��������Ϊ�ڶ���߳��У���Ϊ����˳��������������
		std::lock():�������������һ��û��ס��������������ţ������л���������ס������������(����)
		// Ҫô��������ס��Ҫô������û��ס�����ֻ����һ��������һ��û���ɹ�����ô���������Ѿ���ס�Ľ���
	void inMsgRecvQueue()
		{
			for (int i = 0; i < 100000; i++)
			{
				cout << "inMstRecvQueue, insert a element" << i << endl;
				std::lock(my_mutex1, my_mutex2); // �൱��ÿ����������������.lock()
				msgRecvQueue.push_back(i); // ��������i�����յ���������ֱ��Ū����Ϣ������ȥ
				my_mutex1.unlock();
				my_mutex2.unlock();
			}
		}


	2.std::lock_guard��std::adopt_lock����,�������Ҫ�Լ�unlock()����
	// adopt_lock�Ǹ��ṹ�����һ���������:
	// ����:��ʾ����������Ѿ�lock()
	// ����Ҫ��lock_guard���캯�������mutex�����ٴν���lock()
	void inMsgRecvQueue()
	{
		for (int i = 0; i < 100000; i++)
		{
			cout << "inMstRecvQueue, insert a element" << i << endl;
			std::lock(my_mutex1, my_mutex2); 
			lock_guard<mutex> sbguard1(my_mutex1��std::adopt_lock()); // adopt_lock������lock_guard��lock()����
			lock_guard<mutex> sbguard2(my_mutex2��std::adopt_lock());

			msgRecvQueue.push_back(i); // ��������i�����յ���������ֱ��Ū����Ϣ������ȥ

		}
	}





