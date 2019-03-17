/*
 * @file   23.局部变量.cpp
 * @date   2019.3.16.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0. 能返回static修饰的局部变量(因为在静态存储区)
	char * func_0()
	{
		static  char str[] = "hello"
		return str;
	}
	cout << func_0(); // 正常输出,static修饰，表示存储在静态存储区。

1. 能返回用new创建的局部变量(因为在堆空间)
	char* func_1()
	{
		//char *str = new char[10](); // initial array 
		char *str = new char[10]; // return const char *, 所以*str = "hello"<Err>, str = "hello"<Right>
		str = "world";
		return str;
	}
cout << func_1(); // 正常输出


2. 能返回指向常量的指针，但不能返回指向普通局部变量的指针，否则返回的是乱码(因为后者创建在栈空间)
	char * func_2()
	{
		char str[] = "hello"
		return str;
	}
	cout << func_2(); // 输出乱码,因为return str后，str可以成功的返回，但是str指向内容已经被栈空间清除


	char * func_3()
	{
		char *str = "hello";
		return str;
	}
	cout << func_3(); // 正常输出

3. 能返回局部变量的值

4. 当函数结束时，在栈空间的该函数的普通局部变量会被释放(清除)

5. 普通局部变量是在栈空间生成的，但是程序结束时，局部变量也会被清空

6. static修饰的变量是存储在静态存储区，而不是栈空间

// 在函数返回中，return后跟的东西一定能返回出去，这就是局部变量能返回的原因，
// 但是地址返回(指针)则看情况，取决于其所指向的内存空间是否已被释放