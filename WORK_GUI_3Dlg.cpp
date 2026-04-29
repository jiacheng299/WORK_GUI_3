// WORK_GUI_3Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WORK_GUI_3.h"
#include "WORK_GUI_3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWORK_GUI_3Dlg 对话框




CWORK_GUI_3Dlg::CWORK_GUI_3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWORK_GUI_3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWORK_GUI_3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TOPIC, m_top);
	DDX_Control(pDX, IDC_LISTPIPE, m_listpipe);
	DDX_Control(pDX, IDC_LISTCON, m_listcon);
	DDX_Control(pDX, IDC_LISTCAB, m_listcab);
	DDX_Control(pDX, IDC_EDIT1, Under_Length);
	DDX_Control(pDX, IDC_EDIT2, Under_Width);
	DDX_Control(pDX, IDC_EDIT3, Under_Height);
	DDX_Control(pDX, IDC_EDIT7, Top_Length);
	DDX_Control(pDX, IDC_EDIT8, Top_Width);
	DDX_Control(pDX, IDC_EDIT9, Top_Height);
	DDX_Control(pDX, IDC_EDIT4, Hive_Length);
	DDX_Control(pDX, IDC_EDIT5, Hive_Width);
	DDX_Control(pDX, IDC_EDIT6, Hive_Height);
	DDX_Control(pDX, IDC_LIST1, m_listkong);
}

BEGIN_MESSAGE_MAP(CWORK_GUI_3Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK2, &CWORK_GUI_3Dlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDOK, &CWORK_GUI_3Dlg::OnBnClickedOk)
	ON_STN_CLICKED(IDC_TOPIC, &CWORK_GUI_3Dlg::OnStnClickedTopic)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTPIPE, &CWORK_GUI_3Dlg::OnLvnItemchangedList2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTPIPE, &CWORK_GUI_3Dlg::OnLvnItemchangedListpipe)
	ON_EN_CHANGE(IDC_PIPED2, &CWORK_GUI_3Dlg::OnEnChangePiped2)
	ON_BN_CLICKED(IDOK3, &CWORK_GUI_3Dlg::OnBnClickedOk3)
	ON_EN_CHANGE(IDC_CONNUM2, &CWORK_GUI_3Dlg::OnEnChangeConnum2)
	ON_BN_CLICKED(IDOK4, &CWORK_GUI_3Dlg::OnBnClickedOk4)
	
	ON_BN_CLICKED(IDOK8, &CWORK_GUI_3Dlg::OnBnClickedOk8)
	ON_STN_CLICKED(IDC_CABNUM1, &CWORK_GUI_3Dlg::OnStnClickedCabnum1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTCAB, &CWORK_GUI_3Dlg::OnLvnItemchangedListcab)
	ON_BN_CLICKED(IDOK6, &CWORK_GUI_3Dlg::OnBnClickedOk6)
	ON_BN_CLICKED(IDOK9, &CWORK_GUI_3Dlg::OnBnClickedOk9)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTCON, &CWORK_GUI_3Dlg::OnLvnItemchangedListcon)
	ON_BN_CLICKED(IDOK10, &CWORK_GUI_3Dlg::OnBnClickedOk10)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT1, &CWORK_GUI_3Dlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CWORK_GUI_3Dlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDOK12, &CWORK_GUI_3Dlg::OnBnClickedOk12)
	ON_BN_CLICKED(IDOK11, &CWORK_GUI_3Dlg::OnBnClickedOk11)
	ON_STN_CLICKED(IDC_CONLEN1, &CWORK_GUI_3Dlg::OnStnClickedConlen1)
	ON_STN_CLICKED(IDC_PEPED3, &CWORK_GUI_3Dlg::OnStnClickedPeped3)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CWORK_GUI_3Dlg::OnLvnItemchangedList1)
	ON_STN_CLICKED(IDC_CONWID1, &CWORK_GUI_3Dlg::OnStnClickedConwid1)
	ON_EN_CHANGE(IDC_CABCON2, &CWORK_GUI_3Dlg::OnEnChangeCabcon2)
	ON_BN_CLICKED(IDC_BUTTON1, &CWORK_GUI_3Dlg::OnBnClickedButton1)

	ON_BN_CLICKED(IDC_BUTTON4, &CWORK_GUI_3Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CWORK_GUI_3Dlg::OnBnClickedButton3)
	ON_STN_CLICKED(IDC_PEPED2, &CWORK_GUI_3Dlg::OnStnClickedPeped2)
END_MESSAGE_MAP()


// CWORK_GUI_3Dlg 消息处理程序

BOOL CWORK_GUI_3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	int width = 1600;  // 新的宽度
    int height = 900; // 新的高度
    SetWindowPos(NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
	// 设置滚动条的范围和初始位置
    SCROLLINFO si;
    si.cbSize = sizeof(SCROLLINFO);
    si.fMask = SIF_RANGE | SIF_POS;
    si.nMin = 0;
    si.nMax = 300; // 设置滚动的范围（高度超出值）
	si.nPage=60;
    si.nPos = 0;
    SetScrollInfo(SB_VERT, &si, TRUE);
	 //加入以下部分设置Static字体
    m_Font.CreatePointFont(250,_T( "华文仿宋"), NULL);//参数：字体大小，样式，DC
    m_top.SetFont(&m_Font,true);
    m_top.SetWindowText(_T("多功能模块数字孪生可视化软件"));


                     

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
m_listkong.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); // 整行选择、网格线

// 获取ListCtrl的宽度
CRect rect;
m_listkong.GetClientRect(&rect);
int nColumnWidth = rect.Width() / 4; // 计算每列宽度

// 插入列并设置每列宽度
m_listkong.InsertColumn(0, _T("编号"), LVCFMT_CENTER, nColumnWidth);
m_listkong.InsertColumn(1, _T("横坐标"), LVCFMT_CENTER, nColumnWidth);
m_listkong.InsertColumn(2, _T("纵坐标"), LVCFMT_CENTER, nColumnWidth);
m_listkong.InsertColumn(3, _T("半径"), LVCFMT_CENTER, nColumnWidth);
	//热管报表初始化
m_listpipe.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); // 整行选择、网格线

m_listpipe.InsertColumn(0, _T("热管编号"), LVCFMT_CENTER, 100);

m_listpipe.InsertColumn(1, _T("方向"),LVCFMT_CENTER, 100); // 插入第2列的列名

m_listpipe.InsertColumn(2, _T("DI2"), LVCFMT_CENTER, 100); // 插入第3列的列名
m_listpipe.InsertColumn(3, _T("DI3"),LVCFMT_CENTER, 100); // 插入第2列的列名

m_listpipe.InsertColumn(4, _T("DI4"), LVCFMT_CENTER, 100); // 插入第3列的列名

m_listpipe.InsertColumn(5, _T("外径"), LVCFMT_CENTER, 100); // 插入第3列的列名
// 获取控件的宽度
m_listpipe.GetClientRect(&rect);
int Width1 = rect.Width();
// 手动设置列宽总和超出控件宽度以强制显示滚动条
int totalWidth1 = Width1 + 200; // 让列宽超出控件宽度 200 像素以显示滚动条
// 平均分配列宽
int columnWidth1 = totalWidth1 / 6;
for (int i = 0; i <6; ++i) {
    m_listpipe.SetColumnWidth(i, columnWidth1);
}
	//连接器报表初始化
// 获取ListCtrl的宽度

m_listcon.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); // 整行选择、网格线

m_listcon.InsertColumn(0, _T("连接器编号"), LVCFMT_CENTER, 110);
m_listcon.InsertColumn(1, _T("横坐标"), LVCFMT_CENTER, 80);
m_listcon.InsertColumn(2, _T("纵坐标"), LVCFMT_CENTER, 80);
m_listcon.InsertColumn(3, _T("长"), LVCFMT_CENTER, 80);
m_listcon.InsertColumn(4, _T("宽"), LVCFMT_CENTER, 80);
m_listcon.InsertColumn(5, _T("高"), LVCFMT_CENTER, 80);
m_listcon.InsertColumn(6, _T("安装方向"), LVCFMT_CENTER, 100);
// 获取控件的宽度
m_listcon.GetClientRect(&rect);
int controlWidth = rect.Width();
// 手动设置列宽总和超出控件宽度以强制显示滚动条
int totalColumnWidth = controlWidth + 200; // 让列宽超出控件宽度 200 像素以显示滚动条
// 平均分配列宽
int columnWidth = totalColumnWidth / 7;
for (int i = 0; i < 7; ++i) {
    m_listcon.SetColumnWidth(i, columnWidth);
}


	//电缆线报表初始化
m_listcab.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); // 整行选择、网格线

m_listcab.InsertColumn(0, _T("电缆线编号"), LVCFMT_CENTER, 110);

m_listcab.InsertColumn(1, _T("相连连接器"),LVCFMT_CENTER, 110); // 插入第2列的列名

m_listcab.InsertColumn(2, _T("相连连接器"), LVCFMT_CENTER, 110); // 插入第3列的列名

m_listcab.InsertColumn(3, _T("长"),LVCFMT_CENTER, 100); // 插入第4列的列名

m_listcab.InsertColumn(4, _T("宽"), LVCFMT_CENTER, 100); // 插入第4列的列名

m_listcab.InsertColumn(5, _T("高"), LVCFMT_CENTER, 100); // 插入第5列的列名
m_listcab.InsertColumn(6, _T("最小引出长"), LVCFMT_CENTER, 100); // 插入第4列的列名

m_listcab.InsertColumn(7, _T("半径"), LVCFMT_CENTER, 100); // 插入第5列的列名
// 获取控件的宽度
m_listcon.GetClientRect(&rect);
controlWidth = rect.Width();
// 手动设置列宽总和超出控件宽度以强制显示滚动条
totalColumnWidth = controlWidth + 300; // 让列宽超出控件宽度 200 像素以显示滚动条
// 平均分配列宽
columnWidth = totalColumnWidth / 8;
for (int i = 0; i < 8; ++i) {
    m_listcab.SetColumnWidth(i, columnWidth);
}



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWORK_GUI_3Dlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    SCROLLINFO si;
    GetScrollInfo(SB_VERT, &si, SIF_ALL);
    int yPos = si.nPos;  // 当前滚动条位置

    int yDelta = 0; // 垂直滚动的增量

    switch (nSBCode)
    {
        case SB_LINEUP: yDelta = -10; break;
        case SB_LINEDOWN: yDelta = 10; break;
        case SB_PAGEUP: yDelta = -si.nPage; break;
        case SB_PAGEDOWN: yDelta = si.nPage; break;
        case SB_THUMBPOSITION:
        case SB_THUMBTRACK: yDelta = nPos - yPos; break;
        default: return;
    }

    int newPos = yPos + yDelta;

    // 限制滚动范围，防止超出内容区域
    if (newPos < si.nMin)
        newPos = si.nMin;
    if (newPos > si.nMax)
        newPos = si.nMax;

    // 设置新的滚动位置
    SetScrollPos(SB_VERT, newPos);
    ScrollWindow(0, yPos - newPos);
}
BOOL CWORK_GUI_3Dlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
    SCROLLINFO si;
    GetScrollInfo(SB_VERT, &si, SIF_ALL);
    int yPos = si.nPos;

    int yDelta = (zDelta > 0) ? -50 : 50; // 鼠标滚轮每次滚动的增量

    int newPos = yPos + yDelta;

    // 限制滚动范围
    if (newPos < si.nMin)
        newPos = si.nMin;
    if (newPos > si.nMax)
        newPos = si.nMax;

    SetScrollPos(SB_VERT, newPos);
    ScrollWindow(0, yPos - newPos);

    return TRUE; // 表示消息已处理
}
// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWORK_GUI_3Dlg::OnPaint()
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
	CPaintDC dc(this); // 用于绘制的设备上下文
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
			CRect rect;//矩形区域对象
	GetClientRect(&rect);//获取客户区
	dc.FillSolidRect(rect,RGB(255,242,223));//用绿色填充客户区
		CDialog::OnPaint();

	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWORK_GUI_3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include"Login.h"
void CWORK_GUI_3Dlg::OnBnClickedOk2()
{
	CString strpipe;
		int nCountpipe = m_listpipe.GetItemCount();

		// 插入行
		GetDlgItemText(IDC_PIPENUM2,strpipe);
		m_listpipe.InsertItem(nCountpipe, strpipe); 

		// 设置第2列(方向)
		GetDlgItemText(IDC_PIPELEN2,strpipe);
		m_listpipe.SetItemText(nCountpipe, 1, strpipe); 

		// 设置第3列(DI2)
		GetDlgItemText(IDC_DI2,strpipe);
		m_listpipe.SetItemText(nCountpipe, 2, strpipe); 
		// 设置第4列(DI3)
		GetDlgItemText(IDC_DI3,strpipe);
		m_listpipe.SetItemText(nCountpipe, 3, strpipe); 

		// 设置第5列(DI4)
		GetDlgItemText(IDC_DI4,strpipe);
		m_listpipe.SetItemText(nCountpipe, 4, strpipe);
		// 设置第6列(外径)
		GetDlgItemText(IDC_PIPED2,strpipe);
		m_listpipe.SetItemText(nCountpipe, 5, strpipe);


}
#include"Juzhen.h"
void CWORK_GUI_3Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//OnOK();
	CJuzhen dlg;
	
	dlg.SetParentDlg(this);
	dlg.DoModal();
	
	

		//// 插入行
	
		//m_listshuru.InsertItem(1, _T("5")); 

		////// 设置第2列(长度)
		////GetDlgItemText(IDC_PIPELEN2,strpipe);
		////m_listpipe.SetItemText(nCountpipe, 1, strpipe); 

		////// 设置第3列(外径)
		////GetDlgItemText(IDC_PIPED2,strpipe);
		////m_listpipe.SetItemText(nCountpipe, 2, strpipe);


}

void CWORK_GUI_3Dlg::OnStnClickedTopic()
{
	// TODO: 在此添加控件通知处理程序代码
}



void CWORK_GUI_3Dlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CWORK_GUI_3Dlg::OnLvnItemchangedListpipe(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CWORK_GUI_3Dlg::OnEnChangePiped2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CWORK_GUI_3Dlg::OnBnClickedOk3()
{
	POSITION pospipe = m_listpipe.GetFirstSelectedItemPosition();
if (pospipe == NULL)
{
   MessageBox(_T("请你选择一项再操作"));
	   return;
}

    while (pospipe)
    {
        int nItempipe = m_listpipe.GetNextSelectedItem(pospipe);
		m_listpipe.DeleteItem(nItempipe);
    }
}

void CWORK_GUI_3Dlg::OnEnChangeConnum2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CWORK_GUI_3Dlg::OnBnClickedOk4()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strcon;
		int nCountcon = m_listcon.GetItemCount();//这里是获取项目总数，以便知道应该插入第几行

		// 插入行
		GetDlgItemText(IDC_CONNUM2,strcon);//获取名为 IDC_CONNUM2 的输入框中的文本，并将其存储在 strcon 中。
		m_listcon.InsertItem(nCountcon, strcon); //在nCountcon的位置插入一行，第一列名为strcon
	    // 设置第2列(横坐标)
		GetDlgItemText(IDC_X,strcon);
		m_listcon.SetItemText(nCountcon, 1, strcon); 

		// 设置第3列(纵坐标)
		GetDlgItemText(IDC_Y,strcon);
		m_listcon.SetItemText(nCountcon, 2, strcon); 
		// 设置第4列(长)
		GetDlgItemText(IDC_LEN,strcon);
		m_listcon.SetItemText(nCountcon, 3, strcon); 

		// 设置第5列(宽)
		GetDlgItemText(IDC_WIDTH,strcon);
		m_listcon.SetItemText(nCountcon, 4, strcon); 

		// 设置第6列(高)
		GetDlgItemText(IDC_HEIGHT,strcon);
		m_listcon.SetItemText(nCountcon, 5, strcon); 


		// 设置第7列(安装方向)
		GetDlgItemText(IDC_DIRECTION,strcon);
		m_listcon.SetItemText(nCountcon, 6, strcon); 

}

void CWORK_GUI_3Dlg::OnEnChangeConwid3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CWORK_GUI_3Dlg::OnStnClickedConwid4()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CWORK_GUI_3Dlg::OnBnClickedOk8()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION poscon = m_listcon.GetFirstSelectedItemPosition();
if (poscon == NULL)
{
   MessageBox(_T("请你选择一项再操作"));
	   return;
}

    while (poscon)
    {
        int nItemcon = m_listcon.GetNextSelectedItem(poscon);
		m_listcon.DeleteItem(nItemcon);
    }


}

void CWORK_GUI_3Dlg::OnStnClickedCabnum1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CWORK_GUI_3Dlg::OnLvnItemchangedListcab(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CWORK_GUI_3Dlg::OnBnClickedOk6()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strcab;
		int nCountcab = m_listcab.GetItemCount();

		// 插入行
		GetDlgItemText(IDC_CABNUM2,strcab);
		m_listcab.InsertItem(nCountcab, strcab); 

		// 设置第1列(相连连接器)
		GetDlgItemText(IDC_CABCON2,strcab);
		m_listcab.SetItemText(nCountcab, 1, strcab); 

		// 设置第2列(相连连接器)
		GetDlgItemText(IDC_CABCON4,strcab);
		m_listcab.SetItemText(nCountcab, 2, strcab); 

		// 设置第3列(长)
		GetDlgItemText(IDC_CABLEN2,strcab);
		m_listcab.SetItemText(nCountcab, 3, strcab); 

		// 设置第4列(宽)
		GetDlgItemText(IDC_CABWID2,strcab);
		m_listcab.SetItemText(nCountcab, 4, strcab); 

		// 设置第5列(高)
		GetDlgItemText(IDC_CABTAL2,strcab);
		m_listcab.SetItemText(nCountcab, 5, strcab); 
		// 设置第6列(最小引出端长度)
		GetDlgItemText(IDC_LENGTH,strcab);
		m_listcab.SetItemText(nCountcab, 6, strcab); 

		// 设置第7列(半径)
		GetDlgItemText(IDC_CABTAL3,strcab);
		m_listcab.SetItemText(nCountcab, 7, strcab); 

}

void CWORK_GUI_3Dlg::OnBnClickedOk9()
{
	// TODO: 在此添加控件通知处理程序代码
POSITION poscab = m_listcab.GetFirstSelectedItemPosition();
if (poscab == NULL)
{
   MessageBox(_T("请你选择一项再操作"));
	   return;
}

    while (poscab)
    {
        int nItemcab = m_listcab.GetNextSelectedItem(poscab);
		m_listcab.DeleteItem(nItemcab);
    }


}

void CWORK_GUI_3Dlg::OnLvnItemchangedListcon(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
#include"Model.h"
//考虑到组件通信的麻烦，这个函数可能要被放到juzhen模态框中
#include <shellapi.h> 

void CWORK_GUI_3Dlg::OnBnClickedOk10()
{
	// ===== 0. 先选择模型文件并校验模型类型 =====
	CFileDialog modelDlg(TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		_T("Model Files (*.prt;*.prt.*)|*.prt;*.prt.*|All Files (*.*)|*.*||"), this);
	modelDlg.m_ofn.lpstrTitle = _T("请先选择匹配的模型文件");
	if (modelDlg.DoModal() != IDOK)
		return;

	CString modelName = modelDlg.GetFileTitle(); // 不带扩展名

	// ===== 已支持的模型名称 =====
	// 后续你只需要在这里继续添加允许的模型名
	if (
		modelName != _T("base.prt")&&
		modelName != _T("base")
		)
	{
		AfxMessageBox(_T("不存在此类模型构建"), MB_ICONERROR);
		return;
	}
	// ===== 1. 读取界面输入 =====
	CString strLen, strWidth, strHeight;

	Under_Length.GetWindowText(strLen);
	Under_Width.GetWindowText(strWidth);
	Under_Height.GetWindowText(strHeight);

	strLen.Trim();
	strWidth.Trim();
	strHeight.Trim();

	// ===== 2. 输入校验 =====
	if (strLen.IsEmpty() || strWidth.IsEmpty() || strHeight.IsEmpty())
	{
		AfxMessageBox(_T("请先填写蜂窝层长度、宽度和高度！"), MB_ICONWARNING);
		return;
	}

	// ===== 3. 选择保存路径 =====
	CFileDialog fileDlg(FALSE, _T("txt"), _T("base_rel.txt"),
		OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST,
		_T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||"), this);

	if (fileDlg.DoModal() != IDOK)
		return;

	CString filePath = fileDlg.GetPathName();

	// ===== 4. 创建并写入文件 =====
	CStdioFile outFile;
	if (!outFile.Open(filePath, CFile::modeCreate | CFile::modeWrite | CFile::typeText))
	{
		AfxMessageBox(_T("无法创建输出文件！"), MB_ICONERROR);
		return;
	}

	CString line;
	double  Height = _ttof(strHeight) * 10.0;
	// ===== 参数定义 =====
	line.Format(_T("BASE_LEN=%.0f\n"), _ttof(strLen)/10.0);
	outFile.WriteString(line);

	line.Format(_T("BASE_WIDTH=%.0f\n"), _ttof(strWidth)/10.0);
	outFile.WriteString(line);

	line.Format(_T("BASE_HIGHT=%.0f\n"), Height);
	outFile.WriteString(line);
	// ===== HOLE 参数输出 =====
	int holeCount = m_listkong.GetItemCount();
	CString strX = m_listkong.GetItemText(0, 1);
	CString strY = m_listkong.GetItemText(0, 2);
	CString strR = m_listkong.GetItemText(0, 3);
	double x = _ttof(strX) / 10.0;
	double z = _ttof(strY) / 10.0;
	double r = _ttof(strR) / 10.0;
	double diameter = r * 2.0;
	line.Format(_T("HOLE_R=%.0f\n"), diameter);
	outFile.WriteString(line);

	line.Format(_T("HOLE_Z=%.0f\n"), z);
	outFile.WriteString(line);

	line.Format(_T("HOLE_X=%.0f\n"), x);
	outFile.WriteString(line);

	line.Format(_T("HOLE_HEIGHT=%.0f\n"), Height);
	outFile.WriteString(line);
	// ===== SLOT（连接器）参数定义 =====
	int slotCount = m_listcon.GetItemCount();

	for (int i = 0; i < slotCount; ++i)
	{
		CString strX = m_listcon.GetItemText(i, 1);      // 横坐标
		CString strZ = m_listcon.GetItemText(i, 2);      // 纵坐标
		CString strLen = m_listcon.GetItemText(i, 3);    // 长
		CString strWidth = m_listcon.GetItemText(i, 4);  // 宽
		CString strHeight = m_listcon.GetItemText(i, 5); // 高

		double slotX = _ttof(strX) / 10.0;
		double slotZ = _ttof(strZ) / 10.0;
		double slotLen = _ttof(strLen)/10.0;
		double slotWidth = _ttof(strWidth)/10.0 ;
		double slotHeight = _ttof(strHeight) /10.0;

		CString line;

		line.Format(_T("SLOT%d_X=%.1f\n"), i + 1, slotX);
		outFile.WriteString(line);

		line.Format(_T("SLOT%d_Z=%.1f\n"), i + 1, slotZ);
		outFile.WriteString(line);

		line.Format(_T("SLOT%d_WIDTH=%.1f\n"), i + 1, slotWidth);
		outFile.WriteString(line);

		line.Format(_T("SLOT%d_LEN=%.1f\n"), i + 1, slotLen);
		outFile.WriteString(line);

		line.Format(_T("SLOT%d_HEIGHT=%.1f\n"), i + 1, slotHeight);
		outFile.WriteString(line);

		outFile.WriteString(_T("\n"));
	}
	// ===== 读取 guaidian.txt 并输出 LINE 点 =====
	CStdioFile guaidianFile;
	if (!guaidianFile.Open(_T("guaidian.txt"), CFile::modeRead | CFile::typeText))
	{
		AfxMessageBox(_T("无法打开 guaidian.txt"));
		return;
	}

	int lineIndex = 0;   // LINE编号
	int pointIndex = 0;  // 每条线的点编号

	double baseWidth = _ttof(strWidth) / 10.0; // 用于Z变换

	while (guaidianFile.ReadString(line))
	{
		line.Trim();
		// 跳过空行
		if (line.IsEmpty())
			continue;

		// 遇到 "1:" "2:" 这种，表示新一组
		if (line.Find(_T(":")) != -1)
		{
			lineIndex++;
			pointIndex = 0;
			continue;
		}

		// 解析 X,Z
		int commaPos = line.Find(_T(","));
		if (commaPos == -1)
			continue;

		CString strX = line.Left(commaPos);
		CString strZ = line.Mid(commaPos + 1);

		double x = _ttof(strX);
		double z = _ttof(strZ);

		pointIndex++;

		CString out;

		// LINEi_DOTj_X
		out.Format(_T("LINE%d_DOT%d_X=%.0f\n"), lineIndex, pointIndex, -x);
		outFile.WriteString(out);

		// LINEi_DOTj_Z
		out.Format(_T("LINE%d_DOT%d_Z=%.0f\n"), lineIndex, pointIndex, baseWidth - z);
		outFile.WriteString(out);
	}

	guaidianFile.Close();
	// ===== 第二部分：固定关系 =====
	outFile.WriteString(_T("d0=BASE_LEN\n"));
	outFile.WriteString(_T("d1=BASE_WIDTH\n"));
	outFile.WriteString(_T("d2=0\n"));
	outFile.WriteString(_T("d3=0\n"));
	outFile.WriteString(_T("d4=BASE_HIGHT\n"));
	outFile.WriteString(_T("d88=HOLE_R\n"));
	outFile.WriteString(_T("d89=HOLE_Z\n"));
	outFile.WriteString(_T("d90=HOLE_X\n"));
	outFile.WriteString(_T("d95=HOLE_HEIGHT\n"));
	outFile.WriteString(_T("d9=SLOT1_WIDTH\n"));
	outFile.WriteString(_T("d10=SLOT1_LEN\n"));
	outFile.WriteString(_T("d11=SLOT1_X-SLOT1_LEN/2\n"));
	outFile.WriteString(_T("d12=BASE_WIDTH+SLOT1_WIDTH/2-SLOT1_Z\n"));
	outFile.WriteString(_T("d13=SLOT1_HEIGHT\n"));


	outFile.WriteString(_T("d42=SLOT2_LEN\n"));
	outFile.WriteString(_T("d41=SLOT2_WIDTH\n"));
	outFile.WriteString(_T("d43=SLOT2_X-SLOT2_LEN/2\n"));
	outFile.WriteString(_T("d44=BASE_WIDTH-SLOT2_WIDTH/2-SLOT2_Z\n"));

	outFile.WriteString(_T("d50=SLOT2_HEIGHT\n"));
	outFile.WriteString(_T("d99=SLOT3_WIDTH\n"));
	outFile.WriteString(_T("d100=SLOT3_LEN\n"));
	outFile.WriteString(_T("d102=SLOT3_X-SLOT3_LEN/2\n"));
	outFile.WriteString(_T("d101=BASE_WIDTH-SLOT3_Z-SLOT3_WIDTH/2\n"));
	outFile.WriteString(_T("d103=SLOT3_HEIGHT\n"));
	//第四个电连接器
	outFile.WriteString(_T("d108=SLOT4_WIDTH\n"));
	outFile.WriteString(_T("d109=SLOT4_LEN\n"));
	outFile.WriteString(_T("d110=BASE_WIDTH-SLOT4_Z-SLOT4_WIDTH/2\n"));
	outFile.WriteString(_T("d111=SLOT4_X-SLOT4_LEN/2\n"));
	outFile.WriteString(_T("d112=SLOT4_HEIGHT\n"));
	//第五个
	outFile.WriteString(_T("d124=SLOT5_WIDTH\n"));
	outFile.WriteString(_T("d125=SLOT5_LEN\n"));
	outFile.WriteString(_T("d126=SLOT5_X-SLOT5_LEN/2\n"));
	outFile.WriteString(_T("d127=BASE_WIDTH-SLOT5_Z-SLOT5_WIDTH/2\n"));
	outFile.WriteString(_T("d128=SLOT5_HEIGHT\n"));
	//第六个
	outFile.WriteString(_T("d133=SLOT6_WIDTH\n"));
	outFile.WriteString(_T("d134=SLOT6_LEN\n"));
	outFile.WriteString(_T("d135=BASE_WIDTH-SLOT6_Z-SLOT6_WIDTH/2\n"));
	outFile.WriteString(_T("d136=SLOT6_X-SLOT6_LEN/2\n"));
	outFile.WriteString(_T("d137=SLOT6_HEIGHT\n"));
	//第七个
	outFile.WriteString(_T("d142=SLOT7_WIDTH\n"));
	outFile.WriteString(_T("d143=SLOT7_LEN\n"));
	outFile.WriteString(_T("d144=BASE_WIDTH-SLOT7_Z-SLOT7_WIDTH/2\n"));
	outFile.WriteString(_T("d145=SLOT7_X-SLOT7_LEN/2\n"));
	outFile.WriteString(_T("d146=SLOT7_HEIGHT\n"));
	//第八个
	outFile.WriteString(_T("d151=SLOT8_WIDTH\n"));
	outFile.WriteString(_T("d152=SLOT8_LEN\n"));
	outFile.WriteString(_T("d154=BASE_WIDTH-SLOT8_Z-SLOT8_WIDTH/2\n"));
	outFile.WriteString(_T("d153=SLOT8_X-SLOT8_LEN/2\n"));
	outFile.WriteString(_T("d155=SLOT8_HEIGHT\n"));
	//第九个
	outFile.WriteString(_T("d160=SLOT9_WIDTH\n"));
	outFile.WriteString(_T("d161=SLOT9_LEN\n"));
	outFile.WriteString(_T("d163=BASE_WIDTH-SLOT9_Z-SLOT9_WIDTH/2\n"));
	outFile.WriteString(_T("d162=SLOT9_X-SLOT9_LEN/2\n"));
	outFile.WriteString(_T("d164=SLOT9_HEIGHT\n"));
	//第十个
	outFile.WriteString(_T("d169=SLOT10_WIDTH\n"));
	outFile.WriteString(_T("d170=SLOT10_LEN\n"));
	outFile.WriteString(_T("d172=SLOT10_X-SLOT10_LEN/2\n"));
	outFile.WriteString(_T("d171=BASE_WIDTH-SLOT10_Z-SLOT10_WIDTH/2\n"));
	outFile.WriteString(_T("d173=SLOT10_HEIGHT\n"));
	//十一
	outFile.WriteString(_T("d178=SLOT11_WIDTH\n"));
	outFile.WriteString(_T("d179=SLOT11_LEN\n"));
	outFile.WriteString(_T("d181=SLOT11_X-SLOT11_LEN/2\n"));
	outFile.WriteString(_T("d180=BASE_WIDTH-SLOT11_Z-SLOT11_WIDTH/2\n"));
	outFile.WriteString(_T("d182=SLOT11_HEIGHT\n"));
	//十二
	outFile.WriteString(_T("d187=SLOT12_WIDTH\n"));
	outFile.WriteString(_T("d188=SLOT12_LEN\n"));
	outFile.WriteString(_T("d190=SLOT12_X-SLOT12_LEN/2\n"));
	outFile.WriteString(_T("d189=BASE_WIDTH-SLOT12_Z-SLOT12_WIDTH/2\n"));
	outFile.WriteString(_T("d191=SLOT12_HEIGHT\n"));
	//十三
	outFile.WriteString(_T("d196=SLOT13_WIDTH\n"));
	outFile.WriteString(_T("d197=SLOT13_LEN\n"));
	outFile.WriteString(_T("d199=SLOT13_X-SLOT13_LEN/2\n"));
	outFile.WriteString(_T("d198=BASE_WIDTH-SLOT13_Z-SLOT13_WIDTH/2\n"));
	outFile.WriteString(_T("d200=SLOT13_HEIGHT\n"));
	//十四
	outFile.WriteString(_T("d205=SLOT14_WIDTH\n"));
	outFile.WriteString(_T("d206=SLOT14_LEN\n"));
	outFile.WriteString(_T("d208=SLOT14_X-SLOT14_LEN/2\n"));
	outFile.WriteString(_T("d207=BASE_WIDTH-SLOT14_Z-SLOT14_WIDTH/2\n"));
	outFile.WriteString(_T("d209=SLOT14_HEIGHT\n"));
	//十五
	outFile.WriteString(_T("d214=SLOT15_WIDTH\n"));
	outFile.WriteString(_T("d215=SLOT15_LEN\n"));
	outFile.WriteString(_T("d217=SLOT15_X-SLOT15_LEN/2\n"));
	outFile.WriteString(_T("d216=BASE_WIDTH-SLOT15_Z-SLOT15_WIDTH/2\n"));
	outFile.WriteString(_T("d218=SLOT15_HEIGHT\n"));
	//电缆线路径部分
	//1
	outFile.WriteString(_T("$d269=LINE1_DOT1_X\n"));
	outFile.WriteString(_T("d271=LINE1_DOT1_Z\n"));
	outFile.WriteString(_T("$d272=LINE1_DOT2_X\n"));
	outFile.WriteString(_T("d274=LINE1_DOT2_Z\n"));
	outFile.WriteString(_T("$d275=LINE1_DOT3_X\n"));
	outFile.WriteString(_T("d277=LINE1_DOT3_Z\n"));
	//2
	outFile.WriteString(_T("$d310=LINE2_DOT1_X\n"));
	outFile.WriteString(_T("d312=LINE2_DOT1_Z\n"));
	outFile.WriteString(_T("$d313=LINE2_DOT2_X\n"));
	outFile.WriteString(_T("d315=LINE2_DOT2_Z\n"));
	outFile.WriteString(_T("$d316=LINE2_DOT3_X\n"));
	outFile.WriteString(_T("d318=LINE2_DOT3_Z\n"));
	//3
	outFile.WriteString(_T("$d326=LINE3_DOT1_X\n"));
	outFile.WriteString(_T("d328=LINE3_DOT1_Z\n"));
	outFile.WriteString(_T("$d329=LINE3_DOT2_X\n"));
	outFile.WriteString(_T("d331=LINE3_DOT2_Z\n"));
	outFile.WriteString(_T("$d332=LINE3_DOT3_X\n"));
	outFile.WriteString(_T("d334=LINE3_DOT3_Z\n"));
	//4
	outFile.WriteString(_T("$d348=LINE4_DOT1_X\n"));
	outFile.WriteString(_T("d350=LINE4_DOT1_Z\n"));
	outFile.WriteString(_T("$d345=LINE4_DOT2_X\n"));
	outFile.WriteString(_T("d347=LINE4_DOT2_Z\n"));
	outFile.WriteString(_T("$d342=LINE4_DOT3_X\n"));
	outFile.WriteString(_T("d344=LINE4_DOT3_Z\n"));
	//5
	outFile.WriteString(_T("$d358=LINE5_DOT1_X\n"));
	outFile.WriteString(_T("d360=LINE5_DOT1_Z\n"));
	outFile.WriteString(_T("$d361=LINE5_DOT2_X\n"));  
	outFile.WriteString(_T("d363=LINE5_DOT2_Z\n"));
	outFile.WriteString(_T("$d364=LINE5_DOT3_X\n"));
	outFile.WriteString(_T("d366=LINE5_DOT3_Z\n"));
	//6
	outFile.WriteString(_T("$d373=LINE6_DOT4_X\n"));
	outFile.WriteString(_T("d375=LINE6_DOT4_Z\n"));
	outFile.WriteString(_T("$d376=LINE6_DOT3_X\n"));
	outFile.WriteString(_T("d378=LINE6_DOT3_Z\n"));
	outFile.WriteString(_T("$d379=LINE6_DOT2_X\n"));
	outFile.WriteString(_T("d381=LINE6_DOT2_Z\n"));
	outFile.WriteString(_T("$d382=LINE6_DOT1_X\n"));
	outFile.WriteString(_T("d384=LINE6_DOT1_Z\n"));
	//7
	outFile.WriteString(_T("$d397=LINE7_DOT1_X\n"));
	outFile.WriteString(_T("d399=LINE7_DOT1_Z\n"));
	outFile.WriteString(_T("$d400=LINE7_DOT2_X\n"));
	outFile.WriteString(_T("d402=LINE7_DOT2_Z\n"));
	outFile.WriteString(_T("$d403=LINE7_DOT3_X\n"));
	outFile.WriteString(_T("d405=LINE7_DOT3_Z\n"));
	//8
	outFile.WriteString(_T("$d413=LINE8_DOT3_X\n"));
	outFile.WriteString(_T("d415=LINE8_DOT3_Z\n"));
	outFile.WriteString(_T("$d416=LINE8_DOT2_X\n"));
	outFile.WriteString(_T("d418=LINE8_DOT2_Z\n"));
	outFile.WriteString(_T("$d419=LINE8_DOT1_X\n"));
	outFile.WriteString(_T("d421=LINE8_DOT1_Z\n"));
	outFile.Close();


	AfxMessageBox(_T("基础参数文件导出成功！"), MB_ICONINFORMATION);
}
HBRUSH CWORK_GUI_3Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔

	//将ID为IDC_STATIC的static控件字体颜色设置为红色
 
if(pWnd->GetDlgCtrlID() == IDC_TOPIC)
{
    pDC->SetTextColor(RGB(0,0,255));
	pDC->SetBkColor(RGB(255,242,223));//背景色为绿色
}

	return hbr;
}

void CWORK_GUI_3Dlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CWORK_GUI_3Dlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CWORK_GUI_3Dlg::OnBnClickedOk12()
{
		POSITION pospipe = m_listkong.GetFirstSelectedItemPosition();
	if (pospipe == NULL)
	{
	   MessageBox(_T("请你选择一项再操作"));
		   return;
	}

		while (pospipe)
		{
			int nItempipe = m_listkong.GetNextSelectedItem(pospipe);
			m_listkong.DeleteItem(nItempipe);
		}
}

void CWORK_GUI_3Dlg::OnBnClickedOk11()
{
	CString strpipe;
		int nCountpipe = m_listkong.GetItemCount();

		// 插入行
		GetDlgItemText(IDC_EDIT10,strpipe);
		m_listkong.InsertItem(nCountpipe, strpipe); 
		// 设置第1列(长度)
		GetDlgItemText(IDC_EDIT29,strpipe);
		m_listkong.SetItemText(nCountpipe, 1, strpipe); 
		// 设置第2列(长度)
		GetDlgItemText(IDC_EDIT25,strpipe);
		m_listkong.SetItemText(nCountpipe, 2, strpipe); 

		// 设置第3列(外径)
		GetDlgItemText(IDC_EDIT26,strpipe);
		m_listkong.SetItemText(nCountpipe, 3, strpipe); 
	// TODO: 在此添加控件通知处理程序代码
}

void CWORK_GUI_3Dlg::OnStnClickedConlen1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CWORK_GUI_3Dlg::OnStnClickedCabtal4()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CWORK_GUI_3Dlg::OnStnClickedPeped3()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CWORK_GUI_3Dlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CWORK_GUI_3Dlg::OnStnClickedConwid1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CWORK_GUI_3Dlg::OnEnChangeCabcon2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CWORK_GUI_3Dlg::OnBnClickedButton1()
{
    // Step 1: 创建 device.txt 文件
    CStdioFile deviceFile;
    if (deviceFile.Open(_T("device.txt"), CFile::modeCreate | CFile::modeWrite | CFile::typeText))
    {
       // 获取 m_listkong 的行数
		int rowCount = m_listkong.GetItemCount();
		// Step 2: 遍历每个圆孔，将其坐标转换为矩形并写入文件
		for (int i = 0; i < rowCount; ++i)
		{
			// 获取横坐标、纵坐标和半径
			CString strX = m_listkong.GetItemText(i, 1); // 第二行：横坐标
			CString strY = m_listkong.GetItemText(i, 2); // 第三行：纵坐标
			CString strRadius = m_listkong.GetItemText(i, 3); // 第四行：半径

			// 转换字符串为整数
			int x = _ttoi(strX)/10;
			int y = _ttoi(strY)/10;
			int radius = _ttoi(strRadius)/10;

			// 计算外接矩形的左下角和右上角坐标
			int leftX = x - radius;
			int bottomY = y - radius;
			int rightX = x + radius;
			int topY = y + radius;

			// 格式化输出内容为 "leftX\tbottomY\trightX\ttopY\n"
			CString line;
			line.Format(_T("%d\t%d\t%d\t%d\n"), leftX, bottomY, rightX, topY);

			CStringA lineA(line);
			deviceFile.Write(lineA, lineA.GetLength());
		 }
		// 继续写入 m_listcon 的数据（连接器矩形化处理）
		int conRowCount = m_listcon.GetItemCount();
		for (int i = 0; i < conRowCount; ++i)
		{
			// 获取中心坐标、长宽和方向
			double centerX = wcstod(m_listcon.GetItemText(i, 1), NULL)/10.0;
			double centerY = wcstod(m_listcon.GetItemText(i, 2), NULL)/10.0;
			double length = wcstod(m_listcon.GetItemText(i, 3), NULL) / 10.0;
			double width = wcstod(m_listcon.GetItemText(i, 4), NULL) / 10.0;
			int direction = _ttoi(m_listcon.GetItemText(i, 6));

			// 根据方向计算左下角和右上角的坐标
			double leftBottomX, leftBottomY, rightTopX, rightTopY;
			if (direction == 1 || direction == 3)
			{
				// 长边平行于 x 轴
				leftBottomX = centerX - (length / 2);
				rightTopX = centerX + (length / 2);
				leftBottomY = centerY - (width / 2);
				rightTopY = centerY + (width / 2);
			}
			else if (direction == 2 || direction == 4)
			{
				// 长边平行于 y 轴
				leftBottomX = centerX - (width / 2);
				rightTopX = centerX + (width / 2);
				leftBottomY = centerY - (length / 2);
				rightTopY = centerY + (length / 2);
			}

			// 写入文件
			CString line;
			line.Format(_T("%.0f\t%.0f\t%.0f\t%.0f\n"), leftBottomX, leftBottomY, rightTopX, rightTopY);
			CStringA lineA(line);
			deviceFile.Write(lineA, lineA.GetLength());
		}
		deviceFile.Close();
     }
    else
    {
        AfxMessageBox(_T("无法创建 device.txt 文件"));
        return;
    }
	CStdioFile connectFile;
	if (!connectFile.Open(_T("connectFile.txt"), CFile::modeCreate | CFile::modeWrite | CFile::typeText))
    {
        AfxMessageBox(_T("无法创建 connectFile.txt 文件"));
        return;
    }

    // Step 2: 获取 m_listcab 的行数
    int rowCount = m_listcab.GetItemCount();

    // Step 3: 遍历 m_listcab 每一行
    for (int i = 0; i < rowCount; ++i)
    {
        // 读取 m_listcab 中的连接器编号和电缆参数
        int connectorID1 = _ttoi(m_listcab.GetItemText(i,1)); // 第一列：连接器1编号
        int connectorID2 = _ttoi(m_listcab.GetItemText(i, 2)); // 第二列：连接器2编号
        int cableLength = _ttoi(m_listcab.GetItemText(i, 3));  // 第三列：电缆长度
        int cableWidth = _ttoi(m_listcab.GetItemText(i, 4));   // 第四列：电缆宽度
        int cableHeight = _ttoi(m_listcab.GetItemText(i, 5));  // 第五列：电缆高度
        int minLeadOutLength = _ttoi(m_listcab.GetItemText(i, 6)); // 第六列：最小引出长度
        int minBendRadius = _ttoi(m_listcab.GetItemText(i, 7));    // 第七列：最小弯折半径

        // 从 m_listcon 中获取 connectorID1 和 connectorID2 的中心点和方向
        int centerX1, centerY1, direction1;
        int centerX2, centerY2, direction2;

       // 使用 FindConnectorRow 函数获取指定连接器编号的行
		int conRowCount = m_listcon.GetItemCount();
		int row1;
		for (int i = 0; i < conRowCount; ++i) {
			int id = _ttoi(m_listcon.GetItemText(i, 0)); // 获取连接器编号
			if (id == connectorID1) {
				row1=id;
				break;
			}
		}
		int row2;
		for (int i = 0; i < conRowCount; ++i) {
			int id = _ttoi(m_listcon.GetItemText(i, 0)); // 获取连接器编号
			if (id == connectorID2) {
				row2=id;
				break;
			}
		}
        centerX1 = _ttoi(m_listcon.GetItemText(row1-1, 1)) / 10; // 连接器1中心横坐标
        centerY1 = _ttoi(m_listcon.GetItemText(row1-1, 2)) / 10.0; // 连接器1中心纵坐标
        direction1 = _ttoi(m_listcon.GetItemText(row1-1, 6)); // 连接器1出线方向

        centerX2 = _ttoi(m_listcon.GetItemText(row2-1, 1)) / 10.0; // 连接器2中心横坐标
        centerY2 = _ttoi(m_listcon.GetItemText(row2-1, 2)) / 10.0; // 连接器2中心纵坐标
        direction2 = _ttoi(m_listcon.GetItemText(row2-1, 6)); // 连接器2出线方向

        // 格式化输出内容
        CString line;
        line.Format(_T("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n"),
                    centerX1, centerY1, direction1,
                    centerX2, centerY2, direction2,
                    minLeadOutLength, minBendRadius);
        // 写入文件
        connectFile.WriteString(line);
    }

    connectFile.Close();
   // Step 2: 启动 MATLAB 并执行指定脚本
	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS; 
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = _T("open");            
	ShExecInfo.lpFile = _T("cmd.exe");
	ShExecInfo.lpParameters = _T("/k \"matlab -batch \"main\"\"");
	ShExecInfo.lpDirectory = NULL;              
	ShExecInfo.nShow = SW_SHOW;                 
	ShExecInfo.hInstApp = NULL;

	if (ShellExecuteEx(&ShExecInfo)) {
		// 如果需要等待程序完成
		WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
		CloseHandle(ShExecInfo.hProcess);
	}
	else {
		MessageBox(_T("Failed to start MATLAB"), _T("Error"), MB_OK | MB_ICONERROR);
	}

    
	memset(guaidian, 0, sizeof(guaidian));
	// 读取 guaidian.txt 文件
	CStdioFile guaidianFile;
	if (guaidianFile.Open(_T("guaidian.txt"), CFile::modeRead | CFile::typeText))
	{
		CString line;
		int currentLineIndex = -1;  // 当前线路索引
		int pointIndex = 0;  // 当前线路的拐点索引
		// 遍历文件行
		while (guaidianFile.ReadString(line))
		{
			if (line.IsEmpty() || line.Left(1) == _T("%")) 
			continue;
			// 判断当前行是否包含"线路"，如果包含，说明这一行是线路描述行
			if (line.Find(_T(":")) != -1)
			{
				currentLineIndex ++;
				pointIndex=0;
				continue;
			}

			// 如果当前行不包含"线路"字样，则处理该行中的坐标数据
			if (currentLineIndex != -1)
			{
				// 解析线路的拐点数据
				
				CString coordinates = line.Mid(line.Find(_T(":")) + 1); // 获取冒号后面的坐标部分

				// 使用空格分割坐标
				CString token;
				int commaPos = 0;
				while ((commaPos = coordinates.Find(_T(","))) != -1)
				{
					token = coordinates.Left(commaPos);  // 获取x或y坐标
					coordinates = coordinates.Mid(commaPos + 1);  // 剩余部分

					if (pointIndex < 20)  // 确保不会超出数组范围
					{
						guaidian[currentLineIndex][pointIndex][0] = _ttoi(token); // x坐标
						guaidian[currentLineIndex][pointIndex][1] = _ttoi(coordinates); // y坐标
						pointIndex++;
					}
				}
			}
		}

		guaidianFile.Close();
	}
}


void CWORK_GUI_3Dlg::InitHiveMatrix()
{
	// 初始化默认值
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			hiveMatrix[i][j] = i * 5 + j + 1;
		}
	}
}
void CWORK_GUI_3Dlg::LoadDataFromIni(const CString& iniPath)
{
	// 清空现有数据
	m_listpipe.DeleteAllItems();
	m_listcon.DeleteAllItems();
	m_listcab.DeleteAllItems();
	m_listkong.DeleteAllItems();
	TCHAR buffer[256];

	// 下层尺寸
	GetPrivateProfileString(_T("Dimensions"), _T("Under_Length"), _T(""), buffer, 256, iniPath);
	Under_Length.SetWindowText(buffer);
	GetPrivateProfileString(_T("Dimensions"), _T("Under_Width"), _T(""), buffer, 256, iniPath);
	Under_Width.SetWindowText(buffer);
	GetPrivateProfileString(_T("Dimensions"), _T("Under_Height"), _T(""), buffer, 256, iniPath);
	Under_Height.SetWindowText(buffer);

	// 蜂窝层尺寸
	GetPrivateProfileString(_T("Dimensions"), _T("Hive_Length"), _T(""), buffer, 256, iniPath);
	Hive_Length.SetWindowText(buffer);
	GetPrivateProfileString(_T("Dimensions"), _T("Hive_Width"), _T(""), buffer, 256, iniPath);
	Hive_Width.SetWindowText(buffer);
	GetPrivateProfileString(_T("Dimensions"), _T("Hive_Height"), _T(""), buffer, 256, iniPath);
	Hive_Height.SetWindowText(buffer);

	// 上层尺寸
	GetPrivateProfileString(_T("Dimensions"), _T("Top_Length"), _T(""), buffer, 256, iniPath);
	Top_Length.SetWindowText(buffer);
	GetPrivateProfileString(_T("Dimensions"), _T("Top_Width"), _T(""), buffer, 256, iniPath);
	Top_Width.SetWindowText(buffer);
	GetPrivateProfileString(_T("Dimensions"), _T("Top_Height"), _T(""), buffer, 256, iniPath);
	Top_Height.SetWindowText(buffer);

	for (int i = 1; i <= 5; i++) {
		CString key;
		key.Format(_T("Row%d"), i);

		TCHAR rowData[256];
		GetPrivateProfileString(_T("HiveMatrix"), key, _T(""), rowData, 256, iniPath);

		CStringArray values;
		int pos = 0;
		CString token;
		while ((token = CString(rowData).Tokenize(_T("|"), pos)) != _T("")) {
			values.Add(token);
		}

		// 存入矩阵数据（假设hiveMatrix是5x5的数组）
		for (int j = 0; j < 5 && j < values.GetSize(); j++) {
			hiveMatrix[i - 1][j] = _ttoi(values[j]);
		}
	}
	// 1. 加载热管数据
	TCHAR pipeEntries[4096];
	GetPrivateProfileString(_T("Pipes"), NULL, _T(""), pipeEntries, 4096, iniPath);

	TCHAR* pPipeKey = pipeEntries;
	while (*pPipeKey != _T('\0'))
	{
		CString value;
		GetPrivateProfileString(_T("Pipes"), pPipeKey, _T(""), value.GetBuffer(256), 256, iniPath);
		value.ReleaseBuffer();

		CStringArray fields;
		int pos = 0;
		CString token;
		while ((token = value.Tokenize(_T("|"), pos)) != _T(""))
		{
			fields.Add(token);
		}

		if (fields.GetSize() >= 6)
		{
			int idx = m_listpipe.InsertItem(m_listpipe.GetItemCount(), fields[0]);
			m_listpipe.SetItemText(idx, 1, fields[1]); // 方向
			m_listpipe.SetItemText(idx, 2, fields[2]); // DI2
			m_listpipe.SetItemText(idx, 3, fields[3]); // DI3
			m_listpipe.SetItemText(idx, 4, fields[4]); // DI4
			m_listpipe.SetItemText(idx, 5, fields[5]); // 外径
		}

		pPipeKey += _tcslen(pPipeKey) + 1;
	}

	// 2. 加载连接器数据
	TCHAR conEntries[4096];
	GetPrivateProfileString(_T("Connectors"), NULL, _T(""), conEntries, 4096, iniPath);

	TCHAR* pConKey = conEntries;
	while (*pConKey != _T('\0'))
	{
		CString value;
		GetPrivateProfileString(_T("Connectors"), pConKey, _T(""), value.GetBuffer(256), 256, iniPath);
		value.ReleaseBuffer();

		CStringArray fields;
		int pos = 0;
		CString token;
		while ((token = value.Tokenize(_T("|"), pos)) != _T(""))
		{
			fields.Add(token);
		}

		if (fields.GetSize() >= 7)
		{
			int idx = m_listcon.InsertItem(m_listcon.GetItemCount(), fields[0]);
			m_listcon.SetItemText(idx, 1, fields[1]); // X坐标
			m_listcon.SetItemText(idx, 2, fields[2]); // Y坐标
			m_listcon.SetItemText(idx, 3, fields[3]); // 长度
			m_listcon.SetItemText(idx, 4, fields[4]); // 宽度
			m_listcon.SetItemText(idx, 5, fields[5]); // 高度
			m_listcon.SetItemText(idx, 6, fields[6]); // 方向
		}

		pConKey += _tcslen(pConKey) + 1;
	}

	// 3. 加载电缆数据
	TCHAR cabEntries[4096];
	GetPrivateProfileString(_T("Cables"), NULL, _T(""), cabEntries, 4096, iniPath);

	TCHAR* pCabKey = cabEntries;
	while (*pCabKey != _T('\0'))
	{
		CString value;
		GetPrivateProfileString(_T("Cables"), pCabKey, _T(""), value.GetBuffer(256), 256, iniPath);
		value.ReleaseBuffer();

		CStringArray fields;
		int pos = 0;
		CString token;
		while ((token = value.Tokenize(_T("|"), pos)) != _T(""))
		{
			fields.Add(token);
		}

		if (fields.GetSize() >= 8)
		{
			int idx = m_listcab.InsertItem(m_listcab.GetItemCount(), fields[0]);
			m_listcab.SetItemText(idx, 1, fields[1]); // 连接器1
			m_listcab.SetItemText(idx, 2, fields[2]); // 连接器2
			m_listcab.SetItemText(idx, 3, fields[3]); // 长度
			m_listcab.SetItemText(idx, 4, fields[4]); // 宽度
			m_listcab.SetItemText(idx, 5, fields[5]); // 高度
			m_listcab.SetItemText(idx, 6, fields[6]); // 最小引出长度
			m_listcab.SetItemText(idx, 7, fields[7]); // 半径
		}

		pCabKey += _tcslen(pCabKey) + 1;
	}

	// 4. 加载孔数据
	TCHAR holeEntries[4096];
	GetPrivateProfileString(_T("Holes"), NULL, _T(""), holeEntries, 4096, iniPath);

	TCHAR* pHoleKey = holeEntries;
	while (*pHoleKey != _T('\0'))
	{
		CString value;
		GetPrivateProfileString(_T("Holes"), pHoleKey, _T(""), value.GetBuffer(256), 256, iniPath);
		value.ReleaseBuffer();

		CStringArray fields;
		int pos = 0;
		CString token;
		while ((token = value.Tokenize(_T("|"), pos)) != _T(""))
		{
			fields.Add(token);
		}

		if (fields.GetSize() >= 4)
		{
			int idx = m_listkong.InsertItem(m_listkong.GetItemCount(), fields[0]);
			m_listkong.SetItemText(idx, 1, fields[1]); // X坐标
			m_listkong.SetItemText(idx, 2, fields[2]); // Y坐标
			m_listkong.SetItemText(idx, 3, fields[3]); // 半径
		}

		pHoleKey += _tcslen(pHoleKey) + 1;
	}
}
void CWORK_GUI_3Dlg::SaveAllDataToIni(const CString& filePath)
{

	// 先删除旧的配置文件（如果存在）
	DeleteFile(filePath);

	// 1. 保存尺寸数据 [Dimensions]
	CString strValue;

	// 下层尺寸
	Under_Length.GetWindowText(strValue);
	WritePrivateProfileString(_T("Dimensions"), _T("Under_Length"), strValue, filePath);

	Under_Width.GetWindowText(strValue);
	WritePrivateProfileString(_T("Dimensions"), _T("Under_Width"), strValue, filePath);

	Under_Height.GetWindowText(strValue);
	WritePrivateProfileString(_T("Dimensions"), _T("Under_Height"), strValue, filePath);

	// 蜂窝层尺寸
	Hive_Length.GetWindowText(strValue);
	WritePrivateProfileString(_T("Dimensions"), _T("Hive_Length"), strValue, filePath);

	Hive_Width.GetWindowText(strValue);
	WritePrivateProfileString(_T("Dimensions"), _T("Hive_Width"), strValue, filePath);

	Hive_Height.GetWindowText(strValue);
	WritePrivateProfileString(_T("Dimensions"), _T("Hive_Height"), strValue, filePath);

	// 上层尺寸
	Top_Length.GetWindowText(strValue);
	WritePrivateProfileString(_T("Dimensions"), _T("Top_Length"), strValue, filePath);

	Top_Width.GetWindowText(strValue);
	WritePrivateProfileString(_T("Dimensions"), _T("Top_Width"), strValue, filePath);

	Top_Height.GetWindowText(strValue);
	WritePrivateProfileString(_T("Dimensions"), _T("Top_Height"), strValue, filePath);


	// 3. 保存热管数据 [Pipes]
	for (int i = 0; i < m_listpipe.GetItemCount(); i++)
	{
		CString key;
		key.Format(_T("Pipe_%d"), i + 1);

		CString pipeData;
		for (int j = 0; j < 6; j++) // 热管有6列数据
		{
			if (j != 0) pipeData += _T("|");
			pipeData += m_listpipe.GetItemText(i, j);
		}

		WritePrivateProfileString(_T("Pipes"), key, pipeData, filePath);
	}

	// 4. 保存连接器数据 [Connectors]
	for (int i = 0; i < m_listcon.GetItemCount(); i++)
	{
		CString key;
		key.Format(_T("Connector_%d"), i + 1);

		CString conData;
		for (int j = 0; j < 7; j++) // 连接器有7列数据
		{
			if (j != 0) conData += _T("|");
			conData += m_listcon.GetItemText(i, j);
		}

		WritePrivateProfileString(_T("Connectors"), key, conData, filePath);
	}

	// 5. 保存电缆数据 [Cables]
	for (int i = 0; i < m_listcab.GetItemCount(); i++)
	{
		CString key;
		key.Format(_T("Cable_%d"), i + 1);

		CString cabData;
		for (int j = 0; j < 8; j++) // 电缆有8列数据
		{
			if (j != 0) cabData += _T("|");
			cabData += m_listcab.GetItemText(i, j);
		}

		WritePrivateProfileString(_T("Cables"), key, cabData, filePath);
	}

	// 6. 保存孔数据 [Holes]
	for (int i = 0; i < m_listkong.GetItemCount(); i++)
	{
		CString key;
		key.Format(_T("Hole_%d"), i + 1);

		CString holeData;
		for (int j = 0; j < 4; j++) // 孔有4列数据
		{
			if (j != 0) holeData += _T("|");
			holeData += m_listkong.GetItemText(i, j);
		}

		WritePrivateProfileString(_T("Holes"), key, holeData, filePath);
	}
}
void CWORK_GUI_3Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fileDlg(FALSE, _T("ini"), _T("config.ini"),
		OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST,
		_T("INI Files (*.ini)|*.ini|All Files (*.*)|*.*||"), this);

	if (fileDlg.DoModal() == IDOK)
	{
		CString filePath = fileDlg.GetPathName();
		SaveAllDataToIni(filePath);
		AfxMessageBox(_T("所有数据导出成功！"), MB_ICONINFORMATION);
	}
}
//导入参数的功能实现
void CWORK_GUI_3Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	// 获取当前可执行文件路径
	TCHAR szExePath[MAX_PATH];
	GetModuleFileName(NULL, szExePath, MAX_PATH);

	// 提取目录部分，然后返回上一级
	CString strDir = szExePath;

	// 第一次查找，去掉文件名
	int nPos = strDir.ReverseFind(_T('\\'));
	if (nPos != -1)
	{
		strDir = strDir.Left(nPos); // 去掉文件名，得到当前目录

		// 第二次查找，去掉最后一级目录
		nPos = strDir.ReverseFind(_T('\\'));
		if (nPos != -1)
		{
			strDir = strDir.Left(nPos); // 返回上一级目录
		}
	}

	// 如果无法返回上一级，则使用当前目录
	if (strDir.IsEmpty())
	{
		strDir = szExePath;
		nPos = strDir.ReverseFind(_T('\\'));
		if (nPos != -1)
		{
			strDir = strDir.Left(nPos);
		}
	}

	CFileDialog fileDlg(TRUE, _T("ini"), NULL,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		_T("INI Files (*.ini)|*.ini|All Files (*.*)|*.*||"),
		this);

	// 设置初始目录为上一级目录
	fileDlg.m_ofn.lpstrInitialDir = strDir;
	fileDlg.m_ofn.lpstrTitle = _T("请选择参数配置文件");

	if (fileDlg.DoModal() == IDOK)
	{
		CString iniPath = fileDlg.GetPathName();
		LoadDataFromIni(iniPath); // 加载数据
	}
}

void CWORK_GUI_3Dlg::OnStnClickedPeped2()
{
	// TODO: 在此添加控件通知处理程序代码
}
