// CMapDialog.cpp: 实现文件
//

#include "pch.h"
#include "HustMap.h"
#include "CMapDialog.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "HustMapDoc.h"
#include "CMapModel.h"
#include "HustMapview.h"
#include"Dijkstra.h"
// CMapDialog 对话框

IMPLEMENT_DYNAMIC(CMapDialog, CDialogEx)

CMapDialog::CMapDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAP_DIALOG, pParent)
{

}

CMapDialog::~CMapDialog()
{
}

void CMapDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_START, m_ComboStart);
	DDX_Control(pDX, IDC_COMBO_END, m_ComboEnd);
}


BEGIN_MESSAGE_MAP(CMapDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMapDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CMapDialog 消息处理程序


BOOL CMapDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CComboBox* pComboBoxStart =dynamic_cast<CComboBox*>(this->GetDlgItem(IDC_COMBO_START)); 
	CComboBox* pComboBoxEnd =dynamic_cast<CComboBox*>(this->GetDlgItem(IDC_COMBO_END));//获取终点位置下拉列表框对象指针，类型ccomboBox
	pComboBoxStart->AddString(_T("华中科技大学正门"));
	pComboBoxStart->AddString(_T("华中科技大学南二门"));
	pComboBoxStart->AddString(_T("华中科技大学南三门"));
	pComboBoxStart->AddString(_T("化学学院"));
	pComboBoxStart->AddString(_T("煤燃烧实验室"));
	pComboBoxStart->AddString(_T("紫菘学生公寓"));
	pComboBoxStart->AddString(_T("计算机学院"));
	pComboBoxStart->AddString(_T("电信学院"));
	pComboBoxStart->AddString(_T("图书馆"));
	pComboBoxStart->AddString(_T("西一学生食堂"));
	pComboBoxStart->AddString(_T("人文学院"));
	pComboBoxStart->AddString(_T("法学院"));
	pComboBoxStart->AddString(_T("科技楼"));
	pComboBoxStart->AddString(_T("友谊公寓"));
	pComboBoxStart->AddString(_T("教工活动中心"));
	pComboBoxStart->AddString(_T("印刷厂"));
	pComboBoxStart->AddString(_T("计算中心"));
	pComboBoxStart->AddString(_T("华中教育网中心"));
	pComboBoxStart->AddString(_T("电信收费中心"));
	pComboBoxStart->AddString(_T("档案馆"));
	pComboBoxStart->AddString(_T("八号楼"));
	pComboBoxStart->AddString(_T("招待所"));
	pComboBoxStart->AddString(_T("静园"));
	pComboBoxStart->AddString(_T("南三楼"));
	pComboBoxStart->AddString(_T("西五楼"));
	pComboBoxStart->AddString(_T("西十二楼"));
	pComboBoxStart->AddString(_T("建筑学院"));
	pComboBoxStart->AddString(_T("西五舍"));
	pComboBoxStart->AddString(_T("西六舍"));
	pComboBoxStart->AddString(_T("西学超市"));
	pComboBoxStart->AddString(_T("图像防伪中心"));
	pComboBoxStart->AddString(_T("醉晚亭"));


	pComboBoxEnd->AddString(_T("华中科技大学正门"));
	pComboBoxEnd->AddString(_T("华中科技大学南二门"));
	pComboBoxEnd->AddString(_T("华中科技大学南三门"));
	pComboBoxEnd->AddString(_T("化学学院"));
	pComboBoxEnd->AddString(_T("煤燃烧实验室"));
	pComboBoxEnd->AddString(_T("紫菘学生公寓"));
	pComboBoxEnd->AddString(_T("计算机学院"));
	pComboBoxEnd->AddString(_T("电信学院"));
	pComboBoxEnd->AddString(_T("图书馆"));
	pComboBoxEnd->AddString(_T("西一学生食堂"));
	pComboBoxEnd->AddString(_T("人文学院"));
	pComboBoxEnd->AddString(_T("法学院"));
	pComboBoxEnd->AddString(_T("科技楼"));
	pComboBoxEnd->AddString(_T("友谊公寓"));
	pComboBoxEnd->AddString(_T("教工活动中心"));
	pComboBoxEnd->AddString(_T("印刷厂"));
	pComboBoxEnd->AddString(_T("计算中心"));
	pComboBoxEnd->AddString(_T("华中教育网中心"));
	pComboBoxEnd->AddString(_T("电信收费中心"));
	pComboBoxEnd->AddString(_T("档案馆"));
	pComboBoxEnd->AddString(_T("八号楼"));
	pComboBoxEnd->AddString(_T("招待所"));
	pComboBoxEnd->AddString(_T("静园"));
	pComboBoxEnd->AddString(_T("南三楼"));
	pComboBoxEnd->AddString(_T("西五楼"));
	pComboBoxEnd->AddString(_T("西十二楼"));
	pComboBoxEnd->AddString(_T("建筑学院"));
	pComboBoxEnd->AddString(_T("西五舍"));
	pComboBoxEnd->AddString(_T("西六舍"));
	pComboBoxEnd->AddString(_T("西学超市"));
	pComboBoxEnd->AddString(_T("图像防伪中心"));
	pComboBoxEnd->AddString(_T("醉晚亭"));
	this->UpdateData(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CMapDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString csStart, csEnd;
	int selIndex = this->m_ComboStart.GetCurSel();//获取用户在下拉列表框里选中项的索引(从O开始)
	// void GetLBText(int nIndex, cstring & rstring) .
	// 函数说明:把索引号为nIndex的数据放到rstring变量中.
	this->m_ComboStart.GetLBText(selIndex, csStart);//获取选中项索引对应的字符串
	int endIndex = this->m_ComboEnd.GetCurSel();
	this->m_ComboEnd.GetLBText(endIndex,csEnd);//获取选中项索引对应的字符串
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();//获取主窗口
	pMainFrm->GetOutputWnd()->setBuildwindowContents(_T("起始位置为:") + csStart);
	pMainFrm->GetOutputWnd()->setBuildwindowContents(_T("终止位置为:") + csEnd);
	CDialogEx::OnOK();
	
	CMapModel temp;
	temp.setLocInfo();
	temp.setOrgInfo();
	temp.setDisInfo();





	CHustMapView* pView = dynamic_cast<CHustMapView*>(pMainFrm->GetActiveView());
	pView->Invalidate(); pView->UpdateWindow();
	int bg_num, ed_num;//起始点和终点的序列号

	for (int j = 0; j < 26; j++) {
		pView->DrawCircle(temp.LocInfo[j].position, 5);
	}
	
	for (int i = 1; i <= 25; i++) {
		for (int j = 0; j < 2; j++) {
			if (temp.LocInfo[i].org[j] == csStart) {
				bg_num = i;
			}
			if (temp.LocInfo[i].org[j] == csEnd) {
				ed_num = i;
			}
		}
	}//获取起点和终点

	if (bg_num == ed_num) return;//避免原地打转

	Dijkstra(26, bg_num, dist, ::prev, temp.Edge);//获取起点到所有点的最短路径
	int STACK[maxnum];
	int t = 1;
	STACK[t++] = ed_num;//获得最短路径终点
	int tmp = ::prev[ed_num];//找到对应的最短路径序列
	while (tmp != bg_num)//将栈prev中点转到一个栈中来
	{
		STACK[t++] = tmp;
		tmp = ::prev[tmp];
	}
	STACK[t] = bg_num;
	int last;
	for (int i = t; i >= 1; --i)
	{
		last = i == 1 ? bg_num : STACK[i - 1];
		if (i != 1) {
			pView->DrawCircle(temp.LocInfo[last].position, 5);
			pView->DrawCircle(temp.LocInfo[STACK[i]].position, 5);
			pView->DrawLine(temp.LocInfo[last].position, temp.LocInfo[STACK[i]].position);
		}
	}
	
}
