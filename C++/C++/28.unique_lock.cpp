/*
 * @file   28.unique_lock.cpp
 * @date   2019.3.18.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
1. unique_lock ȡ�� lock_guard
	0. unique_lock�Ǹ���ģ�壬�����У�һ��lock_guard���Ƽ�ʹ�ã�
	1. lock_guard ȡ����mutex��lock()��unlock()
	2. unique_lock��lock_guard���ܶ࣬Ч���ϲ�һ�㣬�ڴ�ռ�ö�һ�� 

bool outMsgLULProc(int &command)
{
	unique_lock<mutex> sbguard(my_mutex);
	//lock_guard<mutex> sbguard(my_mutex);
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

2. unique_lock�ĵڶ�������
	0. lock_guard���Դ��ڶ�������
	// lock_guard<mutex> guard(mu_mutex, adopt_lock);
	1.adopt_lock:��ʾ�������Ѿ���lock���ʱ���ѻ�������ǰlock������ᱨ�쳣
	// ������÷��߳��Ѿ�ӵ���˻��������Ȩ(�Ѿ�lock�ɹ���)���ſ���ʹ��adopt_lock
	// ֪ͨlock_guard��Ҫ�ڹ��캯����lock���������
	// unique_lockҲ���Դ�adopt_lock��ǣ�������ͬ
	/* 
		std::chrono::milliseconds dura(20000) // 20s
		this_thread::sleep_for(dura)
	*/
	2.try_to_lock
	// ������mutex��lock����ȥ�������mutex,�����û�������ɹ�����Ҳ���������أ�����������������
	// try_to_lock��ǰ�������Լ�������ȥlock
	bool outMsgLULProc(int &command)
	{
		// lock()��������ǰlock
		unique_lock<mutex> sbguard(my_mutex, try_to_lock);
		if (my_mutex.owns_lock())
		{ // �ɹ��õ��� }
		else
		{ }
		//lock_guard<mutex> sbguard(my_mutex);
		if (!msgRecvQueue.empty())
		{
			// ��Ϣ���в�Ϊ��
			int command = msgRecvQueue.front();// ���ص�һ��Ԫ�أ����ǲ����Ԫ���Ƿ����

			return true;
		}
		//my_mutex.unlock();
		return false;
	}

	3. defer_lock
	// ��defer_lock��ǰ�����㲻���Լ�ȥ��lock,����ᱨ�쳣
	// ��˼���ǲ�û�и�mutex��������ʼ����һ��û�м�����mutex
	unique_lock<mutex> sbguard(my_mutex, defer_lock);
	sbguard.lock(); // �����Լ�unlock
	// ���������
	sbguard.unlock(); // ��ס֮�������һ�㣬ϣ��unlock��ȥ����һЩ�ǹ������
	// ����ǹ������
	sbguard.lock();
	// ���������

3. unique_lock�ĳ�Ա����
	0. unlock,����
	1. lock������
	2. try_lock��// ���Լ������ɹ�����true,����������
	3. release,//�������������mutex����ָ�룬���ͷ�����Ȩ��Ҳ����˵�����unique_lock��mutex��������ϵ
	// ���ԭ��mutex�����ڼ���״̬���������νӹܹ������������
	bool outMsgLULProc(int &command)
	{
		// lock()��������ǰlock
		unique_lock<mutex> sbguard(my_mutex);
		mutex *ptx = sbguard.release(); // ptx�ӹܹ��������������Լ�����

		// ��Ϣ���в�Ϊ��
		int command = msgRecvQueue.front();// ���ص�һ��Ԫ�أ����ǲ����Ԫ���Ƿ����

		ptx->unlock();
		
		return false;
	}
	4.Ϊʲô��ʱ����Ҫunlock()����Ϊlock��ס�Ĵ���Խ�٣�ִ��Խ�죬������������Ч��Խ��
	 // ��ͷ��ס�Ĵ���Ķ��٣���Ϊ��������
	 // ����̫ϸ�����״����������
	 // ����̫�֣����׽���Ч��

4. unique_lock��ֵ���� // ��Ҫ��ͬһ��mutex�������unique_lock
unique_lock<mutex> sbguard(my_mutex); 
// sbguardӵ��my_mutex������Ȩ
// sbguard���Խ��Լ�������Ȩת�Ƹ�����unique_lock����
// unique_lock�������mutex������Ȩ�����ڿ���ת�ƣ����ǲ��ܸ���
	unique_lock<mutex> sbguard1(my_mutex);
	unique_lock<mutex> sbguard2(sbguard1);  // �������ܸ���
	unique_lock<mutex> sbguard2(move(sbguard1)); // �൱��sbguard2��my_mutex�󶨵�һ���ˣ�����sbguard1ָ��գ�sbguard2ִ��my_mutex

	class A
	{
	public:
		unique_lock<mutex> rtn_unique_lock()
		{
			unique_lock<mutex> tmpguard(my_mutex1);
			return tmpguard;
		}
	private:
		mutex my_mutex1;
	}