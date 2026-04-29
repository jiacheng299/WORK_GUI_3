#pragma once


// CModel 对话框

class CModel : public CDialog
{
	DECLARE_DYNAMIC(CModel)

public:
	CModel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CModel();

// 对话框数据
	enum { IDD = IDD_MODEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
