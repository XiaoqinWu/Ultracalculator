/*======================================================================
//        filename :acrxEntryPoint.cpp
//        description :程序入口
//        created by 吴晓勤   2012-11-10
//        updated by 吴晓勤   2012-11-10		
//======================================================================*/
#include "StdAfx.h"
#include "resource.h"
#define szRDS _RXST("Bat")
void MyAppRun()
{
	acedCommand(RTSTR, _T("bat_uc"), 0);
}
//----- ObjectARX EntryPoint
class CUltracalculatorApp : public AcRxArxApp 
{
public:
	//构造函数
	CUltracalculatorApp () : AcRxArxApp () {}
	//重写初始化消息处理函数
	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) 
	{
		//调用基类的初始化消息函数
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt);
		//加载时显示版本及快捷键
		AcadAppInfo info;
		info.setAppName (_T("Ultracalculator"));   
		if( Acad::eOk == info.readFromRegistry () )
		{
			const TCHAR* desc=info.appDesc();
			int len=_tcslen(desc);
			TCHAR cmds[3]=_T("cc");
			cmds[0]=desc[len-2];
			cmds[1]=desc[len-1];
			acutPrintf(desc);
			acutPrintf(_T("\n"));
			AcEdCommandStack::cast(acrxSysRegistry()->at(ACRX_COMMAND_DOCK))->addCommand(_T("BATTOOL"), _T("ULTRACALCULATOR"), cmds, ACRX_CMD_TRANSPARENT, MyAppRun);
		}
		//返回
		return (retCode) ;
	}
	//重写卸载消息处理函数
	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) 
	{
		//调用基类的卸载消息函数
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;
		//显示卸载成功
		acutPrintf(_T("\n懒人计算器卸载成功。"));
		//返回
		return (retCode) ;
	}
	//注册服务
	virtual void RegisterServerComponents () {}
} ;
IMPLEMENT_ARX_ENTRYPOINT(CUltracalculatorApp)