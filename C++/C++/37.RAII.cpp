/*
0. RAII. ��Դ��ȡ����ʼ��
����C++����Ķ������ջᱻ���ٵ�ԭ��ʹ��һ���������乹��ʱ��ȡ��Ӧ����Դ��
�ڶ����������ڿ��ƶ���Դ�ķ��ʣ�ʹ֮ʼ�ձ�����Ч������ٶ���������ʱ���ͷ�
����ʱ��ȡ����Դ��

1. RAII ���ܽ�����:

��ÿ����Դ��װ��һ���࣬����
���캯��������Դ�������������ڲ������������޷����ʱ�׳��쳣��
���������ͷ���Դ�������׳��쳣��
ʼ�վ��� RAII ���ʵ��ʹ������Ҫ�����Դ������Դ
����ӵ���Զ��洢�ڻ���ʱ�����ڣ���
ӵ�а����Զ�����ʱ�����������


*/

#include<iostream>
using namespace std;

// ver_0
/* ������ʱ����ҪΪ���е�new�����ڴ�delete�������ڴ�ӷ�� */
#if 0
int main()
{
	int *arr = new int[10];
	delete[] arr;
	arr = NULL;
	return 0;
}
#endif


// ver_1
/*
C++�е�������Զ��������������Ĺ��ܡ�
�������Դ������з�װ����������Դ��������װ������ڲ���
�����������н����ͷ���Դ��������ľֲ���������������ʱ��
�������������ͻ��Զ��ı����ã�
�Ͳ��ó���Ա��ʾ��ȥ�����ͷ���Դ�Ĳ����ˡ�
*/
class ArrayOperation
{
public:
	ArrayOperation()
	{
		m_Array = new int[10];
	}

	void InitArray()
	{
		for (int i = 0; i < 10; ++i)
		{
			*(m_Array + i) = i;
		}
	}

	void ShowArray()
	{
		for (int i = 0; i <10; ++i)
		{
			cout << m_Array[i] << endl;
		}
	}

	~ArrayOperation()
	{
		cout << "~ArrayOperation is called" << endl;
		if (m_Array != NULL)
		{
			delete[] m_Array;  
			m_Array = NULL;
		}
	}

private:
	int *m_Array;
};



int main()
{
	ArrayOperation arrayOp;
	arrayOp.InitArray();
	arrayOp.ShowArray();
	return 0;
}