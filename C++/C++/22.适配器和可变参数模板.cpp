/*
 * @file   22.适配器.cpp
 * @date   2019.3.13.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0. template<typename T, typename F>
T use_f(T v, F f)
{
	static int cnt = 0;
	return f(v);
}
class Fp 
{
private:
	double z;
public:
	Fp(double zz = 1.0) :z(zz) {}
	double operator()(double p) { return z * p; }
};
double dub(double x) { return 1.0 * x; }


/*
编译器判断模板参数F的类型：use_f(y, dub);
	0.函数名是指针，因此参数F的类型为double(*)(double):一个指向这样的函数的指针。即它接受一个double参数并返回一个double值
*/


1.可变参数模板:可接受可变数量的参数
	0. 模板参数包
		template<typename T>
		void show_1(T value) { cout << value; }
	1. 函数参数包
		template<typename... Args>                 // Args是一个模板参数包，而args是一个函数参数包。T只和一种类型匹配，而Args与任意数量的类型匹配
		void show_2(Args... args) { ... }
		show_2(2, 3, 4, "string", 8.0);
	2. 展开参数包
		可将省略号放在函数参数包名的右边，将参数展开
		template<typename... Args>                
		void show_3(Args... args) { show_3(args...); }
		show_3(2, 3, 4, "string", 8.0);// show_3(args...) 将展开为 show_3(2, 3, 4, "string", 8.0);
		// args...展开为一个函数参数列表。
		// 但是该函数调用与原始函数调用相同，因此它将使用相同的参数不断调用自己，导致无限递归（此处存在缺陷）
	3. 在可变参数模板函数中使用递归
		0. 将函数参数包展开，对列表的第一项进行处理，再将余下的内容传递给递归调用，以此类推，直到列表为空.
		void show_4() {}// definition for 0 paramsters ---teminating call
		template<typename T, typename... Args>
		void show_4(T value, Args... args) 
		{ 
			cout << value << endl;
			show_4(args...); 
		}
		show_4(4, "string", 8.0);
		