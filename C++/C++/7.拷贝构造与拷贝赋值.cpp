/*
 * @file   7.拷贝构造与拷贝赋值.cpp
 * @date   2019.2.25.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
1.拷贝构造:以同类型对象初始化自我对象
2.拷贝赋值 : 从另一个对象中拷贝其值到自我对象
class Widget
{
public:
	Widget();
	Widget(const Widget& rhs);
	Widget& operator=(const Widget& rhs);
}
Widget w1;       // 调用默认构造函数
Widget w2(w1);   // 调用拷贝构造函数。新建一个对象并将其初始化为同类现象时，复制构造函数都将被调用。
w1 = w2;         // 调用赋值拷贝函数。如果没有新对象被定义，就不会有构造函数被调用。
Widget w3 = w2;  // 调用拷贝构造函数。如果一个新的对象被定义(如w3)，一定会有一个构造函数被调用，不可能调用赋值操作。


bool func(Widget w);
Widget aWidget;
func(aWidget);    // w是通过by-value传递给func(),此复制动作由Widget的拷贝构造函数完成。