/*
 * @file   9.��Ϻͼ̳���ί��.cpp
 * @date   2019.2.27.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
1.���(has-a)������ͷ������һ�ֶ�����

// Adapter:queue
template <class T>
class queue {
protected:
	deque<T> c; // queue has a c
public:
	// ������ȫ����c�Ĳ����������
	bool empty() const { return c.empty(); }
	size_t size() const { return c.size(); }
	reference front() { return c.front(); }
	reference back() { return c.back(); }

	void push(const value_tyep& x) { c.push_back(x); }
	void pop() { c.pop_front(); }
};
�������ڶ��⣺�ⲿ��(queue)�Ĺ��캯�����ȵ����ڲ���(deque)��Ĭ�Ϲ��캯����Ȼ���ִ���Լ� // �������Զ������ǵ����ڲ��Ĺ��캯��
����������ڣ��ⲿ��(queue)��������������ִ���Լ���Ȼ��ŵ����ڲ���(deque)����������
�ⲿ(queue)���ڲ�(deque)��һ����֡�


2.ί��. Composition by reference
// handle / body
class StringRep;
class String { // handle,���ⲻ��
public:
	String();
	String(const char* s);
	String(const String& s); // ��������
	String& operator=(const String& s); // ������ֵ
	~String();
private:
	StringRep* rep; // pimpl
};

class StringRep // �ַ�������������ʵ��, body�� ��ô�䶼��Ӱ��handle(�ͻ���)
{
public:
	StringRep();
};
String ӵ��ָ��ָ��StringRep,�������ָ������ģ���Ϊ����ʲôʱ��repָ��StringRep����֪����
String ӵ��StringRep* rep�����κ�ʱ��㶼���Ե���rep,������ί�и�rep
String�ȳ��֣�����Ҫrep��ʱ����ȥ��������ͬ����


3.�̳�(is-a)
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
base class ��dtor������virtual����������undefined behavior

�������ڶ��⣺Derived�Ĺ��캯�����ȵ���Base��Ĭ�Ϲ��캯����Ȼ���ִ���Լ� // �������Զ������ǵ����ڲ��Ĺ��캯��
����������ڣ�Derived��������������ִ���Լ���Ȼ��ŵ���Base����������

