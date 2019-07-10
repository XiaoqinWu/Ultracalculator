/********************************************************************
		filename :D:\MyAppProject\懒人计算器\代码\source\CMultDText.cpp
    	description :单行文本集合对象
		created	by 吴晓勤 2013/4/1 21:13
    	updated	by 吴晓勤 2013/4/1 21:13
*********************************************************************/
#include "StdAfx.h"
#include "CMultDText.h"
#include "stringhelper.h"
#include "CArxHelper.h"
/*
 *函数功能：根据文本集合，和偏移向量构建对象，适用于不带选择集的新建模式。
 *创建日期：2013/4/1 21:13
 *更新日期：2013/4/1 21:13
*/
CMultDText::CMultDText(const vector<string>& vecvalue,const AcGeVector3d offset)
{
	for(int i=0;i<vecvalue.size();i++)
	{
		AcDbText* pText;
		pText=new AcDbText();
		pText->setTextString(S2WS(vecvalue[i]).c_str());
		pText->setDatabaseDefaults();
		if(DocVars.docData().GetTextHeight()!=0)
		{
			pText->setHeight(DocVars.docData().GetTextHeight());
		}
		m_vecText.push_back(pText);
	}
	m_vecOffset.push_back(offset);
}
/*
 *函数功能：根据文本集合，和文本选择集构建对象，适用于带选择集的新建模式，新的文本样及相对位置来源于该选择集。
 *创建日期：2013/4/1 21:17
 *更新日期：2013/4/1 21:17
*/
CMultDText::CMultDText(const vector<string>& vecvalue,const vector<AcDbObjectId>& vecid)
{
	AcGePoint3d lastPoint;
	for(int i=0;i<vecid.size();i++)
	{
		AcDbText* pSource;
		if(acdbOpenObject(pSource,vecid[i],AcDb::kForRead)==Acad::eOk)
		{
			AcDbText* pText=new AcDbText();
			m_vecText.push_back(pText);
			//设置文字的位置
			pText->setDatabaseDefaults();
			//文字样式、厚度、垂直模式、水平模式、宽度因子、旋转
			pText->setTextStyle(pSource->textStyle());
			pText->setThickness(pSource->thickness());
			//文字的横向对齐模式、竖向对齐模式不能在此设置，这是一个需要研究的问题
			//pText->setVerticalMode(pSource->verticalMode());
			//pText->setHorizontalMode(pSource->horizontalMode());
			pText->setWidthFactor(pSource->widthFactor());
			pText->setRotation(pSource->rotation());
			//文字属性
			pText->setPropertiesFrom(pSource,false);
			//文字内容
			pText->setTextString(S2WS(vecvalue[i]).c_str());
			//文字高度
			if(DocVars.docData().GetTextHeight()!=0)
			{
				pText->setHeight(DocVars.docData().GetTextHeight());
			}
			else
			{
				pText->setHeight(pSource->height());
			}
			//文字间距
			if(i>0)m_vecOffset.push_back(pSource->position()-lastPoint);
			lastPoint=pSource->position();
			pSource->close();
		}
	}
}
/*
 *函数功能：析构时清除m_vecText所指向的文本对象AcDbText,防止内存泄露。
 *创建日期：2013/4/1 21:19
 *更新日期：2013/4/1 21:19
*/
CMultDText::~CMultDText()
{
	clear();
}
/*
 *函数功能：内存清理，集合清空。
 *创建日期：2013/4/1 21:20
 *更新日期：2013/4/1 21:20
*/
void CMultDText::clear()
{
	for(int i=0;i<m_vecText.size();i++)
	{
		delete m_vecText[i];
	}
	m_vecText.clear();
	m_vecOffset.clear();
}
/*
 *函数功能：显示对象的图形
 *创建日期：2013/3/30 23:10
 *更新日期：2013/3/30 23:10
*/
#if _MSC_VER>1400
#pragma message("using subWorldDraw")
Adesk::Boolean CMultDText::subWorldDraw (AcGiWorldDraw* mode)
{
	for(int i=0;i<m_vecText.size();i++)
	{
		mode->geometry().draw(m_vecText[i]);
	}
	return AcDbEntity::subWorldDraw(mode);
}
#else
#pragma message("using worldDraw")
Adesk::Boolean CMultDText::worldDraw (AcGiWorldDraw* mode)
{
	for(int i=0;i<m_vecText.size();i++)
	{
		mode->geometry().draw(m_vecText[i]);
	}
	return AcDbEntity::worldDraw(mode);
}
#endif

/*
 *函数功能：设置基点，第一个文本的位置位于基点，以后的文字根据偏移向量设置位置。
 *创建日期：2013/3/30 23:09
 *更新日期：2013/3/30 23:09
*/
void CMultDText::setBasePoint(AcGePoint3d basePoint)
{
	int offsetNum=m_vecOffset.size();
	AcGePoint3d lastPoint=basePoint;
	for(int i=0;i<m_vecText.size();i++)
	{
		AcGePoint3d pos=(i==0)?lastPoint:(lastPoint+m_vecOffset[(i-1)%offsetNum]);
		m_vecText[i]->setPosition(pos);
		lastPoint=pos;
	}
}
/*
 *函数功能：推送到dwg
 *创建日期：2013/3/30 23:08
 *更新日期：2013/3/30 23:08
*/
void CMultDText::appendToCurrentSpace()
{
	AcDbDatabase * pDb = acdbCurDwg();
	AcDbBlockTable * pBlockTable;
	pDb ->getBlockTable(pBlockTable, AcDb::kForRead);
	AcDbBlockTableRecord *pBlkRec;
	if (pDb ->tilemode())
	{
		pBlockTable ->getAt(ACDB_MODEL_SPACE, pBlkRec, AcDb::kForWrite);
	}
	else
	{
		pBlockTable ->getAt(ACDB_PAPER_SPACE, pBlkRec, AcDb::kForWrite);
	}
	pBlockTable ->close();
	for (int i = 0; i < m_vecText.size(); i++)
	{
		if (Acad::eOk == pBlkRec ->appendAcDbEntity(m_vecText[i]))
		{
			AcGePoint3d pt=m_vecText[i]->position();
			if(DocVars.docData().GetTextHeight()!=0)
			{
				m_vecText[i]->setHeight(DocVars.docData().GetTextHeight());
			}
			m_vecText[i] ->close();
		}
		else
		{
			delete m_vecText[i];
		}
	}
	pBlkRec ->close();
	m_vecText.clear();
	m_vecOffset.clear();
}