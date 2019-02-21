/*
* @file   0.友元.cpp
* @date   2019.2.21.
* @author GBW
* @Description:

* @Note:
1.友元：友元函数、友元类、友元成员函数
2.在为类重载二元运算符时    <<<<<<带两个参数的运算符>>>>>>     常常需要友元---将Timer对象乘以实数就属于此类情况
在Timer实例中，重载的加法和减法运算都结合两个Timer值，而乘法运算将一个Timer值和一个double值结合，此举限制了该运算符的使用方式。
左侧的操作数是调用对象，即 A = B * 2.5 equal to A = B.operator*( 2.75 )
但是 A = 2.75 * B // cannot correspond to a member function
3.解决2中遗留问题的方法
1.服务器友好-客户警惕的解决方案
2.非成员函数(非成员函数不是由对象调用的，其使用的所有值都是显示参数)
1.A = 2.75 * B equal to Time operator* (doubel m, const Timer &t)
2.非成员函数不能直接访问类的私有数据，然而有一类特殊的非成员函数可以访问类的私有成员，即友元函数。
4.创建友元函数
1.将友元函数原型放在类声明中，并在原型声明前加上关键字friend
friend Time operator* (int m, const Time & t);
2.编写函数定义，因为其不是成员函数，故不要使用 Time:: 限定符。 另外不要在定义中使用关键字friend
Time operator*(int m, const Time & t){....}
3.类的友元函数是非成员函数，其访问权限与成员函数相同。



5.两种重载形式的比较
在多数情况下，将运算符重载为类的成员函数和类的友元函数都可以。但成员函数运算符与友元函数运算符也具有各自的特点：
(1) 一般情况下，单目运算符最好重载为类的成员函数；双目运算符则最好重载为类的友元函数。
(2) 以下一些双目运算符不能重载为类的友元函数：=、()、[]、->。
(3) 类型转换函数只能定义为一个类的成员函数而不能定义为类的友元函数。
(4) 若一个运算符的操作需要修改对象的状态，选择重载为成员函数较好。
(5) 若运算符所需的操作数（尤其是第一个操作数）希望有隐式类型转换，则只能选用友元函数。
(6) 当运算符函数是一个成员函数时，最左边的操作数（或者只有最左边的操作数）必须是运算符类的一个类对象（或者是对该类对象的引用）。如果左边的操作数必须是一个不同类的对象，或者是一个内部类型的对象，该运算符函数必须作为一个友元函数来实现。
(7) 当需要重载运算符具有可交换性时，选择重载为友元函数。
*/


// 创建友元
class Time
{
public:
	Time(int m_Data) :m_Data(m_Data) {}
	Time() {}
	Time operator+ (const Time & timer)
	{
		Time res;
		res.m_Data = this->m_Data + timer.m_Data;
		return res;
	}

	Time operator* (const Time & timer) // call with Time T  = Time * Time
	{
		Time res;
		res.m_Data = this->m_Data * timer.m_Data;
		return res;
	}
	void show()
	{
		cout << this->m_Data << endl;
	}
	friend Time operator* (int m, const Time & timer);
private:
	int m_Data;
};

Time operator*(int m, const Time & timer) // call with Time T = operator*( int, Time t) or Time T = int * Time
{
	Time time;
	time.m_Data = m * timer.m_Data;
	return time;
}