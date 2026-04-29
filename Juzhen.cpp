// Juzhen.cpp : 实现文件
//在以下代码中，存在一个隐形问题，就是很多器件的编号不能重复，但是这个需要在另一个对话框中解决，暂时先不管。

#include "stdafx.h"
#include "WORK_GUI_3.h"
#include "Juzhen.h"


// CJuzhen 对话框
IMPLEMENT_DYNAMIC(CJuzhen, CDialog)

CJuzhen::CJuzhen(CWnd* pParent /*=NULL*/)
	: CDialog(CJuzhen::IDD, pParent)
{

}

CJuzhen::~CJuzhen()
{
}
int CJuzhen::GetMax(int a,int b){
	if(a>b) return a;
	else return b;
}
void CJuzhen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHURU, m_listshuru);
	DDX_Control(pDX, IDC_SHEJI, m_listsheji);
	DDX_Control(pDX, IDC_BIAOZHENG, m_listbiaozheng);
	DDX_Control(pDX, IDC_STATICSHURU, m_liststaticshuru);
	DDX_Control(pDX, IDC_STATICSHEJI, m_liststaticsheji);
	DDX_Control(pDX, IDC_STATICBIOAZHENG, m_liststaticbiaozheng);
}


BEGIN_MESSAGE_MAP(CJuzhen, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_SHURU, &CJuzhen::OnLvnItemchangedList3)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_SHEJI, &CJuzhen::OnLvnItemchangedSheji)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_BIAOZHENG, &CJuzhen::OnLvnItemchangedBiaozheng)
//	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CJuzhen 消息处理程序

void CJuzhen::OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
void CJuzhen::SetParentDlg(CWORK_GUI_3Dlg* pParentDlg)
{
    m_ParentDlg = pParentDlg;
}
//自定义的初始化函数，不知道自带的初始化在哪
void CJuzhen::Init()
{

	for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            connector[i][j] = _T("0"); // 将所有元素初始化为空字符串
        }
    }
	//接下来是初始化蜂窝层矩阵
	m_ParentDlg->Under_Length.GetWindowText(hive[0][1]);
	m_ParentDlg->Under_Width.GetWindowText(hive[0][2]);
	m_ParentDlg->Under_Height.GetWindowText(hive[0][3]);
	m_ParentDlg->Hive_Length.GetWindowText(hive[1][1]);
	m_ParentDlg->Hive_Width.GetWindowText(hive[1][2]);
	m_ParentDlg->Hive_Height.GetWindowText(hive[1][3]);
	m_ParentDlg->Top_Length.GetWindowText(hive[2][1]);
	m_ParentDlg->Top_Width.GetWindowText(hive[2][2]);
	m_ParentDlg->Top_Height.GetWindowText(hive[2][3]);
	kongCount=m_ParentDlg->m_listkong.GetItemCount();
	// 遍历每一行
    for (int i =0; i < kongCount; ++i)
    {
        // 遍历每一列（固定为3列）
        for (int j = 0; j < 4; ++j)
        {
            CString itemText1 = m_ParentDlg->m_listkong.GetItemText(i, j);
            hive[i+3][j] = itemText1;
        }
    }
	//接下来是初始化连接器矩阵
	rowCount=m_ParentDlg->m_listcon.GetItemCount();
	// 遍历每一行
    for (int i =0; i < rowCount; ++i)
    {
        // 遍历每一列（固定为4列）
        for (int j = 0; j < 7; ++j)
        {
            // 获取 m_listcon 的第 i 行、第 j 列的文本
            CString itemText = m_ParentDlg->m_listcon.GetItemText(i, j);
            // 存入 connector 矩阵
            connector[i][j] = itemText;
        }
    }
	// 初始化电缆线矩阵
    cableRowCount = m_ParentDlg->m_listcab.GetItemCount();
    for (int i = 0; i < cableRowCount; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
			if(j==1){//这里是因为电缆线有两个参数是表示连接了哪两个连接器，特殊处理
				CString cable1Str = m_ParentDlg->m_listcab.GetItemText(i, j);
				CString cable2Str = m_ParentDlg->m_listcab.GetItemText(i, j + 1); // j + 1 获取第二个参数
				// 将 CString 转换为 int
				int index1=0,index2=0;
				for(int l=0;l<rowCount;l++){
					if(connector[l][0]==cable1Str){
						index1=l;
						break;
					}
				}
				for(int l=0;l<rowCount;l++){
					if(connector[l][0]==cable2Str){
						index2=l;
						break;
					}
				}
				connector[index1][index2+7]="1";
				connector[index2][index1+7]="1";
				j++;
				continue;
			}
            CString itemText = m_ParentDlg->m_listcab.GetItemText(i, j);
            cable[i][j] = itemText; // 从0开始存储
        }
    }
	 // 初始化热管矩阵
    heatPipeRowCount = m_ParentDlg->m_listpipe.GetItemCount();
    for (int i = 0; i < heatPipeRowCount; ++i)
    {
        for (int j = 0; j <6; ++j)
        {
            CString itemText = m_ParentDlg->m_listpipe.GetItemText(i, j);
            heatPipe[i][j] = itemText; // 从0开始存储
        }
    }
	s=GetMax(rowCount+6,cableRowCount);
	s=GetMax(s,heatPipeRowCount);
	s=GetMax(s,3+kongCount);
}
//用来输出蜂窝层矩阵的函数
void CJuzhen::OutputHive(CListCtrl& m_listshuru,int x,int y,int n,int m) {
    for (int i = 0; i < 3; ++i) {
        int nRow = m_listshuru.InsertItem(m_listshuru.GetItemCount(), _T("1"));
        m_listshuru.SetItemText(nRow, y + 1, hive[i][1]); // y+1表示从第(y+1)列开始
        m_listshuru.SetItemText(nRow, y + 2, hive[i][2]);
        m_listshuru.SetItemText(nRow, y + 3, hive[i][3]);
    }
	for (int i = 0; i < kongCount; ++i) { 
		if(m_listshuru.GetItemCount()<=x+i+3){
				m_listshuru.InsertItem(m_listshuru.GetItemCount(),_T("1"));

			}
		m_listshuru.SetItemText(3+i+x,y+1, hive[i+3][1]);
        m_listshuru.SetItemText(3+i+x, y+2, hive[i+3][2]);
        m_listshuru.SetItemText(3+i+x, y+3, hive[i+3][3]);
    }
}
// 用来输出连接器矩阵的函数用来先测试，后面矩阵得改
void CJuzhen::OutputConnectorData(CListCtrl& m_listshuru,int x,int y,int n,int m)
{

    // 遍历 connector，输出有内容的行
    for (int i = 0; i < rowCount; ++i) 
    {
        // 检查该行是否有内容
        if (connector[i][0]!= _T("0")) // 假设第一列有内容则认为这一行有效
        {
            if(m_listshuru.GetItemCount()<=x+i){
				m_listshuru.InsertItem(m_listshuru.GetItemCount(),_T("1"));
			}
			//需要先把每个连接器之间的关系输出出来
			for(int j=0;j<rowCount;j++){
				 m_listshuru.SetItemText(i, y+j, connector[i][j+7]);
			}
			//再输入该连接器数据
            m_listshuru.SetItemText(i+x,y+rowCount, connector[i][1]);
            m_listshuru.SetItemText(i+x, y+rowCount+1, connector[i][2]);
            m_listshuru.SetItemText(i+x, y+rowCount+2, connector[i][3]);
			m_listshuru.SetItemText(i+x,y+rowCount+3, connector[i][4]);
            m_listshuru.SetItemText(i+x, y+rowCount+4, connector[i][5]);
            m_listshuru.SetItemText(i+x, y+rowCount+5, connector[i][6]);
			
        }
    }
}

//用来输出电缆线矩阵的函数，也是用于测试阶段
void CJuzhen::OutputCableData(CListCtrl& m_listshuru,int x,int y,int n,int m)
{
    // 遍历电缆线矩阵，输出有内容的行
    for (int i = 0; i < cableRowCount; ++i) // 从0开始遍历
    {
        // 检查该行是否有内容
        if (!cable[i][0].IsEmpty()) // 假设第一列有内容则认为这一行有效
        {
			if(m_listshuru.GetItemCount()<=x+i){
				m_listshuru.InsertItem(m_listshuru.GetItemCount(),_T("1"));
			}
            m_listshuru.SetItemText(x+i, y, cable[i][3]);
            m_listshuru.SetItemText(x+i, y+1, cable[i][4]);
			m_listshuru.SetItemText(x+i, y+2, cable[i][5]);
			m_listshuru.SetItemText(x+i, y+3, cable[i][6]);
			m_listshuru.SetItemText(x+i, y+4, cable[i][7]);
        }
    }
}
//用来输出热管矩阵的函数，用于测试阶段
void CJuzhen::OutputHeatPipeData(CListCtrl& m_listshuru,int x,int y,int n,int m)
{
    for (int i = 0; i < heatPipeRowCount; ++i) // 从0开始遍历
    {
        // 检查该行是否有内容
        if (!heatPipe[i][0].IsEmpty()) // 假设第一列有内容则认为这一行有效
        {
            if(m_listshuru.GetItemCount()<=x+i){
				m_listshuru.InsertItem(m_listshuru.GetItemCount(),_T("1"));
			}
            m_listshuru.SetItemText(x+i, y, heatPipe[i][1]);
            m_listshuru.SetItemText(x+i, y+1, heatPipe[i][2]);
			m_listshuru.SetItemText(x+i, y+2, heatPipe[i][3]);
            m_listshuru.SetItemText(x+i, y+3, heatPipe[i][4]);
			m_listshuru.SetItemText(x+i, y+4, heatPipe[i][5]);
        }
    }
}
//在矩阵的x,y处输出一个大小为n乘m的矩阵
void CJuzhen::OutputZeroData(CListCtrl& m_listshuru,int x,int y,int n,int m){
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(m_listshuru.GetItemCount()<=i+x){
				m_listshuru.InsertItem(m_listshuru.GetItemCount(),_T("0"));

			}
			m_listshuru.SetItemText(i+x,j+y,_T("0"));
		}
	}
}
void CJuzhen::OutputSheJi(CListCtrl& m_listsheji,int x,int y,int totalColumns){
    // 遍历 guaidian 数组中的每一行
    for (int lineIndex = 0,temp=0; lineIndex < 20; ++lineIndex)
    {
        bool hasValidData = false;
        // 查找该线路是否有有效的拐点
        if (m_ParentDlg->guaidian[lineIndex][0][0] != 0 || m_ParentDlg->guaidian[lineIndex][0][1] != 0)
        {
            hasValidData = true;
        }
        // 如果当前行有有效数据
        if (hasValidData)
        {
			
            
            // 遍历当前行的所有拐点
            int pointIndex = 0;
            for (int i = 0; i< 20; ++i)
            {
                // 获取每个点的 x 和 y 坐标
                if (m_ParentDlg->guaidian[lineIndex][pointIndex][0] != 0 || m_ParentDlg->guaidian[lineIndex][pointIndex][1] != 0)
                {
                    CString xCoord, yCoord;
                    xCoord.Format(_T("%d"), m_ParentDlg->guaidian[lineIndex][pointIndex][0]); // 获取 x 坐标
                    yCoord.Format(_T("%d"), m_ParentDlg->guaidian[lineIndex][pointIndex][1]); // 获取 y 坐标
					if(m_listsheji.GetItemCount()<=x+temp){
						m_listsheji.InsertItem(lineIndex, _T("")); // 插入新行
					}
                    // 将坐标值设置到对应的列
                    m_listsheji.SetItemText(x+temp, pointIndex * 2+y, xCoord);  // 第 2n 列是 x 坐标
                    m_listsheji.SetItemText(x+temp, pointIndex * 2 + 1+y, yCoord);  // 第 2n+1 列是 y 坐标
					pointIndex++;
                }
            }
			// 如果拐点数目不足 totalColumns，则补充 0
            int requiredColumns = 2*totalColumns;  // 需要的总列数
            int currentColumns = pointIndex * 2;  // 当前已填充的列数（每个拐点填充两个列）
            
            // 补充 0 到空余的列
            for (int i = currentColumns; i < requiredColumns; ++i)
            {
                CString zeroCoord = _T("0");  // 补充的坐标值为 0
                m_listsheji.SetItemText(x+temp,y+ i, zeroCoord);  // 设置该列为 0
            }
			temp++;
        }
    }
}
BOOL CJuzhen::OnInitDialog()
{
	CDialog::OnInitDialog();
	Init();
	  //加入以下部分设置Static字体
	m_Font.CreatePointFont(200, _T("宋体"), NULL);//参数：字体大小，样式，DC
    m_liststaticshuru.SetFont(&m_Font,true);
    m_liststaticshuru.SetWindowText(_T(" 输入矩阵"));
	 m_liststaticsheji.SetFont(&m_Font,true);
    m_liststaticsheji.SetWindowText(_T(" 设计矩阵"));
 m_liststaticbiaozheng.SetFont(&m_Font,true);
    m_liststaticbiaozheng.SetWindowText(_T(" 表征矩阵"));


//////////////////////////////////////////////////////////////////输入矩阵///////////////////////////////////////////////////////////////////////////////////////////////
//要注意一个点，由于第一列不知道为什么需要隐藏起来，之后的列数都需要加1
m_listshuru.SetTextBkColor(RGB(204, 255, 153));                         //设置改行文字背景颜色。若要改整个控件底色，文字（规定行列的表格）背景和背景颜色都得
m_listshuru.SetBkColor(RGB(204, 255, 153));								//将背景颜色设置。若要改整个控件底色，文字（规定行列的表格）背景和背景颜色都得改
m_listshuru.SetExtendedStyle(LVS_EX_FULLROWSELECT ); // 整行选择、网格线(已去掉)
//建立列数
m_listshuru.InsertColumn(0, _T("热管编号"), LVCFMT_LEFT,0);//真正的第1列，由于本列使用居中函数无法生效，故将表格宽度设为0进行了隐藏
for(int i=0;i<2*s;i++){
m_listshuru.InsertColumn(i+1, _T("长度"),LVCFMT_CENTER, 40);
}

//输入矩阵由四个矩阵加零矩阵组成，考虑到数量有限，采取有限个函数分开输出
//输出蜂窝层矩阵
OutputHive(m_listshuru,0,0,kongCount+3,3);
OutputZeroData(m_listshuru,0,4,kongCount+3,s-3);
////输出连接器矩阵
OutputConnectorData(m_listshuru,0,s+1,rowCount,rowCount+6);
OutputZeroData(m_listshuru,0,7+s+rowCount,rowCount,s-3-rowCount);
OutputZeroData(m_listshuru,3+kongCount,1,s-3-kongCount,3);
OutputZeroData(m_listshuru,3+kongCount,4,s-3-kongCount,s-3);
OutputZeroData(m_listshuru,rowCount,s+1,s-rowCount,rowCount+6);
OutputZeroData(m_listshuru,rowCount,s+7+rowCount,s-rowCount,s-rowCount-6);
////输出电缆线矩阵
OutputCableData(m_listshuru,s,1,cableRowCount,5);
OutputZeroData(m_listshuru,s,6,cableRowCount,s-5);
////输出热管矩阵
OutputHeatPipeData(m_listshuru,s,s+1,heatPipeRowCount,5);
OutputZeroData(m_listshuru,s,s+6,heatPipeRowCount,s-5);
OutputZeroData(m_listshuru,s+cableRowCount,1,s-cableRowCount,5);
OutputZeroData(m_listshuru,s+cableRowCount,6,s-cableRowCount,s-5);
OutputZeroData(m_listshuru,s+heatPipeRowCount,s+1,s-heatPipeRowCount,5);
OutputZeroData(m_listshuru,s+heatPipeRowCount,s+6,s-heatPipeRowCount,s-5);
//////////////////////////////////////////////////////////////////设计矩阵///////////////////////////////////////////////////////////////////////////////////////////////

m_listsheji.SetTextBkColor(RGB(233, 236, 250));                                        //设置改行文字背景颜色
m_listsheji.SetBkColor(RGB(233, 236, 250));													//将背景颜色设置
m_listsheji.SetExtendedStyle(LVS_EX_FULLROWSELECT ); // 整行选择、网格线(已去掉)
//建立列数
// 找出每一条线路的最大拐点数
int maxPoints = 0,m=0;
for (int i = 0; i < 20; i++)  // 假设最多有20条线路
{
    int pointCount = 0;
    // 统计每条线路的有效拐点个数
    for (int j = 0; j < 20; j++)  // 假设每条线路最多有20个拐点
    {
        if (m_ParentDlg->guaidian[i][j][0] != 0 || m_ParentDlg->guaidian[i][j][1] != 0)  // 检查是否有有效的拐点
        {
            pointCount++;
        }
    }
	if(pointCount!=0) m++;
    maxPoints = max(maxPoints, pointCount);  // 更新最大拐点数
}

int totalColumns = maxPoints * 2;  // 每个拐点有2列（x坐标和y坐标）


// 插入第1列：编号列
m_listsheji.InsertColumn(0, _T("编号"), LVCFMT_LEFT, 0);  // 隐藏该列，宽度设为0

// 根据最大拐点数动态插入列
for (int i = 1; i <= totalColumns||i<=m; i++)
{
    m_listsheji.InsertColumn(i, _T("temp"), LVCFMT_CENTER, 80);
}
OutputSheJi(m_listsheji,0,1,totalColumns);
int t_max=max(m,totalColumns);
OutputZeroData(m_listsheji,0,totalColumns+1,m,m-totalColumns);
OutputZeroData(m_listsheji,m,1,t_max-m,totalColumns);
OutputZeroData(m_listsheji,m,totalColumns+1,t_max-m,t_max-totalColumns);
//////////////////////////////////////////////////////////////////表征矩阵///////////////////////////////////////////////////////////////////////////////////////////////


m_listbiaozheng.SetTextBkColor(RGB(206, 237, 250));                                        //设置改行文字背景颜色
m_listbiaozheng.SetBkColor(RGB(206, 237, 250));													//将背景颜色设置
m_listbiaozheng.SetExtendedStyle(LVS_EX_FULLROWSELECT ); // 整行选择、网格线(已去掉)
//建立列数
// 插入第1列：编号列
m_listbiaozheng.InsertColumn(0, _T("编号"), LVCFMT_LEFT, 0);  // 隐藏该列，宽度设为0
for(int i=1;i<=2*s+2*maxPoints;i++){
	m_listbiaozheng.InsertColumn(i, _T("temp"), LVCFMT_CENTER, 80);
}

OutputHive(m_listbiaozheng,0,0,kongCount+3,3);
OutputZeroData(m_listbiaozheng,0,4,kongCount+3,s-3);
OutputConnectorData(m_listbiaozheng,0,s+1,rowCount,rowCount+6);
OutputZeroData(m_listbiaozheng,0,7+s+rowCount,rowCount,s-3-rowCount);
OutputZeroData(m_listbiaozheng,3+kongCount,1,s-3-kongCount,3);
OutputZeroData(m_listbiaozheng,3+kongCount,4,s-3-kongCount,s-3);
OutputZeroData(m_listbiaozheng,rowCount,s+1,s-rowCount,rowCount+6);
OutputZeroData(m_listbiaozheng,rowCount,s+7+rowCount,s-rowCount,s-rowCount-6);
OutputCableData(m_listbiaozheng,s,1,cableRowCount,5);
OutputZeroData(m_listbiaozheng,s,6,cableRowCount,s-5);
OutputHeatPipeData(m_listbiaozheng,s,s+1,heatPipeRowCount,5);
OutputZeroData(m_listbiaozheng,s,s+6,heatPipeRowCount,s-5);
OutputZeroData(m_listbiaozheng,s+cableRowCount,1,s-cableRowCount,5);
OutputZeroData(m_listbiaozheng,s+cableRowCount,6,s-cableRowCount,s-5);
OutputZeroData(m_listbiaozheng,s+heatPipeRowCount,s+1,s-heatPipeRowCount,5);
OutputZeroData(m_listbiaozheng,s+heatPipeRowCount,s+6,s-heatPipeRowCount,s-5);

OutputZeroData(m_listbiaozheng,0,1+2*s,2*s,2*maxPoints);

OutputZeroData(m_listbiaozheng,2*s,1,2*maxPoints,2*s);

OutputSheJi(m_listbiaozheng,2*s,2*s+1,totalColumns);
OutputZeroData(m_listbiaozheng,2*s,2*s+totalColumns+1,m,m-totalColumns);
OutputZeroData(m_listbiaozheng,m+2*s,1+2*s,t_max-m,totalColumns);
OutputZeroData(m_listbiaozheng,m+2*s,2*s+totalColumns+1,t_max-m,t_max-totalColumns);



	// TODO:  在此添加额外的初始化


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CJuzhen::OnLvnItemchangedSheji(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CJuzhen::OnLvnItemchangedBiaozheng(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

//HBRUSH CJuzhen::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
//
//	// TODO:  在此更改 DC 的任何属性
//将ID为IDC_STATIC的static控件字体颜色设置为红色
// 
//if(pWnd->GetDlgCtrlID() == IDC_SHURU)
//{
//	pDC->SetBkColor(RGB(255,0,0));
//}
//
//	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
//	return hbr;
//}
