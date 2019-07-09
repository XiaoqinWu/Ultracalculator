#include "StdAfx.h"
#include "CEntity.h"
#include "stringhelper.h"
#include "CArxHelper.h"
CDText::CDText()
{
}
CDText::CDText(AcDbObjectId id,string text)
{
	this->id=id;
	this->text=text;
}
bool CDText::Update()
{
	if(id.isValid())
	{
		AcDbText* pText;
		if(acdbOpenObject(pText,id,AcDb::kForWrite)==Acad::eOk)
		{
			pText->setTextString(S2WS(text).c_str());
			if(pText->horizontalMode()==AcDb::kTextLeft)
				pText->setPosition(AcGePoint3d(x,y,z));
			else pText->setAlignmentPoint(AcGePoint3d(x,y,z));
			pText->close();
			return true;
		}
	}
	return false;
}
bool CDText::GetEntity(AcDbObjectId id)
{
	if(id.isValid())
	{
		AcDbText* pText;
		if(acdbOpenObject(pText,id,AcDb::kForRead)==Acad::eOk)
		{
			text=WS2S(TString(pText->textString()));
			if(pText->horizontalMode()==AcDb::kTextLeft)
			{
				x=pText->position().x;
				y=pText->position().y;
				z=pText->position().z;
			}
			else
			{
				x=pText->alignmentPoint().x;
				y=pText->alignmentPoint().y;
				z=pText->alignmentPoint().z;
			}
			this->id=id;
			pText->close();
			return true;
		}
	}
	return false;
}
double CLine::GetLength()
{
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
}
bool CLine::Update()
{
	if(id.isValid())
	{
		AcDbLine* pLine;
		if(acdbOpenObject(pLine,id,AcDb::kForWrite)==Acad::eOk)
		{
			pLine->setStartPoint(AcGePoint3d(x1,y1,z1));
			pLine->setEndPoint(AcGePoint3d(x2,y2,z2));
			x=(x1+x2)/2;
			y=(y1+y2)/2;
			z=(z1+z2)/2;
			pLine->close();
			return true;
		}
	}
	return false;
}
bool CLine::GetEntity(AcDbObjectId id)
{
	if(id.isValid())
	{
		AcDbLine* pLine;
		if(acdbOpenObject(pLine,id,AcDb::kForRead)==Acad::eOk)
		{
			x1=pLine->startPoint().x;
			y1=pLine->startPoint().y;
			z1=pLine->startPoint().z;
			x2=pLine->endPoint().x;
			y2=pLine->endPoint().y;
			z2=pLine->endPoint().z;
			x=(x1+x2)/2;
			y=(y1+y2)/2;
			z=(z1+z2)/2;
			this->id=id;
			pLine->close();
			return true;
		}
	}
	return false;
}
bool CDot::GetEntity(AcDbObjectId id)
{
	if(id.isValid())
	{
		AcDbPolyline* pLine;
		if(acdbOpenObject(pLine,id,AcDb::kForRead)==Acad::eOk)
		{
			if(pLine->numVerts()==2&&pLine->isClosed()&&pLine->hasBulges())
			{
				AcGeCircArc3d arc;
				pLine->getArcSegAt(0,arc);
				x=arc.center().x;
				y=arc.center().y;
				z=arc.center().z;
				double startWidth,endWidth;
				radius=arc.radius();
				pLine->getWidthsAt(0,startWidth,endWidth);
				width=startWidth;
				this->id=id;
				pLine->close();
				return true;
			}
		}
	}
	return false;
}
bool CDot::Update()
{
	if(id.isValid())
	{
		AcDbPolyline* pLine;
		if(acdbOpenObject(pLine,id,AcDb::kForWrite)==Acad::eOk)
		{
			pLine->reset(false,0);
			AcGePoint2d startPoint(x-radius,y);
			AcGePoint2d endPoint(x+radius,y);
			pLine->addVertexAt(0,startPoint,1,width,width);
			pLine->addVertexAt(1,endPoint,1,width,width);
			pLine->setClosed(true);
			pLine->close();
			return true;
		}
	}
	return false;
}
bool CBlock::GetEntity(AcDbObjectId id)
{
	if(id.isValid())
	{
		AcDbBlockReference* pBlock;
		if(acdbOpenObject(pBlock,id,AcDb::kForRead)==Acad::eOk)
		{
			this->id=id;
			x=pBlock->position().x;
			y=pBlock->position().y;
			z=pBlock->position().z;
			pBlock->close();
			return true;
		}
	}
	return false;
}
bool CBlock::Update()
{
	if(id.isValid())
	{
		AcDbBlockReference* pBlock;
		if(acdbOpenObject(pBlock,id,AcDb::kForWrite)==Acad::eOk)
		{
			pBlock->setPosition(AcGePoint3d(x,y,z));
			pBlock->close();
			return true;
		}
	}
	return false;
}