/*
 * @file   11.static和类模板和函数模板.cpp
 * @date   2019.2.28.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
1.static
class Account
{
public:
	static double m_rate;
	static void set_rate(const double& x) { m_rate = x; }
};
double Account::m_rate = 8.0;
void main()
{
	Account::set_rate(5.0);
	Account acc;
	acc.set_rate();
}
调用static函数的方法：
	1.通过object调用
	2.通过class name调用

2.Singleton
// version_1:当外界没人需要用到A，但是a仍然存在，有点浪费。
class A {
public:
	static A& getInstance() { return A; }
private:
	A();
	A(const A& rhs);
	static A a;
};

// version_2:只有当有人调用getInstance的时候，a才会存在。当离开getInstance的时候，a仍然存在。
class A {
public:
	static A& getInstance();
private:
	A();
	A(const A& rhs);
};
A& A::getInstance()
{
	static A a;
	return a;
}

3.类模板
template<typename T>
class complex
{
public:
	complex(T r = 0, T i = 0)
		:re(r), im(i)
	{}

	complex& operator+=(const complex&);
	T real() const { return re; }
	T imag() const { return im; }
private:
	T re, im;
};
void main()
{
	complex<double> c1(2.0, 1.0);
	complex<int> c2(2, 1);
}

4.函数模板
template<class  T> // class == typename
inline
const T& min(const T& a, const T& b)
{
	return b < a ？ b : a;
}
void main()
{
	min(3, 5);
}