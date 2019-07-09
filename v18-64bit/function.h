/*======================================================================
//        filename :function.h
//        description :功能函数
//        created by 吴晓勤   2012-11-7
//        updated by 吴晓勤   2012-11-7	
//======================================================================*/
#ifndef _FUNCTION_H_H
#define _FUNCTION_H_H
#include <iostream>
using namespace std;
namespace func
{
	double toDouble(string str);
	string toString(double num);
	string left(string,int);
	//13个三角函数
	double sqrt(double);
	double sin(double);
	double asin(double);
	double sinh(double);
	double asinh(double);
	double cos(double);
	double acos(double);
	double cosh(double);
	double acosh(double);
	double tan(double);
	double tanh(double);
	double atan(double);
	double atan2(double,double);
	double atanh(double);
	//6个幂指函数
	double ln(double);
	double log(double,double);
	double log10(double);
	double exp(double);
	double sqrt(double);
	double power(double,double);
	//角度函数
	double pi();
	double degrees(double);
	double radians(double);
	//取整函数
	int integer(double);
	double floor(double);
	int	round(double,double);
	int	rounddown(double,double);
	int	roundup(double,double);
	int	ceiling(double,double);
	//其它函数
	int sign(double);
	double mod(double,double);
	double fact(double);
	double rand();
	double abs(double);
	double ceiling(double);
	//字符串函数
	string left(string,int);
	string right(string,int);
	string mid(string,int,int);
	int len(string);
	string substitute(string,string,string);
	//桥梁专业函数
	double kg(double);
}
#endif