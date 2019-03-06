/*
 * @file   14.转换函数.cpp
 * @date   2019.3.6.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
class Fraction
{
public:
	Fraction(int num, int den = 1)
		:m_numerator(num),m_denominator(den){}


	/*
	0.在任何时候Fraction都可以转化为double
	1.转换函数不可以有参数
	2.返回值类型为double,但是C++允许不写返回类型，因为后面已经写了。返回类型为名称里面的double
	3.转换不会改变class中的变量，故加上const
	*/
	operator double() const {
		return (double)(m_numerator / m_denominator);
	}
private:
	int m_numerator; // 分子
	int m_denominator; // 分母
};

Fraction f(3, 5);
double d = 4 + f; // 调用operator double()将f转换为0.6
编译器:
	1.查找是否有函数可以让4+f通过。
	2.能不能将f转换为double,便去查找有没有设计函数将Fraction 转化为 double