/*
 * @file   15.non-explicit-one-argument ctor.cpp
 * @date   2019.3.6.
 * @author GBW
 * @Description: 只要一个实参就够了
 
 * @Note:
 
 */



0.构造函数虽然有two parameters（两个形参），但只有one argument，且构造函数前面没有explicit，所以叫做non - explicit - one - argument constructor。

// version_1
class Fraction
{
public:
	Fraction(int num, int den = 1)
		:m_numerator(num), m_denominator(den) {}

	Fraction operator+(const Fraction &f)
	{
		return Fraction(......);
	}

private:
	int m_numerator; // 分子
	int m_denominator; // 分母
};

Fraction f(3, 5);
double d2 = f + 4; // 调用 non-explicit ctor 将 4转换为Fraction(4,1),然后调用operator+


// version_2
class Fraction
{
public:
	Fraction(int num, int den = 1)
		:m_numerator(num), m_denominator(den) {}

	Fraction operator+(const Fraction &f)
	{
		return Fraction(......);
	}

	operator double() const {
		return (double)(m_numerator / m_denominator);
	}


private:
	int m_numerator; // 分子
	int m_denominator; // 分母
};

Fraction f(3, 5);
double d2 = 4 + f; // [Error] ambiguous


// version_3
class Fraction
{
public:
	explicit Fraction(int num, int den = 1)
		:m_numerator(num), m_denominator(den) {}

	Fraction operator+(const Fraction &f)
	{
		return Fraction(......);
	}

	operator double() const {
		return (double)(m_numerator / m_denominator);
	}


private:
	int m_numerator; // 分子
	int m_denominator; // 分母
};

Fraction f(3, 5);
double d2 = 4 + f; // [Error] conversion from double to Fraction requested
// 由于在构造函数前面增加了explicit关键字，所以不能将4转换成Fraction类型；也不能先将f转换成double类型，与4相加后再将double转换成Fraction。