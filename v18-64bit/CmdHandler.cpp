/********************************************************************
		filename :CmdHandler.cpp
    	description :命令处理器
		created	by 吴晓勤 2013/03/27 9:57
    	updated	by 吴晓勤 2013/03/27 10:03
*********************************************************************/
#include "StdAfx.h"
#include "CmdHelper.h"
#include "CmdHandler.h"
#include "CEntitySelector.h"
//#include "stringhelper.h"
#include <algorithm>
/*
 *函数功能：构造函数
 *创建日期：2013/03/27 9:28
 *更新日期：2013/03/27 9:31
*/
CmdHandler::CmdHandler()
{
	CmdHelper::Initialize(m_mapfunc);
}
/*
 *函数功能：计算表达式
 *创建日期：2013/03/27 9:58
 *更新日期：2013/4/9 23:01
*/
void CmdHandler::run(string express)
{
	if(express.empty())return;
	ExpressionCalculator calc;
	vector<string> vecvar;
	//设置一个标志变量，记录是否有序号变量i。
	bool hasIndexVar=false;
	//输入并解析表达式。
	calc.input(express);
	//得到表达式中的未知变量放到临时变量里面。
	vector<string> temp=calc.getUnknowVar();
	//过滤未知变量中的“i”。
	for(int i=0;i<temp.size();i++)
	{
		if(temp[i]!="i")
		{
			vecvar.push_back(temp[i]);
		}
		else hasIndexVar=true;
	}
	//如果没有未知变量。
	if(vecvar.size()==0)
	{
		//输出模式为新建
		if(GetOutMode()==0)
		{
			if(hasIndexVar)calc.setVarValue("i",0);
			string text=toString(calc.get());
			CTextValueJig* jig=new CTextValueJig();
			jig->doIt(text);
			delete jig;
			return;
		}
		//输出模式为修改或自动
		else
		{
			CArxHelper::ShowMessage("选择要修改的文本集合:");
			vector<CDText> selected=CEntitySelector::GetDText();
			DTextSort(selected);
			for (int i=0;i<selected.size();i++)
			{
				if(hasIndexVar)calc.setVarValue("i",i);
				//CArxHelper::SetDTextContent(selected[i].id,toString(calc.get()));
				selected[i].text=toString(calc.get());
				selected[i].Update();
			}
			return;
		}
	}
	else
	{
		int minlen=MAXSELECT;
		vector<string> vecvalue;
		map<string,vector<CDText> > maptext;
		//从CAD中选择单行文本集合
		for(int i=0;i<vecvar.size();i++)
		{
			string name=vecvar[i];
			CArxHelper::ShowMessage("请选择变量%s的值：",name);
			vector<CDText> vec=CEntitySelector::GetDText();
			if(vec.size()==0)
			{
				CArxHelper::ShowMessage("为变量%s赋值失败。\n",name);
				return;
			}
			//记录最小长度
			if(i==0)minlen=vec.size();
			//如果与最小长度不等则报错
			if(vec.size()!=minlen)
			{
				CArxHelper::ShowMessage("变量%s长度不匹配。\n",name);
				return;
			}
			//排序
			DTextSort(vec);
			//保存
			maptext.insert(pair<string,vector<CDText> >(name,vec));
		}
		//循环计算表达式的值
		for(int i=0;i<minlen;i++)
		{
			//如果有变量i，则设置变量i的值。
			if(hasIndexVar)calc.setVarValue("i",i);
			//设置其它变量的值。
			for(int j=0;j<vecvar.size();j++)
			{
				string name=vecvar[j];
				//calc.setVarValue(name,StringHelper::parseDouble(maptext[name][i].text));
				calc.setVarValue(name,maptext[name][i].text);
			}
			//计算结果进入值向量中。
			vecvalue.push_back(toString(calc.get()));
		}
		//如果输出模式为修改文本
		if(GetOutMode()==1)
		{
			vector<CDText> vecSelectedDText=CEntitySelector::GetDText();
			DTextSort(vecSelectedDText);
			//如果计算结果向量的长度与选择的要修改的文本个数不匹配，要提示用户。2013-05-07修改
			if(vecSelectedDText.size()!=vecvalue.size())
			{
				CArxHelper::ShowMessage("注意：选择的要修改的文本个数是与计算结果的数量不匹配的。\n");
			}
			for(int i=0;i<vecSelectedDText.size();i++)
			{
				//CArxHelper::SetDTextContent(vecSelectedDText[i].id,vecvalue[i%vecvalue.size()]);
				vecSelectedDText[i].text=vecvalue[i%vecvalue.size()];
				vecSelectedDText[i].Update();
			}
			return;
		}
		//如果输出模式为新建
		else
		{
			//为最后一个变量所选择的文本
			vector<AcDbObjectId> veclastids;
			vector<CDText> veclast=maptext[vecvar[vecvar.size()-1]];
			for(int i=0;i<minlen;i++)
			{
				veclastids.push_back(veclast[i].id);
			}
			//新建文本
			if(GetOutMode()==0)
			{
				CTextValueJig* jig=new CTextValueJig();
				jig->doIt(veclastids,vecvalue);
				delete jig;
			}
			//自动修改
			else if(GetOutMode()==2)
			{
				for(int i=0;i<veclast.size();i++)
				{
					veclast[i].text=vecvalue[i];
					veclast[i].Update();
				}
			}
		}
	}
}
/*
 *函数功能：解析命令，返回值表示是否要关闭对话框
 *创建日期：2013/03/27 10:36
 *更新日期：2013/4/9 23:01
*/
void CmdHandler::parse(string express)
{
	if(m_mapfunc.find(express)!=m_mapfunc.end())
	{
		m_mapfunc[express]();
	}
	else
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
			if(selected.size()>0)
			{
				DTextSort(selected);
				for (int i=0;i<selected.size();i++)
				{
					selected[i].text=express;
					selected[i].Update();
				}
			}
		}
	}
}
/*
 *函数功能：得到当前文档的输出模式。
 *创建日期：2013/03/27 9:58
 *更新日期：2013/03/27 9:58
*/
int CmdHandler::GetOutMode()
{
	return DocVars.docData().GetOutMode();
}
/*
 *函数功能：得到当前文档的排序模式。
 *创建日期：2013/03/27 9:59
 *更新日期：2013/03/27 9:59
*/
int CmdHandler::GetSortMode()
{
	return DocVars.docData().GetSortMode();
}
/*
 *函数功能：根据小数位数将double转为string。
 *创建日期：2013/03/27 9:59
 *更新日期：2013/03/27 9:59
*/
string CmdHandler::toString(double value)
{
	return CmdHelper::toString(value);
}
/*
 *函数功能：根据小数位数将variant转为string。
 *创建日期：2013/03/27 10:00
 *更新日期：2013/03/27 10:00
*/
string CmdHandler::toString(variant value)
{
	return CmdHelper::toString(value);
}
/*
 *函数功能：根据当前文档的排序模式对文字排序
 *创建日期：2013/03/27 10:00
 *更新日期：2013/05/07 18:26
*/
void CmdHandler::DTextSort(vector<CDText>& vec)
{
	CmdHelper::EntitySort(vec);
}

