/*
 * @file   4.委托相关设计.cpp
 * @date   2019.2.22.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */

1.Composition(复合or组合)，表示 has-a

2.Inheritance(继承)，表示 is-a

3.组合模式(Composite)
// 例子:文件系统：根目录下面可以放文件、目录
// Component 应该为容器(可以容纳多个文件，即 Primitive.也可以容纳多个目录，即 Composite)，将Component作为Primitive和Composite的父类

class Component
{
private:
	int value;
public:
	Component(int val) { value = val; }
	virtual void add(Component *){} 
};

// Primitive 代表文件
class Primitive :public Component
{
public:
	Primitive(int val):Component(val){}
};

// Composite 代表目录。且应该有add(),既可以添加Primitive，也可以添加Composite.故add的参数为Component*
class Composite :public Component
{
private:
	vector<Component*> c;
public:
	Composite(int val):Component(val){}
	void add(Component* elem) { // 委托
		c.push_back(elem);
	}
};

4.原型模式(Prototype)
// 例子：现在需要一个继承体系，需要创建一个未来才会需要的子类