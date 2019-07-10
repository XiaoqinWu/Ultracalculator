/********************************************************************
		filename :G:\懒人计算器\source\BAT_UC.cpp
    	description :各种快捷命令的实现
		created	by 吴晓勤 2013/03/27 11:10
    	updated	by 吴晓勤 2013/4/9 23:28
*********************************************************************/
#include "StdAfx.h"
#include "CmdHelper.h"
#include "Except.h"
#include "CArxHelper.h"
#include "stringhelper.h"
#include "CEntitySelector.h"
#include <algorithm>
#include "function.h"
/*
 *函数功能：得到当前文档的输出模式。
 *创建日期：2013/03/27 9:58
 *更新日期：2013/03/27 9:58
*/
int CmdHelper::GetOutMode()
{
	return DocVars.docData().GetOutMode();
}
/*
 *函数功能：得到当前文档的排序模式。
 *创建日期：2013/03/27 9:59
 *更新日期：2013/03/27 9:59
*/
int CmdHelper::GetSortMode()
{
	return DocVars.docData().GetSortMode();
}
/*
 *函数功能：根据小数位数将double转为string。
 *创建日期：2013/03/27 9:59
 *更新日期：2013/03/27 9:59
*/
string CmdHelper::toString(double value)
{
	if(value>1e100)return "Error";
	char num[20];
	sprintf(num,"%%.%dlf",DocVars.docData().GetScale());
	char str[MAX];
	sprintf(str,num,value+0.0000000000005);
	return string(str);
}
/*
 *函数功能：字符串转化为实数
 *创建日期：2013/3/30 21:25
 *更新日期：2013/3/30 21:25
*/
double CmdHelper::toDouble(const string& str)
{
	return func::toDouble(str);
}
/*
 *函数功能：根据小数位数将variant转为string。
 *创建日期：2013/03/27 10:00
 *更新日期：2013/03/27 10:00
*/
string CmdHelper::toString(variant value)
{
	//如果计算结果是字符串
	if(value.isString())
	{
		return ((string)value);
	}
	//如果计算结果是数值
	else
	{
		return toString((double)value);
	}
}
bool CmdHelper::EntitySort(vector<CLine>& vec)
{
	if(vec.size()<=0)return false;
	bool sortX=true;
	switch(GetSortMode())
	{
		//按X坐标排序
	case 0:
		sort(vec.begin(),vec.end(),sort_x);
		break;
		//按Y坐标排序
	case 1:
		sort(vec.begin(),vec.end(),sort_y);
		sortX=false;
		break;
		//自动判断排序
	case 2:
		sort(vec.begin(),vec.end(),sort_x);
		double lx=vec.front().x-vec.back().x;
		sort(vec.begin(),vec.end(),sort_y);
		sortX=false;
		double ly=vec.front().y-vec.back().y;
		if(abs(lx)>abs(ly))
		{
			sort(vec.begin(),vec.end(),sort_x);
			sortX=true;
		}
		break;
	}
	return sortX;
}
bool CmdHelper::EntitySort(vector<CDText>& vec)
{
	if(vec.size()<=0)return false;
	bool sortX=true;
	switch(GetSortMode())
	{
		//按X坐标排序
	case 0:
		sort(vec.begin(),vec.end(),sort_x);
		break;
		//按Y坐标排序
	case 1:
		sort(vec.begin(),vec.end(),sort_y);
		sortX=false;
		break;
		//自动判断排序
	case 2:
		sort(vec.begin(),vec.end(),sort_x);
		double lx=vec.front().x-vec.back().x;
		sort(vec.begin(),vec.end(),sort_y);
		sortX=false;
		double ly=vec.front().y-vec.back().y;
		if(abs(lx)>abs(ly))
		{
			sort(vec.begin(),vec.end(),sort_x);
			sortX=true;
		}
		break;
	}
	return sortX;
}
bool CmdHelper::EntitySort(vector<CDot>& vec)
{
	if(vec.size()<=0)return false;
	bool sortX=true;
	switch(GetSortMode())
	{
		//按X坐标排序
	case 0:
		sort(vec.begin(),vec.end(),sort_x);
		break;
		//按Y坐标排序
	case 1:
		sort(vec.begin(),vec.end(),sort_y);
		sortX=false;
		break;
		//自动判断排序
	case 2:
		sort(vec.begin(),vec.end(),sort_x);
		double lx=vec.front().x-vec.back().x;
		sort(vec.begin(),vec.end(),sort_y);
		sortX=false;
		double ly=vec.front().y-vec.back().y;
		if(abs(lx)>abs(ly))
		{
			sort(vec.begin(),vec.end(),sort_x);
			sortX=true;
		}
		break;
	}
	return sortX;
}
bool CmdHelper::EntitySort(vector<CBlock>& vec)
{
	if(vec.size()<=0)return false;
	bool sortX=true;
	switch(GetSortMode())
	{
		//按X坐标排序
	case 0:
		sort(vec.begin(),vec.end(),sort_x);
		break;
		//按Y坐标排序
	case 1:
		sort(vec.begin(),vec.end(),sort_y);
		sortX=false;
		break;
		//自动判断排序
	case 2:
		sort(vec.begin(),vec.end(),sort_x);
		double lx=vec.front().x-vec.back().x;
		sort(vec.begin(),vec.end(),sort_y);
		sortX=false;
		double ly=vec.front().y-vec.back().y;
		if(abs(lx)>abs(ly))
		{
			sort(vec.begin(),vec.end(),sort_x);
			sortX=true;
		}
		break;
	}
	return sortX;
}
/*
 *函数功能：输出文本
 *创建日期：2013/4/9 23:48
 *更新日期：2013/4/9 23:48
*/
void CmdHelper::DTextOut(string express)
{
	//输出模式为新建
	if(GetOutMode()==CDocData::NEW)
	{
		CTextValueJig* jig=new CTextValueJig();
		jig->doIt(express);
		delete jig;
	}
	//输出模式为修改或自动
	else
	{
		CArxHelper::ShowMessage("选择要修改的文本集合:");
		vector<CDText> selected=CEntitySelector::GetDText();
		EntitySort(selected);
		for (int i=0;i<selected.size();i++)
		{
			//CArxHelper::SetDTextContent(selected[i].id,express);
			selected[i].text=express;
			selected[i].Update();
		}
	}
}
/*
	*函数功能：求和命令
	*创建日期：2013-03-22
	*更新日期：2013-03-22
*/
void CmdHelper::BAT_UC_Sum()
{
	CArxHelper::ShowMessage("\n已启用求和命令。请选择一组文本:");
	vector<CDText> vecDText=CEntitySelector::GetDText();
	if(vecDText.size()>0)
	{
		double ret=0;
		for(int i=0;i<vecDText.size();i++)
		{
			double result=0;
			try
			{
				result=toDouble(vecDText[i].text);
				ret+=result;
			}
			catch(ExpressionExcept& error)
			{
				CArxHelper::ShowMessage(vecDText[i].text+error.what());
			}
		}
		DTextOut(toString(ret));
	}
}
/*
	*函数功能：分类求和命令
	*创建日期：2013-03-22
	*更新日期：2013-03-22
*/
void CmdHelper::BAT_UC_SSum()
{
	CArxHelper::ShowMessage("\n已启用分类求和命令。请选择索引组：");
	vector<CDText> vecIndex=CEntitySelector::GetDText();
	if(vecIndex.size()==0)
	{
		CArxHelper::ShowMessage("索引组不能为空。");
		return;
	}
	EntitySort(vecIndex);
	CArxHelper::ShowMessage("选择数据组：\n");
	vector<CDText> vecValue=CEntitySelector::GetDText();
	if(vecValue.size()!=vecIndex.size())
	{
		CArxHelper::ShowMessage("索引与数据个数不匹配。");
		return;
	}
	EntitySort(vecValue);
	//分类求和
	map<string,double> summap;
	for (int i=0;i<vecIndex.size();i++)
	{
		if(summap.find(vecIndex[i].text)!=summap.end())continue;
		double sum=0;
		for (int j=i;j<vecIndex.size();j++)
		{
			if(vecIndex[i].text==vecIndex[j].text)
			{
				try
				{
					sum+=toDouble(StringHelper::parseDouble(vecValue[j].text));
				}
				catch(ExpressionExcept error)
				{
					CArxHelper::ShowMessage(error.what());
				}
			}
		}
		summap.insert(pair<string,double>(vecIndex[i].text,sum));
	}
	vector<AcDbObjectId> vecIds;
	//输出
	vector<string> vecvalue;
	map<string,double>::iterator iter;
	for(iter=summap.begin();iter!=summap.end();++iter)
	{
		vecvalue.insert(vecvalue.begin(),1,iter->first+":"+toString(iter->second));
		//找到索引对应的objectid
		for (int i=0;i<vecIndex.size();i++)
		{
			if(vecIndex[i].text==iter->first)
			{
				vecIds.push_back(vecValue[i].id);
				break;
			}
		}
	}
	vector<string> vecsteelvalue[4];
	for(int i=0;i<vecvalue.size();i++)
	{
		if(vecvalue[i][0]=='$')
		{
			vecsteelvalue[0].push_back(vecvalue[i]);
		}
		else if(vecvalue[i][0]=='&')
		{
			vecsteelvalue[1].push_back(vecvalue[i]);
		}
		else if(vecvalue[i][0]=='^')
		{
			vecsteelvalue[2].push_back(vecvalue[i]);
		}
		else
		{
			vecsteelvalue[3].push_back(vecvalue[i]);
		}
	}
	vecvalue.clear();
	for (int i=0;i<4;i++)
	{
		for (int j=0;j<vecsteelvalue[i].size();j++)
		{
			vecvalue.push_back(vecsteelvalue[i][j]);
		}
	}
	if(GetOutMode()==CDocData::NEW)
	{
		CTextValueJig* jig=new CTextValueJig();
		jig->doIt(vecIds,vecvalue);
		delete jig;
	}
	else
	{
		CArxHelper::ShowMessage("选择要修改的文本集合:");
		vector<CDText> selected=CEntitySelector::GetDText();
		EntitySort(selected);
		//选择的文本刚好匹配
		if(selected.size()==vecvalue.size())
		{
			for (int i=0;i<selected.size();i++)
			{
				selected[i].text=vecvalue[i];
				selected[i].Update();
			}
		}
		//选择的文本刚好是2倍
		else if(selected.size()==2*vecvalue.size())
		{
			for (int i=0;i<vecvalue.size();i++)
			{
				vector<string> vecstr=StringHelper::split(vecvalue[i],':');
				selected[2*i].text=vecstr[0]+":";
				selected[2*i].Update();
				selected[2*i+1].text=vecstr[1];
				selected[2*i+1].Update();
			}
		}
		else
		{
			CArxHelper::ShowMessage("要修改的文本个数不匹配。");
		}
	}
}
/*
	*函数功能：表格直接连乘
	*创建日期：2013-07-01
	*更新日期：2013-07-01
*/
void CmdHelper::BAT_UC_STable()
{
	try
	{
		ExpressionCalculator calc;
		CArxHelper::ShowMessage("\n已启用数量表算量命令。请选择钢筋直径：");
		vector<CDText> vecRadius=CEntitySelector::GetDText();
		if(vecRadius.size()>0)
		{
			EntitySort(vecRadius);
			CArxHelper::ShowMessage("请选择单根长：");
			vector<CDText> vecLen=CEntitySelector::GetDText();
			if(vecLen.size()==vecRadius.size())
			{
				EntitySort(vecLen);
				CArxHelper::ShowMessage("请选择根数：");
				vector<CDText> vecNum=CEntitySelector::GetDText();
				if(vecNum.size()==vecRadius.size())
				{
					EntitySort(vecNum);
					CArxHelper::ShowMessage("请选择共长：");
					vector<CDText> vecSumLen=CEntitySelector::GetDText();
					if(vecSumLen.size()==vecRadius.size())
					{
						EntitySort(vecSumLen);
						calc.input("a*b/1000");
						DocVars.docData().SetScale(2);
						for(int i=0;i<vecRadius.size();i++)
						{
							calc.setVarValue("a",StringHelper::parseDouble(vecLen[i].text));
							calc.setVarValue("b",StringHelper::parseDouble(vecNum[i].text));

							vecSumLen[i].text=toString(calc.get());
							vecSumLen[i].Update();
						}
					}
					else return;
					//计算共重
					CArxHelper::ShowMessage("请选择共重列：");
					vector<CDText> vecSumWet=CEntitySelector::GetDText();
					if(vecSumWet.size()==vecRadius.size())
					{
						EntitySort(vecSumWet);
						calc.input("kg(r)*a");
						DocVars.docData().SetScale(1);
						for(int i=0;i<vecRadius.size();i++)
						{
							calc.setVarValue("a",StringHelper::parseDouble(vecSumLen[i].text));
							calc.setVarValue("r",StringHelper::parseDouble(vecRadius[i].text));
							vecSumWet[i].text=toString(calc.get());
							vecSumWet[i].Update();
						}
					}
					else return;
					//计算分类求和
					map<string,double> summap;
					for (int i=0;i<vecRadius.size();i++)
					{
						if(summap.find(vecRadius[i].text)!=summap.end())continue;
						double sum=0;
						for (int j=i;j<vecRadius.size();j++)
						{
							if(vecRadius[i].text==vecRadius[j].text)
							{
								sum+=toDouble(StringHelper::parseDouble(vecSumWet[j].text));
							}
						}
						summap.insert(pair<string,double>(vecRadius[i].text,sum));
					}
					
					//计算结果
					CArxHelper::ShowMessage("请选择合计列：");
					vector<CDText> vecSSum=CEntitySelector::GetDText();
					EntitySort(vecSSum);
					DocVars.docData().SetScale(0);
					vector<string> vecvalue;
					if(vecSSum.size()==summap.size())
					{
						map<string,double>::iterator iter;
						for(iter=summap.begin();iter!=summap.end();++iter)
						{
							vecvalue.push_back(iter->first+":"+toString(iter->second));
						}
					}
					else if(vecSSum.size()==2*summap.size())
					{
						map<string,double>::iterator iter;
						for(iter=summap.begin();iter!=summap.end();++iter)
						{
							vecvalue.push_back(iter->first+":");
							vecvalue.push_back(toString(iter->second));
						}
					}
					else return;
					for(int i=0;i<vecSSum.size();i++)
					{
						vecSSum[i].text=vecvalue[i];
						vecSSum[i].Update();
					}
				}
			}
		}
	}
	catch(ExpressionExcept error)
	{
		CArxHelper::ShowMessage(error.what());
	}
}
/*
	*函数功能：设置小数位命令
	*创建日期：2013-03-22
	*更新日期：2013-03-22
*/
void CmdHelper::BAT_UC_SDot()
{
	CArxHelper::ShowMessage("\n已启用设置小数位数命令。请选择一组文本:");
	vector<CDText> vecDText=CEntitySelector::GetDText();
	for (int i=0;i<vecDText.size();i++)
	{
		if(StringHelper::isDouble(vecDText[i].text))
		{
			double value=toDouble(StringHelper::parseDouble(vecDText[i].text));
			string result=toString(value);
			vecDText[i].text=result;
			vecDText[i].Update();
		}
	}
}
/*
	*函数功能：设置小原点的大小
	*创建日期：2013-06-15
	*更新日期：2013-06-15
*/
void CmdHelper::BAT_UC_SDotSize()
{
	CArxHelper::ShowMessage("\n已启用设置钢筋小圆点半径命令。请选择一组小圆点:");
	vector<CDot> vecDText=CEntitySelector::GetDot();
	if(vecDText.size()>0)
	{
		vector<double> vecRadius=CArxHelper::GetDouble("\n请输入小圆点外径：",1);
		if(vecRadius.size()<1)return;
		for (int i=0;i<vecDText.size();i++)
		{
			vecDText[i].radius=vecRadius[0]/4;
			vecDText[i].width=vecRadius[0]/2;
			vecDText[i].Update();
		}
	}
}
/*
	*函数功能：取直线长度
	*创建日期：2013-03-22
	*更新日期：2013-03-22
*/
void CmdHelper::BAT_UC_GetLineLen()
{
	vector<string> vecDText;
	CArxHelper::ShowMessage("\n已启用获取直线长命令。请选择一组直线：");
	vector<CLine> vecLine=CEntitySelector::GetLine();
	if(vecLine.size()>0)
	{
		EntitySort(vecLine);
		for(int i=0;i<vecLine.size();i++)
		{
			vecDText.push_back(toString(vecLine[i].GetLength()*100));
		}
		if(vecDText.size()>0)
		{
			CArxHelper::ShowMessage("\n选择要存储直线长度的文本：");
			vector<CDText> selected=CEntitySelector::GetDText();
			if(vecDText.size()!=vecLine.size())
				CArxHelper::ShowMessage("注意：两者个数不相等。");
			EntitySort(selected);
			for (int i=0;i<selected.size();i++)
			{
				selected[i].text=vecDText[i%vecDText.size()];
				selected[i].Update();
			}
		}
	}
}
/*
	*函数功能：将对象等间距调整
	*创建日期：2013-06-04
	*更新日期：2013-06-04
*/
void CmdHelper::BAT_UC_Split()
{
	CArxHelper::ShowMessage("\n已启用等间距排列直线命令。请选择一组直线：");
	vector<CLine> vec=CEntitySelector::GetLine();
	if(vec.size()<2)return;
	EntitySort(vec);
	double dx=-(vec.front().x-vec.back().x)/(vec.size()-1);
	double dy=-(vec.front().y-vec.back().y)/(vec.size()-1);
	double xc=vec.front().x;
	double yc=vec.front().y;
	for(int i=0;i<vec.size();i++)
	{
		double x0=vec[i].x;
		double y0=vec[i].y;
		vec[i].x1+=dx*i+xc-x0;
		vec[i].x2+=dx*i+xc-x0;
		vec[i].y1+=dy*i+yc-y0;
		vec[i].y2+=dy*i+yc-y0;
		vec[i].Update();
	}
}
/*
	*函数功能：将对象等间距调整
	*创建日期：2013-06-04
	*更新日期：2013-06-04
*/
void CmdHelper::BAT_UC_SplitText()
{
	CArxHelper::ShowMessage("\n已启用等间距排列文本命令。请选择一组文本：");
	vector<CDText> vec=CEntitySelector::GetDText();
	if(vec.size()<2)return;
	EntitySort(vec);
	double dx=-(vec.front().x-vec.back().x)/(vec.size()-1);
	double dy=-(vec.front().y-vec.back().y)/(vec.size()-1);
	double xc=vec.front().x;
	double yc=vec.front().y;
	vector<double> vecOffset=CArxHelper::GetDouble("\n请输入间距<等间距>：",1);
	if(vecOffset.size()>0)dy=-vecOffset[0];
	for(int i=0;i<vec.size();i++)
	{
		double x0=vec[i].x;
		double y0=vec[i].y;
		//vec[i].x+=dx*i+xc-x0;
		vec[i].y+=dy*i+yc-y0;
		vec[i].Update();
	}
}
/*
	*函数功能：将对象等间距调整
	*创建日期：2013-06-04
	*更新日期：2013-06-04
*/
void CmdHelper::BAT_UC_SplitDot()
{
	CArxHelper::ShowMessage("\n已启用等间距排列小圆点命令。请选择一组小圆点：");
	vector<CDot> vec=CEntitySelector::GetDot();
	if(vec.size()<2)return;
	EntitySort(vec);
	double dx=-(vec.front().x-vec.back().x)/(vec.size()-1);
	double dy=-(vec.front().y-vec.back().y)/(vec.size()-1);
	double xc=vec.front().x;
	double yc=vec.front().y;
	for(int i=0;i<vec.size();i++)
	{
		double x0=vec[i].x;
		double y0=vec[i].y;
		vec[i].x+=dx*i+xc-x0;
		vec[i].y+=dy*i+yc-y0;
		vec[i].Update();
	}
}
/*
	*函数功能：将对象等间距调整
	*创建日期：2013-06-04
	*更新日期：2013-06-04
*/
void CmdHelper::BAT_UC_SplitBlock()
{
	CArxHelper::ShowMessage("\n已启用等间距排列块命令。请选择一组块：");
	vector<CBlock> vec=CEntitySelector::GetBlock();
	if(vec.size()<2)return;
	EntitySort(vec);
	double dx=-(vec.front().x-vec.back().x)/(vec.size()-1);
	double dy=-(vec.front().y-vec.back().y)/(vec.size()-1);
	double xc=vec.front().x;
	double yc=vec.front().y;
	for(int i=0;i<vec.size();i++)
	{
		double x0=vec[i].x;
		double y0=vec[i].y;
		vec[i].x+=dx*i+xc-x0;
		vec[i].y+=dy*i+yc-y0;
		vec[i].Update();
	}
}
/*
	*函数功能：取所有直线的长度和
	*创建日期：2013-06-08
	*更新日期：2013-06-08
*/
//void CmdHelper::BAT_UC_HRB2HPB()
//{
//	vector<CDText> vec=CEntitySelector::GetDText();
//	for(int i=0;i<vec.size();i++)
//	{
//		string str=vec[i].text;
//		for(int j=0;j<str.size();j++)
//			if(str[j]=='&')str[j]='^';
//		vec[i].text=str;
//		vec[i].Update();
//	}
//}
//void CmdHelper::BAT_UC_HPB2HRB()
//{
//	vector<CDText> vec=CEntitySelector::GetDText();
//	for(int i=0;i<vec.size();i++)
//	{
//		string str=vec[i].text;
//		for(int j=0;j<str.size();j++)
//			if(str[j]=='^')str[j]='&';
//		vec[i].text=str;
//		vec[i].Update();
//	}
//}
void CmdHelper::BAT_UC_AligLeft()
{
	CArxHelper::ShowMessage("\n已启用文本对齐命令。请选择一组文本：");
	vector<CDText> vec=CEntitySelector::GetDText();
	if(vec.size()<2)return;
	if(EntitySort(vec))
	{
		double yc=vec.front().y;
		for(int i=0;i<vec.size();i++)
		{
			vec[i].y=yc;
			vec[i].Update();
		}
	}
	else
	{
		double xc=vec.front().x;
		for(int i=0;i<vec.size();i++)
		{
			vec[i].x=xc;
			vec[i].Update();
		}
	}
}
void CmdHelper::BAT_UC_DoubleChange()
{
	CArxHelper::ShowMessage("\n已启用交换文本命令。请选择一对文本：");
	vector<CDText> vec=CEntitySelector::GetDText();
	if(vec.size()!=2)return;
	string str=vec[0].text;
	vec[0].text=vec[1].text;
	vec[0].Update();
	vec[1].text=str;
	vec[1].Update();
}
void CmdHelper::BAT_UC_GetNumber()
{
	CArxHelper::ShowMessage("\n已启用提取数字命令。请选择一组文本：");
	vector<CDText> vec=CEntitySelector::GetDText();
	if(vec.size()<1)return;
	for(int i=0;i<vec.size();i++)
	{
		string str;
		string s=vec[i].text;
		for (int j=0;j<s.length();j++)
		{
			char ch=s[j];
			if(ch>='0'&&ch<='9')
			{
				str.push_back(ch);
			}
			else if (ch=='.'||ch=='+'||ch=='-')
			{
				str.push_back(ch);
			}
			else if(j<s.length()-1&&(ch=='='||ch==':'))
			{
				str.clear();
			}
		}
		vec[i].text=str;
		vec[i].Update();
	}
}
/*
	*函数功能：钢筋求和命令
	*创建日期：2013-10-16
	*更新日期：2013-10-16
*/
void CmdHelper::BAT_UC_SumSteelBar()
{
	CArxHelper::ShowMessage("\n已启用钢筋求和命令。请选择一组文本或属性快:");
	vector<CDText> vecDText=CEntitySelector::GetDText();
	if(vecDText.size()>0)
	{
		int scale=1;
		bool isMean=false;
		double ret=0;
		for(int i=0;i<vecDText.size();i++)
		{
			double result=0;
			try
			{
				ExpressionCalculator calc;
				if(vecDText[i].text.find("/2")==vecDText[i].text.size()-2)scale=2;
				int pos=vecDText[i].text.find("~");
				if(pos<0)pos=vecDText[i].text.find("～");
				if(pos>-1)
				{
					vecDText[i].text[pos]='+';
					calc.input(vecDText[i].text);
					result=(double)calc.get()/2;
					isMean=true;
				}
				else
				{
					calc.input(vecDText[i].text);
					result=calc.get();
				}
				ret+=result;
			}
			catch(ExpressionExcept& error)
			{
				CArxHelper::ShowMessage(vecDText[i].text+error.what());
				return;
			}
		}
		string valuetext=(isMean?"均":"")+toString(ret*scale);
		//输出模式为新建
		if(GetOutMode()==CDocData::NEW)
		{
			CTextValueJig* jig=new CTextValueJig();
			jig->doIt(valuetext);
			delete jig;
		}
		//输出模式为修改或自动
		else
		{
			CArxHelper::ShowMessage("选择要修改的属性块或文本:");
			static resbuf eb=*acutBuildList(-4,_T("<or"),RTDXF0,_T("TEXT"),RTDXF0,_T("INSERT"),-4,_T("or>"),RTNONE); 
			vector<AcDbObjectId> vecBlockId=CEntitySelector::SelectAcDbObjects(&eb);
			if(vecBlockId.size()>0)
			{
				for(int i=0;i<vecBlockId.size();i++)
				{
					AcDbEntity* pEnt = NULL;
					acdbOpenAcDbEntity(pEnt,vecBlockId[i],AcDb::kForRead);
					if(AcDbBlockReference::desc()==pEnt->isA())
					{
						pEnt->close();
						CArxHelper::SetBlockPr(vecBlockId[i],"长度",valuetext);
					}
					else if(AcDbText::desc()==pEnt->isA())
					{
						pEnt->close();
						CArxHelper::SetDTextContent(vecBlockId[i],valuetext);
					}
				}
			}
		}
	}
}