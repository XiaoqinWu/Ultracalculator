#pragma once
#include <string>
using namespace std;
/*
 *类型功能：基类
 *创建日期：2013-06-04
 *更新日期：2013-06-04
*/
class CSelectedEntity
{
public:
	AcDbObjectId id;
	double x;
	double y;
	double z;
public:
	virtual bool Update()=0;
	virtual bool GetEntity(AcDbObjectId)=0;
};
/*
 *类型功能：从模型中选择的文本对象，可以是、直线、小圆点、多义线
 *创建日期：2013-06-04
 *更新日期：2013-06-04
*/
class CDText:public CSelectedEntity
{
public:
	CDText();
	CDText(AcDbObjectId,string);
	string text;
	virtual bool Update();
	virtual bool GetEntity(AcDbObjectId);
};
/*
 *类型功能：从模型中选择的直线对象
 *创建日期：2013-06-04
 *更新日期：2013-06-04
*/
class CLine:public CSelectedEntity
{
public:
	double x1;
	double y1;
	double z1;
	double x2;
	double y2;
	double z2;
	virtual bool Update();
	virtual bool GetEntity(AcDbObjectId);
	double GetLength();
};
/*
 *类型功能：从模型中选择的小圆点对象
 *创建日期：2013-06-04
 *更新日期：2013-06-04
*/
class CDot:public CSelectedEntity
{
public:
	double radius;
	double width;
	virtual bool Update();
	virtual bool GetEntity(AcDbObjectId);
};
/*
 *类型功能：从模型中选择的块对象
 *创建日期：2013-06-04
 *更新日期：2013-06-04
*/
class CBlock:public CSelectedEntity
{
public:
	virtual bool Update();
	virtual bool GetEntity(AcDbObjectId);
};