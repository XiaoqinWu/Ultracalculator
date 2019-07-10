/********************************************************************
		filename :D:\MyAppProject\懒人计算器\代码\source\DocData.h
    	description :特定于文档的数据存储类
		created	by 吴晓勤 2013/3/30 19:20
    	updated	by 吴晓勤 2013/3/30 19:20
*********************************************************************/
#pragma once
# include <vector>
# include <string>
using namespace std;
//-----------------------------------------------------------------------------
//----- Here you can store the document / database related data.
class CDocData {
public:
	enum{XX=0,YY=1,XY=2};//排序模式
	enum{NEW=0,MODIFY=1,AUTO=2};//输出模式
private:
	int m_nTextOutMode;//文字输出模式，0-新建，1-修改，2-修改自己
	int m_nTextSortMode;//文字排序模式，0-X坐标，1-Y坐标，2-自动判断
	int m_nTextScale;//小数位数
	int m_nIsExpand;//是否展开，0-不展开，非0-展开
	double m_fTextHeight;//文字高度
	vector<string> m_lstExpression;//表达式记录
public:
	CDocData () ;
	CDocData (const CDocData &data) ;
	~CDocData () ;
	void SaveExpression(string);
	string GetLastExpression();
	int GetOutMode();
	int GetSortMode();
	int GetScale();
	string GetTextHeightStr();
	double GetTextHeight();
	void SetOutMode(int);
	void SetSortMode(int);
	void SetScale(int);
	void SetTextHeight(string);
	void SetTextHeight(double);
} ;
