/*======================================================================
//        filename :Maindlg.h
//        description :主界面对话框类定义
//        created by 吴晓勤   2012-11-10
//        updated by 吴晓勤   2013-03-22			
//======================================================================*/
#pragma once
#include "StdAfx.h"
#include "acui.h"
#include "afxwin.h"
#include "CArxHelper.h"
#include "Express.h"
#include "stringhelper.h"
#include <string>
class CmdNode
{
	int ID;
	string Text;
	string Express;//表达式
	int TextOutMode;//文字输出模式，0-新建，1-修改，2-修改自己
	int TextSortMode;//文字排序模式，0-X坐标，1-Y坐标，2-自动判断
	int TextScale;//小数位数
	double TextHeight;//文字高度
};
class CMaindlg : public CAcUiDialog 
{
//添加动态识别及消息映射宏
	DECLARE_DYNAMIC (CMaindlg)
	DECLARE_MESSAGE_MAP()
public:
	CMaindlg (CWnd *pParent =NULL, HINSTANCE hInstance =NULL) ;
	enum { IDD = IDD_MAINDLG,MAX=255,MAXSELECT=1000,MAXEXPRESSLENGTH=1024} ;
private:
	long m_ZKHeight;//展开高度
	bool m_ZKflag;// 展开标记
	CEdit m_Express;// 表达式输入框
	CEdit m_TextHeight;// 文字高度
	CFont m_EditFont;// 表达式输入框字体
	CComboBox m_dotBox;// 小数点位数
	StringT m_str;// 表达式文本
private:
	string toString(double);//浮点数转为文本
	string toString(variant);//计算结果转为文本
	void DTextSort(vector<CDText>&);//文本排序
	void DTextNew(vector<string>&);//新建文本
	void OutputExpressionValue(string);
	void Command_GetValue();
	bool Js();
//各种消息函数
protected:
	virtual void DoDataExchange (CDataExchange *pDX) ;
	virtual BOOL OnInitDialog();
	virtual BOOL FindContextHelpFullPath(LPCTSTR fileName, CString& fullPath){return NULL;};
	afx_msg LRESULT OnAcadKeepFocus (WPARAM, LPARAM) ;
	afx_msg void OnBnClickedButtonZk();
	afx_msg void OnBnClickedButtonJs();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeExpression();
	afx_msg void OnEnChangeTextHeight();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedRadio(UINT);
	afx_msg void OnBnClickedButton(UINT);
//调用入口
public:
	static void CMaindlg::BAT_UC_main(void)
	{
		CMaindlg dlg;
		dlg.DoModal();
	}
	static void GetConfig();
private:
	static int m_config[1];//配置信息
	static vector<CmdNode>* m_pCmdNode;
} ;
//初始化静态成员
//[0]-是否展开
int CMaindlg::m_config[1]={1};
//声明为AutoCAD的命令
ACED_ARXCOMMAND_ENTRY_AUTO(CMaindlg, BAT_UC, _main, bat_uc, ACRX_CMD_TRANSPARENT, NULL)
