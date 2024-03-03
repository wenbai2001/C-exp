#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

const int maxnum = 26;
const int MAX_INT = 999999;

// 各数组都从下标1开始
int dist[maxnum];     // dist[i]是"顶点vs"到"顶点i"的最短路径的长度。
int prev[maxnum];     // 记录当前点的前一个结点,即，prev[i]的值是"顶点vs"到"顶点i"的最短路径所经历的全部顶点中，位于"顶点i"之前的那个顶点。
int c[maxnum][maxnum];   // 记录图两点间本身即权值
int n, line;             // 图的结点数和路径数

void Dijkstra(int n, int vs, int* dist, int* prev, int c[maxnum][maxnum]);
void searchPath(int* prev, int vs, int u);

void Dijkstra(int n, int vs, int* dist, int* prev, int c[maxnum][maxnum])
{
    bool flag[maxnum];    // 判断是否已存入该点到S集合中
    for (int i = 1; i < n; ++i)
    {
        dist[i] = c[vs][i];
        flag[i] = 0;     // 初始都未用过该点,即集合S
        if (dist[i] >= MAX_INT)
            prev[i] = 0;
        else
            prev[i] = vs;
    }
    dist[vs] = 0;
    flag[vs] = 1;   //初始起点自身

    // 依次将未放入S集合的结点中，取dist[]最小值的结点，放入结合S中
    // 一旦S包含了所有V中顶点，dist就记录了从源点到所有其他顶点之间的最短路径长度
         // 注意是从第二个节点开始，第一个为源点
    for (int i = 2; i < n; ++i)
    {
        int tmp = MAX_INT;
        int u = vs;
        // 找出当前未使用的点j的dist[j]最小值
        for (int j = 1; j <= n; ++j)
            if ((!flag[j]) && dist[j] < tmp)
            {
                u = j;              // u保存当前邻接点中距离最小的点的号码
                tmp = dist[j];
            }
        flag[u] = 1;    // 表示u点已存入S集合中

        // 更新dist
        for (int j = 1; j <= n; ++j)
            if ((!flag[j]) && c[u][j] < MAX_INT)
            {
                int newdist = dist[u] + c[u][j];
                if (newdist < dist[j])
                {
                    dist[j] = newdist;
                    prev[j] = u;
                }
            }
    }
}

// 查找从源点v到终点u的路径，并输出
void searchPath(int* prev, int vs, int u)
{
    int STACK[maxnum];
    int t = 1;
    STACK[t] = u;
    t++;
    int tmp = prev[u];
    while (tmp != vs)
    {
        STACK[t] = tmp;
        t++;
        tmp = prev[tmp];
    }
    STACK[t] = vs;
    for (int i = t; i >= 1; --i)
        if (i != 1)
            cout << STACK[i] << " -> ";
        else
            cout << STACK[i] << endl;
}