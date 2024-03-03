#define _CRT_SECURE_NO_WARNINGS 
#include <iomanip> 
#include <exception>
#include <typeinfo>
#include <string.h>
using namespace std;
template <typename T>
class MAT {
	T* const e;							//ָ���������;���Ԫ�ص�ָ��
	const int r, c;							//�������r����c��С
public:
	MAT(int r, int c);						//������
	MAT(const MAT& a);				//�������
	MAT(MAT&& a)noexcept;			//�ƶ�����
	virtual ~MAT()noexcept;
	virtual T* const operator[ ](int r);//ȡ����r�еĵ�һ��Ԫ�ص�ַ��rԽ�����쳣
	virtual MAT operator+(const MAT& a)const;	//����ӷ������ܼ����쳣
	virtual MAT operator-(const MAT& a)const;	//������������ܼ����쳣
	virtual MAT operator*(const MAT& a)const;	//����˷������ܳ����쳣
	virtual MAT operator~()const;					//����ת��
	virtual MAT& operator=(const MAT& a);		//�����ֵ����
	virtual MAT& operator=(MAT&& a)noexcept;	//�ƶ���ֵ����
	virtual MAT& operator+=(const MAT& a);		//��+=������
	virtual MAT& operator-=(const MAT& a);		//��-=������
	virtual MAT& operator*=(const MAT& a);		//��*=������
//print�����s������s�����ÿո���������ûس�����
	virtual char* print(char* s)const noexcept;
};

extern const char* TestMAT(int& s);

template <class T> MAT<T>::MAT(int r, int c) :e(new T[(r * c)]()), r(r), c(c) {} //������

template <class T> MAT<T>::MAT(const MAT& a) : e(new T[(a.r * a.c)]()), r(a.r), c(a.c) {	 //�������
	for (int i = 0; i < c * r; i++)
	{
		e[i] = a.e[i];
	}
}

template <class T> MAT<T>::MAT(MAT&& a)noexcept :e(a.e), r(a.r), c(a.c) {  //�ƶ�����
	*(T*)&a.c = 0;
	*(T**)&a.e = NULL;
	*(T*)&a.r = 0;
}

template <class T> MAT<T>::~MAT()noexcept {   //��������
	if (e)
	{
		//*(T *)&c = 0;
		*(T**)&e = NULL;
		//*(T *)&r = 0;
	}
}

template <class T> T* const MAT<T>:: operator[ ](int r) { //ȡ����r�еĵ�һ��Ԫ�ص�ַ
	if (r < 0 || r > MAT<T>::r - 1)
	{
		throw("the row is overflowed");
		return NULL;
	}
	else {
		return &e[r * c];
	}
}

template <class T> MAT<T>  MAT<T>::operator+(const MAT& a)const {	//����ӷ�
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

template <class T> MAT<T>  MAT<T>::operator-(const MAT& a)const {	//�������
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

template <class T> MAT<T>  MAT<T>::operator*(const MAT& a)const {	//����˷�
	if (c == a.r)
	{
		MAT<T> x(r, a.c);
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < a.c; j++)
			{
				for (int p = 0; p < c; p++)
				{
					x.e[i * a.c + j] += e[i * c + p] * a.e[p * a.c + j];	//���ݾ���˷���������ۼ�
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

template <class T> MAT<T>  MAT<T>:: operator~()const {	//����ת��
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

template <class T> MAT<T>& MAT<T>:: operator=(const MAT& a)		//�����ֵ����
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

template <class T> MAT<T>& MAT<T>:: operator=(MAT&& a)noexcept	//�ƶ���ֵ����
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

template <class T> MAT<T>& MAT<T>::operator*=(const MAT& a) {	//����˷�
	if (c == a.r)
	{
		MAT<T> x(r, a.c);
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < a.c; j++)
			{
				for (int p = 0; p < c; p++)
				{
					x.e[i * a.c + j] += e[i * c + p] * a.e[p * a.c + j];	//���ݾ���˷���������ۼ�
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

template <class T> char* MAT<T>::print(char* s)const noexcept {	//�����ÿ���ÿո������ÿ�лس�����
	int buf = 0;
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			if (typeid(T) == typeid(int)) {	//���ͱ���
				buf += sprintf(s + buf, "%6ld ", e[i * c + j]);
			}
			else if (typeid(T) == typeid(float)) {	//�����ͱ���
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


int main(int argc, char* argv[]) 					//����չmain()������������
{
	/*
	MAT<int>   a(1, 2), b(2, 2), c(1, 2);
	char t[2048];
	a[0][0] = 1;			//���Ƶس�ʼ�����������Ԫ��
	a[0][1] = 2; 			//�ȼ��ڡ�*(a.operator[ ](0)+1)=2;�����ȼ��ڡ�*(a[0]+1)=2;��
	a.print(t);			//��ʼ�����������þ���
	b[0][0] = 3; 	b[0][1] = 4;		//����T* const operator[ ](int r)��ʼ������Ԫ��
	b[1][0] = 5; 	b[1][1] = 6;
	b.print(t);
	c = a * b;						//���Ծ���˷�����
	c.print(t);
	(a + c).print(t);					//���Ծ���ӷ�����
	c = c - a;						//���Ծ����������
	c.print(t);
	c += a;							//���Ծ���+=������
	c.print(t);
	c = ~a;							//���Ծ���ת������
	c.print(t);
	return 0;
	*/
	int mark;
	const char* e = TestMAT(mark);
	printf("%s\n%d", e, mark);
	return 0;
}
