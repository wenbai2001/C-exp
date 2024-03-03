#define _CRT_SECURE_NO_WARNINGS 
#include <iomanip> 
#include <exception>
#include <typeinfo>
#include <string.h>
using namespace std;
template <typename T>
class MAT {
	T* const e;							//指向所有整型矩阵元素的指针
	const int r, c;							//矩阵的行r和列c大小
public:
	MAT(int r, int c);						//矩阵定义
	MAT(const MAT& a);				//深拷贝构造
	MAT(MAT&& a)noexcept;			//移动构造
	virtual ~MAT()noexcept;
	virtual T* const operator[ ](int r);//取矩阵r行的第一个元素地址，r越界抛异常
	virtual MAT operator+(const MAT& a)const;	//矩阵加法，不能加抛异常
	virtual MAT operator-(const MAT& a)const;	//矩阵减法，不能减抛异常
	virtual MAT operator*(const MAT& a)const;	//矩阵乘法，不能乘抛异常
	virtual MAT operator~()const;					//矩阵转置
	virtual MAT& operator=(const MAT& a);		//深拷贝赋值运算
	virtual MAT& operator=(MAT&& a)noexcept;	//移动赋值运算
	virtual MAT& operator+=(const MAT& a);		//“+=”运算
	virtual MAT& operator-=(const MAT& a);		//“-=”运算
	virtual MAT& operator*=(const MAT& a);		//“*=”运算
//print输出至s并返回s：列用空格隔开，行用回车结束
	virtual char* print(char* s)const noexcept;
};

extern const char* TestMAT(int& s);

template <class T> MAT<T>::MAT(int r, int c) :e(new T[(r * c)]()), r(r), c(c) {} //矩阵定义

template <class T> MAT<T>::MAT(const MAT& a) : e(new T[(a.r * a.c)]()), r(a.r), c(a.c) {	 //深拷贝构造
	for (int i = 0; i < c * r; i++)
	{
		e[i] = a.e[i];
	}
}

template <class T> MAT<T>::MAT(MAT&& a)noexcept :e(a.e), r(a.r), c(a.c) {  //移动构造
	*(T*)&a.c = 0;
	*(T**)&a.e = NULL;
	*(T*)&a.r = 0;
}

template <class T> MAT<T>::~MAT()noexcept {   //析构函数
	if (e)
	{
		//*(T *)&c = 0;
		*(T**)&e = NULL;
		//*(T *)&r = 0;
	}
}

template <class T> T* const MAT<T>:: operator[ ](int r) { //取矩阵r行的第一个元素地址
	if (r < 0 || r > MAT<T>::r - 1)
	{
		throw("the row is overflowed");
		return NULL;
	}
	else {
		return &e[r * c];
	}
}

template <class T> MAT<T>  MAT<T>::operator+(const MAT& a)const {	//矩阵加法
	if (r == a.r && c == a.c)
	{
		MAT<T> x(r, c);
		for (int i = 0; i < r * c; i++)
		{
			x.e[i] = e[i] + a.e[i];
		}
		return x;
	}
	else
	{
		throw("less than 0");
		return *this;
	}
}

template <class T> MAT<T>  MAT<T>::operator-(const MAT& a)const {	//矩阵减法
	if (r == a.r && c == a.c)
	{
		MAT<T> x(r, c);
		for (int i = 0; i < r * c; i++)
		{
			x.e[i] = e[i] - a.e[i];
		}
		return x;
	}
	else
	{
		throw("less than 0");
		return *this;
	}
}

template <class T> MAT<T>  MAT<T>::operator*(const MAT& a)const {	//矩阵乘法
	if (c == a.r)
	{
		MAT<T> x(r, a.c);
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < a.c; j++)
			{
				for (int p = 0; p < c; p++)
				{
					x.e[i * a.c + j] += e[i * c + p] * a.e[p * a.c + j];	//根据矩阵乘法规则进行累加
				}
			}
		}
		return x;
	}
	else
	{
		throw("less than 0");
		return *this;
	}
}

template <class T> MAT<T>  MAT<T>:: operator~()const {	//矩阵转置
	MAT<T> x(c, r);
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			x.e[i * c + j] = e[j * r + i];
		}
	}
	return x;
}

template <class T> MAT<T>& MAT<T>:: operator=(const MAT& a)		//深拷贝赋值运算
{
	if (this == &a) return *this;
	if (e) delete(e);
	*(T*)&c = a.c;
	*(T*)&r = a.r;
	*(T**)&e = new T[r * c]();
	for (int i = 0; i < r * c; i++)
	{
		e[i] = a.e[i];
	}
	return *this;
}

template <class T> MAT<T>& MAT<T>:: operator=(MAT&& a)noexcept	//移动赋值运算
{
	if (this == &a) return *this;
	if (e) delete(e);
	*(T*)&c = a.c;
	*(T*)&r = a.r;
	*(T**)&e = a.e;
	*(T*)&a.r = 0;
	*(T*)&a.c = 0;
	*(T**)&a.e = NULL;
	return *this;
}

template <class T> MAT<T>& MAT<T>::operator+=(const MAT& a) {	//+=
	if (r == a.r && c == a.c)
	{
		for (int i = 0; i < r * c; i++)
		{
			e[i] += a.e[i];
		}
		return *this;
	}
	else
	{
		throw("less than 0");
		return *this;
	}
}

template <class T> MAT<T>& MAT<T>::operator-=(const MAT& a) {	//-=
	if (r == a.r && c == a.c)
	{
		for (int i = 0; i < r * c; i++)
		{
			e[i] -= a.e[i];
		}
		return *this;
	}
	else
	{
		throw("less than 0");
		return *this;
	}
}

template <class T> MAT<T>& MAT<T>::operator*=(const MAT& a) {	//矩阵乘法
	if (c == a.r)
	{
		MAT<T> x(r, a.c);
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < a.c; j++)
			{
				for (int p = 0; p < c; p++)
				{
					x.e[i * a.c + j] += e[i * c + p] * a.e[p * a.c + j];	//根据矩阵乘法规则进行累加
				}
			}
		}
		for (int i = 0; i < r * c; i++)
		{
			e[i] = x.e[i];
		}
		return *this;
	}
	else
	{
		throw("less than 0");
		return *this;
	}
}

template <class T> char* MAT<T>::print(char* s)const noexcept {	//输出：每列用空格隔开，每行回车结束
	int buf = 0;
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			if (typeid(T) == typeid(int)) {	//整型变量
				buf += sprintf(s + buf, "%6ld ", e[i * c + j]);
			}
			else if (typeid(T) == typeid(float)) {	//浮点型变量
				buf += sprintf(s + buf, "%8f ", e[i * c + j]);
			}
			else if (typeid(T) == typeid(double)) {	//double
				buf += sprintf(s + buf, "%8lf ", e[i * c + j]);
			}
			else
				//long long
			{
				buf += sprintf(s + buf, "%6lld ", e[i * c + j]);
			}
		}
		buf += sprintf(s + buf, "\n");
	}
	return s;
}













template MAT<long long>;
template MAT<int>;


int main(int argc, char* argv[]) 					//请扩展main()测试其他运算
{
	/*
	MAT<int>   a(1, 2), b(2, 2), c(1, 2);
	char t[2048];
	a[0][0] = 1;			//类似地初始化矩阵的所有元素
	a[0][1] = 2; 			//等价于“*(a.operator[ ](0)+1)=2;”即等价于“*(a[0]+1)=2;”
	a.print(t);			//初始化矩阵后输出该矩阵
	b[0][0] = 3; 	b[0][1] = 4;		//调用T* const operator[ ](int r)初始化数组元素
	b[1][0] = 5; 	b[1][1] = 6;
	b.print(t);
	c = a * b;						//测试矩阵乘法运算
	c.print(t);
	(a + c).print(t);					//测试矩阵加法运算
	c = c - a;						//测试矩阵减法运算
	c.print(t);
	c += a;							//测试矩阵“+=”运算
	c.print(t);
	c = ~a;							//测试矩阵转置运算
	c.print(t);
	return 0;
	*/
	int mark;
	const char* e = TestMAT(mark);
	printf("%s\n%d", e, mark);
	return 0;
}
