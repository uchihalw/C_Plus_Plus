/*
 * @file   17.�쳣.cpp
 * @date   2019.3.8.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */

0. abort() ����ԭ��λ��cstdlib.h || stdlib.h
	�˺�����ֱ����ֹ���򣬶����Ƿ��ص�main().��ʾ�ĳ����쳣�ж���Ϣ�����������
double hmean(double a, double b)
{
	if (a == -b)
	{
		cout << "untenable argu\n" << endl;
		abort();
	}
}
void main()
{
	cout << "start" << endl;
	hmean(3.0, -3.0);
	cout << "end" << endl;

}

1. ���쳣�Ĵ���
	0. �����쳣��throw���(��ʾ�����쳣)ʵ��������ת����������ֵָ�����쳣������
	1. ʹ�ô�����򲶻��쳣��catch(arg) ��ʾ�����쳣, ����arg��ʾ�쳣Ҫ��Ӧ���쳣����
	2. ʹ��try�飺��ʶ�����ض����쳣���ܱ�����Ĵ���飬�������һ������catch��
	// ִ��throw���������ִ�з�����䣬��Ϊ��Ҳ����ֹ������ִ�У���throw���ǽ�����Ȩ���ظ����ó��򣬶��ǵ��³����غ����������к��ˣ�ֱ���ҵ�����try��ĺ���
	3. ��������������쳣����û��try���û��ƥ��Ĵ������ʱ����Ĭ������£��������ս�����abort()����


2. �쳣�淶������
	1. �����û�������Ҫʹ��try��
	2. �ñ��������ִ�н׶μ��Ĵ���
	// noexceptָ���������������쳣��noexcept()�ж���������Ƿ�������쳣


3. ջ���ˣ����������쳣(�����Ƿ���)����ֹ��������ͷ�ջ�е��ڴ棬���������ͷ�ջ�ĵ�һ�����ص�ַ��ֹͣ�����Ǽ����ͷ�ջ��ֱ���ҵ�һ��λ��try���еķ��ص�ַ��
          ������Ȩ��ת����β���쳣������򣬶����Ǻ������ú���ĵ�һ����䡣
	1. ��������
		in: func_1()->func_2()->func_3()[flag = 0]-> return(func_3)
		ou: return(func_3)-> return(func_2)-> return(func_1)-> #2-> #3-> #5

	2. ��������
		in: func_1()->func_2()->func_3()[flag = 1]-> #0
		ou: #0-> #3-> #4-> #5

void func_3() {
	int flag;
	if (flag)
		throw "hello";					// #0
	return;
}
void func_2() { func_3(); return; }
void func_1() { func_2(); return; }
void main()
{
	try
	{
		cout << "before func_1" << endl; // #1
		func_1();
		cout << "after func_1" << endl;  // #2

	}									 // #3
	catch (const char* s)
	{
		cout << "after func_1 catch" << endl; // #4
	}

}											  // #5


4. ��������
	0. tips: �����һ���쳣��̳в�νṹ��catch���˳��:������λ�ڲ�νṹ��������쳣���catch��������ǰ�棬
	����������쳣��catch����������档
	1. catch (...) {} // catch any exception


class problem { ... };
void super() throw (problem)
{
	if (oh_no)
	{
		problem oops; // construct object
		throw oops;   // throw it
	}
}
try
{
	super();
}
catch (problem &p) { ... } // pָ��oops�ĸ���������oops������Ϊ����super()ִ����Ϻ�oops����������


5. δ�����쳣
δ�����쳣���ᵼ�³��������쳣��ֹ���෴���������ȵ��ú���terminate()��
��Ĭ������£�terminate()����abort()���������⣬����ָ��terminate()Ӧ���õĺ���(������abort())���޸�terminate()��������Ϊ��

