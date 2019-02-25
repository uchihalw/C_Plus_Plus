/*
 * @file   6.复现string的实现过程.cpp
 * @date   2019.2.24.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
class String
{
public:
	String(const char* cstr = 0);
	String(const String& str); // 拷贝构造
	String& operator=(const String& str); // 拷贝赋值。返回String& 是因为结果要返回的结果要放到局部变量
	~String();
	char* get_c_str() const { return m_data; } // 因为get_c_str()没有改变函数体内的变量，故加const
private:
	char* m_data;
};

inline String::String(const char* cstr = 0)
{
	if (cstr) // 替传进来的分配空间
	{
		m_data = new char[strlen[cstr] + 1]; // cstr = "hello"; strlen(cstr) = 5; m_data也要存放'\0'
		strcpy(m_data, cstr);
	}
	else // 未指定初始值
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
	if (this == &str) // 拷贝赋值一定要注意是不是自我赋值
		return *this;
	delete[] m_data;
	m_data = new char[strlen[str.m_data] + 1];
	strcpy(m_data, str.m_data);
	return *this;
	/* 
	int x, y, z;
	x = y = z = 15;
	赋值采用右结合律，所以上述连锁赋值被解析为:x = (y = (x = 15))
	为实现连锁赋值，赋值操作符必须返回一个reference指向操作符的左侧实参。
	*/
}