/*
 * @file   8.RTTI.cpp
 * @date   2019.2.27.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0. RTTI ���н׶�����ʶ��
	1.����п��ܵĻ���dynamic_cast�������ʹ��һ��ָ������ֵ��������һ��ָ���������ָ�룻
      ���򣬸����������0-��ָ��
	2.typeid���������һ��ָ����������͵�ֵ
	3.type_info�ṹ�洢���й��ض����͵���Ϣ
	//** ֻ�ܽ�RTTI���ڰ����麯�������νṹ��ԭ������ֻ�ж����������νṹ����Ӧ�ý���������ĵ�ַ��ֵ������ָ�롣

1. dynamic_cast�����(���Իش��Ƿ���԰�ȫ�ؽ�����ĵ�ַ�����ض����͵�ָ��)

class Grand{ has virtual methods};
class Superb:public Grand {...};
class Magnificent:public Superb{...};

Grand* pg = new Grand;
Grand* ps = new Superb;
Grand* pm = new Magnificent;

// ����ת��
Magnificent* p1 = (Magnificent*) pm; // ��ȫ����Ϊ��Magnificent���͵�ָ��ָ������ΪMagnificent�Ķ���
Magnificent* p2 = (Magnificent*) pg; // ����ȫ����Ϊ���������ĵ�ַ����������ָ��(��������������������������������ͨ���ǲ����ܵģ���Ϊ��������ܺ��л���û�еĳ�Ա)
Superb * p3 = (Magnificent*) pm;     // ��ȫ����Ϊ������������ĵ�ַ��������ָ��

ͨ�������ָ��Ķ���*pt������ΪType�����Ǵ�Typeֱ�ӻ��߼���������������ͣ�������ı�ʾ��ָ��ptת��ΪType���͵�ָ��
Type *t = dynamic_cast<Type *>(pt)
���򣬽��Ϊ0������ָ�롣

2.typeid�������type_info��
	1. typeid(���� | ���Ϊ����ı��ʽ)�����ʹ���ܹ�ȷ�����������Ƿ�Ϊͬ����
	2. typeid���������һ����type_info���������
	3. type_info��ͷ�ļ���typeinfo
	4. typeid(Magnificent) == typeid(*pg) //���pgָ�����һ��Magnificent��������true,��֮Ϊfalse