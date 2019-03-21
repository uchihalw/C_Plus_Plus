/*
 * @file   30.condition_variable+wait+notify_one+notify_all.cpp
 * @date   2019.3.21.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0. ��������condition_variable��wait��notify_one():֪ͨһ���߳�



queue msgRecvQueu;
mutex my_mutex;
condition_variable my_cond; // ����һ����������������Ҫ�ͻ��������ʹ��
void inMsgRecvQueue()
{
	for (int i = 0; i< 5; i++)
	{
		unique_lock<mutex> my_mutex(my_mutex);
		msgRecvQueu.push();

		// ����outMsgRecvQueue���ڴ���һ�������Ҫһ��ʱ�䣬�������ڿ���wait()����ȴ��㻽�ѣ���ô��ʱnotify_one()�ĵ���Ҳ��û��Ч��
		my_cond.notify_one(); // ���԰�wait()���̻߳��ѣ�ִ�������У���ôoutMsgRecvQueue�����wait()�ͻᱻ����
	}
}
void outMsgRecvQueue()
{
	int command = 0;
	while (true)
	{
		unique_lock<mutex> my_guard(my_mutex);


		// wait()������һ������
		// ����ڶ�������lambda���ʽ�ķ���ֵ��false,��ôwait()�������������������������С�
		// ����ڶ�������lambda���ʽ�ķ���ֵ��true,��ôwait()ֱ�ӷ���
		// ��ô������ʲôʱ��Ϊֹ���µ�����ĳ���̵߳���notify_one()��Ա����Ϊֹ
		// ���wait()�ĵڶ�������ȱʡ����my_cond.wait(my_guard),��ô�͸��ڶ�������lambda���ʽ����falseЧ��һ������������û�л�ȡ����
		// �������߳���notify_one()����wait()���Ѻ�wait()�Ϳ�ʼ�ָ��ɻ
		// a).wait()���ϵĳ������»�ȡ���������������ȡ����������������wait����ȴ���ȡ�������ȡ��(���ڼ�����)��wait()�ͽ�������ȥ��ִ��b
		// b).��ȡ��������������
			// b1.)���wait�еڶ������������ж����lambda���ʽ��������ʽΪfalse,��ôwait�ֶԻ������������ֿ�ʼ����������ȴ��ٴα�notify����
			// b2.)������ʽΪtrue����ô��������������ʱ�����������š�
			// b3.)���waitû�еڶ�����������ôwait���أ�����������������������������������������������������ȡ����
		my_cond.wait(my_guard, [this] { // һ��lambda����һ���ɵ��ö��󣨺�����
			if (!msgRecvQueu.empty())
				return true;
			return false;
		
		});

		// �����ߵ������������������һ�������ŵġ�ͬʱ����ȷ�� msgRecvQueu ������һ������
		command = msgRecvQueu.front();
		msgRecvQueu.pop();
		my_guard.unlock(); // ��Ҫ�ֶ�������������ס̫��ʱ��

	}
}
A myobj;
thread obj1(&A::outMsgRecvQueue, &myobj);
thread obj3(&A::inMsgRecvQueue, &myobj);


2. notify_all()
A myobj;
thread obj1(&A::outMsgRecvQueue, &myobj);
thread obj2(&A::outMsgRecvQueue, &myobj);
thread obj3(&A::inMsgRecvQueue, &myobj);

// �����notify_one()�᲻ȷ��������һ��inMsgRecvQueue����ֻ�ܼ���һ���߳�
// ��������̶߳���Ҫ�����ѣ���ônotify_all()����ͬʱ���������߳�
