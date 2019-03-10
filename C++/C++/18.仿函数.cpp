/*
 * @file   18.�º���.cpp
 * @date   2019.3.8.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0.  STL�㷨��ʹ�ú�������Ҳ�к�������
	�������ǿ����Ժ�����ʽ��()���ʹ�õ��������
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


// foreachԭ��
template<class InputIterator, class Function>
Function foreach(InputIterator first, InputIterator last, function f);

1. ����������
	1. ������:�ǲ��ò����Ϳ��Ե��õĺ�����
	2. һԪ���� : ����һ�������Ϳ��Ե��õĺ�����
	3. ��Ԫ���� : ���������������Ե��õĺ�����

	// �ṩ��Щ����������Ϊ��֧�ֽ�������Ϊ������STL������


2. �º����ֳ�Ϊ�����Ķ�����һ������ʹ�������ܵ���
	0. Ϊʲô��Ҫһ����ȥ��ʹ��������


// code_0 :
bool LengthLessThanFive(const string & str)
{
	return str.length < 5;
}
int res = cout_if(vec.begin(), vec.end(), LengthLessThanFive);

// code_1: �����Ҫ���ض�����ֵ����Ҳ����Ļ�
bool LengthLessThanFive(const string & str�� int len)
{
	return str.length < len;
}

// ����count_ifҪ����ǣ�������һ����������Ϊ�������һ��Ԫ�أ���������ҵ�code_0 ��code_1�����н������
// ���º���:ͨ��ʹ�ó�Ա��������Ϊ��Ա�������Ժ���Ȼ�ķ��ʳ�Ա����
// code_2:�º���:��������ͨ����һ��������������Ĳ��������ܴ洢���ߴ������������Ҫ����Ϣ��
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
// LengthLessThanThold(length)ͨ��������ʱ�������operator()