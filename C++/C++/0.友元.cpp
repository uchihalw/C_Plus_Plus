/*
* @file   0.��Ԫ.cpp
* @date   2019.2.21.
* @author GBW
* @Description:

* @Note:
1.��Ԫ����Ԫ��������Ԫ�ࡢ��Ԫ��Ա����
2.��Ϊ�����ض�Ԫ�����ʱ    <<<<<<�����������������>>>>>>     ������Ҫ��Ԫ---��Timer�������ʵ�������ڴ������
��Timerʵ���У����صļӷ��ͼ������㶼�������Timerֵ�����˷����㽫һ��Timerֵ��һ��doubleֵ��ϣ��˾������˸��������ʹ�÷�ʽ��
���Ĳ������ǵ��ö��󣬼� A = B * 2.5 equal to A = B.operator*( 2.75 )
���� A = 2.75 * B // cannot correspond to a member function
3.���2����������ķ���
1.�������Ѻ�-�ͻ�����Ľ������
2.�ǳ�Ա����(�ǳ�Ա���������ɶ�����õģ���ʹ�õ�����ֵ������ʾ����)
1.A = 2.75 * B equal to Time operator* (doubel m, const Timer &t)
2.�ǳ�Ա��������ֱ�ӷ������˽�����ݣ�Ȼ����һ������ķǳ�Ա�������Է������˽�г�Ա������Ԫ������
4.������Ԫ����
1.����Ԫ����ԭ�ͷ����������У�����ԭ������ǰ���Ϲؼ���friend
friend Time operator* (int m, const Time & t);
2.��д�������壬��Ϊ�䲻�ǳ�Ա�������ʲ�Ҫʹ�� Time:: �޶����� ���ⲻҪ�ڶ�����ʹ�ùؼ���friend
Time operator*(int m, const Time & t){....}
3.�����Ԫ�����Ƿǳ�Ա�����������Ȩ�����Ա������ͬ��



5.����������ʽ�ıȽ�
�ڶ�������£������������Ϊ��ĳ�Ա�����������Ԫ���������ԡ�����Ա�������������Ԫ���������Ҳ���и��Ե��ص㣺
(1) һ������£���Ŀ������������Ϊ��ĳ�Ա������˫Ŀ��������������Ϊ�����Ԫ������
(2) ����һЩ˫Ŀ�������������Ϊ�����Ԫ������=��()��[]��->��
(3) ����ת������ֻ�ܶ���Ϊһ����ĳ�Ա���������ܶ���Ϊ�����Ԫ������
(4) ��һ��������Ĳ�����Ҫ�޸Ķ����״̬��ѡ������Ϊ��Ա�����Ϻá�
(5) �����������Ĳ������������ǵ�һ����������ϣ������ʽ����ת������ֻ��ѡ����Ԫ������
(6) �������������һ����Ա����ʱ������ߵĲ�����������ֻ������ߵĲ���������������������һ������󣨻����ǶԸ����������ã��������ߵĲ�����������һ����ͬ��Ķ��󣬻�����һ���ڲ����͵Ķ��󣬸����������������Ϊһ����Ԫ������ʵ�֡�
(7) ����Ҫ������������пɽ�����ʱ��ѡ������Ϊ��Ԫ������
*/


// ������Ԫ
class Time
{
public:
	Time(int m_Data) :m_Data(m_Data) {}
	Time() {}
	Time operator+ (const Time & timer)
	{
		Time res;
		res.m_Data = this->m_Data + timer.m_Data;
		return res;
	}

	Time operator* (const Time & timer) // call with Time T  = Time * Time
	{
		Time res;
		res.m_Data = this->m_Data * timer.m_Data;
		return res;
	}
	void show()
	{
		cout << this->m_Data << endl;
	}
	friend Time operator* (int m, const Time & timer);
private:
	int m_Data;
};

Time operator*(int m, const Time & timer) // call with Time T = operator*( int, Time t) or Time T = int * Time
{
	Time time;
	time.m_Data = m * timer.m_Data;
	return time;
}