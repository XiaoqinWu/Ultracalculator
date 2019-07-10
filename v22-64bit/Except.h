/*======================================================================
//        filename :ExpressionCalculator.h
//        description :表达式计算
//        created by 吴晓勤   2012-10-17
//        updated by 吴晓勤   2012-11-09	
//======================================================================*/
#ifndef _EXPRESSIONEXCEPT_H_H
#define _EXPRESSIONEXCEPT_H_H
# include <string>
using namespace std;
/*
 *类型功能：表达式异常类
 *创建日期：2012-11-08
 *更新日期：2012-11-08
*/
class ExpressionExcept
{
private:
	string error;
public:
	string what(){return error;};
	ExpressionExcept(string str){error=str;};
	ExpressionExcept(string str,string name){error=str.replace(str.find("%s"),2,name);};
};
#endif