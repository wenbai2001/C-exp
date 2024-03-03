#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

const int maxnum = 26;
const int MAX_INT = 999999;

// �����鶼���±�1��ʼ
int dist[maxnum];     // dist[i]��"����vs"��"����i"�����·���ĳ��ȡ�
int prev[maxnum];     // ��¼��ǰ���ǰһ�����,����prev[i]��ֵ��"����vs"��"����i"�����·����������ȫ�������У�λ��"����i"֮ǰ���Ǹ����㡣
int c[maxnum][maxnum];   // ��¼ͼ����䱾��Ȩֵ
int n, line;             // ͼ�Ľ������·����

void Dijkstra(int n, int vs, int* dist, int* prev, int c[maxnum][maxnum]);
void searchPath(int* prev, int vs, int u);

void Dijkstra(int n, int vs, int* dist, int* prev, int c[maxnum][maxnum])
{
    bool flag[maxnum];    // �ж��Ƿ��Ѵ���õ㵽S������
    for (int i = 1; i < n; ++i)
    {
        dist[i] = c[vs][i];
        flag[i] = 0;     // ��ʼ��δ�ù��õ�,������S
        if (dist[i] >= MAX_INT)
            prev[i] = 0;
        else
            prev[i] = vs;
    }
    dist[vs] = 0;
    flag[vs] = 1;   //��ʼ�������

    // ���ν�δ����S���ϵĽ���У�ȡdist[]��Сֵ�Ľ�㣬������S��
    // һ��S����������V�ж��㣬dist�ͼ�¼�˴�Դ�㵽������������֮������·������
         // ע���Ǵӵڶ����ڵ㿪ʼ����һ��ΪԴ��
    for (int i = 2; i < n; ++i)
    {
        int tmp = MAX_INT;
        int u = vs;
        // �ҳ���ǰδʹ�õĵ�j��dist[j]��Сֵ
        for (int j = 1; j <= n; ++j)
            if ((!flag[j]) && dist[j] < tmp)
            {
                u = j;              // u���浱ǰ�ڽӵ��о�����С�ĵ�ĺ���
                tmp = dist[j];
            }
        flag[u] = 1;    // ��ʾu���Ѵ���S������

        // ����dist
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

// ���Ҵ�Դ��v���յ�u��·���������
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