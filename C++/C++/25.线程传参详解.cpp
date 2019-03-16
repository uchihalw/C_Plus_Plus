/*
 * @file   25.�̴߳������.cpp
 * @date   2019.3.16.
 * @author GBW
 * @Description: �̴߳�����⣬detach()��ӡ���Ա�������̺߳���
 
 * @Note:
 
 */
0. ������ʱ������Ϊ�̺߳���
	/*
		0. ֻҪ����ʱ�����A�������Ϊ�������ݸ��̣߳���һ���ܹ������߳�ִ�����ǰ���̺߳����ĵڶ������������������Ӷ�
		   ȷ��detach()���߳�Ҳ��ȫ���� 
	*/

	0. Ҫ���������1
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
		/* var��i��ix�ĵ�ַ����� */

		// version_2
		void func(const int &ix, char *buf)
		{
			cout << ix // ����, ix������var�����ã�ʵ����ָ���ݣ����Լ�ʹ���߳�detach�����̣߳���ô���߳��е�ixҲ��������ʹ��
			cout << buf; // ָ����detach���߳�ʱ�����Ի�������
		}
		void main()
		{
			int i = 0;
			int &var = i;
			char buf[] = "hello";
			thread myobj(func,var,buf);
			myobj.detach();
		}
		/* var��i���ĵ�ַ�����, ǰ��������ix�ĵ�ַ����� */

		// version_3
		void func(const int &ix, const strng & str)
		{
			cout << ix // ����, ix������var�����ã�ʵ����ָ���ݣ����Լ�ʹ���߳�detach�����̣߳���ô���߳��е�ixҲ��������ʹ��
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
		/* buf��str�ĵ�ַ����� */

	1. Ҫ���������2
		// version_1
		void func(const int &ix, const strng & str)
		{
			cout << ix // ����, ix������var�����ã�ʵ����ָ���ݣ����Լ�ʹ���߳�detach�����̣߳���ô���߳��е�ixҲ��������ʹ��
			cout << *str; // 
		}
		void main()
		{
			int i = 0;
			int &var = i;
			char buf[] = "hello";
			thread myobj(func, var, string(buf)); // buf����ʲôʱ��ת��string
										          // ��ʵ�ϴ��ڣ�buf����������(main����ִ������)��ϵͳ����bufȥתstring
			myobj.detach();                       // ��ͨ��string������ʱbuf,ֱ�ӽ�bufת����string����
		}
		/* buf��str�ĵ�ַ����� */


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
			thread myobj(func, var, A(5));  // �ڴ����̵߳�ͬʱ������ʱ����ķ������ݲ����ǿ��еģ��˴������һ�ι���Ϳ���
			myobj.detach();                    
		}
	2. �ܽ�
		0. ������int���ּ����͵Ĳ��������鶼��ֵ���ݣ���Ҫ����
		1. �����������󣬱�����ʽ����ת����ȫ�����ڴ����̵߳�ͬʱ��������ʱ��������Ȼ���ڲ�������������������(����������ã������һ�ι��캯�������ο�������)
		2. ���鲻ʹ��detach()��ֻʹ��join()���Ͳ����ھֲ����������̶߳��ڴ�ķǷ���������

1.��ʱ������Ϊ�̲߳���������
	0. �߳�id���������std::this_thread::get_id()����ȡ


2.�������������ָ����Ϊ�̲߳���
	0. ���������
		// version_1
		class A {
		public:
			mutable int _i;
			A(int i) :_i(i) {}
			A(const A& tmp) :_i(tmp._i) {}
			~A() {}
		};
		void func(const A& buf) // ���߳��б������ᰴ�տ������н���
		{
			buf._i = 99;
		}
		void main()
		{
			A a(10);
			thread myobj(func, a); // func()�н�buf._i����Ϊ99�� ����main()��a._i��ȻΪ10
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
		void func(A& buf) // ���߳��б��������ᰴ�տ������н���
		{
			buf._i = 99;
		}
		void main()
		{
			A a(10);
			thread myobj(func, ref(a)); // func()�н�buf._i����Ϊ99�� ����main()��a._iҲ��Ϊ99
			myobj.join();
		}
	1. ��������ָ��
		void func(unique_ptr<int> ptr){}
		void main()
		{
			unique_ptr<int> my(new int(100));
			thread myobj(func, move(my));
			myobj.join();
		}

3. �ó�Ա����ָ�����̲߳���
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