/*
 * @file   4.委托相关设计.cpp
 * @date   2019.2.22.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0.三把武器:继承、复合、委托

1.Composition(复合or组合)，表示 has-a

2.Inheritance(继承)，表示 is-a

3.组合模式(Composite)
// 例子:文件系统：根目录下面可以放文件、目录

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
	// Component 应该为容器(可以容纳多个文件，即 Primitive.也可以容纳多个目录，即 Composite)，将Component作为Primitive和Composite的父类
	// 容器当中要放对象指针，因为指针一定一样大小。
	vector<Component*> c;
public:
	Composite(int val):Component(val){}
	void add(Component* elem) { // 委托
		c.push_back(elem);
	}
};


4.原型模式(Prototype)
// 例子：现在需要一个继承体系，需要创建一个未来才会需要的子类，即未来的class对象
// 解决思路:子类自己去创建自己
 
enum imageType{LAST, SPOT};

class Image
{
public:
	virtual void draw() = 0;
	static Image* findAndClone(imageType type); // virtual ctor
protected:
	virtual imageType returnType() = 0;
	virtual Image * clone() = 0;
	static void addPrototype(Image *image)
	{
		_prototypes[_nextSlot++] = image;
	}

private:
	static Image* _prototypes[10]; // 容器:存放所有原型
	static int _nextSlot;
};
Image *Image::_prototypes[]; // ????
int Image::_nextSlot;


// client calls this public static member function when it needs instance of an Image subclass
Image* Image::findAndClone(imageType type)
{
	for (int i = 0; i < _nextSlot; i++)
	{
		if (_prototypes[i]->returnType() == type)
			return _prototypes[i]->clone();
	}
}




class LandSatImage :public Image
{
public:
	imageType returnType() { return LAST; }

	void draw() { cout << "LandSatImage::draw" << _id << endl; }
	
	Image *clone()
	{
		return new LandSatImage(1);
	}

protected:
	// This is only called from clone()
	// 此构造函数是通过原型来调用的，可以为procted || private。只要能跟上面的区分开
	LandSatImage(int dummy) // dummy 只是用来跟默认构造函数区分，更本没有用到此参数
	{
		_id = _count++;
	}

private:
	// Mechanism for initialize an Image subclass-this causes the 
	// default  ctor to be called when registers the subclass`s prototype
	static LandSatImage _landSatImage;
	// 私有构造函数 
	// This is only called when the private static data member is inited
	LandSatImage() {
		addPrototype(this);
	}
	int id;
	static int _count;
};
// register the subclass`s prototype
LandSatImage LandSatImage::_landSatImage;
int LandSatImage::_count = 1;

// Simulated stream of creation requests
const int NUM_IMAGES = 8;
imageType input[NUM_IMAGES] = { LAST, LAST, LAST, LAST, SPOT, LAST, SPOT, SPOT, LAST };
int main()
{
	Image *images[NUM_IMAGES];

	// Given an image type, find the right prototype, and return a clone
	for (int i = 0; i < NUM_IMAGES; i++)
		images[i] = Image::findAndClone(input[i]);
	// Demonstrate that correct image objects have been cloned
	for (int i = 0; i < NUM_IMAGES; i++)
		images[i]->draw();
	for (int i = 0; i < NUM_IMAGES; i++)
		delete images[i];
}


















