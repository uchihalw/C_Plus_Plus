/*
 * @file   23.�ֲ�����.cpp
 * @date   2019.3.16.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0. �ܷ���static���εľֲ�����(��Ϊ�ھ�̬�洢��)
	char * func_0()
	{
		static  char str[] = "hello"
		return str;
	}
	cout << func_0(); // �������,static���Σ���ʾ�洢�ھ�̬�洢����

1. �ܷ�����new�����ľֲ�����(��Ϊ�ڶѿռ�)
	char* func_1()
	{
		//char *str = new char[10](); // initial array 
		char *str = new char[10]; // return const char *, ����*str = "hello"<Err>, str = "hello"<Right>
		str = "world";
		return str;
	}
cout << func_1(); // �������


2. �ܷ���ָ������ָ�룬�����ܷ���ָ����ͨ�ֲ�������ָ�룬���򷵻ص�������(��Ϊ���ߴ�����ջ�ռ�)
	char * func_2()
	{
		char str[] = "hello"
		return str;
	}
	cout << func_2(); // �������,��Ϊreturn str��str���Գɹ��ķ��أ�����strָ�������Ѿ���ջ�ռ����


	char * func_3()
	{
		char *str = "hello";
		return str;
	}
	cout << func_3(); // �������

3. �ܷ��ؾֲ�������ֵ

4. ����������ʱ����ջ�ռ�ĸú�������ͨ�ֲ������ᱻ�ͷ�(���)

5. ��ͨ�ֲ���������ջ�ռ����ɵģ����ǳ������ʱ���ֲ�����Ҳ�ᱻ���

6. static���εı����Ǵ洢�ھ�̬�洢����������ջ�ռ�

// �ں��������У�return����Ķ���һ���ܷ��س�ȥ������Ǿֲ������ܷ��ص�ԭ��
// ���ǵ�ַ����(ָ��)�������ȡ��������ָ����ڴ�ռ��Ƿ��ѱ��ͷ�