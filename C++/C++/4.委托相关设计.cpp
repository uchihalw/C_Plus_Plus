/*
 * @file   4.ί��������.cpp
 * @date   2019.2.22.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */

1.Composition(����or���)����ʾ has-a

2.Inheritance(�̳�)����ʾ is-a

3.���ģʽ(Composite)
// ����:�ļ�ϵͳ����Ŀ¼������Է��ļ���Ŀ¼
// Component Ӧ��Ϊ����(�������ɶ���ļ����� Primitive.Ҳ�������ɶ��Ŀ¼���� Composite)����Component��ΪPrimitive��Composite�ĸ���

class Component
{
private:
	int value;
public:
	Component(int val) { value = val; }
	virtual void add(Component *){} 
};

// Primitive �����ļ�
class Primitive :public Component
{
public:
	Primitive(int val):Component(val){}
};

// Composite ����Ŀ¼����Ӧ����add(),�ȿ������Primitive��Ҳ�������Composite.��add�Ĳ���ΪComponent*
class Composite :public Component
{
private:
	vector<Component*> c;
public:
	Composite(int val):Component(val){}
	void add(Component* elem) { // ί��
		c.push_back(elem);
	}
};

4.ԭ��ģʽ(Prototype)
// ���ӣ�������Ҫһ���̳���ϵ����Ҫ����һ��δ���Ż���Ҫ������