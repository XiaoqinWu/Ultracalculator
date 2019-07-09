#pragma once
#include "StdAfx.h"
#include "CArxHelper.h"
#include "stringhelper.h"
/*
 *函数功能：jig类构造函数
 *创建日期：2013-03-25
 *更新日期：2013-03-25
*/
CTextValueJig::CTextValueJig()
{ }
/*
 *函数功能：开始拖动,单个文本直接拖动。
 *创建日期：2013-03-25
 *更新日期：2013-03-25
*/
void CTextValueJig::doIt(string text)
{
#ifdef _UNICODE
	vector<string> vecvalue;
	vecvalue.push_back(text);
	m_pEntity=new CMultDText(vecvalue,AcGeVector3d(0,0,0));
	m_basepoint=m_startpoint=AcGePoint3d(0,0,0);
	setDispPrompt(_T("指定点: "));
	if ( AcEdJig::kNormal == drag() )
	{
		m_pEntity ->appendToCurrentSpace();
	}
	else m_pEntity->clear();
	delete m_pEntity;
#endif
}
/*
 *函数功能：开始拖动,以所选择的一列文本作为模板。
 *创建日期：2013-03-25
 *更新日期：2013-03-25
*/
void CTextValueJig::doIt(const vector<AcDbObjectId>& vecid, const vector<string>& vecvalue)
{
	if(vecid.size()==0)return;
	CDText dtext=CArxHelper::GetEntityByObjectId(vecid[0]);
	m_basepoint=AcGePoint3d(dtext.x,dtext.y,dtext.z);
	ads_point ptResult;
	if(RTNORM==acedGetPoint(NULL,_T("\n指定基点: "),ptResult))
	{
		m_pEntity=new CMultDText(vecvalue,vecid);
		m_startpoint.x=ptResult[0];
		m_startpoint.y=ptResult[1];
		m_startpoint.z=ptResult[2];
		setDispPrompt(_T("指定第二个点: "));
		if ( AcEdJig::kNormal == drag() )
		{	
			m_pEntity ->appendToCurrentSpace();
		}
		else m_pEntity->clear();
		delete m_pEntity;
		m_pEntity=NULL;
	}
}
/*
 *函数功能：开始拖动，以offset作为间距
 *创建日期：2013-03-25
 *更新日期：2013-03-25
*/
void CTextValueJig::doIt(AcGeVector3d offset, const vector<string>& vecvalue)
{
	m_pEntity=new CMultDText(vecvalue,offset);
	m_basepoint=m_startpoint=AcGePoint3d(0,0,0);
	setDispPrompt(_T("指定点: "));
	if ( AcEdJig::kNormal == drag() )
	{	
		m_pEntity ->appendToCurrentSpace();
	}
	else m_pEntity->clear();
	delete m_pEntity;
	m_pEntity=NULL;
}
/*
 *函数功能：重写sampler函数，用于采集样本点
 *创建日期：2012-11-13
 *更新日期：2013-03-24
*/
AcEdJig::DragStatus	CTextValueJig::sampler()
{
	setUserInputControls((UserInputControls)
		(AcEdJig::kAccept3dCoordinates
		| AcEdJig::kNoNegativeResponseAccepted
		| AcEdJig::kNoZeroResponseAccepted));

	static AcGePoint3d dTempPoint;
	DragStatus stat = acquirePoint(m_endpoint);
	if (dTempPoint != m_endpoint)
	{
		dTempPoint = m_endpoint;
	}
	else if (stat == AcEdJig::kNormal)
	{
		return AcEdJig::kNoChange;
	}
	return stat;
}
/*
 *函数功能：重写update函数，用于实时更新。
 *创建日期：2012-11-13
 *更新日期：2013-03-25
*/
Adesk::Boolean CTextValueJig::update()
{
	m_pEntity->setBasePoint(m_basepoint+(m_endpoint-m_startpoint));
	return Adesk::kTrue;
}
/*
 *函数功能：重写entity函数,用于拖动结束后的更新。
 *创建日期：2012-11-13
 *更新日期：2012-11-13
*/
AcDbEntity*	CTextValueJig::entity() const
{
	m_pEntity->setBasePoint(m_basepoint+(m_endpoint-m_startpoint));
	return m_pEntity;
}
