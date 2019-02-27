/*
 * @file   8.RTTI.cpp
 * @date   2019.2.27.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0. RTTI 运行阶段类型识别
	1.如果有可能的话，dynamic_cast运算符将使用一个指向基类的值针来生成一个指向派生类的指针；
      否则，该运算符返回0-空指针
	2.typeid运算符返回一个指出对象的类型的值
	3.type_info结构存储了有关特定类型的信息
	//** 只能将RTTI用于包含虚函数的类层次结构，原因在于只有对于这种类层次结构，才应该将派生对象的地址赋值给基类指针。

1. dynamic_cast运算符(可以回答是否可以安全地将对象的地址赋给特定类型的指针)

class Grand{ has virtual methods};
class Superb:public Grand {...};
class Magnificent:public Superb{...};

Grand* pg = new Grand;
Grand* ps = new Superb;
Grand* pm = new Magnificent;

// 类型转换
Magnificent* p1 = (Magnificent*) pm; // 安全，因为将Magnificent类型的指针指向类型为Magnificent的对象
Magnificent* p2 = (Magnificent*) pg; // 不安全，因为将基类对象的地址赋给派生类指针(程序将期望基类对象有派生类的特征，这通常是不可能的，因为派生类可能含有基类没有的成员)
Superb * p3 = (Magnificent*) pm;     // 安全，因为它将派生对象的地址赋给基类指针

通常，如果指向的对象*pt的类型为Type或者是从Type直接或者间接派生而来的类型，则下面的表示将指针pt转换为Type类型的指针
Type *t = dynamic_cast<Type *>(pt)
否则，结果为0，即空指针。

2.typeid运算符合type_info类
	1. typeid(类名 | 结果为对象的表达式)运算符使得能够确定两个对象是否为同类型
	2. typeid运算符返回一个对type_info对象的引用
	3. type_info的头文件是typeinfo
	4. typeid(Magnificent) == typeid(*pg) //如果pg指向的是一个Magnificent对象，则结果true,反之为false