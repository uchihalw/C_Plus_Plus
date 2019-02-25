/*
 * @file   6.����string��ʵ�ֹ���.cpp
 * @date   2019.2.24.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
class String
{
public:
	String(const char* cstr = 0);
	String(const String& str); // ��������
	String& operator=(const String& str); // ������ֵ������String& ����Ϊ���Ҫ���صĽ��Ҫ�ŵ��ֲ�����
	~String();
	char* get_c_str() const { return m_data; } // ��Ϊget_c_str()û�иı亯�����ڵı������ʼ�const
private:
	char* m_data;
};

inline String::String(const char* cstr = 0)
{
	if (cstr) // �洫�����ķ���ռ�
	{
		m_data = new char[strlen[cstr] + 1]; // cstr = "hello"; strlen(cstr) = 5; m_dataҲҪ���'\0'
		strcpy(m_data, cstr);
	}
	else // δָ����ʼֵ
	{
		m_data = new char[1];
		*m_data = '\0';

	}
}

String::~String()
{
	delete[] m_data;
}

String::String(const String& str)
{
	m_data = new char[strlen[str.m_data] + 1]; 
	strcpy(m_data, str);
}

String& String:: operator=(const String& str)
{
	if (this == &str) // ������ֵһ��Ҫע���ǲ������Ҹ�ֵ
		return *this;
	delete[] m_data;
	m_data = new char[strlen[str.m_data] + 1];
	strcpy(m_data, str.m_data);
	return *this;
	/* 
	int x, y, z;
	x = y = z = 15;
	��ֵ�����ҽ���ɣ���������������ֵ������Ϊ:x = (y = (x = 15))
	Ϊʵ��������ֵ����ֵ���������뷵��һ��referenceָ������������ʵ�Ρ�
	*/
}