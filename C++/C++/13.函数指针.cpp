/*
 * @file   13.函数指针.cpp
 * @date   2019.3.6.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
1. 获取函数的地址
	1. 即函数名(后面不跟参数)。如果think()是一个函数，则think就是该函数的地址
	2. 要将函数作为参数进行传递，必须传递函数名
	func(think);

2. 声明函数指针
	声明指向函数的指针时，必须指定指针指向的函数类型。
	double pam(int);  // 函数原型
	double(*pf)(int); // pf指向一个函数，一个以int做参数且返回值是double类型的函数。
	pf = pam;         // pf now 指向pam() 函数
					  
	// pam是函数，因此(*pf)也是函数，而如果(*pf)是函数，则pf就是函数指针
	// 如果pam()的特征标和返回类型与pf不相同，编译器将拒绝这种赋值。

3. 使用指针来调用函数
	double pam(int);
	double(*pf)(int);
	pf = pam;
	double x = pam(4);
	double y = (*pf)(5);
	double z = pf(5);
4.函数指针数组
const double *(*pa[3])(const double *, int) = {f1, f2, f3}



4. auto 只能适用于单值初始化，而不能用于初始化列表
