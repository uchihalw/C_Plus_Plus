/*
 * @file   3.Inheritance with virtual functions.cpp
 * @date   2019.2.22.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
1.non-virtual����:�㲻ϣ��drived class ���¶���(override,����)����
	int objectID() const;
2.virtual����:��ϣ��derived class ���¶������������������Ĭ�϶��塣
	virtual void erroe(const string& msg);
3.pure virtual����: ��ϣ��derived class һ��Ҫ�������������û��Ĭ�϶��塣
	virtual void draw() const = 0;
class Shape {
public:
	
	
		
};