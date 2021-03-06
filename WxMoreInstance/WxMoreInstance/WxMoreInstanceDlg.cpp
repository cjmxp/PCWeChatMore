
// WxMoreInstanceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WxMoreInstance.h"
#include "WxMoreInstanceDlg.h"
#include "../InjectDll/InjectDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL checkMutex();
BOOL checkEvent();
void checkInstance();

HANDLE mutex;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CWxMoreInstanceDlg 对话框




CWxMoreInstanceDlg::CWxMoreInstanceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWxMoreInstanceDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWxMoreInstanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWxMoreInstanceDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CWxMoreInstanceDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_MORE, &CWxMoreInstanceDlg::OnBnClickedBtnMore)
END_MESSAGE_MAP()


// CWxMoreInstanceDlg 消息处理程序

BOOL CWxMoreInstanceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	checkInstance();		//测试自己的程序去的，跟微信没有任何关系
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWxMoreInstanceDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWxMoreInstanceDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWxMoreInstanceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CWxMoreInstanceDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//杀死句柄
	StartHook();

	//HANDLE mutex1 = ::CreateMutex(NULL,FALSE,L"_WeChat_App_Instance_Identity_Mutex_Name");//这个句柄不行啊
	/*HANDLE mutex1 = ::OpenMutex(MUTEX_ALL_ACCESS,FALSE,L"_WeChat_App_Instance_Identity_Mutex_Name1");//这个句柄不行啊
	int err = GetLastError();
	CloseHandle(mutex1);
	printf("%d", err);

	HANDLE hNewHandle = NULL;
	BOOL bVal = DuplicateHandle(GetCurrentProcess(), mutex, GetCurrentProcess(), &hNewHandle, 0, FALSE, DUPLICATE_CLOSE_SOURCE);
	if(bVal){
		::MessageBox(NULL, L"xxxxxxxx", L"error", 0);
	}else{
		int err = GetLastError();
		printf("%d", err);
	}
	CloseHandle(hNewHandle);*/

}

BOOL checkMutex(){
	mutex = ::CreateMutex(NULL,FALSE,L"_WeChat_App_Instance_Identity_Mutex_Name1");
	int err = GetLastError();
	if (err == ERROR_ALREADY_EXISTS)
	{
		MessageBox(NULL, _T("already exist"), _T("ERROR"), SW_NORMAL);
		return FALSE;
	}
	return TRUE;
}


void checkInstance(){

	if(!checkMutex()){
		MessageBox(NULL, _T("已经有了单例，将要退出程序"), _T("ERROR"), SW_NORMAL);
		ExitProcess(0);
	}else{
		
		//CloseHandle(mutex);
		//OpenMutex(NULL, FALSE, )
	}
}
void CWxMoreInstanceDlg::OnBnClickedBtnMore()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(m_hWnd, _T("open"), _T("http://www.xiaoyutang.net/wordpress/?p=97"), NULL, NULL, SW_SHOWNORMAL);
}
