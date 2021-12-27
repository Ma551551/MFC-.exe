
// MFC应用程序.cpp: 定义应用程序的类行为。

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MFC应用程序.exe.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "MFC应用程序.exeDoc.h"
#include "MFC应用程序.exeView.h"
#include "FCool.h"
#include <afxmsg_.h>
#include "RadioListBox.h"
#include <Gdiplus.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CMFC应用程序App

BEGIN_MESSAGE_MAP(CMFC应用程序exeApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CMFC应用程序exeApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CMFC应用程序App 构造

CMFC应用程序exeApp::CMFC应用程序exeApp() noexcept
{
	m_bHiColorIcons = TRUE;


	m_nAppLook = 0;
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则: 
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("MFC应用程序.AppID.NoVersion"));

	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的 CMFC应用程序App 对象
CMFC应用程序exeApp theApp;


// CMFC应用程序App 初始化
BOOL CMFC应用程序exeApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// 使用 RichEdit 控件需要 AfxInitRichEdit2()
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。  文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MFCexeTYPE,
		RUNTIME_CLASS(CMFC应用程序exeDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CMFC应用程序exeView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// 创建主 MDI 框架窗口
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;



	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 调度在命令行中指定的命令。  如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// 主窗口已初始化，因此显示它并对其进行更新
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CMFC应用程序exeApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CMFC应用程序App 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CCoolButton login;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CButton lanqiu;
	afx_msg void OnBnClickedButton5();
	CEdit edit;
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnSetfocusEdit1();
	CComboBox m_box;  //第一个下拉框
	CComboBox m_box2; //第二个下拉框
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnCbnSelchangeCombo1();
	CListBox list;   //list box添加变量
	//CRadioListBox list;  //使用扩展美化带单选框   //报错mfc140ud.dll待解决
	afx_msg void OnBnClickedButton9();
	CListCtrl m_list;   //为高级列表控件添加变量
	afx_msg void OnBnClickedButton8();
	afx_msg void OnLvnBeginlabeleditList9(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnEndlabeleditList9(NMHDR* pNMHDR, LRESULT* pResult);

	CImageList imag;    //添加一个图形类型的变量
	CEdit yin_edit;
	afx_msg void OnNMDblclkList9(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnKillfocusEdit6();
	afx_msg void OnNMRClickList9(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnText32771();
	afx_msg void OnText32772();
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX), login(IDB_BITMAP1, IDB_BITMAP2, IDB_BITMAP3)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	//解决添加图片类型成员变量报错mfc140ud.dll这个bug
	//成员变量使用完资源必须释放，否则就会报错!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	imag.DeleteImageList();     //DoDataExchange：这个函数执行完释放图片资源


////////////////////////////////////////////////////////////////////////////////////////////
	//为确定按钮添加变量，是为了实现扩展控件需求
	DDX_Control(pDX, IDOK, login);

	//第一种方式：
	//单选框默认选择  第一组
	//CButton* pnan = (CButton*)GetDlgItem(IDC_RADIO_nan);
	//if (pnan)
	//{
	//	pnan->SetCheck(BST_CHECKED);
	//}
	//第一种方式：
	//单选框默认选择   第二组
	//CButton* pjingcha = (CButton*)GetDlgItem(IDC_RADIO1);
	//if (pjingcha)
	//{
	//	pjingcha->SetCheck(BST_CHECKED);
	//}

	//第二种方式：单选框默认选择    参数1和参数2是个范围    参数3：指要选中的控件
	CheckRadioButton(IDC_RADIO_nan, IDC_RADIO_nv, IDC_RADIO_nan);   //第一组
	CheckRadioButton(IDC_RADIO1, IDC_RADIO4, IDC_RADIO1);           //第二组



//复选框默认选择方式：
	CButton* pbtn = (CButton*)GetDlgItem(IDC_CHECK1);
	if (pbtn)
	{
		pbtn->SetCheck(BST_CHECKED);
	}

	DDX_Control(pDX, IDC_CHECK1, lanqiu);
	DDX_Control(pDX, IDC_EDIT1, edit);
	DDX_Control(pDX, IDC_COMBO1, m_box);

	//下拉框默认选择内容调用SetCurSel函数，参数为索引下标
	m_box.SetCurSel(0);
	DDX_Control(pDX, IDC_COMBO2, m_box2);

	/////////////////////////////////////////////////////////////////////////////////////////
	//listbox控件操作：
	DDX_Control(pDX, IDC_LIST3, list);
	list.AddString(_T("111"));   //默认是按升序排序的，若需要降序可以在属性中把排序设置为false
	list.AddString(_T("000"));
	list.AddString(_T("222"));

	//自定义位置插入数据：  这种方式不受属性排序影响，但需要提供下标位置
	list.InsertString(0, _T("aaa"));  //自定义位置调用InsertString函数  //参数1是下标位置，参数2是插入内容
	DDX_Control(pDX, IDC_LIST9, m_list);


	///////////////////////////////////////////////////////////////////////////////////////
	//list control高级列表控件
	//设置列表样式风格
	DWORD dwStyle = m_list.GetExtendedStyle();
	//LVS_EX_FULLROWSELECT:  选中某行使整行高亮（只适用与report 风格的ListControl ）
	//LVS_EX_GRIDLINES:      网格线（只适用与report 风格的ListControl ）
	//LVS_EX_CHECKBOXES:     Item前生成checkbox 控件
	//LVS_SHOWSELALWAYS:     使listctrl控件一直处于选中状态，即使该控件没有焦点（鼠标移动到某项上自动变为选中）
	//LVS_EX_SUBITEMIMAGES:  想在子列插入图标必须使ListCtrl控件具备LVS_EX_SUBITEMIMAGES风格
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES | LVS_SHOWSELALWAYS | LVS_EX_SUBITEMIMAGES;
	m_list.SetExtendedStyle(dwStyle);


	//为list control控件插入图标
	//参数1：图标长度  参数2：图标宽度   参数3：图标风格  参数4：包含的图像数目   参数5：每次需要添加的图片数目
	imag.Create(16, 16, ILC_MASK | ILC_COLOR32, 5, 1);
	imag.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	imag.Add(AfxGetApp()->LoadIcon(IDI_ICON2));
	imag.Add(AfxGetApp()->LoadIcon(IDI_ICON3));
	m_list.SetImageList(&imag, LVSIL_SMALL);


	//插入列
	//InsertColumn:参数1：列下标   参数2：列文本  参数3：   参数4：宽度
	m_list.InsertColumn(0, _T("第一列"), LVCFMT_LEFT, 60);
	m_list.InsertColumn(1, _T("第二列"), LVCFMT_LEFT, 60);
	m_list.InsertColumn(2, _T("第三列"), LVCFMT_LEFT, 60);

	//插入行  参数1：行  参数2：文本   参数3：图标下标
	m_list.InsertItem(0, _T("000"), 0);// 插入行
	m_list.InsertItem(1, _T("111"), 1);
	m_list.InsertItem(2, _T("222"), 2);

	//指定单元格添加图标
	m_list.SetItem(0, 1, LVIF_IMAGE, NULL, 0, 0, 0, 0);

	m_list.SetItemText(0, 1, _T("aaa"));// 设置几行几列数据
	m_list.SetItemText(0, 2, _T("bbb"));
	m_list.SetItemText(1, 1, _T("ddd"));
	m_list.SetItemText(1, 2, _T("ccc"));

	//为list control控件其它单元格可编辑添加一个隐藏的edit控件
	DDX_Control(pDX, IDC_EDIT6, yin_edit);
	//SW_HIDE: 隐藏窗口并将活动状态传递给其它窗口
	yin_edit.ShowWindow(SW_HIDE);    //隐藏该控件

	//////////////////////////////////////////////////////////////////////////////////////

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAboutDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAboutDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAboutDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAboutDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CAboutDlg::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT1, &CAboutDlg::OnEnChangeEdit2)
	ON_EN_SETFOCUS(IDC_EDIT1, &CAboutDlg::OnSetfocusEdit1)
	ON_BN_CLICKED(IDC_BUTTON6, &CAboutDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CAboutDlg::OnBnClickedButton7)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAboutDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON9, &CAboutDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON8, &CAboutDlg::OnBnClickedButton8)
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_LIST9, &CAboutDlg::OnLvnBeginlabeleditList9)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST9, &CAboutDlg::OnLvnEndlabeleditList9)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST9, &CAboutDlg::OnNMDblclkList9)
	ON_EN_KILLFOCUS(IDC_EDIT6, &CAboutDlg::OnEnKillfocusEdit6)
	ON_NOTIFY(NM_RCLICK, IDC_LIST9, &CAboutDlg::OnNMRClickList9)
	ON_COMMAND(ID_TEXT_32771, &CAboutDlg::OnText32771)
	ON_COMMAND(ID_TEXT_32772, &CAboutDlg::OnText32772)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CMFC应用程序exeApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMFC应用程序App 自定义加载/保存方法

void CMFC应用程序exeApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CMFC应用程序exeApp::LoadCustomState()
{
}

void CMFC应用程序exeApp::SaveCustomState()
{
}

// CMFC应用程序App 消息处理程序


void CAboutDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox(_T("欢迎来到vc驿站"));   //点击此按钮(按钮)显示对话框MessageBox中的内容

 //第一种win32 sdk api方式： 
 //参数1：是当前对话框窗口句柄  参数2：当前对话框哪一个控件ID   返回值是一个句柄
 //HWND hw=::GetDlgItem(GetSafeHwnd(),IDOK);    //：：是全局   //获得对话框某一个句柄通过GetDlgItem函数
 //if (hw)   //如果控件句柄不为空，是有效的    
 //{
 // ::EnableWindow(hw, FALSE);    //通过全局EnableWindow这个函数进行禁用(FALSE)或启用(TRUE)指定的按钮
 //}

 //第三种方式：通过点击需要操作的按钮图标进行添加变量  ：直接使用变量调用操作按钮的函数
	login.EnableWindow(FALSE);
}


void CAboutDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	////MFC方式：
 ////第二种方法对按钮进行禁用和启用操作
 //CWnd* hw = GetDlgItem(IDOK);
 //if (hw)
 //{
 // ::EnableWindow(hw->GetSafeHwnd(), TRUE);    //这里也可以不用全局，用内部
 // hw->EnableWindow(TRUE);      //内部的
 //}


//第三种方式：通过点击按钮图标进行添加变量    ：直接使用变量调用操作按钮的函数
	login.EnableWindow(TRUE);
}


//通过此函数获得一个按钮组内哪个单选框按钮被选中了，也可以调试查看
void CAboutDlg::OnBnClickedButton3()  //通过此函数获得一个按钮组内哪个单选框按钮被选中了，调试才能查看
{
	int nId = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO4); //GetCheckedRadioButton获得选中的按钮
	CString str;
	str.Format(_T("选中了值为%d的单选框"), nId);
	MessageBox(str);
}



//通过此函数获得哪个复选框按钮被选中了
void CAboutDlg::OnBnClickedButton4()
{
	//第一种方式：通过指针的方式
	//CButton* cbu = (CButton*)GetDlgItem(IDC_CHECK1);
	//int icheck = cbu->GetCheck();
	//if (icheck==BST_CHECKED)
	//{
	//	MessageBox(_T("篮球复选框被勾选"));
	//}
	//else if (icheck==BST_UNCHECKED)
	//{
	//	MessageBox(_T("篮球复选框未被勾选"));
	//}


	//第二种方式：通过添加变量点击按钮图标进行进行操控按钮
	int icheck = lanqiu.GetCheck();
	if (icheck == BST_CHECKED)
	{
		MessageBox(_T("篮球复选框被勾选"));
	}
	else if (icheck == BST_UNCHECKED)
	{
		MessageBox(_T("篮球复选框未被勾选"));
	}
}


//编辑框控件函数
void CAboutDlg::OnBnClickedButton5()
{
	//SetDlgItemText(IDC_EDIT1, _T("111"));   //通过点击按钮在对话框中显示111
	//edit.SetWindowTextW(_T("222"));    //通过添加变量点击按钮图标进行进行操控按钮

	//通过sdk API的方式：
	//HWND hw = ::GetDlgItem(GetSafeHwnd(), IDC_EDIT1);
	//::SetWindowTextW(hw, _T("666"));



	//获得编辑框中的文本内容：
	//CString str;
	//GetDlgItemText(IDC_EDIT1,str);
	//MessageBox(str);

	//通过控件类型变量进行获取：
	//CString str;
	//edit.GetWindowTextW(str);
	//MessageBox(str);

	//通过sdk API方式进行获取：
	//HWND hw = ::GetDlgItem(GetSafeHwnd(), IDC_EDIT1);
	//TCHAR tc[200] = { 0 };
	//::GetWindowTextW(hw, tc, 200);
	//MessageBox(tc);


	////获得编辑框能输入多少个字符：  默认情况下编辑框控件的文本长度有限制
	//UINT un=edit.GetLimitText();

	////要解除这个限制或更改大一些，用SetLimitText(0)这个函数
	//edit.SetLimitText(0);
	//un = edit.GetLimitText();


	//向编辑框的结尾增加数据：
	//TCHAR th[] = _T("hello world\r\n");
	//int len = edit.GetWindowTextLengthW();
	//edit.SetSel(len, len, TRUE);
	//edit.ReplaceSel(th, FALSE);

	TCHAR th[] = _T("hello world.\r\n");
	int len = edit.GetWindowTextLengthW();
	edit.SetSel(len, len, TRUE);
	edit.ReplaceSel(th, FALSE);
}


//通过添加事件处理程序，实现编辑框内只允许输入大写ABC字符
void CAboutDlg::OnEnChangeEdit2()
{
	//CString str;
	//edit.GetWindowTextW(str);     //获取编辑框内容
	//for (int idx=0;idx<str.GetLength();idx++)    //通过for循环遍历这个字符串
	//{
	//	if (str[idx]!='A'&& str[idx] != 'B'&& str[idx] != 'C')
	//	{
	//		str.SetAt(idx, '#');     //如果条件不满足，则统一替换成#
	//	}
	//}
	//str.Replace(_T("#"), _T(""));    //把#替换成空字符
	//edit.SetWindowTextW(str);        //SetWindowTextW：改变控件的文本内容

	//始终显示最新的数据：光标定位到文本结尾
	//edit.SetFocus();
	//edit.SetSel(-1);
}


//只读的编辑框隐藏光标的实现函数,配合OnEnChangeEdit2（）函数进行使用
void CAboutDlg::OnSetfocusEdit1()
{
	::SendMessage(GetDlgItem(IDC_EDIT1)->GetSafeHwnd(), WM_KILLFOCUS, NULL, NULL);
}




//下拉框控件的内容是自动排序的，如果不需要被排序，可以把该排序属性设置为false
void CAboutDlg::OnBnClickedButton6()  //操作下拉框添加数据按钮，功能是点一下这个按钮，添加以下信息到下拉框
{
	m_box.AddString(_T("111"));    //需要给下拉框控件添加一个变量m_box,通过变量调用AddString函数
	m_box.AddString(_T("000"));
	m_box.AddString(_T("江西省"));
	m_box.AddString(_T("广东省"));
	m_box.AddString(_T("江苏省"));

	//自定义位置插入数据：
	m_box.InsertString(0, _T("湖北省"));   //参数1就是下标从0开始的，参数2是需要插入的数据
}




void CAboutDlg::OnBnClickedButton7()   //操作下拉框删除数据按钮
{
	//m_box.DeleteString(1);   //点击此按钮：通过下拉框变量，调用DeleteString函数按照索引下标位置删除数据
	//m_box.ResetContent();    //点击此按钮：通过ResetContent函数把下拉框数据全部清除

	//下拉框默认的选择：
	//m_box.SetCurSel(1);    //点击此按钮：参数是默认数据的下标
	//m_box.SetCurSel(-1);     //点击此按钮：如果不想选中任何一条，那么就传递 -1

	int cur = m_box.GetCurSel();        //点击此按钮：获取当前选中数据的下标

	//如果cur>=0，获取该下标中的数据信息：
	if (cur >= 0)
	{
		CString cstr;  //创建一个字符串类型变量
		m_box.GetLBText(cur, cstr);   //通过按钮变量调用GetLBText函数，参数1是下标，参数2是字符串变量
		MessageBox(cstr);    //通过MessageBox窗口提示该下标中的数据信息
	}
}



//省份下拉框控件
void CAboutDlg::OnCbnSelchangeCombo1()
{
	int cur = m_box.GetCurSel();
	if (cur < 0)   //判断如果下标<0那就是没有数据，直接return掉
	{
		return;
	}
	m_box2.ResetContent();   //清空   //如果不清空那么在下一个省份的城市中会包含上一个省份的城市

	CString cstr;
	m_box.GetLBText(cur, cstr);
	if (cstr == _T("江苏省"))
	{
		m_box2.AddString(_T("南京市"));
		m_box2.AddString(_T("扬州市"));
		m_box2.AddString(_T("昆山市"));
	}
	else if (cstr == _T("广东省"))
	{
		m_box2.AddString(_T("深圳市"));
		m_box2.AddString(_T("东莞市"));
		m_box2.AddString(_T("广州市"));
	}
}


void CAboutDlg::OnBnClickedButton9()  //获得条目按钮
{
	//获得列表框中总共有多少条目：
	int icount = list.GetCount();  //通过GetCount函数获得有多少条目就是多少条数据
	//list.DeleteString(0);   //通过DeleteString函数删除索引为0的数据
	//list.ResetContent();    //通过ResetContent函数删除所有数据
	list.SetCurSel(2); //单选       //通过SetCurSel函数设置列表框选中某条数据   //不想选中参数就传-1
	int a = list.GetCurSel();  //通过GetCurSel函数获得列表框当前选中的是哪条数据   //调试查看返回值a   //如果没有选中返回的是-1

	list.SetSel(0);  //多选    //通过SetSel函数点击条目按钮会自动选中这3个下标的数据
	list.SetSel(1, FALSE);   //参数2：FALSE不选中  
	list.SetSel(2);


	//获取选中的条目下标并提示出来
	int sel = list.GetSelCount();  //GetSelCount:获得当前选中的行数
	if (sel > 0)
	{
		int* parr = new int[sel];
		list.GetSelItems(sel, parr);   //GetSelItems:获得当前选中那些行

		for (int i = 0; i < sel; i++)
		{
			int a = parr[i];
			CString str;
			str.Format(_T("选中下标为%d"), a);
			MessageBox(str);
		}
	}


	//获得指定索引下标的文本内容：
	////第一种方式：
	//CString str;
	//list.GetText(0, str);
	//MessageBox(str);

	////第二种方式：
	//int len = list.GetTextLen(1);   //获得文本长度
	//TCHAR* ch = new TCHAR[len + 1];
	//memset(ch, 0, sizeof(TCHAR) * (len + 1));
	//list.GetText(1, ch);
	//MessageBox(ch);
	//delete[] ch;
}


//选中和取消选中一行按钮
void CAboutDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.SetFocus();   //加上这句话，不然不能高亮
	// 选中
	//m_list.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	// 取消选中
	//m_list.SetItemState(0, 0, LVIS_SELECTED | LVIS_FOCUSED);


	////获得ListControl中所有行的checkbox的状态   //也就是行的状态
	//int count = m_list.GetItemCount();   //GetItemCount:获得所有行数
	//for (int i = 0; i < count; i++)
	//{
	//	CString str = m_list.GetItemText(i, 0);
	//	str.Format(_T("第%d 行的checkbox 为选中状态"), i);
	//	MessageBox(str);
	//}


	////获得ListControl中所有行列的文本信息
	//int count = m_list.GetItemCount();   //GetItemCount:获得所有行数
	//int lcount = m_list.GetHeaderCtrl()->GetItemCount();   //获得总列数
	//for (int i = 0; i < count; i++)
	//{
	//	for (int j=0;j<lcount;j++)
	//	{
	//		CString str = m_list.GetItemText(i, j);  //参数1：行下标   参数2：列下标
	//		//str.Format(_T("第%d行%d列"), i,j);  //提示所有行列下标，就取消注释这一行
	//		MessageBox(str);
	//	}
	//}


	////获得当前选中的行
	//POSITION pos = m_list.GetFirstSelectedItemPosition();
	//while (pos)
	//{
	//	int row = m_list.GetNextSelectedItem(pos);

	//	CString str;
	//	str.Format(_T("%d"), row);
	//	MessageBox(str);
	//}


	////删除指定的行
	//m_list.DeleteItem(0);

	////删除所有行
	//m_list.DeleteAllItems();

	////删除指定的列
	//m_list.DeleteColumn(1);

	////删除所有列:    只能从尾巴删除，因为从头删除第一列，第二列就变成第一列了
	//int lcount = m_list.GetHeaderCtrl()->GetItemCount();
	//for (int i = lcount-1; i >=0; i--)
	//{
	//	m_list.DeleteColumn(i);
	//}
}


//////////////////////////////////////////////////////////////////////////////////////////////
//list control控件只能编辑第一列文本：需要为控件添加事件处理程序OnLvnBeginlabeleditList9和OnLvnEndlabeleditList9
void CAboutDlg::OnLvnBeginlabeleditList9(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO* pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

//只在这个事件处理器做处理   //特性：只能编辑第一列   //想要编辑其它列要添加一个Edit控件隐藏，这个手动添加代码
void CAboutDlg::OnLvnEndlabeleditList9(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO* pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//参数1：行   参数2：列  参数3：文本
	m_list.SetItemText(pDispInfo->item.iItem, pDispInfo->item.iSubItem, pDispInfo->item.pszText);

	*pResult = 0;
}
////////////////////////////////////////////////////////////////////////////////////////////

//为list control控件添加左键双击时间处理程序，实现其他单元格也可以进行编辑,通过隐藏的Edit控件
int m_Row = 0;
int m_Col = 0;
void CAboutDlg::OnNMDblclkList9(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CRect rc;
	m_Row = pNMItemActivate->iItem;     //获得选中的行
	m_Col = pNMItemActivate->iSubItem;  //获得选中的列

	if (m_Col != 0) //如果选择子项
	{
		m_list.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);   //获得子项的RECT
		yin_edit.SetParent(&m_list);    //将yin_edit控件坐标转换坐标为列表框中的坐标
		yin_edit.MoveWindow(rc);        //移动Edit到RECT坐在的位置
		yin_edit.SetWindowText(m_list.GetItemText(m_Row, m_Col));  //将该子项中的值放在Edit控件中；
		yin_edit.ShowWindow(SW_SHOW);    //显示Edit控件
		yin_edit.SetFocus();       //设置Edit焦点
		yin_edit.ShowCaret();      //显示光标
		yin_edit.SetSel(0, -1);    //全选编辑框的内容
	}

	*pResult = 0;
}

//为Edit控件添加事件处理程序：当失去光标，把新内容更新到编辑框
void CAboutDlg::OnEnKillfocusEdit6()
{
	// TODO: 在此添加控件通知处理程序代码

	CString str;
	yin_edit.GetWindowTextW(str);    //得到用户输入的新的内容  
	m_list.SetItemText(m_Row, m_Col, str);   //设置编辑框的新内容  
	yin_edit.ShowWindow(SW_HIDE);   //隐藏编辑框 
}


////////////////////////////////////////////////////////////////////////////////////////////
//list conyrol控件右键单击item弹出菜单
void CAboutDlg::OnNMRClickList9(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMItemActivate->iItem != -1)
	{
		//GetMessagePos():获得光标位置的X，y坐标。X坐标在低位整数，y坐标在高位整数
		//DWORD:是无符号的, 相当于unsigned long ，它是MFC的数据类型
		DWORD dwPos = GetMessagePos();
		//CPoint:表示一个坐标：x、y分别是点的横坐标和纵坐标
		//LOWORD返回低16位，HIWORD返回高16位
		CPoint point(LOWORD(dwPos), HIWORD(dwPos));

		CMenu menu;     //CMenu:创建一个菜单变量
		menu.LoadMenu(IDR_MENU1);    //加载指定菜单资源ID
		//GetSubMenu:获取子菜单的句柄(假如说子菜单中有2个菜单)那么，参数就是下标，0就是第一个菜单，1就是第二个菜单
		CMenu* popup = menu.GetSubMenu(0);

		//TrackPopupMenu:在指定位置显示一个浮动的弹出菜单，并在弹出菜单上跟踪项的选定内容
		//参数1：指定屏幕位置和鼠标位置标志 
		//参数2：指定弹出菜单的屏幕坐标中的水平位置
		//参数3：指定屏幕顶部菜单的屏幕坐标中的垂直位置
		//参数4：标识拥有弹出菜单的窗口
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}

	*pResult = 0;
}

//list conyrol控件在子项删除菜单：实现右键删除功能：右键添加事件处理程序–COMMAND
void CAboutDlg::OnText32771()
{
	// TODO: 在此添加命令处理程序代码

	int i, iState;
	int nItemSelected = m_list.GetSelectedCount();   //是获取当前选中的行数
	int nItemCount = m_list.GetItemCount();  //获得总行数
	if (nItemSelected < 1)   //如果没有选中行数
	{
		return;
	}

	for (i = nItemCount - 1; i >= 0; i--)    //遍历行数
	{
		//GetItemState:获取列表视图项的状态是否被选中
		//LVIS_SELECTED:选择项目。所选项目的外观取决于它是否具有焦点，也取决于用于选择的系统颜色。
		iState = m_list.GetItemState(i, LVIS_SELECTED);
		if (iState != 0)
		{
			m_list.DeleteItem(i);
		}
	}
}


//list conyrol控件复制剪切板 在子项复制菜单–右键添加事件处理程序–COMMAND
void CAboutDlg::OnText32772()
{
	// TODO: 在此添加命令处理程序代码
	CString	str;
	int	nItem;
	TCHAR* psz;
	HGLOBAL	hClipboardData;   //HGLOBAL:表示一个内存块

	nItem = m_list.GetSelectionMark();   //GetSelectionMark:获得有没有选中的项
	if (nItem != -1)
	{
		str = m_list.GetItemText(nItem, 2);
		//MessageBox(str);
	}

	//复制剪切板
	//isEmpty() 方法用于判断字符串是否为空
	if (!str.IsEmpty())
	{
		if (OpenClipboard())   //OpenClipboard:打开剪切板
		{
			EmptyClipboard();  //EmptyClipboard:清空剪切板:写入前必须先清空，得到剪切板占有权

			//GlobalAlloc:从堆中分配一定数目的字节数
			//参数1：指定如何分配内存：是一个标志    参数2：指定要申请的字节数
			//GetLength:获取选中字符串的长度,+1是因为字符串有一个结尾标志，TCHAR：在 Multi-Byte 字符集下占 1 个字节，在 Unicode 字符集下占 2 个字节。
			hClipboardData = GlobalAlloc(GMEM_DDESHARE, (str.GetLength() + 1) * sizeof(TCHAR));
			if (hClipboardData)
			{
				//GlobalLock：锁定内存中指定的内存块，并返回一个地址值，令其指向内存块的起始处
				psz = (TCHAR*)GlobalLock(hClipboardData);
				wcscpy(psz, str);
				//GlobalUnlock函数:解除锁定的内存块
				GlobalUnlock(hClipboardData);
				//SetClipboardData是把指定数据按照指定格式放入剪切板中
				//参数1：数据格式：网上查找   参数2：指定具有指定格式的数据的句柄
				//CF_UNICODETEXT:为Unicode 字符集
				SetClipboardData(CF_UNICODETEXT, hClipboardData);
			}
			//CloseClipboard:关闭剪贴板, 这使其他窗口或程序能访问剪贴板。
			CloseClipboard();
		}
	}
}

