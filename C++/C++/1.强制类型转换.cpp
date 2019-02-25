/*
 * @file   1.强制类型转换.cpp
 * @date   2019.2.22.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */



1.dynamic_cast <type_name> (expression) : type_name的类型与expression的类型一样，为类指针类型or引用
	
	作用：
		1.类层次结构中进行上行转换or下行转换。将一个基类对象指针(或引用)cast到继承类指针，dynamic_cast会根据指针是否真正指向继承类来做相应处理。
		2.在类层次间进行上行转换时，dynamic_cast和static_cast的效果是一样的
		3.在进行下行转换时，dynamic_cast具有类型检查功能，比static_cast更安全
		5.对指针进行dynamic_cast，失败返回null，成功返回正常cast后的对象指针.
		6.对引用进行dynamic_cast，失败抛出一个异常，成功返回正常cast后的对象引用
		7.dynamic_cast可以在执行期决定真正的类型
			1.downcast是安全的(即基类指针或者引用确实指向一个派生对象)，此运算符会传回适当转型过的指针
			2.downcast不是安全的，此运算符会传回空指针(即基类指针或者引用没有指向一个派生类对象)
		8.dynamic_cast->判断是不是某个类型->如果是的话就把该指针强转成你要的这个类型
		9.与一般的强转相比
			1.dynamic_cast应用的范围更小一些, 只能对指针或者引用来进行强转
			2.多了一步安全的检查
code:
class base
{
public:
	int m_Num = 3;
	virtual void foo() {}
};
class drived : public base
{
public:
	char m_Name[10] = "string";
};

void funcDown(base *pBase) // 接受base类型的指针，进行下转型
{
	drived *pDrived1 = static_cast<drived *>(pBase);
	drived *pDrived2 = dynamic_cast<drived *>(pBase);
	cout << pDrived1->m_Name << endl;
	cout << pDrived2->m_Name << endl;

}
void funcUp(base *pBase) // 接受drived类型的指针，进行上转型
{
	base *pBase1 = static_cast<base *>(pBase);
	base *pBase2 = dynamic_cast<base *>(pBase);
	cout << pBase1->m_Num << endl;
	cout << pBase2->m_Num << endl;

}
/*
	base *b = new base();
	drived *d = new drived();
	1.funcDown(d).
		0.当funcDown()中pBase指向drived类型的对象，那么pDrived1、pDrived2是一样的，并且对这两个指针执行drived类型的任何操作都是安全的
		1.dynamic_cast: base类中必须有virtual函数，否则报错。需要检测有虚函数的原因：类中存在虚函数，就说明它想要让基类指针或者引用指向派生类对象的情况
		此时转换才有意义。这是由于运行时类型检查需要运行时类型消息，而这个信息存储在类的虚函数表中，只有定义了虚函数的类才有虚函数表
		2.static_cast: base类中有无virtual函数，都没有影响

	2.funcDown(b).--->进行下行转换时，dynamic_cast具有类型检查功能，比static_cast更安全
		0.当funcDown()中pBase指向base类型的对象。
		1.pDrived1将是一个指向该对象的指针，对它进行drived类型的操作将是不安全的（如访问m_Name）
		2.pDrived2是一个空指针

	3.funcUp(d).--->进行上转型时，dynamic_cast和static_cast的效果是一样的
		0.funcUp()函数正确执行

	4.funcUp(b).--->同级转型
		0.funcUp()函数正确执行
*/


2.static_cast <type_name> (expression)
	作用：
		1.仅当type_name可被隐式转换为expression所属的类型或expression可被隐式转换为type_name所属的类型，此运算符生效。
		2.假设High是Low的基类，而Pond是一个无关的类，则从High到Low的转换、从Low到High的转换都是合法的，而从Low到Pond的转换是不允许的
		3.由于无需进行类型转换，枚举值就可以被转换为整型，所以可以用static_cast将整型转换为枚举型
		4.可以使用static_cast将double转换为int、将float转换为long以及其他各种数值转换

code:
class High {};
class Low :public High {};
High bar;
Low blow;
High * pb = static_cast<High *> (&blow); // valid upcast,上转换可以显示的进行
Low  * pl = static_cast<Low *> (&bar);   // valid downcast，此转换是从基类指针到派生类指针，在不进行显示类型转换的情况下，将无法进行。
										 // 但是由于无需进行类型转换，便可以进行另一个方向的类型转换，因此使用static_cast来进行向下转换是合法的。
Pond * pmer = static_cast<Pond *> (&blow); // invalid, Pond unrelated




3.const_cast  <type_name> (expression) : 用于执行只有一种用途的类型转换，即改变值为const 或 volatile。

	作用：
		1.如果类型的其他方面也被修改，则上述类型转换将出错。即除了const或volatile特征(有或无)可以不同外，type name 和 expression 的类型必须相同。
		2.此运算符的目的在于 : 有时候可能需要一个值，它在大多数时候是常量，而有时又是可以修改的。在此情况下，可以将这个值声明为const, 并在需要修改它的时候，使用const_cast.
		  此操作也可以通过通用类型转换来实现，但通用转换也可能同时改变类型。
		  High bar;
		  const High * pbar = &bar;
		  High * pb = (High *)(bar); // valid
		  Low *pl = (Low *)(pbar); // valid

code:
class High {};
class Low :public High {};
High bar;
const High *pbar = &bar; 
High *pb = const_cast<High *>(pbar); // valid. 使得*pb成为一个可用于修改bar对象值的指针，它删除const标签
const Low *pb = const_cast<const Low *> (pbar);// invalid. 因为它同时尝试将类型从const High * 改为 const Low *。


4.reinterpret_cast 运算符用于天生危险的类型转换。它不允许删除const，但会执行其它令人生厌的操作。
	作用：
		1.reinterpret_cast并不支持所有的类型转换。
			eg.可以将指针类型转换为足以存储指针表示的整型，但不能讲指针转换为更小的整数或浮点型
		2.不能讲函数指针转换为数据指针，反之亦然。
		3.char ch = char ( &d )// convert address to a char
		  //在类型转换在c语言中是允许的，但在C++中通常不允许，因为对于多数C++实现，char类型都太小，不能存储指针。
code:
struct dat { short a; short b; };
long value = 0xA224B118;
dat *pd = reinterpret_cast<dat *>(&value);
cout << hex << pd->a; // display first 2 bytes of value
