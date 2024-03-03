
// HustMapView.h: CHustMapView 类的接口
//

#pragma once


class CHustMapView : public CView
{
protected: // 仅从序列化创建
	CHustMapView() noexcept;
	DECLARE_DYNCREATE(CHustMapView)
protected:
	//每次鼠标左键按下时的坐标点，作为画线的起点
	CPoint m_LineStart;
	//上次画线的终点,作用后面就明白了
	CPoint m_LastLineEnd;
	//鼠标是否位于拖拽状态(即按下鼠标左键同时移动鼠标的状态)
	boolean m_DraggingState = false;
	boolean m_TrackingState = false;
	CToolTipCtrl m_Tooltip;//在视图里显示Tooltip

// 特性
public:
	CHustMapDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CHustMapView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void DrawCircle(CPoint center, LONG radius);//画圆，指定圆心center和半径radius
	void DrawLine(CPoint start, CPoint end);//画直线，指定起点start和终点end

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void DrawRubberLine(CPoint start, CPoint end);
	afx_msg void OnEditFind();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnMouseLeave();
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

#ifndef _DEBUG  // HustMapView.cpp 中的调试版本
inline CHustMapDoc* CHustMapView::GetDocument() const
   { return reinterpret_cast<CHustMapDoc*>(m_pDocument); }
#endif

