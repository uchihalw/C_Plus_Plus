/*
 * @file   10.静态联编和动态联编.cpp
 * @date   2019.2.28.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */

0.转型
	1.向上强制转型: 将派生类引用或指针转换为基类引用或指针，这使公有继承不需要进行 显示 类型转换
	2.向下强制转换: 将基类指针或引用转换为派生类指针或引用，如果不使用显示类型转换，则向下强制转换是不允许的
	// 因为is-a关系通常是不可逆的，派生类可以新增数据成员，因此使用这些数据成员的类成员函数是不能应用于基类。

1.静态联编(早期联编):在编译过程中进行联编
	1.动态联编与通过指针和引用调用方法相关。
	2.指向基类的引用或指针可以引用派生类对象，而不必进行显示类型转换
	3.编译器对非虚方法使用静态联编


2.动态联编(晚期联编):编译器必须生成能够在程序运行时选择正确的虚方法的代码
	1.编译器对非虚方法使用动态联编



3.code
class base {
	virtual void func() { cout << "base" << endl; }
};
class drived:public base {
	virtual void func() { cout << "drived" << endl; }
};
void main()
{
	base* pB = new base;
	drived* pD = new drived;

	base* pBt = dynamic_cast<base*>(pD); // 向上转换(不用显示转换)，等价于 base* pBt = pD;
	drived* pDt;

	pDt = static_cast<drived*>(pB); // 向下转换，当类型之间可隐式转换时，staic_cast的转化才是合法的。

	pDt = dynamic_cast<drived*>(pB);  //向下转型，dynamic_cast涉及运行时检查，如果安全则返回转型过的指针，反之返回空指针。	且要使用dynamic_cast类中必须定义虚函数 
	if (pDt)
	{
		pDt->func();
	}

}