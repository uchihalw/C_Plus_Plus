/*
 * @file   3.Inheritance with virtual functions.cpp
 * @date   2019.2.22.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
1.non-virtual函数:你不希望drived class 重新定义(override,覆盖)它。
	int objectID() const;
	非虚函数的效率比虚函数稍高，但不具备动态联编功能。

2.virtual函数:你希望derived class 重新定义它，且你对它已有默认定义。
	virtual void erroe(const string& msg);
	1.编译器处理虚函数的方法是:给每个对象添加一个隐藏成员。隐藏成员中保存了一个指向函数地址数组的指针。这种数组称为虚函数表。
	  虚函数表中存储了为类对象进行声明的虚函数的地址。
	  eg:
		基类对象包含一个指针，该指针指向基类中所有虚函数的地址表。
		派生类对象将包含一个指向独立地址表的指针。
		如果派生类提供了虚函数的重新定义，该虚函数将保持新函数的地址。
		如果派生类没有重新定义虚函数，该虚函数表将保存函数原始版本的地址。
		如果派生类定义了新的虚函数，则该函数的地址将被添加到vtbl中。
		注意，无论类中包含的虚函数是1还是10，都只需要在对象中添加1个地址成员，只是表的大小不同而已。

	2.调用虚函数时，程序将查看存储在对象中的vtbl地址，然后转向相应的函数地址表。
	  如果使用类声明中定义的第一个虚函数，则程序将使用数组中的第一个函数地址。
	  如果使用类声明中定义的第三个虚函数，程序将使用地址为数组中第三个元素的函数

	3.虚函数的成本
	  1.每个对象都将增大，增大量未存储地址的空间
	  2.对于每个类，编译器都创建一个虚函数地址表
	  3.对于每个函数的调用，都需要执行一项额外的操作，即到表中查找地址


	4.虚函数需要注意的事项
	  1.构造函数不是虚函数
		创建派生类对象时，将调用派生类的构造函数，而不是基类的构造函数，然后，派生类的构造函数将使用基类的一个构造函数
		这种顺序不同于继承机制。因此，派生类不继承基类的构造函数，故声明构造函数为虚函数没什么意义。
	  2.析构函数应当是虚函数，除非类不用做基类

	  3.友元不能是虚函数，因为友元不是类成员，而只有成员才能是虚函数
	
	  4.没有重新定义，如果派生类没有重新定义函数，将使用该函数的基类版本


	  5.重新定义将隐藏方法
		class Dwelling { public: virtual void show(int a); };
		class Hovel:public Dwelling { public: virtual void show(); };
		Hovel hove;
		hove.show();  // valid
		hove.show(5); // invalid

		1.重新定义不会生成函数的两个重载版本，而是隐藏了解接受一个int参数的基类版本。
		总之，重新定义继承的方法并不是重载，如果在派生类中重新定义函数，将不是使用相同的函数特征覆盖基类声明，而是隐藏同名的基类方法。
		2.如果重新定义继承的方法，应确保与原来的原型完全相同，但如果返回类型时基类引用或指针
		  则可以修改为指向派生类的引用或指针。此特性为返回类型协变(允许返回类型随类类型的变化而变化)
		  class Dwelling { public: virtual Dwelling& show(); };
		  class Hovel :public Dwelling { public: virtual Hovel& show(); };

	


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