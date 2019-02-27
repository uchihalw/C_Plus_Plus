/*
 * @file   9.组合和继承与委托.cpp
 * @date   2019.2.27.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
1.组合(has-a)，我里头有另外一种东西。

// Adapter:queue
template <class T>
class queue {
protected:
	deque<T> c; // queue has a c
public:
	// 以下完全利用c的操作函数完成
	bool empty() const { return c.empty(); }
	size_t size() const { return c.size(); }
	reference front() { return c.front(); }
	reference back() { return c.back(); }

	void push(const value_tyep& x) { c.push_back(x); }
	void pop() { c.pop_front(); }
};
构造由内而外：外部的(queue)的构造函数首先调用内部的(deque)的默认构造函数，然后才执行自己 // 编译器自动帮我们调用内部的构造函数
析构由外而内：外部的(queue)的析构函数首先执行自己，然后才调用内部的(deque)的析构函数
外部(queue)和内部(deque)是一起出现。


2.委托. Composition by reference
// handle / body
class StringRep;
class String { // handle,对外不变
public:
	String();
	String(const char* s);
	String(const String& s); // 拷贝构造
	String& operator=(const String& s); // 拷贝赋值
	~String();
private:
	StringRep* rep; // pimpl
};

class StringRep // 字符串功能真正的实现, body。 怎么变都不影响handle(客户端)
{
public:
	StringRep();
};
String 拥有指针指向StringRep,但是这个指向是虚的，因为具体什么时候rep指向StringRep对象不知道。
String 拥有StringRep* rep，在任何时间点都可以调用rep,把任务委托给rep
String先出现，在需要rep的时候再去创建，不同步。


3.继承(is-a)
struct _List_node_base
{
	_List_node_base* _M_next;
	_List_node_base* _M_prev;
};

template<typename _Tp>
struct _List_node
	:public _List_node_base
{
	_Tp _M_data;
};

class Base{};
class derived : public Base{};
base class 的dtor必须是virtual，否则会出现undefined behavior

构造由内而外：Derived的构造函数首先调用Base的默认构造函数，然后才执行自己 // 编译器自动帮我们调用内部的构造函数
析构由外而内：Derived的析构函数首先执行自己，然后才调用Base的析构函数

