/*
 *函数功能：自定义单行文本集合对象
 *创建日期：2013-03-25
 *更新日期：2013-03-25
*/
#pragma once
#include <string>
#include <vector>
using namespace std;
class CMultDText : public AcDbEntity
{
public:
	CMultDText(const vector<string>&,const AcGeVector3d offset);//直接给一个偏移向量
	CMultDText(const vector<string>&,const vector<AcDbObjectId>&);//给定一个模板
	~CMultDText();
#if _MSC_VER>1400
	virtual Adesk::Boolean CMultDText::subWorldDraw (AcGiWorldDraw*);
#else
	virtual Adesk::Boolean worldDraw (AcGiWorldDraw*);
#endif
	void setBasePoint(AcGePoint3d);
	void appendToCurrentSpace();
	void clear();
private:
	vector<AcDbText*> m_vecText;
	vector<AcGeVector3d> m_vecOffset;
	AcGePoint3d m_basePoint;
};