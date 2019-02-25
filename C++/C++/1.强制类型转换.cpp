/*
 * @file   1.ǿ������ת��.cpp
 * @date   2019.2.22.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */



1.dynamic_cast <type_name> (expression) : type_name��������expression������һ����Ϊ��ָ������or����
	
	���ã�
		1.���νṹ�н�������ת��or����ת������һ���������ָ��(������)cast���̳���ָ�룬dynamic_cast�����ָ���Ƿ�����ָ��̳���������Ӧ����
		2.�����μ��������ת��ʱ��dynamic_cast��static_cast��Ч����һ����
		3.�ڽ�������ת��ʱ��dynamic_cast�������ͼ�鹦�ܣ���static_cast����ȫ
		5.��ָ�����dynamic_cast��ʧ�ܷ���null���ɹ���������cast��Ķ���ָ��.
		6.�����ý���dynamic_cast��ʧ���׳�һ���쳣���ɹ���������cast��Ķ�������
		7.dynamic_cast������ִ���ھ�������������
			1.downcast�ǰ�ȫ��(������ָ���������ȷʵָ��һ����������)����������ᴫ���ʵ�ת�͹���ָ��
			2.downcast���ǰ�ȫ�ģ���������ᴫ�ؿ�ָ��(������ָ���������û��ָ��һ�����������)
		8.dynamic_cast->�ж��ǲ���ĳ������->����ǵĻ��ͰѸ�ָ��ǿת����Ҫ���������
		9.��һ���ǿת���
			1.dynamic_castӦ�õķ�Χ��СһЩ, ֻ�ܶ�ָ���������������ǿת
			2.����һ����ȫ�ļ��
code:
class base
{
public:
	int m_Num = 3;
	virtual void foo() {}
};
class drived : public base
{
public:
	char m_Name[10] = "string";
};

void funcDown(base *pBase) // ����base���͵�ָ�룬������ת��
{
	drived *pDrived1 = static_cast<drived *>(pBase);
	drived *pDrived2 = dynamic_cast<drived *>(pBase);
	cout << pDrived1->m_Name << endl;
	cout << pDrived2->m_Name << endl;

}
void funcUp(base *pBase) // ����drived���͵�ָ�룬������ת��
{
	base *pBase1 = static_cast<base *>(pBase);
	base *pBase2 = dynamic_cast<base *>(pBase);
	cout << pBase1->m_Num << endl;
	cout << pBase2->m_Num << endl;

}
/*
	base *b = new base();
	drived *d = new drived();
	1.funcDown(d).
		0.��funcDown()��pBaseָ��drived���͵Ķ�����ôpDrived1��pDrived2��һ���ģ����Ҷ�������ָ��ִ��drived���͵��κβ������ǰ�ȫ��
		1.dynamic_cast: base���б�����virtual���������򱨴���Ҫ������麯����ԭ�����д����麯������˵������Ҫ�û���ָ���������ָ���������������
		��ʱת���������塣������������ʱ���ͼ����Ҫ����ʱ������Ϣ���������Ϣ�洢������麯�����У�ֻ�ж������麯����������麯����
		2.static_cast: base��������virtual��������û��Ӱ��

	2.funcDown(b).--->��������ת��ʱ��dynamic_cast�������ͼ�鹦�ܣ���static_cast����ȫ
		0.��funcDown()��pBaseָ��base���͵Ķ���
		1.pDrived1����һ��ָ��ö����ָ�룬��������drived���͵Ĳ������ǲ���ȫ�ģ������m_Name��
		2.pDrived2��һ����ָ��

	3.funcUp(d).--->������ת��ʱ��dynamic_cast��static_cast��Ч����һ����
		0.funcUp()������ȷִ��

	4.funcUp(b).--->ͬ��ת��
		0.funcUp()������ȷִ��
*/


2.static_cast <type_name> (expression)
	���ã�
		1.����type_name�ɱ���ʽת��Ϊexpression���������ͻ�expression�ɱ���ʽת��Ϊtype_name���������ͣ����������Ч��
		2.����High��Low�Ļ��࣬��Pond��һ���޹ص��࣬���High��Low��ת������Low��High��ת�����ǺϷ��ģ�����Low��Pond��ת���ǲ������
		3.���������������ת����ö��ֵ�Ϳ��Ա�ת��Ϊ���ͣ����Կ�����static_cast������ת��Ϊö����
		4.����ʹ��static_cast��doubleת��Ϊint����floatת��Ϊlong�Լ�����������ֵת��

code:
class High {};
class Low :public High {};
High bar;
Low blow;
High * pb = static_cast<High *> (&blow); // valid upcast,��ת��������ʾ�Ľ���
Low  * pl = static_cast<Low *> (&bar);   // valid downcast����ת���Ǵӻ���ָ�뵽������ָ�룬�ڲ�������ʾ����ת��������£����޷����С�
										 // �������������������ת��������Խ�����һ�����������ת�������ʹ��static_cast����������ת���ǺϷ��ġ�
Pond * pmer = static_cast<Pond *> (&blow); // invalid, Pond unrelated




3.const_cast  <type_name> (expression) : ����ִ��ֻ��һ����;������ת�������ı�ֵΪconst �� volatile��

	���ã�
		1.������͵���������Ҳ���޸ģ�����������ת��������������const��volatile����(�л���)���Բ�ͬ�⣬type name �� expression �����ͱ�����ͬ��
		2.���������Ŀ������ : ��ʱ�������Ҫһ��ֵ�����ڴ����ʱ���ǳ���������ʱ���ǿ����޸ĵġ��ڴ�����£����Խ����ֵ����Ϊconst, ������Ҫ�޸�����ʱ��ʹ��const_cast.
		  �˲���Ҳ����ͨ��ͨ������ת����ʵ�֣���ͨ��ת��Ҳ����ͬʱ�ı����͡�
		  High bar;
		  const High * pbar = &bar;
		  High * pb = (High *)(bar); // valid
		  Low *pl = (Low *)(pbar); // valid

code:
class High {};
class Low :public High {};
High bar;
const High *pbar = &bar; 
High *pb = const_cast<High *>(pbar); // valid. ʹ��*pb��Ϊһ���������޸�bar����ֵ��ָ�룬��ɾ��const��ǩ
const Low *pb = const_cast<const Low *> (pbar);// invalid. ��Ϊ��ͬʱ���Խ����ʹ�const High * ��Ϊ const Low *��


4.reinterpret_cast �������������Σ�յ�����ת������������ɾ��const������ִ��������������Ĳ�����
	���ã�
		1.reinterpret_cast����֧�����е�����ת����
			eg.���Խ�ָ������ת��Ϊ���Դ洢ָ���ʾ�����ͣ������ܽ�ָ��ת��Ϊ��С�������򸡵���
		2.���ܽ�����ָ��ת��Ϊ����ָ�룬��֮��Ȼ��
		3.char ch = char ( &d )// convert address to a char
		  //������ת����c������������ģ�����C++��ͨ����������Ϊ���ڶ���C++ʵ�֣�char���Ͷ�̫С�����ܴ洢ָ�롣
code:
struct dat { short a; short b; };
long value = 0xA224B118;
dat *pd = reinterpret_cast<dat *>(&value);
cout << hex << pd->a; // display first 2 bytes of value
