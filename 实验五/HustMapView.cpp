
// HustMapView.cpp: CHustMapView 类的实现
//
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "HustMap.h"
#endif

#include "HustMapDoc.h"
#include "HustMapView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "MainFrm.h"
#include "CMapDialog.h"

// CHustMapView

IMPLEMENT_DYNCREATE(CHustMapView, CView)

BEGIN_MESSAGE_MAP(CHustMapView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHustMapView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_EDIT_FIND, &CHustMapView::OnEditFind)
	ON_COMMAND(ID_EDIT_CUT, &CHustMapView::OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, &CHustMapView::OnEditPaste)
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()

// CHustMapView 构造/析构

CHustMapView::CHustMapView() noexcept
{
	// TODO: 在此处添加构造代码

}

CHustMapView::~CHustMapView()
{
}

BOOL CHustMapView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CHustMapView 绘图

void CHustMapView::OnDraw(CDC* pDC)
{
		CHustMapDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc) return;
		if (pDoc->m_MapModel.GetMapFilePath() != _T("")) {
			// MessageBox(_T("更新视图"));
			//HB工TMAP是图片的句柄
			HBITMAP hBit;
			hBit = (HBITMAP)LoadImage(NULL, pDoc->m_MapModel.GetMapFilePath(),//地图文件路径
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);//载入图像
				// CBitmap是MFc定义的一个类，在这个类中对HB工TMAF进行了封装
			CBitmap cBit;
			//Attach()函数是cBitmap类的成员函数，作用就是将HBITMAP类型转换成cBitmap类型
			cBit.Attach(hBit);
			//创建与当前设备描述表相适应的内存DC
			CDC MemDC;
			MemDC.CreateCompatibleDC(pDC);//创建与当前设备描述表相适应的内存Dc

			BITMAP bitmap;
			cBit.GetBitmap(&bitmap); // cetBitmap函数也是cBitmap类的成员函数，作用就是获取位图的信息，并将位图的信息保存在BInsaP结构指针中。

			CBitmap* oldBit;//将位图选入到内存pc中(MemDc.selectobject (&cBit) )，并返回旧的位图
			oldBit = MemDC.SelectObject(&cBit);

			CRect rect;
			GetClientRect(&rect); //用于获取绘图的客户区域//画出B工TMAF位图
			pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);


		}
		// TODO: 在此处为本机数据添加绘制代码
	
}


// CHustMapView 打印


void CHustMapView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHustMapView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CHustMapView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CHustMapView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CHustMapView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	//OnContextMenu(this, point);
	CMapDialog dlg;//声明一个对话框对象，类型为CMapDialog
	//创建模态对话框
	//模态对话框指的是:只有当用户关闭对话框后才能回到程序;
	// 否则主界面是不会获得鼠标和键盘焦点(按鼠标或键盘时主界面不会有响应)//当用户点击确定按钮，对话框关闭， ret =IDOK
	//当用户点击取消按钮，对话框关闭， ret =IDCANCEL
	int ret = dlg. DoModal( );
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetMainWnd();//获取主窗口
	if (ret == IDOK) {
		pMainFrm->GetOutputWnd()->setBuildwindowContents(_T("点击了对话框的确定按钮"));
	}
	else if (ret == IDCANCEL) {
		pMainFrm->GetOutputWnd()->setBuildwindowContents(_T("点击了对话框的取消按钮"));
	}
}

void CHustMapView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
	theApp.GetContextMenuManager()->ShowPopupMenu(ID_EDIT_FIND, point.x, point.y, this, TRUE);
	theApp.GetContextMenuManager()->ShowPopupMenu(ID_EDIT_CUT, point.x, point.y, this, TRUE);
	theApp.GetContextMenuManager()->ShowPopupMenu(ID_EDIT_PASTE, point.x, point.y, this, TRUE);
#endif
}


// CHustMapView 诊断

#ifdef _DEBUG
void CHustMapView::AssertValid() const
{
	CView::AssertValid();
}

void CHustMapView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHustMapDoc* CHustMapView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHustMapDoc)));
	return (CHustMapDoc*)m_pDocument;
}
#endif //_DEBUG


// CHustMapView 消息处理程序


void CHustMapView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	LONG xpos = point.x; // 获取鼠标点击时的x坐标
	LONG ypos = point.y; // 获取鼠标点击时的y坐标
	CString posInfo;
	posInfo.Format(_T("鼠标点击位置:(%d,%d)"), xpos, ypos);
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	//获取主窗口
	pMainFrm->GetOutputWnd()->setBuildwindowContents(posInfo);
	DrawCircle(point, 5); // 在鼠标点击位置画一个实心圆
	//把鼠标点击时坐标保存到数据成员m_LineStart，作为新的画线起点
	this->m_LineStart = point;

	CView::OnLButtonDown(nFlags, point);
}


void CHustMapView:: DrawCircle(CPoint center, LONG radius) {
	CClientDC dc(this);
	//MFC最常用的就是绘图工具画笔(cPen)和画刷(cBrush)。
	CBrush brush, *oldbrush;
	brush.CreateSolidBrush(RGB(0xFF,0x00,0x00));//创建新的用于填充的画刷，填充颜色为红色
	oldbrush = dc.SelectObject(&brush);//将新的画刷选进dc，返回dc里旧的画刷
	//用新的画刷画圆
	dc.Ellipse(center.x - radius,center.y - radius,center.x + radius,center.y + radius);//再将旧画刷恢复进dc
	dc.SelectObject(oldbrush);
}


void CHustMapView:: DrawLine(CPoint start, CPoint end) {
	CClientDC dc(this);
	CPen pen(PS_SOLID,3,RGB(0xFF,0x00,0x00));//建立一个画笔类对象，构造时设置画笔属性，颜色红色，粗细为3个像素
	CPen *oldPen;
	oldPen = dc.SelectObject(&pen); // 将新的画笔选进dc，返回dc里旧的画笔
	dc.MoveTo(start.x, start.y); // 画笔首先移动到起点
	dc.LineTo(end.x, end.y); // 画笔移动到终点，完成直线的绘制
	dc.SelectObject(oldPen);
}

void CHustMapView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//鼠标左键释放时，参数point作为画线终点
	this-> DrawLine(this->m_LineStart, point);
	//鼠标不再处于拖拽状态
	this->m_DraggingState = false;

	CView::OnLButtonUp(nFlags, point);
}
void CHustMapView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_LBUTTON) {
		if (this->m_DraggingState) {
			this->DrawRubberLine(this->m_LineStart, this->m_LastLineEnd);
		}
		this->DrawRubberLine(this->m_LineStart, point);
		this->m_LastLineEnd = point;
		this->m_DraggingState = true;
	}
	else {
		static CPoint lastPoint(0, 0);
		if (lastPoint == point) {
			return;
		}
		CMapModel tmp;
		tmp.setLocInfo();
		tmp.setOrgInfo();
		std::vector<CString> orgs = tmp.GetOrganizations(point);
		CString posInfo;
		posInfo.Format(_T("(%d,%d)"), point.x, point.y);
		if (orgs.size() > 0) {
			for (auto start = orgs.begin(); start != orgs.end(); start++) {
				posInfo += CString("\n") + *start;
			}
		}
		m_Tooltip.UpdateTipText(posInfo, this);
		CPoint pt = point;
		this->ClientToScreen(&pt);
		CToolInfo sTinfo;
		m_Tooltip.GetToolInfo(sTinfo, this);
		sTinfo.uFlags = TTF_TRACK;
		m_Tooltip.SetToolInfo(&sTinfo);

		m_Tooltip.SendMessage(TTM_TRACKPOSITION, 0, (LPARAM)MAKELONG(pt.x + 5, pt.y + 5));
		if (orgs.size() > 0) {
			m_Tooltip.SendMessage(TTM_TRACKACTIVATE, TRUE, (LPARAM)&sTinfo);
		}
		else {
			m_Tooltip.SendMessage(TTM_TRACKACTIVATE, false, (LPARAM)&sTinfo);
		}
		lastPoint = point;

		if (!m_TrackingState) {
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE;
			tme.hwndTrack = m_hWnd;
			m_TrackingState = _TrackMouseEvent(&tme);
		}
	}



	CView::OnMouseMove(nFlags, point);
}
void CHustMapView::DrawRubberLine(CPoint start, CPoint end) {
	CClientDC dc(this);
	dc.SetROP2(R2_NOTXORPEN); //final pixel = NOr(pen XOR screen pixel)，请百度setRoP2
	CPen pen(PS_SOLID,3,RGB(0xFF,0x00,0x00));//建立一个画笔类对象，构造时设置画笔届性，颜色红色，粗细为3个像素
	CPen *oldPen;
	oldPen = dc.SelectObject(&pen);//将新的画笔选进dc，返回dc里旧的画笔dc.MoveTo(start.x,start.y) ;l/画笔首先移动到起点
	dc.LineTo(end.x, end.y); // 画笔移动到终点，完成直线的绘制
	dc.SelectObject(oldPen);
}

void CHustMapView::OnEditFind()
{
	// TODO: 在此添加命令处理程序代码
}


void CHustMapView::OnEditCut()
{
	// TODO: 在此添加命令处理程序代码
}


void CHustMapView::OnEditPaste()
{
	// TODO: 在此添加命令处理程序代码
}


void CHustMapView::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CToolInfo sTinfo;// 提示信息
	m_Tooltip.GetToolInfo(sTinfo, this);
	sTinfo.uFlags = TTF_TRACK;  // 显示方式设置
	m_Tooltip.SetToolInfo(&sTinfo);
	m_Tooltip.SendMessage(TTM_TRACKACTIVATE,false,(LPARAM)&sTinfo); //当鼠标立刻cHustMapView，tips不显示m_Trackingstate =FALSE;

	CView::OnMouseLeave();
}


void CHustMapView::OnInitialUpdate() {
	CView::OnInitialUpdate();
	this->EnableToolTips(TRUE);
	m_Tooltip.Create(this);
	m_Tooltip.Activate(TRUE);
	m_Tooltip.AddTool(this, _T("这是Tooltip"));
	m_Tooltip.SetTipTextColor(RGB(0, 0, 255));
	m_Tooltip.SetDelayTime(1000);  // 1s，毫秒为单位
	m_Tooltip.SetMaxTipWidth(150);

}


BOOL CHustMapView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_Tooltip.RelayEvent(pMsg);

	return CView::PreTranslateMessage(pMsg);
}
