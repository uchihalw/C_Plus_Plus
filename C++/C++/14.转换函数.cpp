/*
 * @file   14.ת������.cpp
 * @date   2019.3.6.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0. ת������:����������У�ͨ��ָ���ؼ���operator������������ת����Ŀ�����ͺ����ǾͿ�������ת��������
	1.operator type()
	2.ת�����������ǳ�Ա������������������ָ���������ͺͲ����б�
	3.���ת������û�����Ա�����޸ģ������ں�������������const�ؼ��֣����Ӵ���Ľ�׳��
	4.ת���������෽����ζ��:����Ҫͨ������������ã��Ӷ���֪����Ҫת����ֵ�����Ժ�������Ҫ����


class Fraction
{
public:
	Fraction(int num, int den = 1)
		:m_numerator(num),m_denominator(den){}


	/*
	0.���κ�ʱ��Fraction������ת��Ϊdouble
	1.ת�������������в���
	2.����ֵ����Ϊdouble,����C++����д�������ͣ���Ϊ�����Ѿ�д�ˡ���������Ϊ���������double
	3.ת������ı�class�еı������ʼ���const
	*/
	operator double() const {
		return (double)(m_numerator / m_denominator);
	}
private:
	int m_numerator; // ����
	int m_denominator; // ��ĸ
};

Fraction f(3, 5);
double d = f + 4; // ����operator double()��fת��Ϊ0.6
������:
	1.�����Ƿ��к���������4+fͨ����
	2.�ܲ��ܽ�fת��Ϊdouble,��ȥ������û����ƺ�����Fraction ת��Ϊ double
	3.��һ�������Ȳ���Fraction�Ƿ������ز����� operator + (double, Fraction) �ĺ���������û�У����Ե��û�ת������operator double() const��