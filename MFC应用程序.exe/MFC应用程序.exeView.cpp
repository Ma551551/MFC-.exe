
// MFC应用程序.exeView.cpp: CMFC应用程序exeView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFC应用程序.exe.h"
#endif

#include "MFC应用程序.exeDoc.h"
#include "MFC应用程序.exeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC应用程序exeView

IMPLEMENT_DYNCREATE(CMFC应用程序exeView, CView)

BEGIN_MESSAGE_MAP(CMFC应用程序exeView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFC应用程序exeView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFC应用程序exeView 构造/析构

CMFC应用程序exeView::CMFC应用程序exeView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFC应用程序exeView::~CMFC应用程序exeView()
{
}

BOOL CMFC应用程序exeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFC应用程序exeView 绘图

void CMFC应用程序exeView::OnDraw(CDC* /*pDC*/)
{
	CMFC应用程序exeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFC应用程序exeView 打印


void CMFC应用程序exeView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFC应用程序exeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFC应用程序exeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFC应用程序exeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMFC应用程序exeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFC应用程序exeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFC应用程序exeView 诊断

#ifdef _DEBUG
void CMFC应用程序exeView::AssertValid() const
{
	CView::AssertValid();
}

void CMFC应用程序exeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC应用程序exeDoc* CMFC应用程序exeView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC应用程序exeDoc)));
	return (CMFC应用程序exeDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFC应用程序exeView 消息处理程序
