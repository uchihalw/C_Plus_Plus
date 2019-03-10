/*
 * @file   18.仿函数.cpp
 * @date   2019.3.8.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0.  STL算法都使用函数对象，也叫函数符。
	函数符是可以以函数方式与()结合使用的任意对象。
class Linear
{
private:
	double slope;
public:
	Linear(double x) :x(slope) {}
	double operator() (double y) { return x + y; }
};
Linear f1;
Linear f1(10.0);
double x = f1(12.0); // right-hand side is f1.operator()(12.0)


// foreach原型
template<class InputIterator, class Function>
Function foreach(InputIterator first, InputIterator last, function f);

1. 函数符概念
	1. 生成器:是不用参数就可以调用的函数符
	2. 一元函数 : 是用一个参数就可以调用的函数符
	3. 二元函数 : 是用两个参数可以调用的函数符

	// 提供这些函数对象是为了支持将函数作为参数的STL函数。


2. 仿函数又称为函数的对象，是一个能行使函数功能的类
	0. 为什么需要一个类去行使函数功能


// code_0 :
bool LengthLessThanFive(const string & str)
{
	return str.length < 5;
}
int res = cout_if(vec.begin(), vec.end(), LengthLessThanFive);

// code_1: 如果需要将特定的阈值长度也传入的话
bool LengthLessThanFive(const string & str， int len)
{
	return str.length < len;
}

// 但是count_if要求的是（仅带有一个参数）作为它的最后一个元素，所以如何找到code_0 和code_1的折中解决方案
// 即仿函数:通过使用成员变量，因为成员函数可以很自然的访问成员变量
// code_2:仿函数:既能像普通函数一样传入给定数量的参数，还能存储或者处理更多我们需要的信息。
class LengthLessThanThold {
public:
	explicit LengthLessThanThold(int maxLength) :len(maxLength) {}
	bool operator()(const string &str) const {
		return str.length() < len;
	}
private:
	const int len;
};
int res = cout_if(vec.begin(), vec.end(), LengthLessThanThold(length));
// LengthLessThanThold(length)通过创建临时对象调用operator()