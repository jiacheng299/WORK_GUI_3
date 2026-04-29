// Model.cpp : 实现文件
//

#include "stdafx.h"
#include "WORK_GUI_3.h"
#include "Model.h"


// CModel 对话框

IMPLEMENT_DYNAMIC(CModel, CDialog)

CModel::CModel(CWnd* pParent /*=NULL*/)
	: CDialog(CModel::IDD, pParent)
{

}

CModel::~CModel()
{
}

void CModel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModel, CDialog)
END_MESSAGE_MAP()


// CModel 消息处理程序
