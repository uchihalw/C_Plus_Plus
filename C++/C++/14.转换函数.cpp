/*
 * @file   14.转换函数.cpp
 * @date   2019.3.6.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0. 转换函数:在类的声明中，通过指定关键字operator，并在其后加上转换的目标类型后，我们就可以声明转换函数。
	1.operator type()
	2.转换函数必须是成员函数，它的声明不能指定返回类型和参数列表。
	3.如果转换函数没有类成员进行修改，可以在函数声明中增加const关键字，增加代码的健壮性
	4.转换函数是类方法意味着:它需要通过类对象来调用，从而告知函数要转换的值，所以函数不需要参数


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
double d = f + 4; // 调用operator double()将f转换为0.6
编译器:
	1.查找是否有函数可以让4+f通过。
	2.能不能将f转换为double,便去查找有没有设计函数将Fraction 转化为 double
	3.这一语句会首先查找Fraction是否有重载操作符 operator + (double, Fraction) 的函数，由于没有，所以调用会转换函数operator double() const。