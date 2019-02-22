/*
 * @file   3.Inheritance with virtual functions.cpp
 * @date   2019.2.22.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
1.non-virtual����:�㲻ϣ��drived class ���¶���(override,����)����
	int objectID() const;
2.virtual����:��ϣ��derived class ���¶������������������Ĭ�϶��塣
	virtual void erroe(const string& msg);
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