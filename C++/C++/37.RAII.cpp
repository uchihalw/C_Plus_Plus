/*
0. RAII. 资源获取即初始化
利用C++构造的对象最终会被销毁的原则。使用一个对象，在其构造时获取对应的资源，
在对象生命期内控制对资源的访问，使之始终保持有效，最后再对象析构的时候，释放
构造时获取的资源。

1. RAII 可总结如下:

将每个资源封装入一个类，这里
构造函数请求资源，并建立所有内部变量或在它无法完成时抛出异常，
析构函数释放资源并决不抛出异常；
始终经由 RAII 类的实例使用满足要求的资源，该资源
自身拥有自动存储期或临时生存期，或
拥有绑定于自动或临时对象的生存期


*/

#include<iostream>
using namespace std;

// ver_0
/* 程序复杂时，需要为所有的new分配内存delete，导致内存臃肿 */
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
C++中的类具有自动调用析构函数的功能。
如果把资源用类进行封装起来，对资源操作都封装在类的内部，
在析构函数中进行释放资源。当定义的局部变量的生命结束时，
它的析构函数就会自动的被调用，
就不用程序员显示的去调用释放资源的操作了。
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