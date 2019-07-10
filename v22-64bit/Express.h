/*======================================================================
//        filename :ExpressionCalculator.h
//        description :表达式计算
//        created by 吴晓勤   2012-10-17
//        updated by 吴晓勤   2012-11-09	
//======================================================================*/
#ifndef _EXPRESSIONCALCULATOR_H_H
#define _EXPRESSIONCALCULATOR_H_H

# include <stack>
# include <vector>
# include <map>
# include <string>
# include <iostream>
# include <list>

using namespace std;
class ExpressionCalculator;
struct variant;
variant& operator<<(variant&,const string&);
variant& operator<<(variant&,const double&);
variant& operator<<(variant&,const int&);
variant& operator<<(variant&,const variant&);
string& operator<<(string&,const variant&);
double& operator<<(double&,const variant&);
int& operator<<(int&,const variant&);
/*
 *类型功能：处理器载体
 *创建日期：2012-10-21
 *更新日期：2012-11-08
*/
struct Handler
{
	int num;
	int weight;
	int parameter;
	int funcid;
	union _func
	{
		variant (ExpressionCalculator::*vivv)(int,variant,variant);//处理符号
		int (*giv)();
		double (*gdv)();
		double (*gdd)(double);
		double (*gddd)(double,double);
		double (*gddi)(double,int);
		int (*gid)(double);
		int (*gis)(string);
		string (*gssi)(string,int);
		string (*gssii)(string,int,int);
		string (*gssss)(string,string,string);
	}func;
};
/*
 *常量功能：标定数据的类型
 *创建日期：2012-10-27
 *更新日期：2012-11-01
*/
enum{Double,String,Integer,Bool};//数值类型
/*
 *类型功能：数据载体
 *创建日期：2012-10-29
 *更新日期：2012-11-08
*/
struct variant
{
	int type;
	union _value
	{
		int String;
		double Double;
	}value;
	bool isString(){return type==String?true:false;};
	operator string(){string str;return str<<*this;};
	operator double(){double num;return num<<*this;};
	operator int(){int num;return num<<*this;};
	operator bool(){return value.Double==0?false:true;};
};
/*
 *类型功能：表达式计算元素
 *创建日期：2012-10-17
 *更新日期：2012-11-08
*/
struct Element
{
	int type;
	union _value
	{
		Handler handler;
		variant number;
	}e;
};
/*
 *类型功能：表达式计算类定义
 *创建日期：2012-10-17
 *更新日期：2012-11-09
*/
class ExpressionCalculator
{
public:
	ExpressionCalculator();
	//基本操作
	void input(string);//输入表达式字符串
	variant get();//得到结果
	//高级操作
	void clear();//清空变量
	variant getVarValue(string);
	void setVarValue(string,variant);
	void setVarValue(string,double);
	void setVarValue(string,string);
	void addVar(string,variant);
	void addVar(string,double);
	void addVar(string,string);
	string getCurrentVarName();
	variant getCurrentVarValue();
	vector<string> getUnknowVar();
	//全局成员
	static double toDouble(string);//字符串转数字
	static string toString(double);//字符串转数字
	static vector<string>* m_pconst;//静态全局变量
private:
	enum{giv=1,gdv,gdd,gddd,gddi,vivv,gid,gssi,gssii,gis,gssss};//函数类型
	enum{operatorsymbol=0,operatorvariant=1};//元素类型
	stack<Handler> m_symbolstack;//符号栈
	stack<variant> m_variantstack;//数值栈
	list<Element> m_elements;//扫描后的元素
	vector<string> m_const;//字符常量
	map<string,variant> m_varmap;//变量到变体的映射
	list<string> m_varnotmap;//未赋值的变量列表
	map<string,Handler> m_handlermap;//函数映射
	string m_expression;//表达式值
	string m_currentvar;//当前变量
	int m_precision;//输出精度
	void initialize();//初始化
	void calculate();//计算核心
	void scan();//扫描
	void check();//扫描后检查
	bool isSymbol(char);//是否为符号
	bool isNumber(char);//是否为数字或小数点
	bool isAbc(char);//是否字母
	int getWeight(char);//操作符权重分配
	Handler getHandler(string);//得到函数或操作符的handler
	double doSymbol(int,double,double);//处理操作符
	variant doSymbol(int,variant,variant);//处理操作符
	double doVar(int);//处理变量
	void doIt();//handler处理中枢
	void addHandler(string,double (*)());
	void addHandler(string,int (*)());
	void addHandler(string,int (*)(double));
	void addHandler(string,double (*)(double));
	void addHandler(string,double (*)(double,double));
	void addHandler(string,double (*)(double,int));
	void addHandler(string,string (*)(string,int));
	void addHandler(string,string (*)(string,int,int));
	void addHandler(string,int (*)(string));
	void addHandler(string,string (*)(string,string,string));
	string getErrorExpress();
# ifdef _DEBUG
public:
	void output();//输出中间结果
#endif
};
#endif