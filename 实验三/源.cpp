#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
class QUEUE {
    int* const  elems;	//elems申请内存用于存放队列的元素
    const  int  max;	//elems申请的最大元素个数为max
    int   head, tail;	 	//队列头head和尾tail，队空head=tail;初始head=tail=0
public:
    //QUEUE();
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

class STACK : public QUEUE {
    QUEUE q;
public:
    STACK(int m);                    		//初始化栈：最多存放2m-2个元素
    STACK(const STACK& s);         		//用栈s深拷贝初始化栈
    STACK(STACK&& s)noexcept;     		//用栈s移动拷贝初始化栈
    int  size()const noexcept;		  		//返回栈的容量即2m
    operator int() const noexcept;	   		//返回栈的实际元素个数
    STACK& operator<<(int e); 	     		//将e入栈，并返回当前栈
    STACK& operator>>(int& e);     		//出栈到e，并返回当前栈
    STACK& operator=(const STACK& s);	//深拷贝赋值并返回被赋值栈
    STACK& operator=(STACK&& s)noexcept;//移动赋值并返回被赋值栈
    char* print(char* b)const noexcept;	//从栈底到栈顶打印栈元素 
    ~STACK()noexcept;	              	//销毁栈
};


extern const char* TestSTACK(int& s);

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

STACK::STACK(int m) :QUEUE(m), q(m) {}   //初始化栈：最多存放2m-2个元素

STACK::STACK(const STACK& s) : QUEUE(s), q(s.q) {}//用栈s深拷贝初始化栈


STACK::STACK(STACK&& s)noexcept :QUEUE(std::move(s)), q(std::move(s.q)) {}   //用栈s移动拷贝初始化栈


int  STACK::size()const noexcept {  //返回栈的容量即2m
    return 2 * q.size();
}

STACK::operator int() const noexcept {  //返回栈的实际元素个数
    return QUEUE::operator int() + int(q);
}

STACK& STACK::operator<<(int e) {   //将e入栈，并返回当前栈
    if (QUEUE::operator int() < QUEUE::size() - 1)    //基队列未满时直接入栈
    {
        QUEUE::operator<<(e);
    }
    else if (q.operator int() < q.size() - 1) //基队列满栈未满时，让基队列保存最新的m-1个元素，其他元素保存在另一队列中
    {
        int x;
        QUEUE::operator>>(x);
        q.operator<<(x);
        QUEUE::operator<<(e);
    }
    else//栈满时报错
    {
        throw("STACK is full!");
    }
    return *this;
}

STACK& STACK::operator>>(int& e) {  //出栈到e，并返回当前栈
    int x, y;
    int num = STACK::operator int();
    if (QUEUE::operator int() == 0) {   //判断栈是否为空，栈空时报错
        throw("STACK is empty!");
    }
    else if (q.operator int() == 0)
    {
        for (int i = 0; i < num - 1; i++)
        {
            QUEUE::operator>>(x);   //通过出栈入栈将待出栈元素移动至出队位置
            QUEUE::operator<<(x);
        }
        QUEUE::operator>>(e);
    }
    else {
        for (int i = 0; i < q.size() - 2; i++)
        {
            QUEUE::operator>>(x);   //通过出栈入栈将待出栈元素移动至基队列出队位置
            q.operator>>(y);
            QUEUE::operator<<(y);
            q.operator<<(x);
        }
        QUEUE::operator>>(e);
        q.operator>>(x);
        QUEUE::operator<<(x);
        for (int i = 0; i < num - q.size(); i++)    //将栈复原成标准储存格式
        {
            QUEUE::operator>>(x);
            q.operator>>(y);
            QUEUE::operator<<(y);
            q.operator<<(x);
        }
    }
    return *this;
}

STACK& STACK::operator=(const STACK& s) {   //深拷贝赋值并返回被赋值栈
    if (this == &s) return *this;
    else
    {
        *(QUEUE*)this = s;
        q = s.q;

    }
    return *this;
}

STACK& STACK::operator=(STACK&& s)noexcept {    //移动赋值并返回被赋值栈
    if (this == &q) return *this;
    else
    {
        *(QUEUE*)this = ((QUEUE&&)s);
        q = (QUEUE&&)s.q;

    }
    return *this;
}

char* STACK::print(char* b)const noexcept { //从栈底到栈顶打印栈元素 
    if (q.operator int() > 0) {
        q.print(b);
        *(b + strlen(b)) = ',';
    }
    QUEUE::print((b + strlen(b)));
    return b;
}

STACK::~STACK()noexcept {}  //销毁栈



int main() {
    int x = 0;
    const char* p = TestSTACK(x);
    printf("%s\n%d", p, x);
    return 0;
}