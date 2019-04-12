/*
 * @file   21.Lambda.cpp
 * @date   2019.3.13.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0. 假设生成一个随机数整数列表，并判断其中多少个整数可被3整除，多少个整数可被13整除。
	// version_1
	0. 生成整数列表
		vector<int> numbers(1000);
		generate(vector.begin(), vector.end(), rand) // 接受一个区间，并将每个元素设置为第三个参数返回的值，且第三个参数是一个不接受任何参数的函数对象
	1. count_if(),计算有多少个元素可被3整除
		bool f3(int x) { return x % 3 == 0; }
		bool f13(int x) { return x % 13 == 0; }
		int cnt1 = count_if(numbers.begin(), numbers.end(), f3);
		int cnt2 = count_if(numbers.begin(), numbers.end(), f13);
	// version_2
	2. 使用函数符完成
		class f_mod
		{
		private:
			int dv;
		public:
			f_mod(int d = 1):dv(d){}
			bool operator()(int x) { return x % dv == 0; }
		};
		// f_mod obj(3) // f_mod.dv set to 3
		bool is_div_by_3 = obj(7);// same as obj.operator()(7)
		int cnt3 = count_if(numbers.begin(), numbers.end(), f_mod(3));
		// 参数f_mod(3)创建一个对象，存储了值3；count_if()使用该对象来调用operator()

1. lambda：无需给函数命名
	0. C++11中，对于接受函数指针或函数符的函数，可使用匿名函数定义(lambda)作为其参数
		[](int x) { return x % 3 == 0;} // equal to f3(),使用[]代替了函数名(这就是匿名的由来)，没有声明返回类型。
		// 返回类型相当于使用decltyp根据返回值推断得到的
		int cnt4 = count_if(numbers.begin(), numbers.end(), [](int x) { return x % 3 == 0; });
		// 仅当lambda表达式完全由一条返回语句组成时，自动类型推断才管用；否则需要使用新增的返回类型后置语法

	1.lamdba的使用
		auto mod3 = [](int x) { return x % 3 == 0; };
		int cnt4 = count_if(numbers.begin(), numbers.end(), mod3);
2. 仅当lambda表达式完全由一条返回语句组成时，自动类型推断才管用；
   否则，需要使用新增的返回类型后置语法
   [] (double x) {return x;}
	[](double x)->double {x = x + 1.0; return x; }

3. lambda可访问作用域内的任何动态变量:要捕获要使用的变量，可将其名称放在中括号内
	int cnt;
	cnt = std::count_if(vec.begin(), vec.end(), [] int(x) { return x; })

	// equal to
	int cnt = 0;
	for_each(vec.begin(), vec.end(), [&cnt] int(x) { return x= x+cnt; });

	// [&cnt]使得lambda在其代码中使用可以使用cnt,又由于cnt是按引用捕获的，因此lambda中的任何修改都将影响原始cnt

4. [&]使得能够在lambda中使用所有的自动变量，包括cnt2、cnt1
	int cnt1 = 0;
	int cnt2 = 0;
	std::for_each(vec.begin(), vec.end(), [&] int(x) { return x = x + cnt1 + cnt2; })

