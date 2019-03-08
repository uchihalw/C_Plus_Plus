/*
 * @file   2.关键字.cpp
 * @date   2019.2.22.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
1. explicit 修饰构造函数，使之不能参加隐式转换。

2. volatile 作为指令关键字，确保本条指令不会因编译器的优化而省略，且要求每次直接读值
	1.声明成volatile的变量其内容是“不稳定的”（unstable），它的值可能在编译器不知道的情况下发生变化
	2.所有对声明成volatile的数据的写操作都是“可见的”（observable）, 因此必须严格执行这些写操作
	3.所以对声明成volatile的数据的操作都必须按源代码中的顺序执行

3. typedef 创建类型别名

4. noexcept 指出函数不会引发异常。 noexcept() 判断其操作数是否会引发异常。

5. auto 用于默认为自动的变量。主要用途是指出当前变量为局部自动变量。