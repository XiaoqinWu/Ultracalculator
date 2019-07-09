/*======================================================================
//        filename :Command.h
//        description :命令处理器，目的是将逻辑与界面分开
//        created by 吴晓勤   2013-03-26
//        updated by 吴晓勤   2013-03-26	
//======================================================================*/
#ifndef _EXPRESSIONCOMMAND_H_H
#define _EXPRESSIONCOMMAND_H_H
#include <string>
#include "Express.h"
#include "CArxHelper.h"
class CmdHelper
{
public:
	static string toString(double);
	static string toString(variant);
	static double toDouble(const string& str);
	static void DTextOut(string);
	static void DTextOut(vector<string>);
	static bool EntitySort(vector<CLine>& vec);
	static bool EntitySort(vector<CDText>& vec);
	static bool EntitySort(vector<CDot>& vec);
	static bool EntitySort(vector<CBlock>& vec);
	//命令映射
	static void Initialize(map<string,void(*)()>& mapfunc)
	{
		mapfunc.insert(pair<string,void(*)()>("sum",BAT_UC_Sum));
		mapfunc.insert(pair<string,void(*)()>("ssum",BAT_UC_SSum));
		mapfunc.insert(pair<string,void(*)()>("stb",BAT_UC_STable));
		mapfunc.insert(pair<string,void(*)()>("sdot",BAT_UC_SDot));
		mapfunc.insert(pair<string,void(*)()>("sdos",BAT_UC_SDotSize));
		mapfunc.insert(pair<string,void(*)()>("gll",BAT_UC_GetLineLen));
		mapfunc.insert(pair<string,void(*)()>("spl",BAT_UC_Split));
		mapfunc.insert(pair<string,void(*)()>("splt",BAT_UC_SplitText));
		mapfunc.insert(pair<string,void(*)()>("spld",BAT_UC_SplitDot));
		mapfunc.insert(pair<string,void(*)()>("splb",BAT_UC_SplitBlock));
		//mapfunc.insert(pair<string,void(*)()>("hpb",BAT_UC_HRB2HPB));
		//mapfunc.insert(pair<string,void(*)()>("hrb",BAT_UC_HPB2HRB));
		mapfunc.insert(pair<string,void(*)()>("al",BAT_UC_AligLeft));
		mapfunc.insert(pair<string,void(*)()>("dc",BAT_UC_DoubleChange));
		mapfunc.insert(pair<string,void(*)()>("gn",BAT_UC_GetNumber));
		mapfunc.insert(pair<string,void(*)()>("ssl",BAT_UC_SumSteelBar));
	};
	static void BAT_UC_Sum();
	static void BAT_UC_SSum();
	static void BAT_UC_STable();
	static void BAT_UC_SDot();
	static void BAT_UC_SDotSize();
	static void BAT_UC_GetLineLen();
	//2013-06-08 15:38
	static void BAT_UC_SplitText();
	static void BAT_UC_SplitDot();
	static void BAT_UC_SplitBlock();
	static void BAT_UC_HRB2HPB();
	static void BAT_UC_HPB2HRB();
	static void BAT_UC_AligLeft();
	//2013-07-01 17:00
	static void BAT_UC_Split();
	static void BAT_UC_DoubleChange();
	static void BAT_UC_GetNumber();
	static void BAT_UC_SumSteelBar();
private:
	static bool sort_x(const CSelectedEntity & m1, const CSelectedEntity & m2) {return m1.x < m2.x;}
	static bool sort_y(const CSelectedEntity & m1, const CSelectedEntity & m2) {return m1.y > m2.y;}
	static bool sort_z(const CSelectedEntity & m1, const CSelectedEntity & m2) {return m1.z < m2.z;}
	enum {MAX=255,MAXSELECT=1000,MAXEXPRESSLENGTH=1024} ;
	static int GetOutMode();
	static int GetSortMode();
};
ACED_ARXCOMMAND_ENTRY_AUTO(CmdHelper, BAT_UC, _GetLineLen, bat_getlinelen, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CmdHelper, BAT_UC, _SplitText, bat_SplitText, ACRX_CMD_TRANSPARENT, NULL)
//ACED_ARXCOMMAND_ENTRY_AUTO(CmdHelper, BAT_UC, _HRB2HPB, bat_HRB2HPB, ACRX_CMD_TRANSPARENT, NULL)
//ACED_ARXCOMMAND_ENTRY_AUTO(CmdHelper, BAT_UC, _HPB2HRB, bat_HPB2HRB, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CmdHelper, BAT_UC, _AligLeft, bat_AligLeft, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CmdHelper, BAT_UC, _Split, bat_Split, ACRX_CMD_TRANSPARENT, NULL)
#endif