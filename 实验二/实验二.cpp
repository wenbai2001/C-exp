// Two_Queue.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
class QUEUE {
    int* const  elems;	//elems申请内存用于存放队列的元素
    const  int  max;	//elems申请的最大元素个数为max
    int   head, tail;	 	//队列头head和尾tail，队空head=tail;初始head=tail=0
public:
    QUEUE(int m);		//初始化队列：最多申请m个元素
    QUEUE(const QUEUE& q); 			//用q深拷贝初始化队列
    QUEUE(QUEUE&& q)noexcept;		//用q移动初始化队列
    virtual operator int() const noexcept;	//返回队列的实际元素个数
    virtual int size() const noexcept;		//返回队列申请的最大元素个数max
    virtual QUEUE& operator<<(int e);  	//将e入队列尾部，并返回当前队列
    virtual QUEUE& operator>>(int& e); 	//从队首出元素到e，并返回当前队列
    virtual QUEUE& operator=(const QUEUE& q);//深拷贝赋值并返回被赋值队列
    virtual QUEUE& operator=(QUEUE&& q)noexcept;//移动赋值并返回被赋值队列
    virtual char* print(char* s) const noexcept;//打印队列至s并返回s
    virtual ~QUEUE();	 					//销毁当前队列
};

extern const char* TestQUEUE(int& s);

QUEUE::QUEUE(int m) :elems(new int[m]), head(0), tail(0), max(m) {}  //初始化队列：最多申请m个元素

QUEUE::QUEUE(const QUEUE& q) : elems(new int[q.max]), head(q.head), tail(q.tail), max(q.max) {   //用q深拷贝初始化队列
    for (int i = 0; i < max; i++)
    {
        elems[i] = q.elems[i];  //通过循环赋值的方式将s的elems写入p中
    }
}

QUEUE::QUEUE(QUEUE&& q)noexcept :elems(q.elems), head(q.head), tail(q.tail), max(q.max) {   //用q移动初始化队列
    *(int**)&q.elems = NULL;    //将q清空
    q.head = 0;
    q.tail = 0;
    *(int*)&q.max = 0;
}

QUEUE::operator int() const noexcept {  //返回队列的实际元素个数
    if (max == 0)   //当最大元素数为0时直接返回0
    {
        return 0;
    }
    return (tail + max - head) % max;   //根据头尾位置以及最大元素数计算实际的元素个数
}

int QUEUE::size() const noexcept {  //返回队列申请的最大元素个数max
    return max;
}

QUEUE& QUEUE::operator<<(int e) {  //将e入队列尾部，并返回当前队列
    if (head == (tail + 1) % max)  //满队列入队时throw错误信息
    {
        throw "QUEUE is full!";
    }
    else
    {
        *(int*)&elems[tail] = e;  //不为满队列时通过修改尾部实现入队
        tail = (tail + 1) % max;
    }
    return *this;
}

QUEUE& QUEUE::operator>>(int& e) { //从队首出元素到e，并返回当前队列
    if (head == tail) //空队列出队时throw错误信息
    {
        throw "QUEUE is empty!";
    }
    else
    {
        e = elems[head];  //不为空队列时通过修改头部实现出队
        head = (head + 1) % max;
    }
    return *this;
}

QUEUE& QUEUE::operator=(const QUEUE& q) {  //深拷贝赋值并返回被赋值队列
    if (elems == q.elems)    //队列与q相同时的特殊考量
    {
        return *this;
    }
    else if (elems != NULL)  //队列不为空时free防止缓冲区溢出
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

QUEUE& QUEUE::operator=(QUEUE&& q)noexcept {   //移动赋值并返回被赋值队列
    if (elems == q.elems)    //队列与q相同时的特殊考量
    {
        return *this;
    }
    else if (elems != NULL)  //队列不为空时free防止缓冲区溢出
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

char* QUEUE::print(char* s) const noexcept {    //打印队列至s并返回s
    int pos = head;  //pos函数记录当前位置
    int offset = 0;
    int num = (tail + max - head) % max;
    if (max == 0)
    {
        num = 0;
    }
    for (int i = 0; i < num; i++) //进行元素数次循环
    {
        offset += sprintf(s + offset, "%d,", elems[pos]);    //offset保存偏移量
        pos = (pos + 1) % max;
    }
    s[offset - 1] = '\0';
    return s;
}

QUEUE::~QUEUE() {   //销毁当前队列
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