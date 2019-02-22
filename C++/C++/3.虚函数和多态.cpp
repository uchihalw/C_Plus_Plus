/*
 * @file   3.Inheritance with virtual functions.cpp
 * @date   2019.2.22.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
1.non-virtual函数:你不希望drived class 重新定义(override,覆盖)它。
	int objectID() const;
2.virtual函数:你希望derived class 重新定义它，且你对它已有默认定义。
	virtual void erroe(const string& msg);
3.pure virtual函数: 你希望derived class 一定要定义它，你对它没有默认定义。
	virtual void draw() const = 0;
4.Delegation 是一种机制，而不是模式。
	1.Delegation是一种实现机制：一个对象转发或者委托一个请求给另一个对象。被委托的一方(delegate)替原先的对象处理请求。
	2.Delegation可以使组合(composition)实现继承(inheritance)所实现的功能。
	3.在Delegation中，有两个对象与请求的处理有关:接受请求的对象将操作委托给代理。此举与子类替父类处理请求类似


5.Delegation(委托) + Inheritance(继承),类似于观察者模式
// Subject 和 Observer 的关系为:1对多
// Observer(病人)都拥有一个update(打针)、[ObserverA. ObserverB. ObserverC]不同种类的病人、Subject(护士)根据不同的病人执行不同的update(打针)操作
class Observer //此类可以被继承，且其子类创建出来以后，都可以放进Subject类中的m_views容器中。
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