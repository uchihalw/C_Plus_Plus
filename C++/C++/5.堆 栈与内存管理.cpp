/*
 * @file   5.�� ջ���ڴ����.cpp
 * @date   2019.2.24.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
1.Stack.�Ǵ�����ĳ������(scope)��һ���ڴ�ռ�(memory space)�����統����ú����������������γ�һ��stack���������������յĲ������Լ����ص�ַ��
		��ʵ�����������������κα���������ʹ�õ��ڴ�鶼ȡ������stack��


2.Heap. ��νsystem heap����ָ�ɲ���ϵͳ�ṩ��һ��global�ڴ�ռ䣬����ɶ�̬�������������顣

class Complex{......};
...
{
	Complex c1(1�� 2)��// c1��ռ�õĿռ�����stack���ֲ����������Զ�������
	static Complex c2(1, 2); // ��������������(scope)����֮����Ȼ���ڣ�ֱ���������������
	Complex *p = new Complex(3); // Complex(3)��ռ�ÿռ�����Heap,��Ϊ��ͨ��new��̬��õġ�
}


3.new: �ȷ���memory�� �ٵ���ctor��
Complex* pc = new Complex(1, 2);
	0.Complex *pc;
	1.void* mem = operator new(sizeof(Complex)); // �����ڴ�, �ڲ�����malloc(n)
	2.pc = static_cast<Complex *>(mem);			 // ת��
	3.pc->Complex::Complex(1, 2);				 // ���캯��, equal to Complex::Complex(pc, 1, 2), pc == this.

4.delete:�ȵ���dtor, ���ͷ�memory
String* ps = new String("Hello");
...
delete ps;
	0.String::~String(ps);
	1.operator delete(ps)                         // ���ڲ�����free(ps)


5.array new һ��Ҫ���� array delete
	String* p = new String[3];
	1.delete[] p; // ����3��dtor,[]��֪������Ҫɾ������һ������
	2.delete p;   // ����1��dtor�����������[]������ڴ�й©�������ڴ�й©�Ĳ���p[0]������p[1]��p[2]���������class��û�ж�̬�ڴ���䡢ָ�룬��ô������[]Ҳû������(���ǲ�������ô��)��