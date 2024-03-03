#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
class QUEUE {
    int* const  elems;	//elems�����ڴ����ڴ�Ŷ��е�Ԫ��
    const  int  max;	//elems��������Ԫ�ظ���Ϊmax
    int   head, tail;	 	//����ͷhead��βtail���ӿ�head=tail;��ʼhead=tail=0
public:
    //QUEUE();
    QUEUE(int m);		//��ʼ�����У��������m��Ԫ��
    QUEUE(const QUEUE& q); 			//��q�����ʼ������
    QUEUE(QUEUE&& q)noexcept;		//��q�ƶ���ʼ������
    virtual operator int() const noexcept;	//���ض��е�ʵ��Ԫ�ظ���
    virtual int size() const noexcept;		//���ض�����������Ԫ�ظ���max
    virtual QUEUE& operator<<(int e);  	//��e�����β���������ص�ǰ����
    virtual QUEUE& operator>>(int& e); 	//�Ӷ��׳�Ԫ�ص�e�������ص�ǰ����
    virtual QUEUE& operator=(const QUEUE& q);//�����ֵ�����ر���ֵ����
    virtual QUEUE& operator=(QUEUE&& q)noexcept;//�ƶ���ֵ�����ر���ֵ����
    virtual char* print(char* s) const noexcept;//��ӡ������s������s
    virtual ~QUEUE();	 					//���ٵ�ǰ����
};

class STACK : public QUEUE {
    QUEUE q;
public:
    STACK(int m);                    		//��ʼ��ջ�������2m-2��Ԫ��
    STACK(const STACK& s);         		//��ջs�����ʼ��ջ
    STACK(STACK&& s)noexcept;     		//��ջs�ƶ�������ʼ��ջ
    int  size()const noexcept;		  		//����ջ��������2m
    operator int() const noexcept;	   		//����ջ��ʵ��Ԫ�ظ���
    STACK& operator<<(int e); 	     		//��e��ջ�������ص�ǰջ
    STACK& operator>>(int& e);     		//��ջ��e�������ص�ǰջ
    STACK& operator=(const STACK& s);	//�����ֵ�����ر���ֵջ
    STACK& operator=(STACK&& s)noexcept;//�ƶ���ֵ�����ر���ֵջ
    char* print(char* b)const noexcept;	//��ջ�׵�ջ����ӡջԪ�� 
    ~STACK()noexcept;	              	//����ջ
};


extern const char* TestSTACK(int& s);

QUEUE::QUEUE(int m) :elems(new int[m]), head(0), tail(0), max(m) {}  //��ʼ�����У��������m��Ԫ��
QUEUE::QUEUE(const QUEUE& q) : elems(new int[q.max]), head(q.head), tail(q.tail), max(q.max) {   //��q�����ʼ������
    for (int i = 0; i < max; i++)
    {
        elems[i] = q.elems[i];  //ͨ��ѭ����ֵ�ķ�ʽ��s��elemsд��p��
    }
}
QUEUE::QUEUE(QUEUE&& q)noexcept :elems(q.elems), head(q.head), tail(q.tail), max(q.max) {   //��q�ƶ���ʼ������
    *(int**)&q.elems = NULL;    //��q���
    q.head = 0;
    q.tail = 0;
    *(int*)&q.max = 0;
}
QUEUE::operator int() const noexcept {  //���ض��е�ʵ��Ԫ�ظ���
    if (max == 0)   //�����Ԫ����Ϊ0ʱֱ�ӷ���0
    {
        return 0;
    }
    return (tail + max - head) % max;   //����ͷβλ���Լ����Ԫ��������ʵ�ʵ�Ԫ�ظ���
}
int QUEUE::size() const noexcept {  //���ض�����������Ԫ�ظ���max
    return max;
}
QUEUE& QUEUE::operator<<(int e) {  //��e�����β���������ص�ǰ����
    if (head == (tail + 1) % max)  //���������ʱthrow������Ϣ
    {
        throw "QUEUE is full!";
    }
    else
    {
        *(int*)&elems[tail] = e;  //��Ϊ������ʱͨ���޸�β��ʵ�����
        tail = (tail + 1) % max;
    }
    return *this;
}
QUEUE& QUEUE::operator>>(int& e) { //�Ӷ��׳�Ԫ�ص�e�������ص�ǰ����
    if (head == tail) //�ն��г���ʱthrow������Ϣ
    {
        throw "QUEUE is empty!";
    }
    else
    {
        e = elems[head];  //��Ϊ�ն���ʱͨ���޸�ͷ��ʵ�ֳ���
        head = (head + 1) % max;
    }
    return *this;
}
QUEUE& QUEUE::operator=(const QUEUE& q) {  //�����ֵ�����ر���ֵ����
    if (elems == q.elems)    //������q��ͬʱ�����⿼��
    {
        return *this;
    }
    else if (elems != NULL)  //���в�Ϊ��ʱfree��ֹ���������
    {
        free(elems);
    }
    *(int**)&elems = (int*)malloc(sizeof(int) * q.max);
    head = q.head;
    tail = q.tail;
    *(int*)&max = q.max;
    for (int i = 0; i < q.max; i++)
    {
        elems[i] = q.elems[i];
    }
    return *this;
}
QUEUE& QUEUE::operator=(QUEUE&& q)noexcept {   //�ƶ���ֵ�����ر���ֵ����
    if (elems == q.elems)    //������q��ͬʱ�����⿼��
    {
        return *this;
    }
    else if (elems != NULL)  //���в�Ϊ��ʱfree��ֹ���������
    {
        free(elems);
    }
    *(int**)&elems = q.elems;
    head = q.head;
    tail = q.tail;
    *(int*)&max = q.max;
    *(int**)&q.elems = NULL;
    q.head = 0;
    q.tail = 0;
    *(int*)&q.max = 0;
    return *this;
}
char* QUEUE::print(char* s) const noexcept {    //��ӡ������s������s
    int pos = head;  //pos������¼��ǰλ��
    int offset = 0;
    int num = (tail + max - head) % max;
    if (max == 0)
    {
        num = 0;
    }
    for (int i = 0; i < num; i++) //����Ԫ������ѭ��
    {
        offset += sprintf(s + offset, "%d,", elems[pos]);    //offset����ƫ����
        pos = (pos + 1) % max;
    }
    s[offset - 1] = '\0';
    return s;
}
QUEUE::~QUEUE() {   //���ٵ�ǰ����
    if (elems)
    {
        free(elems);
        *(int**)&elems = NULL;
        *(int*)&max = 0;
        head = 0;
        tail = 0;
    }
}

STACK::STACK(int m) :QUEUE(m), q(m) {}   //��ʼ��ջ�������2m-2��Ԫ��

STACK::STACK(const STACK& s) : QUEUE(s), q(s.q) {}//��ջs�����ʼ��ջ


STACK::STACK(STACK&& s)noexcept :QUEUE(std::move(s)), q(std::move(s.q)) {}   //��ջs�ƶ�������ʼ��ջ


int  STACK::size()const noexcept {  //����ջ��������2m
    return 2 * q.size();
}

STACK::operator int() const noexcept {  //����ջ��ʵ��Ԫ�ظ���
    return QUEUE::operator int() + int(q);
}

STACK& STACK::operator<<(int e) {   //��e��ջ�������ص�ǰջ
    if (QUEUE::operator int() < QUEUE::size() - 1)    //������δ��ʱֱ����ջ
    {
        QUEUE::operator<<(e);
    }
    else if (q.operator int() < q.size() - 1) //��������ջδ��ʱ���û����б������µ�m-1��Ԫ�أ�����Ԫ�ر�������һ������
    {
        int x;
        QUEUE::operator>>(x);
        q.operator<<(x);
        QUEUE::operator<<(e);
    }
    else//ջ��ʱ����
    {
        throw("STACK is full!");
    }
    return *this;
}

STACK& STACK::operator>>(int& e) {  //��ջ��e�������ص�ǰջ
    int x, y;
    int num = STACK::operator int();
    if (QUEUE::operator int() == 0) {   //�ж�ջ�Ƿ�Ϊ�գ�ջ��ʱ����
        throw("STACK is empty!");
    }
    else if (q.operator int() == 0)
    {
        for (int i = 0; i < num - 1; i++)
        {
            QUEUE::operator>>(x);   //ͨ����ջ��ջ������ջԪ���ƶ�������λ��
            QUEUE::operator<<(x);
        }
        QUEUE::operator>>(e);
    }
    else {
        for (int i = 0; i < q.size() - 2; i++)
        {
            QUEUE::operator>>(x);   //ͨ����ջ��ջ������ջԪ���ƶ��������г���λ��
            q.operator>>(y);
            QUEUE::operator<<(y);
            q.operator<<(x);
        }
        QUEUE::operator>>(e);
        q.operator>>(x);
        QUEUE::operator<<(x);
        for (int i = 0; i < num - q.size(); i++)    //��ջ��ԭ�ɱ�׼�����ʽ
        {
            QUEUE::operator>>(x);
            q.operator>>(y);
            QUEUE::operator<<(y);
            q.operator<<(x);
        }
    }
    return *this;
}

STACK& STACK::operator=(const STACK& s) {   //�����ֵ�����ر���ֵջ
    if (this == &s) return *this;
    else
    {
        *(QUEUE*)this = s;
        q = s.q;

    }
    return *this;
}

STACK& STACK::operator=(STACK&& s)noexcept {    //�ƶ���ֵ�����ر���ֵջ
    if (this == &q) return *this;
    else
    {
        *(QUEUE*)this = ((QUEUE&&)s);
        q = (QUEUE&&)s.q;

    }
    return *this;
}

char* STACK::print(char* b)const noexcept { //��ջ�׵�ջ����ӡջԪ�� 
    if (q.operator int() > 0) {
        q.print(b);
        *(b + strlen(b)) = ',';
    }
    QUEUE::print((b + strlen(b)));
    return b;
}

STACK::~STACK()noexcept {}  //����ջ



int main() {
    int x = 0;
    const char* p = TestSTACK(x);
    printf("%s\n%d", p, x);
    return 0;
}