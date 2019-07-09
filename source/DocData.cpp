/********************************************************************
		filename :DocData.cpp
    	description :特定于文档的数据存储类
		created	by 吴晓勤 2013/3/30 19:10
    	updated	by 吴晓勤 2013/3/30 19:10
*********************************************************************/
#include "StdAfx.h"
#include "stringhelper.h"
AcApDataManager<CDocData> DocVars ;
/*
 *函数功能：构造函数中设置默认值
 *创建日期：2013/3/30 19:14
 *更新日期：2013/3/30 19:14
*/
CDocData::CDocData ()
{
	m_nTextScale=1;
	m_nTextSortMode=2;
	m_nTextOutMode=1;
	m_nIsExpand=0;
	m_fTextHeight=0;
}

/*
 *函数功能：拷贝构造函数
 *创建日期：2013/3/30 19:18
 *更新日期：2013/3/30 19:18
*/
CDocData::CDocData (const CDocData &data)
{
	m_nTextScale=1;
	m_nTextSortMode=2;
	m_nTextOutMode=1;
	m_nIsExpand=0;
	m_fTextHeight=0;
}

/*
 *函数功能：析构函数
 *创建日期：2013/3/30 19:19
 *更新日期：2013/3/30 19:19
*/
CDocData::~CDocData () {
}
/*
 *函数功能：添加表达式到列表
 *创建日期：2013-03-22
 *更新日期：2013-03-22
*/
void CDocData::SaveExpression(string expression)
{
	if(m_lstExpression.size()>0 && m_lstExpression.back()==expression)
		return;
	m_lstExpression.push_back(expression);
}
/*
 *函数功能：得到最后一个表达式
 *创建日期：2013-03-22
 *更新日期：2013-03-22
*/
string CDocData::GetLastExpression()
{
	if(m_lstExpression.size()==0)
		return "";
	return m_lstExpression.back();
}
/*
 *函数功能：得到输出模式
 *创建日期：2013/3/30 19:30
 *更新日期：2013/3/30 19:30
*/
int CDocData::GetOutMode()
{
	return m_nTextOutMode;
}
/*
 *函数功能：得到排序模式
 *创建日期：2013/3/30 19:29
 *更新日期：2013/3/30 19:29
*/
int CDocData::GetSortMode()
{
	return m_nTextSortMode;
}
/*
 *函数功能：得到保留小数位数
 *创建日期：2013/3/30 19:29
 *更新日期：2013/3/30 19:29
*/
int CDocData::GetScale()
{
	return m_nTextScale;
}
/*
 *函数功能：设置输出模式
 *创建日期：2013/3/30 19:27
 *更新日期：2013/3/30 19:27
*/
void CDocData::SetOutMode(int mode)
{
	m_nTextOutMode=mode;
}
/*
 *函数功能：设置排序模式
 *创建日期：2013/3/30 19:26
 *更新日期：2013/3/30 19:26
*/
void CDocData::SetSortMode(int mode)
{
	m_nTextSortMode=mode;
}
/*
 *函数功能：设置保留小数位数
 *创建日期：2013/3/30 19:26
 *更新日期：2013/3/30 19:26
*/
void CDocData::SetScale(int scale)
{
	m_nTextScale=scale;
}
/*
 *函数功能：设置当前文字高度
 *创建日期：2013/3/30 19:25
 *更新日期：2013/3/30 19:25
*/
void CDocData::SetTextHeight(double height)
{
	m_fTextHeight=height;
}
/*
 *函数功能：设置文字高度
 *创建日期：2013/3/30 21:23
 *更新日期：2013/3/30 21:23
*/
void CDocData::SetTextHeight(string height)
{
	m_fTextHeight=StringHelper::toDouble(height);
}
/*
 *函数功能：得到文字高度的字符串表示
 *创建日期：2013/3/30 21:54
 *更新日期：2013/3/30 21:54
*/
string CDocData::GetTextHeightStr()
{
	return StringHelper::toString(m_fTextHeight);
}
/*
 *函数功能：得到文字高度
 *创建日期：2013/3/30 21:55
 *更新日期：2013/3/30 21:55
*/
double CDocData::GetTextHeight()
{
	return m_fTextHeight;
}