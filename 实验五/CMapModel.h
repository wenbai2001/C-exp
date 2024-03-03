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
    CString m_sMapFilePath = _T("");            //地图文件路径
    CString m_sLocationFilePath = _T("");       //位置文件路径
    CString m_sEdgeFilePath = _T("");           //距离文件路径
    CString m_sOrgFilePath = _T("");            //机构文件路径
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
    void setLocInfo();//获取位置
    void setOrgInfo();//获取挂靠单位
    void setDisInfo();//获取欧式距离

};

