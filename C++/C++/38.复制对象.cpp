class Base {
public:
	Base(int x) :a(x) {
	}
	Base(const Base& rhs) :a(rhs.a) {
	}
	Base& operator=(const Base& rhs) {
		a = rhs.a;
		return *this;
	}

	~Base() {}
	void show() { cout << "Base" << a << endl; }
private:
	int a;

};


class Derived :public Base {
public:
	Derived(int x, int y) :Base(x), b(y) {
	}
	Derived(const Derived& rhs) :Base(rhs), b(rhs.b) {
	}
	Derived& operator=(const Derived& rhs) {

		Base::operator=(rhs); //**调用基类的赋值操作符**
		b = rhs.b;
		return *this;
	}
	~Derived() {}
private:
	int b;
};


int main() {

	Derived s1(3, 4);
	s1.show();
	Derived s2(5, 6);
	s2.show();
	s2 = s1;
	s2.show();
}