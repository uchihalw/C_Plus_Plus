/*
 * @file   22.������.cpp
 * @date   2019.3.13.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0. template<typename T, typename F>
T use_f(T v, F f)
{
	static int cnt = 0;
	return f(v);
}
class Fp 
{
private:
	double z;
public:
	Fp(double zz = 1.0) :z(zz) {}
	double operator()(double p) { return z * p; }
};
double dub(double x) { return 1.0 * x; }


/*
�������ж�ģ�����F�����ͣ�use_f(y, dub);
	0.��������ָ�룬��˲���F������Ϊdouble(*)(double):һ��ָ�������ĺ�����ָ�롣��������һ��double����������һ��doubleֵ
*/


1.�ɱ����ģ��:�ɽ��ܿɱ������Ĳ���
	0. ģ�������
		template<typename T>
		void show_1(T value) { cout << value; }
	1. ����������
		template<typename... Args>                 // Args��һ��ģ�����������args��һ��������������Tֻ��һ������ƥ�䣬��Args����������������ƥ��
		void show_2(Args... args) { ... }
		show_2(2, 3, 4, "string", 8.0);
	2. չ��������
		�ɽ�ʡ�Ժŷ��ں��������������ұߣ�������չ��
		template<typename... Args>                
		void show_3(Args... args) { show_3(args...); }
		show_3(2, 3, 4, "string", 8.0);// show_3(args...) ��չ��Ϊ show_3(2, 3, 4, "string", 8.0);
		// args...չ��Ϊһ�����������б�
		// ���Ǹú���������ԭʼ����������ͬ���������ʹ����ͬ�Ĳ������ϵ����Լ����������޵ݹ飨�˴�����ȱ�ݣ�
	3. �ڿɱ����ģ�庯����ʹ�õݹ�
		0. ������������չ�������б�ĵ�һ����д����ٽ����µ����ݴ��ݸ��ݹ���ã��Դ����ƣ�ֱ���б�Ϊ��.
		void show_4() {}// definition for 0 paramsters ---teminating call
		template<typename T, typename... Args>
		void show_4(T value, Args... args) 
		{ 
			cout << value << endl;
			show_4(args...); 
		}
		show_4(4, "string", 8.0);
		