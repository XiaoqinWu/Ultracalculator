#include "StdAfx.h"
#include "CArxHelper.h"
#include "stringhelper.h"
#include "Express.h"
#include "Except.h"
#include "CmdHelper.h"
/*
 *函数功能：根据id得到对象
 *创建日期：2012-11-12
 *更新日期：2012-11-12
*/
CDText CArxHelper::GetEntityByObjectId(AcDbObjectId id)
{
	CDText ret;
	AcDbText* pText;
	//通过id打开对象并获得对象指针
	if(acdbOpenObject(pText,id,AcDb::kForRead)==Acad::eOk)
	{
		ret.x=pText->position().x;
		ret.y=pText->position().y;
		ret.z=pText->position().z;
		ret.id=id;
		ret.text=WS2S(TString(pText->textString()));
		pText->close();
	}
	return ret;
}
/*
 *函数功能：根据id列得到对象列
 *创建日期：2012-11-12
 *更新日期：2012-11-12
*/
vector<CDText> CArxHelper::GetEntityByObjectId(vector<AcDbObjectId> ids)
{
	vector<CDText> ret;
	for(int i=0;i<ids.size();i++)
	{
		ret.push_back(GetEntityByObjectId(ids[i]));
	}
	return ret;
}
/*
 *函数功能：绘制文本对象到当前dwg
 *创建日期：2012-11-12
 *更新日期：2012-11-12
*/
AcDbObjectId CArxHelper::Draw(CDText entity)
{
	AcDbObjectId ret;
	//打开当前数据库中的符号表BlockTable
	AcDbBlockTable *pbt;
	acdbHostApplicationServices()->workingDatabase()->getSymbolTable(pbt,AcDb::kForWrite);
	//打开BlockTable记录
	AcDbBlockTableRecord *pbtr;
	pbt->getAt(ACDB_MODEL_SPACE,pbtr,AcDb::kForWrite);
	AcGePoint3d pt(entity.x,entity.y,entity.z);
	AcDbText *pText=new AcDbText(pt,S2WS(entity.text).c_str());
	pbtr->appendAcDbEntity(ret,pText);
	pText->close();
	//关闭块表
	pbtr->close();
	pbt->close();
	return ret;
}
/*
 *函数功能：绘制文本对象列到当前dwg
 *创建日期：2012-11-12
 *更新日期：2012-11-12
*/
vector<AcDbObjectId> CArxHelper::Draw(vector<CDText> entities)
{
	vector<AcDbObjectId> ret;
	for(int i=0;i<entities.size();i++)
	{
		ret.push_back(Draw(entities[i]));
	}
	return ret;
}
/*
 *函数功能：拾取点
 *创建日期：2012-11-12
 *更新日期：2012-11-13
*/
bool CArxHelper::PickPoint(AcGePoint3d& pt,string msg)
{
	return acedGetPoint(NULL,S2WS(msg).c_str(),asDblArray(pt))==RTNORM?true:false;
}
/*
 *函数功能：交互式获取文本对象的id
 *创建日期：2012-11-12
 *更新日期：2012-11-12
*/
vector<AcDbObjectId> CArxHelper::SelectAcDbObjects(struct resbuf* eb)
{
	vector<AcDbObjectId> ret;
	ads_name ssname;
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
/*
 *函数功能：格式化
 *创建日期：2012-11-12
 *更新日期：2012-11-12
*/
void CArxHelper::Format(AcDbObjectId source,AcDbObjectId dest)
{
	AcDbText* pSource,*pDest;
	//通过id打开对象并获得对象指针
	if(acdbOpenObject(pSource,source,AcDb::kForRead)==Acad::eOk && 
		acdbOpenObject(pDest,dest,AcDb::kForWrite)==Acad::eOk)
	{
		pDest->setHeight(pSource->height());
		pDest->setTextStyle(pSource->textStyle());
	}
	pSource->close();
	pDest->close();
}
/*
 *函数功能：格式化
 *创建日期：2012-11-12
 *更新日期：2012-11-12
*/
void CArxHelper::Format(vector<AcDbObjectId> source,vector<AcDbObjectId> dest)
{
	for(int i=0;i<source.size();i++)Format(source[i],dest[i]);
}
/*
 *函数功能：在cad命令行输入提示信息
 *创建日期：2012-11-12
 *更新日期：2012-11-12
*/
void CArxHelper::ShowMessage(string msg,string name)
{
	if(!msg.empty()&&!name.empty())
	{
		msg.replace(msg.find("%s"),2,name);
		acedPrompt(S2WS(msg).c_str());
	}
}
/*
 *函数功能：在cad命令行输入提示信息
 *创建日期：2012-11-12
 *更新日期：2012-11-12
*/
void CArxHelper::ShowMessage(string msg)
{
	if(!msg.empty())
		acedPrompt(S2WS(msg).c_str());
}
/*
 *函数功能：ucs到wcs的转换
 *创建日期：2012-11-13
 *更新日期：2012-11-13
*/
AcGePoint3d CArxHelper::ucs2wcs(const AcGePoint3d& ucsPt)
{
	AcGePoint3d ret;
	struct resbuf rbFrom, rbTo;
	rbFrom.restype = RTSHORT;
	rbFrom.resval.rint = 1; // from UCS
	rbTo.restype = RTSHORT;
	rbTo.resval.rint = 0; // to WCS
	acedTrans(asDblArray(ucsPt), &rbFrom, &rbTo,
		Adesk::kFalse, asDblArray(ret));//Adesk::kFalse表示是点还是向量
	return ret;
}
/*
 *函数功能：wcs到ucs的转换
 *创建日期：2012-11-13
 *更新日期：2012-11-13
*/
AcGePoint3d CArxHelper::wcs2ucs(const AcGePoint3d& wcsPt)
{
	AcGePoint3d ret;
	struct resbuf rbFrom, rbTo;
	rbFrom.restype = RTSHORT;
	rbFrom.resval.rint =0; // from WCS
	rbTo.restype = RTSHORT;
	rbTo.resval.rint = 1; // to UCS
	acedTrans(asDblArray(wcsPt), &rbFrom, &rbTo,
		Adesk::kFalse, asDblArray(ret));//Adesk::kFalse表示是点还是向量
	return ret;
}
/*
 *函数功能：设置单行文本的内容
 *创建日期：2013-03-22
 *更新日期：2013-03-22
*/
void CArxHelper::SetDTextContent(AcDbObjectId id,string content)
{
	AcDbText* pText;
	//通过id打开对象并获得对象指针
	if(acdbOpenObject(pText,id,AcDb::kForWrite)==Acad::eOk)
	{
		pText->setTextString(S2WS(content).c_str());
		pText->close();
	}
}
vector<double> CArxHelper::GetDouble(string msg,int num)
{
	vector<double> ret;
	ads_real value;
	for(int i=0;i<num;i++)
	{
		if(RTNORM==acedGetReal(S2WS(msg).c_str(),&value))
		{
			ret.push_back(value);
		}
	}
	return ret;
}
bool CArxHelper::SetBlockPr(AcDbObjectId id,string tag,string text)
{
	AcDbObjectIterator* pAttrIter = NULL;
	AcDbEntity* pAEnt = NULL;
	AcDbEntity* pEnt = NULL;
	acdbOpenAcDbEntity(pEnt,id,AcDb::kForRead);
	AcDbBlockReference* pBlkRef = AcDbBlockReference::cast(pEnt);
	//块属性
	pAttrIter = pBlkRef->attributeIterator();

	if (pAttrIter != NULL)
	{
		for (pAttrIter->start();!pAttrIter->done();pAttrIter->step())
		{
			if (Acad::eOk == acdbOpenAcDbEntity(pAEnt,pAttrIter->objectId(),AcDb::kForRead))
			{
				AcDbAttribute* pAttrib = AcDbAttribute::cast(pAEnt);
				if (pAttrib != NULL )
				{
					StringT str=TString(pAttrib->tag());
					if(str==S2WS(tag))
					{
						pAttrib->upgradeOpen();
						pAttrib->setTextString(S2WS(text).c_str());
						pAttrib->downgradeOpen();
					}
				}
				pAEnt->close();
			}
		}
		delete pAttrIter;
	}
	pEnt->close();
	return true;
}