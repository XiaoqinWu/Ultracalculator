#pragma once
#include <string>
#include <vector>
#include "CMultDText.h"
#include "CEntity.h"
using namespace std;
/*
 *类型功能：arx帮助类
 *创建日期：2012-11-11
 *更新日期：2012-11-13
*/
class CArxHelper
{
public:
	static CDText GetEntityByObjectId(AcDbObjectId);
	static vector<CDText> GetEntityByObjectId(vector<AcDbObjectId>);
	static AcDbObjectId Draw(CDText);
	static vector<AcDbObjectId> Draw(vector<CDText>);
	static vector<AcDbObjectId> SelectAcDbObjects(struct resbuf*);
	static vector<double> GetDouble(string,int);
	//static vector<CDText> SelectDTextEntity(string msg="\n请选择文本");
	//static vector<CDText> SelectLineEntity(string msg="\n请选择直线");
	//static resbuf GetFilter(AcRxClass*);
	static void ShowMessage(string,string);
	static void ShowMessage(string);
	static bool PickPoint(AcGePoint3d&,string);
	static void Format(AcDbObjectId,AcDbObjectId);
	static void Format(vector<AcDbObjectId>,vector<AcDbObjectId>);
	static AcGePoint3d wcs2ucs(const AcGePoint3d&);
	static AcGePoint3d ucs2wcs(const AcGePoint3d&);
	static void SetDTextContent(AcDbObjectId id,string content);
	static double SumDText(vector<CDText>);
	static double MultDText(vector<CDText>);
	static double MeanDText(vector<CDText>);
	static double MaxDText(vector<CDText>);
	static double MinDText(vector<CDText>);
	static bool CArxHelper::SetBlockPr(AcDbObjectId id,string tag,string text);
};
/*
 *类型功能：jig类
 *创建日期：2012-11-13
 *更新日期：2012-11-13
*/
class CTextValueJig:public AcEdJig
{
public:
	CTextValueJig(const vector<AcDbObjectId>&,const vector<string>&);
	CTextValueJig();
	void doIt(string);
	void doIt(const vector<AcDbObjectId>&,const vector<string>&);
	void doIt(AcGeVector3d,const vector<string>&);
	virtual DragStatus sampler();
	virtual Adesk::Boolean update();
	virtual AcDbEntity* entity() const;
private:
	AcGePoint3d m_basepoint;//用于记录选择集中第一个文本的坐标，没有选择集则设为原点。
	AcGePoint3d m_endpoint;//表示鼠标拖动时点的实时位置。
	AcGePoint3d m_startpoint;//拖动前选择的起点。
	CMultDText* m_pEntity;//产生的实体。
};