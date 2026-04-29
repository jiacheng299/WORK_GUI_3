// WORK_GUI_3Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CWORK_GUI_3Dlg 对话框
class CWORK_GUI_3Dlg : public CDialog
{
// 构造
public:
	CWORK_GUI_3Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_WORK_GUI_3_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	private:  
     CFont m_Font; //csdn改字体

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP();
	// INI 文件操作
	void LoadDataFromIni(const CString& iniPath);  // 从 INI 加载数据
	void SaveDataToIni(const CString& iniPath);    // 保存数据到 INI
	void SaveAllDataToIni(const CString& filePath);
	void InitHiveMatrix();                    // 初始化蜂窝层矩阵)
	// 解析单行数据的辅助函数
	void ParsePipeLine(const CString& line);       // 解析热管行
	void ParseConnectorLine(const CString& line);  // 解析连接器行
	void ParseCableLine(const CString& line);      // 解析电缆行
	void ParseHoleLine(const CString& line);       // 解析孔行
public:
	int hive[4][4];//这个矩阵用来存蜂窝层夹板
	int hiveMatrix[5][5]; // 蜂窝层矩阵
	int guaidian[20][20][2];
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonExportAll();
	CStatic m_top;
	afx_msg void OnStnClickedTopic();

	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listpipe;
	afx_msg void OnLvnItemchangedListpipe(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangePiped2();
	afx_msg void OnBnClickedOk3();
	CListCtrl m_listcon;
	afx_msg void OnEnChangeConnum2();
	afx_msg void OnBnClickedOk4();
	afx_msg void OnEnChangeConwid3();
	afx_msg void OnStnClickedConwid4();
	afx_msg void OnBnClickedOk8();
	afx_msg void OnStnClickedCabnum1();
	CListCtrl m_listcab;
	afx_msg void OnLvnItemchangedListcab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk6();
	afx_msg void OnBnClickedOk9();
	afx_msg void OnLvnItemchangedListcon(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk10();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeEdit1();
	CEdit Under_Length;
	afx_msg void OnEnChangeEdit2();
	CEdit Under_Width;
	CEdit Under_Height;
	CEdit Top_Length;
	CEdit Top_Width;
	CEdit Top_Height;
	CEdit Hive_Length;
	CEdit Hive_Width;
	CEdit Hive_Height;
	afx_msg void OnBnClickedOk12();
	afx_msg void OnBnClickedOk11();
	CListCtrl m_listkong;
	afx_msg void OnStnClickedConlen1();
	afx_msg void OnStnClickedCabtal4();
	afx_msg void OnStnClickedPeped3();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnStnClickedConwid1();
	afx_msg void OnEnChangeCabcon2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk13();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnStnClickedPeped2();
};
   