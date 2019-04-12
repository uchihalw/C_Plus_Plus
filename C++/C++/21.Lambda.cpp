/*
 * @file   21.Lambda.cpp
 * @date   2019.3.13.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
0. ��������һ������������б����ж����ж��ٸ������ɱ�3���������ٸ������ɱ�13������
	// version_1
	0. ���������б�
		vector<int> numbers(1000);
		generate(vector.begin(), vector.end(), rand) // ����һ�����䣬����ÿ��Ԫ������Ϊ�������������ص�ֵ���ҵ�����������һ���������κβ����ĺ�������
	1. count_if(),�����ж��ٸ�Ԫ�ؿɱ�3����
		bool f3(int x) { return x % 3 == 0; }
		bool f13(int x) { return x % 13 == 0; }
		int cnt1 = count_if(numbers.begin(), numbers.end(), f3);
		int cnt2 = count_if(numbers.begin(), numbers.end(), f13);
	// version_2
	2. ʹ�ú��������
		class f_mod
		{
		private:
			int dv;
		public:
			f_mod(int d = 1):dv(d){}
			bool operator()(int x) { return x % dv == 0; }
		};
		// f_mod obj(3) // f_mod.dv set to 3
		bool is_div_by_3 = obj(7);// same as obj.operator()(7)
		int cnt3 = count_if(numbers.begin(), numbers.end(), f_mod(3));
		// ����f_mod(3)����һ�����󣬴洢��ֵ3��count_if()ʹ�øö���������operator()

1. lambda���������������
	0. C++11�У����ڽ��ܺ���ָ��������ĺ�������ʹ��������������(lambda)��Ϊ�����
		[](int x) { return x % 3 == 0;} // equal to f3(),ʹ��[]�����˺�����(���������������)��û�������������͡�
		// ���������൱��ʹ��decltyp���ݷ���ֵ�ƶϵõ���
		int cnt4 = count_if(numbers.begin(), numbers.end(), [](int x) { return x % 3 == 0; });
		// ����lambda���ʽ��ȫ��һ������������ʱ���Զ������ƶϲŹ��ã�������Ҫʹ�������ķ������ͺ����﷨

	1.lamdba��ʹ��
		auto mod3 = [](int x) { return x % 3 == 0; };
		int cnt4 = count_if(numbers.begin(), numbers.end(), mod3);
2. ����lambda���ʽ��ȫ��һ������������ʱ���Զ������ƶϲŹ��ã�
   ������Ҫʹ�������ķ������ͺ����﷨
   [] (double x) {return x;}
	[](double x)->double {x = x + 1.0; return x; }

3. lambda�ɷ����������ڵ��κζ�̬����:Ҫ����Ҫʹ�õı������ɽ������Ʒ�����������
	int cnt;
	cnt = std::count_if(vec.begin(), vec.end(), [] int(x) { return x; })

	// equal to
	int cnt = 0;
	for_each(vec.begin(), vec.end(), [&cnt] int(x) { return x= x+cnt; });

	// [&cnt]ʹ��lambda���������ʹ�ÿ���ʹ��cnt,������cnt�ǰ����ò���ģ����lambda�е��κ��޸Ķ���Ӱ��ԭʼcnt

4. [&]ʹ���ܹ���lambda��ʹ�����е��Զ�����������cnt2��cnt1
	int cnt1 = 0;
	int cnt2 = 0;
	std::for_each(vec.begin(), vec.end(), [&] int(x) { return x = x + cnt1 + cnt2; })

