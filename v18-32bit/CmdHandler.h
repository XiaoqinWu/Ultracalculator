/*======================================================================
//        filename :CmdHandler.h
//        description :命令处理器，目的是将逻辑与界面分开
//        created by 吴晓勤   2013-03-26
//        updated by 吴晓勤   2013-03-26	
//======================================================================*/
#ifndef _EXPRESSIONCMDHANDLER_H_H
#define _EXPRESSIONCMDHANDLER_H_H
#include "Express.h"
#include "CArxHelper.h"
#include <map>
#include <vector>

class CmdHandler
{
private:
	enum {MAX=255,MAXSELECT=1000,MAXEXPRESSLENGTH=1024} ;
	string toString(double);
	string toString(variant);
	void DTextSort(vector<CDText>&);
	int GetOutMode();
	int GetSortMode();
	map<string,void(*)()> m_mapfunc;
	void initialize();
public:
	CmdHandler();
	void run(string);
	void parse(string);
};
#endif