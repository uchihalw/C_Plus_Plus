/*
 * @file   15.non-explicit-one-argument ctor.cpp
 * @date   2019.3.6.
 * @author GBW
 * @Description: ֻҪһ��ʵ�ξ͹���
 
 * @Note:
 
 */
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
	int m_numerator; // ����
	int m_denominator; // ��ĸ
};

Fraction f(3, 5);
double d2 = f + 4; // ���� non-explicit ctor �� 4ת��ΪFraction(4,1),Ȼ�����operator+


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
	int m_numerator; // ����
	int m_denominator; // ��ĸ
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
	int m_numerator; // ����
	int m_denominator; // ��ĸ
};

Fraction f(3, 5);
double d2 = 4 + f; // [Error] conversion from double to Fraction requested