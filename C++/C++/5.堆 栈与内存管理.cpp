/*
 * @file   5.堆 栈与内存管理.cpp
 * @date   2019.2.24.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
1.Stack.是存在于某作用域(scope)的一块内存空间(memory space)。例如当你调用函数，函数本身即会形成一个stack用来放置它所接收的参数，以及返回地址。
		其实函数本体内声明的任何变量，其所使用的内存块都取自上述stack。


2.Heap. 所谓system heap，是指由操作系统提供的一块global内存空间，程序可动态分配获得若干区块。

class Complex{......};
...
{
	Complex c1(1， 2)；// c1所占用的空间来自stack，局部变量，会自动被清理。
	static Complex c2(1, 2); // 其生命在作用域(scope)结束之后仍然存在，直到整个程序结束。
	Complex *p = new Complex(3); // Complex(3)所占用空间来自Heap,因为是通过new动态获得的。
}


3.new: 先分配memory， 再调用ctor。
Complex* pc = new Complex(1, 2);
	0.Complex *pc;
	1.void* mem = operator new(sizeof(Complex)); // 分配内存, 内部调用malloc(n)
	2.pc = static_cast<Complex *>(mem);			 // 转型
	3.pc->Complex::Complex(1, 2);				 // 构造函数, equal to Complex::Complex(pc, 1, 2), pc == this.

4.delete:先调用dtor, 再释放memory
String* ps = new String("Hello");
...
delete ps;
	0.String::~String(ps);
	1.operator delete(ps)                         // 其内部调用free(ps)


5.array new 一定要搭配 array delete
	String* p = new String[3];
	1.delete[] p; // 调用3次dtor,[]告知编译器要删除的是一个数组
	2.delete p;   // 唤起1次dtor，如果不搭配[]会出现内存泄漏。但是内存泄漏的不是p[0]，而是p[1]、p[2]。但是如果class中没有动态内存分配、指针，那么不搭配[]也没有问题(但是不建议这么做)。