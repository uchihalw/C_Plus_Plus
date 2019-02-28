/*
 * @file   3.Inheritance with virtual functions.cpp
 * @date   2019.2.22.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
1.non-virtual����:�㲻ϣ��drived class ���¶���(override,����)����
	int objectID() const;
	���麯����Ч�ʱ��麯���Ըߣ������߱���̬���๦�ܡ�

2.virtual����:��ϣ��derived class ���¶������������������Ĭ�϶��塣
	virtual void erroe(const string& msg);
	1.�����������麯���ķ�����:��ÿ���������һ�����س�Ա�����س�Ա�б�����һ��ָ������ַ�����ָ�롣���������Ϊ�麯����
	  �麯�����д洢��Ϊ���������������麯���ĵ�ַ��
	  eg:
		����������һ��ָ�룬��ָ��ָ������������麯���ĵ�ַ��
		��������󽫰���һ��ָ�������ַ���ָ�롣
		����������ṩ���麯�������¶��壬���麯���������º����ĵ�ַ��
		���������û�����¶����麯�������麯�������溯��ԭʼ�汾�ĵ�ַ��
		��������ඨ�����µ��麯������ú����ĵ�ַ������ӵ�vtbl�С�
		ע�⣬�������а������麯����1����10����ֻ��Ҫ�ڶ��������1����ַ��Ա��ֻ�Ǳ�Ĵ�С��ͬ���ѡ�

	2.�����麯��ʱ�����򽫲鿴�洢�ڶ����е�vtbl��ַ��Ȼ��ת����Ӧ�ĺ�����ַ��
	  ���ʹ���������ж���ĵ�һ���麯���������ʹ�������еĵ�һ��������ַ��
	  ���ʹ���������ж���ĵ������麯��������ʹ�õ�ַΪ�����е�����Ԫ�صĺ���

	3.�麯���ĳɱ�
	  1.ÿ�����󶼽�����������δ�洢��ַ�Ŀռ�
	  2.����ÿ���࣬������������һ���麯����ַ��
	  3.����ÿ�������ĵ��ã�����Ҫִ��һ�����Ĳ������������в��ҵ�ַ


	4.�麯����Ҫע�������
	  1.���캯�������麯��
		�������������ʱ��������������Ĺ��캯���������ǻ���Ĺ��캯����Ȼ��������Ĺ��캯����ʹ�û����һ�����캯��
		����˳��ͬ�ڼ̳л��ơ���ˣ������಻�̳л���Ĺ��캯�������������캯��Ϊ�麯��ûʲô���塣
	  2.��������Ӧ�����麯���������಻��������

	  3.��Ԫ�������麯������Ϊ��Ԫ�������Ա����ֻ�г�Ա�������麯��
	
	  4.û�����¶��壬���������û�����¶��庯������ʹ�øú����Ļ���汾


	  5.���¶��彫���ط���
		class Dwelling { public: virtual void show(int a); };
		class Hovel:public Dwelling { public: virtual void show(); };
		Hovel hove;
		hove.show();  // valid
		hove.show(5); // invalid

		1.���¶��岻�����ɺ������������ذ汾�����������˽����һ��int�����Ļ���汾��
		��֮�����¶���̳еķ������������أ�����������������¶��庯����������ʹ����ͬ�ĺ����������ǻ�����������������ͬ���Ļ��෽����
		2.������¶���̳еķ�����Ӧȷ����ԭ����ԭ����ȫ��ͬ���������������ʱ�������û�ָ��
		  ������޸�Ϊָ������������û�ָ�롣������Ϊ��������Э��(�����������������͵ı仯���仯)
		  class Dwelling { public: virtual Dwelling& show(); };
		  class Hovel :public Dwelling { public: virtual Hovel& show(); };

	


3.pure virtual����: ��ϣ��derived class һ��Ҫ�������������û��Ĭ�϶��塣
	virtual void draw() const = 0;
4.Delegation ��һ�ֻ��ƣ�������ģʽ��
	1.Delegation��һ��ʵ�ֻ��ƣ�һ������ת������ί��һ���������һ�����󡣱�ί�е�һ��(delegate)��ԭ�ȵĶ���������
	2.Delegation����ʹ���(composition)ʵ�ּ̳�(inheritance)��ʵ�ֵĹ��ܡ�
	3.��Delegation�У�����������������Ĵ����й�:��������Ķ��󽫲���ί�и������˾��������游�ദ����������


5.Delegation(ί��) + Inheritance(�̳�),�����ڹ۲���ģʽ
// Subject �� Observer �Ĺ�ϵΪ:1�Զ�
// Observer(����)��ӵ��һ��update(����)��[ObserverA. ObserverB. ObserverC]��ͬ����Ĳ��ˡ�Subject(��ʿ)���ݲ�ͬ�Ĳ���ִ�в�ͬ��update(����)����
class Observer //������Ա��̳У��������ഴ�������Ժ󣬶����ԷŽ�Subject���е�m_views�����С�
{
public:
	virtual void updata(Subject* sub);
};
class ObserverA :public Observer
{
public:
	virtual void updata(Subject* sub) {}
};
class ObserverB :public Observer
{
public:
	virtual void updata(Subject* sub) {}
};
class ObserverC :public Observer
{
public:
	virtual void updata(Subject* sub) {}
};

class Subject
{
private:
	int m_value;
	vector<Observer*> m_views;
public:
	void attach(Observer* obs) 
	{
		m_views.push_back(obs);
	}
	void set_val(int value)
	{
		m_value = value;
		notify();
	}
	void notify()
	{
		for (int i = 0; i < m_views.size(); ++i)
			m_views[i]->updata(this, m_value);
	}
};