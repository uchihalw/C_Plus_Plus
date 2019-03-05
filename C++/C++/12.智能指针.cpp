/*
 * @file   12.智能指针.cpp
 * @date   2019.3.5.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0. auto_ptr、unique_ptr、shared_ptr
	当智能指针过期时，其析构函数将使用delete来释放内存。因此，如果将new返回的地址赋值给
	这些对象，将无需记住稍后释放这些内存:在智能指针过期时，这些内存将自动被释放。
void demo_1()
{
	doubel * pd = new double; // 为pd和一个double值分配存储空间，保存地址
	*pd = 25;				  // 将值复制到动态内存中
	return;					  // 删除pd,值被保留在动态内存中
}

void demo_2()
{
	auto_ptr<double> ap(new double); // 为ap和一个double值分配存储空间保存地址
	*ap = 25;						 // 将值复制到动态内存中
	return;							 // 删除ap,ap的析构函数释放动态内存
}
// unique_ptr<double> pdu(new double);
// auto_ptr<string> ps(new string);

1. 创建智能指针对象，必须包含头文件memory,该文件模板定义。
auto_ptr:
template<class x>
class auto_ptr {
public:
	explicit auto_ptr(x *p = 0) throw();
};

#include <memory>
void remodel(siring &str)
{
	auto_ptr<string> ps(new string(str));
	str = *ps;
	return;
}


2. 所有智能指针类都有一个explicit构造函数，该构造函数将指针作为参数，因此不需要自动将指针转换为智能对象。


3.智能指针的注意事项
auto_ptr<string> ps(new string("hello world"));
auto_ptr<string> vocation;
vocation = ps;

	1. 如果上面两个指针都是常规指针，则两个指针将指向同一个string对象。
	这是不能接受的，因为程序试图删除同一个对象两次 : 一次是ps过期时，一次是vocation过期时。
		要避免上述问题：
		1.定义赋值运算，使之执行深复制，将两个指针指向不同的对象，其中一个对象是另一个对象的副本
		2.建立所有权概念，对于特定对象，只能有一个智能指针可拥有它，这样只有拥有对象的智能指针的构造函数会删除该对象。
		然后让赋值操作转让所有权，这就是用于auto_ptr和unique_prt的策略。
		3.创建智能更高的指针，跟踪引用特定对象的智能指针数，这称为引用计数。
		eg : 赋值时，计数 + 1，而指针过期时，计数 - 1。仅当最后一个指针过期时，才调用delete.这是shared_ptr采用的策略。

	void main()
	{
		auto_ptr<string> file[3] = {
			auto_ptr<string> (new string("first"));
			auto_ptr<string> (new string("second"));
			auto_ptr<string> (new string("third"));
		}
		// method_1 :在运行阶段崩溃
		auto_ptr<string> pwin;
		pwin = file[1]; // file[1] loose ownership
		cout<<*file[1] <<endl; // error, file[1]不再引用该字符串，在auto_ptr放弃对象的所有权后，便可能使用它来访问该对象。

		// method_2 :正常运行
		shared_ptr<string> pwin;
		pwin = file[1];  
		// pwin和file[1]指向同一个对象，而引用计数从1增加到2.
		// 在程序末尾，后声明的pwin首先调用其析构函数，该析构函数将引用降低到1。
		// 然后，shared_ptr数组的成员被释放，对file[1]调用析构函数时，将其引用计数降低到0，并释放以前分配的空间。
		cout<<*file[1]<<endl;

		// method_3 :程序不会等到运行阶段崩溃，在编译期间报错。
		unique_ptr<string> pwin;
		pwin = file[1];  // file[1] loose ownership
		cout << *file[1] << endl;
	}

	2. unique_ptr与auto_ptr
	// method_1
	auto_ptr<string> p1(new string("hello"));
	auto_ptr<string> p2;
	p2 = p1; 
	/*
	p2接管string对象的所有权后，p1的所有权将被剥夺。可防止p1和p2的析构函数试图删除同一个对象；
	但如果随后程序试图使用p1，这将是坏事，因为p1不再指向有效数据
	*/


	// method_2
	unique_ptr<string> p3(new string("hello"));
	unique_ptr<string> p4;
	p4 = p3;
	/*
	编译器认为p4 = p3语句非法，避免了p3不再指向有效数据的问题。(即编译阶段错误)
	*/
	

	// method_3
	unique_ptr<string> pu1(new string("hello"));
	unique_ptr<string> pu2;
	pu2 = pu1; // 不允许，将留下悬挂的unique_ptr(pu1)
	unique_ptr<string> pu3;
	pu3 = unique_ptr<string>(new string("hello")) // 允许,不会留下悬挂的unique_ptr(pu2)。因为调用的是unique_ptr的构造函数，该构造函数创建的临时对象在其所有权转让给pu3后就会被销毁。


	/* 不使用new分配内存时，不能使用auto_ptr或shared_ptr； 不使用new或new[] 分配内存时，不能使用unique_ptr */

	4. 选择智能指针
		1.shared_ptr
		程序要使用多个指向同一个对象的指针。
		2.unique_ptr
			1.程序不需要多个指向同一个对象的指针。如果函数使用new分配内存，并返回指向该内存的指针，将其返回类型声明为unipue_ptr是不错的选择，
			因为，所有权将转让给接受返回值的unique_ptr，而该智能指针将负责调用delete
			2.unique_ptr为右值时，可将其赋值给shared_ptr
			// make() return type is unique_ptr<int>
			unique_ptr<int> pup(make()); // ok
			shared_ptr<int> spp(pup);        // not allowed
			shared_ptr<int> spr(make());     // ok
			// shared_ptr包含一个显示构造函数，可用于将右值unique_ptr转换为shared_ptr。shared_ptr将接管原来归unique_ptr所有的对象。