/*
 * @file   3.Inheritance with virtual functions.cpp
 * @date   2019.2.22.
 * @author GBW
 * @Description: 
 
 * @Note:
 
 */
1.non-virtual函数:你不希望drived class 重新定义(override,覆盖)它。
	int objectID() const;
2.virtual函数:你希望derived class 重新定义它，且你对它已有默认定义。
	virtual void erroe(const string& msg);
3.pure virtual函数: 你希望derived class 一定要定义它，你对它没有默认定义。
	virtual void draw() const = 0;
class Shape {
public:
	
	
		
};