/*
 * @file   17.异常.cpp
 * @date   2019.3.8.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */

0. abort() 函数原型位于cstdlib.h || stdlib.h
	此函数将直接终止程序，而不是返回到main().显示的程序异常中断消息随编译器而异
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

1. 对异常的处理
	0. 引发异常：throw语句(表示引发异常)实际上是跳转。紧随其后的值指出了异常的特征
	1. 使用处理程序捕获异常：catch(arg) 表示捕获异常, 其中arg表示异常要响应的异常类型
	2. 使用try块：标识其中特定的异常可能被激活的代码块，它后面跟一个或多个catch块
	// 执行throw语句类似于执行返回语句，因为它也将终止函数的执行；但throw不是将控制权返回给调用程序，而是导致程序沿函数调用序列后退，直到找到包含try块的函数
	3. 如果函数引发了异常，而没有try块或没有匹配的处理程序时。在默认情况下，程序最终将调用abort()函数


2. 异常规范的作用
	1. 告诉用户可能需要使用try块
	2. 让编译器添加执行阶段检查的代码
	// noexcept指出函数不会引发异常，noexcept()判断其操作数是否会引发异常


3. 栈解退：函数由于异常(而不是返回)而终止，则程序将释放栈中的内存，但不会在释放栈的第一个返回地址后停止，而是继续释放栈，直到找到一个位于try块中的返回地址。
          随后控制权将转到块尾的异常处理程序，而不是函数调用后面的第一条语句。
	1. 函数返回
		in: func_1()->func_2()->func_3()[flag = 0]-> return(func_3)
		ou: return(func_3)-> return(func_2)-> return(func_1)-> #2-> #3-> #5

	2. 函数解退
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


4. 其他特性
	0. tips: 如果有一个异常类继承层次结构，catch块的顺序:将捕获位于层次结构最下面的异常类的catch语句放在最前面，
	将捕获基类异常的catch语句放在最后面。
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
catch (problem &p) { ... } // p指向oops的副本而不是oops本身。因为函数super()执行完毕后，oops将不复存在


5. 未捕获异常
未捕获异常不会导致程序立刻异常终止。相反，程序将首先调用函数terminate()。
在默认情况下，terminate()调用abort()函数。此外，可以指定terminate()应调用的函数(而不是abort())来修改terminate()的这种行为。

