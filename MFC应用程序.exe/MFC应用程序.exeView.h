
// MFC应用程序.exeView.h: CMFC应用程序exeView 类的接口
//

#pragma once


class CMFC应用程序exeView : public CView
{
protected: // 仅从序列化创建
	CMFC应用程序exeView() noexcept;
	DECLARE_DYNCREATE(CMFC应用程序exeView)

// 特性
public:
	CMFC应用程序exeDoc* GetDocument() const;

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
	virtual ~CMFC应用程序exeView();
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
};

#ifndef _DEBUG  // MFC应用程序.exeView.cpp 中的调试版本
inline CMFC应用程序exeDoc* CMFC应用程序exeView::GetDocument() const
   { return reinterpret_cast<CMFC应用程序exeDoc*>(m_pDocument); }
#endif

