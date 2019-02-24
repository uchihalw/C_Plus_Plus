/*
 * @file   4.ί��������.cpp
 * @date   2019.2.22.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0.��������:�̳С����ϡ�ί��

1.Composition(����or���)����ʾ has-a

2.Inheritance(�̳�)����ʾ is-a

3.���ģʽ(Composite)
// ����:�ļ�ϵͳ����Ŀ¼������Է��ļ���Ŀ¼

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
	// Component Ӧ��Ϊ����(�������ɶ���ļ����� Primitive.Ҳ�������ɶ��Ŀ¼���� Composite)����Component��ΪPrimitive��Composite�ĸ���
	// ��������Ҫ�Ŷ���ָ�룬��Ϊָ��һ��һ����С��
	vector<Component*> c;
public:
	Composite(int val):Component(val){}
	void add(Component* elem) { // ί��
		c.push_back(elem);
	}
};


4.ԭ��ģʽ(Prototype)
// ���ӣ�������Ҫһ���̳���ϵ����Ҫ����һ��δ���Ż���Ҫ�����࣬��δ����class����
// ���˼·:�����Լ�ȥ�����Լ�
 
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
	static Image* _prototypes[10]; // ����:�������ԭ��
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
	// �˹��캯����ͨ��ԭ�������õģ�����Ϊprocted || private��ֻҪ�ܸ���������ֿ�
	LandSatImage(int dummy) // dummy ֻ��������Ĭ�Ϲ��캯�����֣�����û���õ��˲���
	{
		_id = _count++;
	}

private:
	// Mechanism for initialize an Image subclass-this causes the 
	// default  ctor to be called when registers the subclass`s prototype
	static LandSatImage _landSatImage;
	// ˽�й��캯�� 
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


















