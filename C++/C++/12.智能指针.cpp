/*
 * @file   12.����ָ��.cpp
 * @date   2019.3.5.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0. auto_ptr��unique_ptr��shared_ptr
	������ָ�����ʱ��������������ʹ��delete���ͷ��ڴ档��ˣ������new���صĵ�ַ��ֵ��
	��Щ���󣬽������ס�Ժ��ͷ���Щ�ڴ�:������ָ�����ʱ����Щ�ڴ潫�Զ����ͷš�
void demo_1()
{
	doubel * pd = new double; // Ϊpd��һ��doubleֵ����洢�ռ䣬�����ַ
	*pd = 25;				  // ��ֵ���Ƶ���̬�ڴ���
	return;					  // ɾ��pd,ֵ�������ڶ�̬�ڴ���
}

void demo_2()
{
	auto_ptr<double> ap(new double); // Ϊap��һ��doubleֵ����洢�ռ䱣���ַ
	*ap = 25;						 // ��ֵ���Ƶ���̬�ڴ���
	return;							 // ɾ��ap,ap�����������ͷŶ�̬�ڴ�
}
// unique_ptr<double> pdu(new double);
// auto_ptr<string> ps(new string);

1. ��������ָ����󣬱������ͷ�ļ�memory,���ļ�ģ�嶨�塣
auto_ptr:
template<class x>
class auto_ptr {
public:
	explicit auto_ptr(x *p = 0) throw();
};

#include <memory>
void remodel(siring &str)
{
	auto_ptr<string> ps(new string(str));
	str = *ps;
	return;
}


2. ��������ָ���඼��һ��explicit���캯�����ù��캯����ָ����Ϊ��������˲���Ҫ�Զ���ָ��ת��Ϊ���ܶ���


3.����ָ���ע������
auto_ptr<string> ps(new string("hello world"));
auto_ptr<string> vocation;
vocation = ps;

	1. �����������ָ�붼�ǳ���ָ�룬������ָ�뽫ָ��ͬһ��string����
	���ǲ��ܽ��ܵģ���Ϊ������ͼɾ��ͬһ���������� : һ����ps����ʱ��һ����vocation����ʱ��
		Ҫ�����������⣺
		1.���帳ֵ���㣬ʹִ֮����ƣ�������ָ��ָ��ͬ�Ķ�������һ����������һ������ĸ���
		2.��������Ȩ��������ض�����ֻ����һ������ָ���ӵ����������ֻ��ӵ�ж��������ָ��Ĺ��캯����ɾ���ö���
		Ȼ���ø�ֵ����ת������Ȩ�����������auto_ptr��unique_prt�Ĳ��ԡ�
		3.�������ܸ��ߵ�ָ�룬���������ض����������ָ���������Ϊ���ü�����
		eg : ��ֵʱ������ + 1����ָ�����ʱ������ - 1���������һ��ָ�����ʱ���ŵ���delete.����shared_ptr���õĲ��ԡ�

	void main()
	{
		auto_ptr<string> file[3] = {
			auto_ptr<string> (new string("first"));
			auto_ptr<string> (new string("second"));
			auto_ptr<string> (new string("third"));
		}
		// method_1 :�����н׶α���
		auto_ptr<string> pwin;
		pwin = file[1]; // file[1] loose ownership
		cout<<*file[1] <<endl; // error, file[1]�������ø��ַ�������auto_ptr�������������Ȩ�󣬱����ʹ���������ʸö���

		// method_2 :��������
		shared_ptr<string> pwin;
		pwin = file[1];  
		// pwin��file[1]ָ��ͬһ�����󣬶����ü�����1���ӵ�2.
		// �ڳ���ĩβ����������pwin���ȵ������������������������������ý��͵�1��
		// Ȼ��shared_ptr����ĳ�Ա���ͷţ���file[1]������������ʱ���������ü������͵�0�����ͷ���ǰ����Ŀռ䡣
		cout<<*file[1]<<endl;

		// method_3 :���򲻻�ȵ����н׶α������ڱ����ڼ䱨��
		unique_ptr<string> pwin;
		pwin = file[1];  // file[1] loose ownership
		cout << *file[1] << endl;
	}

	2. unique_ptr��auto_ptr
	// method_1
	auto_ptr<string> p1(new string("hello"));
	auto_ptr<string> p2;
	p2 = p1; 
	/*
	p2�ӹ�string���������Ȩ��p1������Ȩ�������ᡣ�ɷ�ֹp1��p2������������ͼɾ��ͬһ������
	�������������ͼʹ��p1���⽫�ǻ��£���Ϊp1����ָ����Ч����
	*/


	// method_2
	unique_ptr<string> p3(new string("hello"));
	unique_ptr<string> p4;
	p4 = p3;
	/*
	��������Ϊp4 = p3���Ƿ���������p3����ָ����Ч���ݵ����⡣(������׶δ���)
	*/
	

	// method_3
	unique_ptr<string> pu1(new string("hello"));
	unique_ptr<string> pu2;
	pu2 = pu1; // ���������������ҵ�unique_ptr(pu1)
	unique_ptr<string> pu3;
	pu3 = unique_ptr<string>(new string("hello")) // ����,�����������ҵ�unique_ptr(pu2)����Ϊ���õ���unique_ptr�Ĺ��캯�����ù��캯����������ʱ������������Ȩת�ø�pu3��ͻᱻ���١�


	/* ��ʹ��new�����ڴ�ʱ������ʹ��auto_ptr��shared_ptr�� ��ʹ��new��new[] �����ڴ�ʱ������ʹ��unique_ptr */

	4. ѡ������ָ��
		1.shared_ptr
		����Ҫʹ�ö��ָ��ͬһ�������ָ�롣
		2.unique_ptr
			1.������Ҫ���ָ��ͬһ�������ָ�롣�������ʹ��new�����ڴ棬������ָ����ڴ��ָ�룬���䷵����������Ϊunipue_ptr�ǲ����ѡ��
			��Ϊ������Ȩ��ת�ø����ܷ���ֵ��unique_ptr����������ָ�뽫�������delete
			2.unique_ptrΪ��ֵʱ���ɽ��丳ֵ��shared_ptr
			// make() return type is unique_ptr<int>
			unique_ptr<int> pup(make()); // ok
			shared_ptr<int> spp(pup);        // not allowed
			shared_ptr<int> spr(make());     // ok
			// shared_ptr����һ����ʾ���캯���������ڽ���ֵunique_ptrת��Ϊshared_ptr��shared_ptr���ӹ�ԭ����unique_ptr���еĶ���