#pragma once
#include <afx.h>
#include <vector>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
struct info {
    CPoint position;
    CString org[2];
};

class CMapModel :
    public CObject
{
private:
    CString m_sMapFilePath = _T("");            //��ͼ�ļ�·��
    CString m_sLocationFilePath = _T("");       //λ���ļ�·��
    CString m_sEdgeFilePath = _T("");           //�����ļ�·��
    CString m_sOrgFilePath = _T("");            //�����ļ�·��
    vector<CPoint> points;
public:
    DECLARE_SERIAL(CMapModel)
    CMapModel();
    virtual ~CMapModel();
public:
    virtual void Serialize(CArchive& ar);
public:
    CString GetMapFilePath();
    CString GetLocationFilePath();
    CString GetEdgeFilePath();
    CString GetOrgFilePath();
    void SetMapFilePath(CString path);
    void SetLocationFilePath(CString path);
    void SetGetEdgeFilePath(CString path);
    void SetOrgFilePath(CString path);
    std::vector<CString> GetOrganizations(CPoint point);
    int Edge[26][26];
    info LocInfo[26];
    void setLocInfo();//��ȡλ��
    void setOrgInfo();//��ȡ�ҿ���λ
    void setDisInfo();//��ȡŷʽ����

};

