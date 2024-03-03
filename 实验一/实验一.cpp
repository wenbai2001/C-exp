#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Queue {                                              //���нṹ
    int* const  elems;	   	                                //elems�����ڴ����ڴ�Ŷ��е�Ԫ��
    const  int  max;	  	                                //elems��������Ԫ�ظ���max
    int   head, tail;	 	                                //����ͷhead��βtail���ӿ�head=tail;��ʼhead=tail=0
};
void initQueue(Queue* const p, int m);	                    //��ʼ��pָ���У��������m��Ԫ��
void initQueue(Queue* const p, const Queue& s);             //��s�����ʼ��pָ����
void initQueue(Queue* const p, Queue&& s);                  //��s�ƶ���ʼ��pָ����
int  number(const Queue* const p);	                        //����pָ���е�ʵ��Ԫ�ظ���
int  size(const Queue* const p);			                //����pָ������������Ԫ�ظ���max
Queue* const enter(Queue* const p, int e);                  //��e�����β����������p
Queue* const leave(Queue* const p, int& e);                 //�Ӷ��׳�Ԫ�ص�e��������p
Queue* const assign(Queue* const p, const Queue& q);        //�����s�����в�����p
Queue* const assign(Queue* const p, Queue&& q);             //�ƶ���s�����в�����p
char* print(const Queue* const p, char* s);                 //��ӡpָ������sβ��������s
void destroyQueue(Queue* const p);	                        //����pָ��Ķ���

extern const char* TestQueue(int& s);

void initQueue(Queue* const p, int m) { 
    *(int**)&p->elems = (int*)malloc(sizeof(int) * m);
    p->head = 0;
    p->tail = 0;
    *(int*)&p->max = m;
}

void initQueue(Queue* const p, const Queue& s) {   
    *(int**)&p->elems = (int*)malloc(sizeof(int) * s.max);  
    p->head = s.head;
    p->tail = s.tail;
    *(int*)&p->max = s.max;
    for (int i = 0; i < s.max; i++) 
    {
        p->elems[i] = s.elems[i];
    }
}

void initQueue(Queue* const p, Queue&& s) { 
    *(int**)&p->elems = s.elems;   
    p->head = s.head;
    p->tail = s.tail;
    *(int*)&p->max = s.max;
    *(int**)&s.elems = NULL;    
    s.head = 0;
    s.tail = 0;
    *(int*)&s.max = 0;
}

int  number(const Queue* const p) { 
    if (p->max == 0)    
    {
        return 0;
    }
    return (p->tail + p->max - p->head) % p->max;   
}

int  size(const Queue* const p) {   
    return p->max;
}

Queue* const enter(Queue* const p, int e) { 
    if (p->head == (p->tail + 1) % p->max)  
    {
        throw "Queue is full!";
    }
    else
    {
        *(int*)&p->elems[p->tail] = e;  
        p->tail = (p->tail + 1) % p->max;
    }
    return p;
}

Queue* const leave(Queue* const p, int& e) {   
    if (p->head == p->tail) 
    {
        throw "Queue is empty!";
    }
    else
    {
        e = p->elems[p->head]; 
        p->head = (p->head + 1) % p->max;
    }
    return p;
}

Queue* const assign(Queue* const p, const Queue& q) {   
    if (p->elems == q.elems)    
    {
        return p;
    }
    else if (p->elems != NULL)  
    {
        free(p->elems);
    }
    *(int**)&p->elems = (int*)malloc(sizeof(int) * q.max);
    p->head = q.head;
    p->tail = q.tail;
    *(int*)&p->max = q.max;
    for (int i = 0; i < q.max; i++)
    {
        p->elems[i] = q.elems[i];
    }
    return p;
}

Queue* const assign(Queue* const p, Queue&& q) {   
    if (p->elems == q.elems)    
    {
        return p;
    }
    else if (p->elems != NULL) 
    {
        free(p->elems);
    }
    *(int**)&p->elems = q.elems;
    p->head = q.head;
    p->tail = q.tail;
    *(int*)&p->max = q.max;
    *(int**)&q.elems = NULL;
    q.head = 0;
    q.tail = 0;
    *(int*)&q.max = 0;
    return p;
}

char* print(const Queue* const p, char* s) {    
    int pos = p->head; 
    int offset = 0;
    for (int i = 0; i < number(p); i++) 
    {
        offset += sprintf(s + offset, " %d", p->elems[pos]);   
        pos = (pos + 1) % p->max;
    }
    return s;
}

void destroyQueue(Queue* const p) { 
    if (p) {
        if (p->elems)
        {
            free(p->elems);
            *(int**)&p->elems = NULL;
            *(int*)&p->max = 0;
            p->head = 0;
            p->tail = 0;
        }
    }

}

int main()
{
    int x = 0;
    const char* p = TestQueue(x);
    printf("%s\n%d", p, x);
    return 0;
}
