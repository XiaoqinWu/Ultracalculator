/*======================================================================
//        filename :ExpressionCalculator.cpp
//        description :表达式计算
//        created by 吴晓勤   2012-10-17
//        updated by 吴晓勤   2012-11-09			
//======================================================================*/
# include "Express.h"
#include "Except.h"
#include "function.h"
#include <cmath>
#include <string>
#include <sstream>
# define MAXARGUMENTNUMBER 3

using namespace::std;
/*
 *函数功能：string转variant
 *创建日期：2012-10-20
 *更新日期：2012-10-25
*/
variant& operator<<(variant& var,const string& str)
{
	vector<string>* g_pconst=ExpressionCalculator::m_pconst;
	var.type=String;
	int pos=-1;
	for(int i=0;i<g_pconst->size();i++)
	{
		if(str==g_pconst->at(i))
		{
			pos=i;
			break;
		}
	}
	if(pos!=-1)
	{
		var.value.String=pos;
	}
	else
	{
		g_pconst->push_back(str);
		var.value.String=g_pconst->size()-1;
	}
	return var;
}
/*
 *函数功能：double转variant
 *创建日期：2012-10-20
 *更新日期：2012-10-25
*/
variant& operator<<(variant& var,const double& number)
{
	var.type=Double;
	var.value.Double=number;
	return var;
}
/*
 *函数功能：int转variant
 *创建日期：2012-10-20
 *更新日期：2012-10-25
*/
variant& operator<<(variant& var,const int& number)
{
	var.type=Integer;
	var.value.Double=number;
	return var;
}
/*
 *函数功能：variant转variant
 *创建日期：2012-10-20
 *更新日期：2012-10-25
*/
variant& operator<<(variant& var,const variant& number)
{
	var.type=number.type;
	var.value=number.value;
	return var;
}
/*
 *函数功能：variant转string
 *创建日期：2012-10-20
 *更新日期：2012-10-25
*/
string& operator<<(string& str,const variant& var)
{
	vector<string>* g_pconst=ExpressionCalculator::m_pconst;
	switch(var.type)
	{
	case String:
		str=g_pconst->at(var.value.String);break;
	case Double:
	case Integer:
		str=func::toString(var.value.Double);break;
	case Bool:
		str=var.value.Double==0?"false":"true";break;
	default:
		throw(ExpressionExcept("参数类型未知"));
	}
	return str;
}
/*
 *函数功能：variant转double
 *创建日期：2012-10-20
 *更新日期：2012-10-26
*/
double& operator<<(double& number,const variant& var)
{
	vector<string>* g_pconst=ExpressionCalculator::m_pconst;
	if(var.type==String)
	{
		string str=g_pconst->at(var.value.String);
		number=func::toDouble(str);
	}		
	else number=var.value.Double;
	return number;
}
/*
 *函数功能：variant转int
 *创建日期：2012-10-20
 *更新日期：2012-10-25
*/
int& operator<<(int& number,const variant& variant)
{
	double num;
	number=(num<<variant,(int)(num+0.5));
	return number;
}
/*
 *函数功能：字符串转数字，支持科学计数表示的数字
 *创建日期：2012-10-20
 *更新日期：2012-10-30
*/
double ExpressionCalculator::toDouble(string str)
{
	return func::toDouble(str);
}
/*
 *函数功能：数字转字符串
 *创建日期：2012-10-20
 *更新日期：2012-11-01
*/
string ExpressionCalculator::toString(double num)
{
	return func::toString(num);
}
/*
 *变量功能：指向字符常量列表的指针
 *创建日期：2012-11-09
 *更新日期：2012-11-09
*/
vector<string>* ExpressionCalculator::m_pconst=NULL;
/*
 *函数功能：构造函数
 *创建日期：2012-10-17
 *更新日期：2012-10-25
*/
ExpressionCalculator::ExpressionCalculator()
{
	initialize();
}
/*
 *函数功能：添加新的变量，并且赋值
 *创建日期：2012-11-08
 *更新日期：2012-11-08
*/
void ExpressionCalculator::addVar(string name,variant value)
{
	list<string>::iterator iter;
	//如果在未知变量里面有的话，先把这个变量名删除
	for(iter=m_varnotmap.begin();iter!=m_varnotmap.end();++iter)
	{
		if((*iter)==name)m_varnotmap.erase(iter);
	}
	//添加到已知变量表里面去
	m_varmap[name]=value;
}
/*
 *函数功能：添加新的变量，并且赋值
 *创建日期：2012-11-08
 *更新日期：2012-11-08
*/
void ExpressionCalculator::addVar(string name,double value)
{
	variant var;
	var<<value;
	addVar(name,var);
}
/*
 *函数功能：添加新的变量，并且赋值
 *创建日期：2012-11-08
 *更新日期：2012-11-08
*/
void ExpressionCalculator::addVar(string name,string value)
{
	variant var;
	var<<value;
	addVar(name,var);
}
/*
 *函数功能：设置已有变量的值
 *创建日期：2012-11-09
 *更新日期：2012-11-09
*/
void ExpressionCalculator::setVarValue(string var,variant value)
{
	//如果在已知变量表里面没有，那么看未知变量表里面有没有，有则添加
	if(m_varmap.find(var)==m_varmap.end())
	{
		bool hasTheName=false;
		list<string>::iterator iter;
		for(iter=m_varnotmap.begin();iter!=m_varnotmap.end();++iter)
		{
			if((*iter)==var)
			{
				m_varmap[var]=value;
				m_varnotmap.erase(iter);
				hasTheName=true;
				break;
			}
		}
		if(!hasTheName)throw(ExpressionExcept("变量%s未定义",var));
	}
	else m_varmap[var]=value;
}
/*
 *函数功能：设置已有变量的值
 *创建日期：2012-11-08
 *更新日期：2012-11-08
*/
void ExpressionCalculator::setVarValue(string name,double value)
{
	variant var;
	var<<value;
	setVarValue(name,var);
}
/*
 *函数功能：设置已有变量的值
 *创建日期：2012-11-09
 *更新日期：2012-11-09
*/
void ExpressionCalculator::setVarValue(string name,string value)
{
	variant var;
	var<<value;
	setVarValue(name,var);
}
/*
 *函数功能：得到当前变量的名称
 *创建日期：2012-11-08
 *更新日期：2012-11-08
*/
string ExpressionCalculator::getCurrentVarName()
{
	return m_currentvar;
}
/*
 *函数功能：得到当前变量的值
 *创建日期：2012-11-08
 *更新日期：2012-11-08
*/
variant ExpressionCalculator::getCurrentVarValue()
{
	return getVarValue(m_currentvar);
}
/*
 *函数功能：得到指定变量的值
 *创建日期：2012-11-09
 *更新日期：2012-11-09
*/
variant ExpressionCalculator::getVarValue(string name)
{
	if(m_varmap.find(name)==m_varmap.end())throw(ExpressionExcept("变量%s不存在",name));
	try
	{
		//通过入栈出栈计算字符串表达式的值
		calculate();
	}
	catch(ExpressionExcept&error)
	{
		while(!m_symbolstack.empty())m_symbolstack.pop();
		while(!m_variantstack.empty())m_variantstack.pop();
		throw(error);
	}
	//否则返回该变量的值
	return m_varmap[name];
}
/*
 *函数功能：得到指定变量的数量
 *创建日期：2012-11-09
 *更新日期：2012-11-09
*/
vector<string> ExpressionCalculator::getUnknowVar()
{
	vector<string> ret;
	list<string>::iterator iter;
	for(iter=m_varnotmap.begin();iter!=m_varnotmap.end();++iter)
	{
		ret.push_back(*iter);
	}
	return ret;
}
/*
 *函数功能：输入字符串表达式
 *创建日期：2012-11-08
 *更新日期：2012-11-08
*/
void ExpressionCalculator::input(string expression)
{
	//变量名默认为ans
	string first="ans";
	string second;
	int count=0;
	//将等号左边的变量和等号右边的表达式分离出来
	for(int i=0;i<expression.size();i++)
	{
		if(expression[i]=='=')
		{
			count++;
			if(!second.empty())first=second;
			second.clear();
			continue;
		}
		second.push_back(expression[i]);
	}
	if(second.empty())throw(ExpressionExcept("表达式不能为空"));
	//出现多个等于则报错
	if(count>1)throw(ExpressionExcept("有多个等于符号"));
	else
	{
		int parenthesis=0;
		//检查括号是否匹配
		for(int i=0;i<second.size();i++)
		{
			if(second[i]=='(')parenthesis++;
			if(second[i]==')')parenthesis--;
			if(parenthesis<0)throw(ExpressionExcept("括号不匹配"));
		}
		if(parenthesis!=0)throw(ExpressionExcept("括号不匹配"));
	}
	//将待计算的字符串清空
	m_expression.clear();
	//将待计算的字符串写成((var)=(表达式))的形式
	m_expression.append("(");
	m_expression.append(first);
	m_expression.append("=(");
	m_expression.append(second);
	m_expression.append("))");
	//记录当前的变量名
	m_currentvar=first;
	//如果这个变量不存在,则添加
	if(m_varmap.find(first)==m_varmap.end())addVar(first,0);
	//扫描之前清空元素里面的东西
	m_elements.clear();
	//扫描待计算的字符串
	try
	{
		scan();
	}
	catch(ExpressionExcept& error)
	{
		//扫描出错则清空元素里面的东西
		m_elements.clear();
		throw(error);
	}
}
/*
 *函数功能：得到计算结果或者变量“ans”的值
 *创建日期：2012-10-30
 *更新日期：2012-11-08
*/
variant ExpressionCalculator::get()
{
	return getVarValue("ans");
}
/*
 *函数功能：计算核心
 *创建日期：2012-10-19
 *更新日期：2012-11-09
*/
void ExpressionCalculator::calculate()
{
	//计算之前，符号栈和数值栈都要清空,以便于后面的校对
	while(!m_symbolstack.empty())m_symbolstack.pop();
	while(!m_variantstack.empty())m_variantstack.pop();
	//动态权重，用于记录括号已进入的层数
	int weight=0;
	list<Element>::iterator iter;
	//顺序遍历元素链表
	for(iter=m_elements.begin();iter!=m_elements.end();++iter)
	{
		Element element=*iter;
		//判断是否为操作符或函数或变量
		if(element.type==operatorsymbol)
		{
			Handler handler=element.e.handler;
			//如果为左括号，左括号入栈，并动态权重加1
			if(handler.parameter=='(')
			{
				m_symbolstack.push(element.e.handler);
				weight++;
			}
			//如果为右括号，弹出符号栈栈顶的操作符，直到遇到左括号为止
			else if(handler.parameter==')')
			{
				//遇到右括号时弹出当前括号内所有操作符
				while(m_symbolstack.top().parameter!='(')doIt();
				//最后弹出左括号，并动态权重减1
				m_symbolstack.pop();
				weight--;
			}
			//是函数、变量或者数学操作符，则准备入栈
			else
			{
				//新入栈的操作符优先级=固有权重+动态权重
				element.e.handler.weight+=weight;
				//入栈前弹出当前栈顶所有优先级高的操作符
				while(m_symbolstack.top().parameter!='(' && element.e.handler.weight <= m_symbolstack.top().weight)doIt();
				//新操作符入栈
				m_symbolstack.push(element.e.handler);
			}
		}
		//是数值
		else
		{
			//数值入栈
			m_variantstack.push(element.e.number);
		}
	}
	//最后进行一个错误检查
	if(m_variantstack.size()!=1||m_symbolstack.size()!=0)throw(ExpressionExcept("清栈不平衡"+getErrorExpress()));
}
/*
 *函数功能：扫描表达式
 *创建日期：2012-10-19
 *更新日期：2013-03-21
*/
void ExpressionCalculator::scan()
{
	//扫描前清空位置变量
	m_varnotmap.clear();
	//扫描前清空元素链表
	m_elements.clear();
	//记录当前所处理函数的参数个数
	stack<int> arguments;
	//记录当前函数的参数列表里面已经遇到的左括号数量
	stack<int> parenthesis;
	//设置初始值
	arguments.push(1);
	parenthesis.push(1);
	//顺序遍历待计算表达式的每个字符
	for(int i=0;i<m_expression.size();i++)
	{
		//取得当前字符
		char ch=m_expression[i];
		//判断是数学操作符+ - * /等
		if(isSymbol(ch))
		{
			Element element;
			element.type=operatorsymbol;
			//如果是逗号，插入右括号和左括号，并且函数参数计数减1
			if(ch==',')
			{
				element.e.handler=getHandler(")");
				m_elements.push_back(element);
				element.e.handler=getHandler("(");
				m_elements.push_back(element);
				arguments.top()=arguments.top()-1;
				continue;
			}
			//如果是左括号，括号计数加1
			else if(ch=='(')parenthesis.top()=parenthesis.top()+1;
			//如果是右括号，括号计数减1
			else if(ch==')')
			{
				parenthesis.top()=parenthesis.top()-1;
				//判断括号计数等于0，且参数计数小于等于1（因为0个参数和1个参数都没有逗号），则说明函数扫描完毕
				if(parenthesis.top()==0 && arguments.top()<=1)
				{
					//插入右括号
					element.e.handler=getHandler(")");
					m_elements.push_back(element);
					//参数计数和括号计数弹出
					arguments.pop();
					parenthesis.pop();
				}
			}
			string str;
			str.push_back(ch);
			//取操作符的处理器
			element.e.handler=getHandler(str);
			m_elements.push_back(element);
		}
		//判断是英文字母
		else if(isAbc(ch))
		{
			Element element;
			//元素类型设置为操作符
			element.type=operatorsymbol;
			string strVar;
			//将一连串的英文字母读完
			while(isAbc(m_expression[i])||isNumber(m_expression[i]))
				strVar.push_back(m_expression[i++]);
			//紧接着如果不是左括号的话当做变量处理
			if(m_expression[i]!='(')
			{
				//变量后面如果不是数值操作符则报错
				if(!isSymbol(m_expression[i]))throw(ExpressionExcept("变量%s使用不正确",strVar));
				//变量前面插入左括号
				element.e.handler=getHandler("(");
				m_elements.push_back(element);
				//如果这个变量不存在，添加到未知变量列表
				if(m_varmap.find(strVar)==m_varmap.end())
				{
					//2013-3-21修改，使未知变量不会重复添加
					bool found=false;
					list<string>::iterator iter;
					for(iter=m_varnotmap.begin();iter!=m_varnotmap.end();++iter)
					{
						if((*iter)==strVar)found=true;
					}
					if(!found)m_varnotmap.push_back(strVar);
				}
				//为变量添加处理器，这是一个特殊的空处理器
				Handler handler;
				{
					handler.num=0;
					handler.weight=0;
					handler.funcid=0;//关键是通过funcid为0来判断是变量
					variant var;var<<strVar;
					handler.parameter=var.value.String;
				}
				element.e.handler=handler;
				m_elements.push_back(element);
				//变量后面插入右括号
				element.e.handler=getHandler(")");
				//将该变量存入元素表
				m_elements.push_back(element);
				//因为做了一个超前检查，这里要回退一个字符
				i--;
			}
			//否则当做是函数处理
			else
			{
				string strFunc=strVar;
				//函数前面插入左括号
				element.e.handler=getHandler("(");
				m_elements.push_back(element);
				//插入该函数的处理器
				element.e.handler=getHandler(strFunc);	
				m_elements.push_back(element);
				//添加参数计数器和括号计数器
				arguments.push(element.e.handler.num);
				parenthesis.push(0);
				//因为做了一个超前检查，这里要回退一个字符
				i--;
			}
		}
		//是数字
		else if(isNumber(ch))
		{
			Element element;
			string strNumber;
			//将一连串数字一次性读完
			while(isNumber(m_expression[i]))
				strNumber.push_back(m_expression[i++]);
			//判断是不是科学计数法表示的数字
			if(m_expression[i]=='e'||m_expression[i]=='E')
			{
				//将‘e’压入
				strNumber.push_back(m_expression[i++]);
				//判断e后面是不是数字或者正负号
				if(m_expression[i]=='+'||m_expression[i]=='-'||isNumber(m_expression[i]))
				{
					//将正负号压入
					strNumber.push_back(m_expression[i++]);
					//将之后一连串数字压入
					while(isNumber(m_expression[i]))
						strNumber.push_back(m_expression[i++]);
					//因为做了一个超前检查，这里要回退一个字符
					i--;
				}
				//否则报错
				else throw("数值表示有误");
			}
			else
			{
				//因为做了一个超前检查，这里要回退一个字符
				i--;
			}
			//元素类型设置为数值
			element.type=operatorvariant;
			//转化为double
			element.e.number<<toDouble(strNumber);
			m_elements.push_back(element);
		}
		//是字符串
		else if('"'==ch)
		{
			Element element;
			string str;
			//将双引号中的内容取出
			while(m_expression[++i]!='"'&& i<m_expression.size())
				str.push_back(m_expression[i]);
			//元素类型设置为数值
			element.type=operatorvariant;
			element.e.number<<str;
			m_elements.push_back(element);
		}
	}
	if(arguments.size()!=1||parenthesis.size()!=1)throw(ExpressionExcept("参数个数不匹配"+getErrorExpress()));
	check();
}
/*
 *函数功能：扫描后的检查
 *创建日期：2012-11-07
 *更新日期：2012-12-04
*/
void ExpressionCalculator::check()
{
	list<Element>::iterator iter;
	bool hasSymbol=false;
	//仅仅处理紧临括号后面正负号
	for(iter=m_elements.begin();iter!=m_elements.end();++iter)
	{
		if(iter->type==operatorsymbol)
		{
			if(iter->e.handler.parameter=='(')
			{
				hasSymbol=true;
				continue;
			}
			if(hasSymbol && (iter->e.handler.parameter=='+'||iter->e.handler.parameter=='-'))
			{
				Element element;
				element.type=operatorvariant;
				element.e.number<<0.0;
				m_elements.insert(iter,element);
				++iter;
			}
			hasSymbol=false;
		}
		else hasSymbol=false;
	}
}
/*
 *函数功能：清空变量
 *创建日期：2012-10-21
 *更新日期：2012-11-09
*/
void ExpressionCalculator::initialize()
{
	m_pconst=&m_const;
	//三角函数
	addHandler("sin",func::sin);
	addHandler("asin",func::asin);
	addHandler("sinh",func::sinh);
	addHandler("cos",func::cos);
	addHandler("acos",func::acos);
	addHandler("cosh",func::cosh);
	addHandler("tan",func::tan);
	addHandler("tanh",func::tanh);
	addHandler("atan",func::atan);
	addHandler("atan2",func::atan2);
	//幂指函数
	addHandler("ln",func::ln);
	addHandler("log",func::log);
	addHandler("log10",func::log10);
	addHandler("exp",func::exp);
	addHandler("sqrt",func::sqrt);
	addHandler("power",func::power);
	//角度函数
	addHandler("pi",func::pi);
	addHandler("degrees",func::degrees);
	addHandler("radians",func::radians);
	//取整函数
	addHandler("int",func::integer);
	addHandler("floor",func::floor);
	addHandler("ceiling",func::ceiling);
	//其它函数
	addHandler("sign",func::sign);
	addHandler("mod",func::mod);
	addHandler("fact",func::fact);
	addHandler("rand",func::rand);
	addHandler("abs",func::abs);
	//字符串函数
	addHandler("left",func::left);
	addHandler("right",func::right);
	addHandler("mid",func::mid);
	addHandler("len",func::len);
	addHandler("substitute",func::substitute);
	//桥梁专业函数
	addHandler("kg",func::kg);
}
/*
 *函数功能：计算器初始化
 *创建日期：2012-10-21
 *更新日期：2012-11-09
*/
void ExpressionCalculator::clear()
{
	//清除字符常量列表
	m_const.clear();
	//清除已知变量
	m_varmap.clear();
	//清除表达式字符串
	m_expression.clear();
	//清除当前变量
	m_currentvar.clear();
	//清除未知变量
	m_varnotmap.clear();
}
/*
 *函数功能：执行处理器
 *创建日期：2012-10-19
 *更新日期：2012-11-07
*/
void ExpressionCalculator::doIt()
{
	variant var;
	variant args[MAXARGUMENTNUMBER];
	if(m_symbolstack.empty())throw(ExpressionExcept("表达式有误"));
	Handler handler=m_symbolstack.top();
	//根据参数个数弹出数字
	int i=handler.num-1;
	while(i>=0)
	{	
		if(m_variantstack.empty())throw(ExpressionExcept("表达式有误"));
		args[i--]=m_variantstack.top();
		m_variantstack.pop();
	}
	//处理函数
	string varname;
	switch(handler.funcid)
	{
	//是变量
	case 0:
		//得到变量名
		varname=m_const[handler.parameter];
		//检查变量是否存在
		if(m_varmap.find(varname)==m_varmap.end())throw(ExpressionExcept("变量%s未定义",varname));
		//取出变量的值
		var=m_varmap[varname];break;
	case gdv:
		var<<(*handler.func.gdv)();break;
	case gid:
		var<<(*handler.func.gid)(args[0]);break;
	case giv:
		var<<(*handler.func.giv)();break;
	case gdd:
		var<<(*handler.func.gdd)(args[0]);break;
	case gddd:	
		var<<(*handler.func.gddd)(args[0],args[1]);break;
	case gddi:
		var<<(*handler.func.gddi)(args[0],args[1]);break;
	case vivv:
		var<<(this->*handler.func.vivv)(handler.parameter,args[0],args[1]);break;
	case gssi:
		var<<(*handler.func.gssi)(args[0],args[1]);break;
	case gssii:
		var<<(*handler.func.gssii)(args[0],args[1],args[2]);break;
	case gis:
		var<<(*handler.func.gis)(args[0]);break;
	case gssss:
		var<<(*handler.func.gssss)(args[0],args[1],args[2]);break;
	default:
		throw(ExpressionExcept("有无法识别的操作符或者函数"));
	}
	m_variantstack.push(var);
	m_symbolstack.pop();
}
/*
 *函数功能：操作符处理函数
 *创建日期：2012-10-20
 *更新日期：2012-11-08
*/
variant ExpressionCalculator::doSymbol(int symbol,variant v1,variant v2)
{
	variant ret;
	switch(symbol)
	{
	case '+':
		return ret<<(double)v1+(double)v2;
	case '-':
		return ret<<(double)v1-(double)v2;
	case '*':
		return ret<<(double)v1*(double)v2;
	case '/':
		if(((double)v2)==0)throw(ExpressionExcept("除零异常"));
		return ret<<(double)v1/(double)v2;
	case '^':
		return ret<<pow((double)v1,(double)v2);
	case '%':
		return ret<<fmod((double)v1,(double)v2);
	case '&':
		return ret<<(string)v1+(string)v2;
	case '=':
		m_varmap[m_currentvar]=v2;
		return v2;
	default:
		throw(ExpressionExcept("未知操作符"));
	}
}
/*
 *函数功能：得到操作符的固定优先级
 *创建日期：2012-10-19
 *更新日期：2012-11-01
*/
int ExpressionCalculator::getWeight(char symbol)
{
	switch(symbol)
	{
	case '=':
		return -1;
	case '&':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '%':
		return 3;
	case '^':
		return 4;
	default:
		return 0;
	}
}
/*
 *函数功能：得到函数处理器
 *创建日期：2012-10-20
 *更新日期：2012-11-09
*/
Handler ExpressionCalculator::getHandler(string str)
{
	if(str.empty())throw(ExpressionExcept("得到处理器失败"));
	char ch=str[0];
	//是操作符
	if(isSymbol(ch))
	{
		Handler handler;
		handler.num=2;
		handler.parameter=ch;
		handler.weight=getWeight(ch);
		handler.funcid=vivv;
		handler.func.vivv=&ExpressionCalculator::doSymbol;
		return handler;
	}
	string funcname;
	for(int i=0;i<str.length();i++)
	{
		funcname.push_back(tolower(str[i]));
	}
	if(m_handlermap.find(funcname)==m_handlermap.end())throw(ExpressionExcept("未知函数%s",str));
	return m_handlermap[funcname];
}
/*
 *函数功能：判断是否是英文字母
 *创建日期：2012-10-19
 *更新日期：2012-10-20
*/
bool ExpressionCalculator::isAbc(char ch)
{
	if((ch>='a' && ch<='z')||(ch>='A' && ch<='Z'))
	{
		return true;
	}
	return false;
}
/*
 *函数功能：判断是否是符号
 *创建日期：2012-10-19
 *更新日期：2012-10-20
*/
bool ExpressionCalculator::isSymbol(char ch)
{
	switch(ch)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '^':
	case '(':
	case ')':
	case ',':
	case '&':
	case '=':
		return true;
	default:
		return false;
	}
}
/*
 *函数功能：判断是否是数字
 *创建日期：2012-10-19
 *更新日期：2012-10-20
*/
bool ExpressionCalculator::isNumber(char ch)
{
	if((ch>='0' && ch<='9')||(ch=='.'))
	{
		return true;
	}
	return false;
}
/*
 *函数功能：添加函数处理器
 *创建日期：2012-11-08
 *更新日期：2012-11-08
*/
void ExpressionCalculator::addHandler(string name,double (*func)(double))
{
	Handler handler;
	handler.weight=0;
	handler.funcid=gdd;
	handler.num=1;
	handler.func.gdd=func;
	m_handlermap.insert(pair<string,Handler>(name,handler));
}
/*
 *函数功能：添加函数处理器
 *创建日期：2012-11-08
 *更新日期：2012-11-08
*/
void ExpressionCalculator::addHandler(string name,double (*func)())
{
	Handler handler;
	handler.weight=0;
	handler.funcid=gdv;
	handler.num=0;
	handler.func.gdv=func;
	m_handlermap.insert(pair<string,Handler>(name,handler));
}
/*
 *函数功能：添加函数处理器
 *创建日期：2012-11-08
 *更新日期：2012-11-08
*/
void ExpressionCalculator::addHandler(string name,int (*func)())
{
	Handler handler;
	handler.weight=0;
	handler.funcid=giv;
	handler.num=0;
	handler.func.giv=func;
	m_handlermap.insert(pair<string,Handler>(name,handler));
}
/*
 *函数功能：添加函数处理器
 *创建日期：2012-11-08
 *更新日期：2012-11-08
*/
void ExpressionCalculator::addHandler(string name,int (*func)(double))
{
	Handler handler;
	handler.weight=0;
	handler.funcid=gid;
	handler.num=1;
	handler.func.gid=func;
	m_handlermap.insert(pair<string,Handler>(name,handler));
}
/*
 *函数功能：添加函数处理器
 *创建日期：2012-11-08
 *更新日期：2012-11-08
*/
void ExpressionCalculator::addHandler(string name,double (*func)(double,double))
{
	Handler handler;
	handler.weight=0;
	handler.funcid=gddd;
	handler.num=2;
	handler.func.gddd=func;
	m_handlermap.insert(pair<string,Handler>(name,handler));
}
/*
 *函数功能：添加函数处理器
 *创建日期：2012-11-08
 *更新日期：2012-11-08
*/
void ExpressionCalculator::addHandler(string name,double (*func)(double,int))
{
	Handler handler;
	handler.weight=0;
	handler.funcid=gddi;
	handler.num=2;
	handler.func.gddi=func;
	m_handlermap.insert(pair<string,Handler>(name,handler));
}
/*
 *函数功能：添加函数处理器
 *创建日期：2012-11-09
 *更新日期：2012-11-09
*/
void ExpressionCalculator::addHandler(string name,string (*func)(string,int))
{
	Handler handler;
	handler.weight=0;
	handler.funcid=gssi;
	handler.num=2;
	handler.func.gssi=func;
	m_handlermap.insert(pair<string,Handler>(name,handler));
}
/*
 *函数功能：添加函数处理器
 *创建日期：2013-08-22
 *更新日期：2013-08-22
*/
void ExpressionCalculator::addHandler(string name,string (*func)(string,int,int))
{
	Handler handler;
	handler.weight=0;
	handler.funcid=gssii;
	handler.num=3;
	handler.func.gssii=func;
	m_handlermap.insert(pair<string,Handler>(name,handler));
}
/*
 *函数功能：添加函数处理器
 *创建日期：2013-08-22
 *更新日期：2013-08-22
*/
void ExpressionCalculator::addHandler(string name,int (*func)(string))
{
	Handler handler;
	handler.weight=0;
	handler.funcid=gis;
	handler.num=1;
	handler.func.gis=func;
	m_handlermap.insert(pair<string,Handler>(name,handler));
}
/*
 *函数功能：添加函数处理器
 *创建日期：2013-08-22
 *更新日期：2013-08-22
*/
void ExpressionCalculator::addHandler(string name,string (*func)(string,string,string))
{
	Handler handler;
	handler.weight=0;
	handler.funcid=gssss;
	handler.num=3;
	handler.func.gssss=func;
	m_handlermap.insert(pair<string,Handler>(name,handler));
}
/*
 *函数功能：输出出错的表达式
 *创建日期：2012-12-04
 *更新日期：2012-12-04
*/
string ExpressionCalculator::getErrorExpress()
{
	ostringstream out;
	list<Element>::iterator iter;
	for(iter=m_elements.begin();iter!=m_elements.end();++iter)
	{
		switch(iter->type)
		{
		case operatorsymbol:
			//是操作符函数
			if(iter->e.handler.funcid==vivv)
			{
				char ch=iter->e.handler.parameter;
				out<<ch;
			}
			else if(iter->e.handler.funcid==0)out<<m_const[iter->e.handler.parameter];
			else out<<"[F"<<iter->e.handler.funcid<<"]";
			break;
		case operatorvariant:
			if(iter->e.number.isString())out<<(string)iter->e.number;
			else out<<(double)iter->e.number;
			break;
		}
	}
	return out.str();
}

# ifdef _DEBUG
/*
 *函数功能：添加流操作
 *创建日期：2012-11-01
 *更新日期：2012-11-08
*/
ostream& operator<<(ostream& cout,const variant& var)
{
	variant out=var;
	if(out.type==String)
	{
		cout<<"\""<<(string)out<<"\"";
	}
	else
	{
		cout<<(double)out;
	}
	return cout;
}
/*
 *函数功能：在命令行中输出扫描后的结果
 *创建日期：2012-11-01
 *更新日期：2012-11-09
*/
void ExpressionCalculator::output()
{
	cout<<m_expression<<endl;
	list<Element>::iterator iter;
	for(iter=m_elements.begin();iter!=m_elements.end();++iter)
	{
		switch(iter->type)
		{
		case operatorsymbol:
			//是操作符函数
			if(iter->e.handler.funcid==vivv)
			{
				char ch=iter->e.handler.parameter;
				cout<<ch;
			}
			else if(iter->e.handler.funcid==0)cout<<m_const[iter->e.handler.parameter];
			else cout<<"[F"<<iter->e.handler.funcid<<"]";
			break;
		case operatorvariant:
			cout<<iter->e.number;
			break;
		}
		//cout<<',';
	}
	vector<string> vec=getUnknowVar();
	for(int i=0;i<vec.size();i++)
	{
		cout<<","<<vec[i];
	}
	cout<<endl;
}
#endif