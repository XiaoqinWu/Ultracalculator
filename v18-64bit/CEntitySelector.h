#pragma once
#include <vector>
#include "CEntity.h"
using namespace std;
class CEntitySelector
{
public :
	static vector<CDText> GetDText();
	static vector<CLine> GetLine();
	static vector<CDot> GetDot();
	static vector<CBlock> GetBlock();
	static vector<AcDbObjectId> SelectAcDbObjects(struct resbuf*);
	//static vector<CDText> SelectDTextEntity(string msg="");
	//static vector<CDText> SelectLineEntity(string msg="");
	static resbuf GetFilter(AcRxClass*);
	static bool PickPoint(AcGePoint3d&,string);
};

