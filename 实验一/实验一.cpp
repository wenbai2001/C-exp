#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Queue {                                              //队列结构
    int* const  elems;	   	                                //elems申请内存用于存放队列的元素
    const  int  max;	  	                                //elems申请的最大元素个数max
    int   head, tail;	 	                                //队列头head和尾tail，队空head=tail;初始head=tail=0
};
void initQueue(Queue* const p, int m);	                    //初始化p指队列：最多申请m个元素
void initQueue(Queue* const p, const Queue& s);             //用s深拷贝初始化p指队列
void initQueue(Queue* const p, Queue&& s);                  //用s移动初始化p指队列
int  number(const Queue* const p);	                        //返回p指队列的实际元素个数
int  size(const Queue* const p);			                //返回p指队列申请的最大元素个数max
Queue* const enter(Queue* const p, int e);                  //将e入队列尾部，并返回p
Queue* const leave(Queue* const p, int& e);                 //从队首出元素到e，并返回p
Queue* const assign(Queue* const p, const Queue& q);        //深拷贝赋s给队列并返回p
Queue* const assign(Queue* const p, Queue&& q);             //移动赋s给队列并返回p
char* print(const Queue* const p, char* s);                 //打印p指队列至s尾部并返回s
void destroyQueue(Queue* const p);	                        //销毁p指向的队列

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
