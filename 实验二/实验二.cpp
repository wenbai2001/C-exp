// Two_Queue.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
class QUEUE {
    int* const  elems;	//elems�����ڴ����ڴ�Ŷ��е�Ԫ��
    const  int  max;	//elems��������Ԫ�ظ���Ϊmax
    int   head, tail;	 	//����ͷhead��βtail���ӿ�head=tail;��ʼhead=tail=0
public:
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

extern const char* TestQUEUE(int& s);

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


int main() {
    int x = 0;
    const char* p = TestQUEUE(x);
    printf("%s\n%d", p, x);
    return 0;
}