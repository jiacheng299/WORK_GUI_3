#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "WORK_GUI_3Dlg.h"

// CJuzhen 对话框

class CJuzhen : public CDialog
{
	DECLARE_DYNAMIC(CJuzhen)

public:
	CJuzhen(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CJuzhen();

// 对话框数据
	enum { IDD = IDD_JUZHEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listshuru;
	afx_msg void OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedSheji(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listsheji;
	afx_msg void OnLvnItemchangedBiaozheng(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listbiaozheng;
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CStatic m_liststaticshuru;
	CStatic m_liststaticsheji;
	CStatic m_liststaticbiaozheng;
	void SetParentDlg(CWORK_GUI_3Dlg* pParentDlg);
	//下面是我新定义的一些变量
	CString hive[100][4];//蜂窝层矩阵
	CString connector[100][100];//连接器矩阵
	CString cable[100][10]; // 假设电缆线矩阵最大行数为100
	int kongCount;//蜂窝层打孔个数
	int rowCount;//连接器的个数
    int cableRowCount; // 当前电缆线
	int s;//s是论文中提及的max(l+3, m, n)。l是连接器个数，m是电缆线个数，n是热管个数
	CString heatPipe[100][10]; // 假设热管矩阵最大行数为100
    int heatPipeRowCount;      // 当前热管行数
	//下面是我新定义的一些函数,降低耦合性
	int GetMax(int a,int b);
	void OutputZeroData(CListCtrl& m_listshuru,int x, int y, int n, int m);
	void OutputHive(CListCtrl& m_listshuru,int x,int y,int n,int m);
	void OutputHeatPipeData(CListCtrl& m_listshuru,int x,int y,int n,int m);
	void OutputCableData(CListCtrl& m_listshuru,int x,int y,int n,int m);
	void OutputConnectorData(CListCtrl& m_listshuru,int x,int y,int n,int m);
	void Init();
	void CJuzhen::OutputSheJi(CListCtrl& m_listsheji,int x,int y,int totalColumns);
private:  
	 CWORK_GUI_3Dlg* m_ParentDlg;
     CFont m_Font; 
};
  