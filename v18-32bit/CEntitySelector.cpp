#include "StdAfx.h"
#include "CArxHelper.h"
#include "CEntitySelector.h"
#include "CmdHelper.h"
#include "stringhelper.h"
vector<CDText> CEntitySelector::GetDText()
{
	vector<CDText> ret;
	static resbuf eb=GetFilter(AcDbText::desc());
	vector<AcDbObjectId> ids=SelectAcDbObjects(&eb);
	for(int i=0;i<ids.size();i++)
	{
		CDText entity;
		if(entity.GetEntity(ids[i]))
			ret.push_back(entity);
	}
	return ret;
}
vector<CLine> CEntitySelector::GetLine()
{
	vector<CLine> ret;
	static resbuf eb=GetFilter(AcDbLine::desc());
	vector<AcDbObjectId> ids=SelectAcDbObjects(&eb);
	for(int i=0;i<ids.size();i++)
	{
		CLine entity;
		if(entity.GetEntity(ids[i]))
			ret.push_back(entity);
	}
	return ret;
}
vector<CDot> CEntitySelector::GetDot()
{
	vector<CDot> ret;
	static resbuf eb=GetFilter(AcDbPolyline::desc());
	vector<AcDbObjectId> ids=SelectAcDbObjects(&eb);
	for(int i=0;i<ids.size();i++)
	{
		CDot entity;
		if(entity.GetEntity(ids[i]))
			ret.push_back(entity);
	}
	return ret;
}
vector<CBlock> CEntitySelector::GetBlock()
{
	vector<CBlock> ret;
	static resbuf eb=GetFilter(AcDbBlockReference::desc());
	vector<AcDbObjectId> ids=SelectAcDbObjects(&eb);
	for(int i=0;i<ids.size();i++)
	{
		CBlock entity;
		if(entity.GetEntity(ids[i]))
			ret.push_back(entity);
	}
	return ret;
}
/*
 *函数功能：得到选择过滤器
 *创建日期：2012-11-12
 *更新日期：2013-05-08
*/
resbuf CEntitySelector::GetFilter(AcRxClass* aClass)
{
	struct resbuf ret;
	if(aClass==AcDbText::desc())
	{
		ret=*acutBuildList(RTDXF0,_T("TEXT"),RTNONE); 
	}
	else if(aClass==AcDbLine::desc())
	{
		ret=*acutBuildList(RTDXF0,_T("LINE"),RTNONE); 
	}
	else if(aClass==AcDbPolyline::desc())
	{
		ret=*acutBuildList(RTDXF0,_T("LWPOLYLINE"),RTNONE); 
	}
	else if(aClass==AcDbBlockReference::desc())
	{
		ret=*acutBuildList(RTDXF0,_T("INSERT"),RTNONE); 
	}
	return ret;
}
/*
 *函数功能：拾取点
 *创建日期：2012-11-12
 *更新日期：2012-11-13
*/
bool CEntitySelector::PickPoint(AcGePoint3d& pt,string msg)
{
	return acedGetPoint(NULL,S2WS(msg).c_str(),asDblArray(pt))==RTNORM?true:false;
}
/*
 *函数功能：交互式获取文本对象的id
 *创建日期：2012-11-12
 *更新日期：2012-11-12
*/
vector<AcDbObjectId> CEntitySelector::SelectAcDbObjects(struct resbuf* eb)
{
	vector<AcDbObjectId> ret;
	ads_name ssname;
	if(eb==NULL) return ret;
	//获得选择集
	long length=0;
	if(acedSSGet(NULL,NULL,NULL,eb,ssname)==RTNORM && acedSSLength(ssname,&length)==RTNORM)
	{
		AcDbObjectId id=AcDbObjectId::kNull;
		ads_name ent;
		for(int i=0;i<length;i++)
		{
			//获得选择集ssname中第j个对象的ads_name
			if(acedSSName(ssname,i,ent)==RTNORM && acdbGetObjectId(id,ent)==Acad::eOk)
			{
				ret.push_back(id);
			}
		}
	}
	acedSSFree(ssname);
	return ret;
}