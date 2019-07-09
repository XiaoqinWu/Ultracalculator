/*======================================================================
//        filename :function.cpp
//        description :功能函数
//        created by 吴晓勤   2012-11-7
//        updated by 吴晓勤   2012-11-7	
//======================================================================*/
#include "function.h"
#include <iostream>
#include <cmath>
#include "time.h"
#include "Except.h"
namespace func
{
	//两个重要的数学函数
	//string to double
	double toDouble(string s)
	{
		//return atof(str.c_str());
		//转换前将字符串里面的非数字的东西过滤掉
		string str;
		for (int i=0;i<s.length();i++)
		{
			char ch=s[i];
			if(ch>='0'&&ch<='9')
			{
				str.push_back(ch);
			}
			else if (ch=='.'||ch=='+'||ch=='-')
			{
				str.push_back(ch);
			}
			else if(i<s.length()-1&&(ch=='='||ch==':'))
			{
				str.clear();
			}
		}
		if(str.length()==0)
			throw(ExpressionExcept("数字错误"));
		string index;
		double indexnum=0;
		double weight=0;
		double ret=0;
		bool isNegative=false;
		for(int i=0;i<str.size();i++)
		{
			char ch=str[i];
			if(ch=='-'&& i==0)isNegative=true;
			else if(ch=='+'&& i==0)continue;
			else if(ch=='.'&& weight==0)weight=10;
			else if(ch>='0' && ch<='9')
			{
				double num=ch-'0';
				if(weight)
				{
					ret=ret+num/weight;
					weight*=10;
				}
				else ret=ret*10+num;
			}
			else if(ch=='e'||ch=='E'&&i!=0 && i!=str.size()-1)
			{
				index.assign(str,i+1,str.size()-i-1);
				break;
			}
			else throw(ExpressionExcept("数字错误"));
		}
		ret=ret*(isNegative?-1:1);
		//求指数
		isNegative=false;
		for(int i=0;i<index.size();i++)
		{
			char ch=index[i];
			if(ch=='-'&& i==0)isNegative=true;
			else if(ch=='+'&& i==0)continue;
			else if(ch>='0' && ch<='9')indexnum=indexnum*10+ch-'0';
			else throw(ExpressionExcept("数字错误"));
		}
		indexnum=indexnum*(isNegative?-1:1);
		if(std::abs(indexnum)>307)throw(ExpressionExcept("数字错误"));
		return ret*std::pow(10.0,indexnum);
	}
	//double to string
	string toString(double num)
	{
		//设置一个指数，超过它则用科学计数法表示
		int precision_e=13;
		string str;
		string ret;
		//得到指数的绝对值
		int n=std::floor(abs(log10(abs(num))));
		//判断数的正负号
		if(num<0)ret.push_back('-');
		//超过范围报错
		if(std::abs(n)>307)throw(ExpressionExcept("数字错误"));
		//n的值超过设定的指数
		else if(n>precision_e)
		{
			string str_n;
			//判断指数的正负号
			if(std::log10(abs(num))<0)str_n.push_back('-');
			//将num表示成科学计数的形式
			double x=std::log10(abs(num))<0?std::abs(num*pow(10.0,n)):std::abs(num*pow(10.0,-n));
			//小数位全部提取出来
			for(int i=0;i<precision_e;i++)
			{
				char ch=(int(x))%10+'0';
				if(i==1)str.push_back('.');
				str.push_back(ch);
				x=(x-int(x))*10;
			}
			//去除末尾多余的0
			for(int i=str.size()-1;i>0;i--)
			{
				if(str[i]=='.')
				{
					str.erase(i);
					break;
				}
				if(str[i]=='0')str.erase(i);
				else break;
			}
			//得到指数
			string temp;
			while(n)
			{
				temp.push_back(n%10+'0');n=n/10;
			}
			for(int i=temp.size()-1;i!=-1;i--)str_n.push_back(temp[i]);
			ret.append(str);
			ret.append("e");
			ret.append(str_n);
			return ret;
		}
		else
		{
			string strbig,strsmall;
			double big,small;
			big=std::floor(abs(num));
			small=std::abs(num)-big+0.0000000000005;
			//添加整数部分
			while(std::abs(big)>std::pow(10.0,-precision_e))
			{
				strbig.push_back(std::fmod(big,10)+'0');
				big=std::floor(big/10);
			}
			if(strbig.empty())strbig.push_back('0');
			for(int i=strbig.size()-1;i>-1;i--)ret.push_back(strbig[i]);

			//添加小数部分
			for(int i=0;i<precision_e-1;i++)
			{
				small*=10;
				strsmall.push_back(((int)small)+'0');
				small=small-(int)small;
			}
			//去除末尾多余的0
			for(int i=strsmall.size()-1;i!=-1;i--)
			{
				if(strsmall[i]=='0')strsmall.erase(i);
				else break;
			}
			if(!strsmall.empty())
			{
				ret.append(".");
				ret.append(strsmall);
			}
			return ret;
		}
	}
	//13个三角函数
	double sin(double x)
	{
		return std::sin(x*pi()/180.0);
	}
	double asin(double x)
	{
		return std::asin(x)*180.0/pi();
	}
	double sinh(double x)
	{
		return std::sinh(x);
	}
	double cos(double x)
	{
		return std::cos(x*pi()/180.0);
	}
	double acos(double x)
	{
		return std::acos(x*180.0/pi());
	}
	double cosh(double x)
	{
		return std::cosh(x);
	}
	double tan(double x)
	{
		return std::tan(x*pi()/180.0);
	}
	double tanh(double x)
	{
		return std::tanh(x);
	}
	double atan(double x)
	{
		return std::atan(x*180.0/pi());
	}
	double atan2(double x,double y)
	{
		return std::atan2(x,y);
	}
	//6个幂指函数
	double ln(double x)
	{
		if(x<=0)throw(ExpressionExcept("ln()的参数不能为负或零。"));
		return std::log(x);
	}
	double log(double x,double y)
	{
		if(x<=0||y<=0)throw(ExpressionExcept("log()的参数不能为负或零。"));
		return std::log(y)/std::log(x);
	}
	double log10(double x)
	{
		if(x<=0)throw(ExpressionExcept("log10()的参数不能为负或零。"));
		return std::log10(x);
	}
	double exp(double x)
	{
		return std::exp(x);
	}
	double sqrt(double x)
	{
		if(x<0)throw(ExpressionExcept("sqrt()的参数不能为负。"));
		return std::sqrt(x);
	}
	double power(double x,double y)
	{
		return std::pow(x,y);
	}
	//角度函数
	double pi()
	{
		return 3.14159265358979;
	}
	double degrees(double x)
	{
		return x/3.14159265358979*180;
	}
	double radians(double x)
	{
		return x/180*3.14159265358979;
	}
	//取整函数
	int integer(double x)
	{
		return std::floor(x+0.5);
	}
	double floor(double x)
	{
		return std::floor(x);
	}
	//其它函数
	int sign(double x)
	{
		return (x<=0)?0:1;
	}
	double mod(double x,double y)
	{
		return std::fmod(x,y);
	}
	double fact(double x)
	{
		if(x<0)throw(ExpressionExcept("fact()的参数不能小于零。"));
		double ret=1;
		int n=(int)x;
		if(x<=0)return 0;
		for(int i=0;i<n;i++)ret=ret*(i+1);
		return ret;
	}
	double rand()
	{
		std::srand(clock());
		return std::rand()*1.0/RAND_MAX;
	}
	double abs(double x)
	{
		return std::fabs(x);
	}
	double ceiling(double x)
	{
		return std::ceil(x);
	}
	//字符串函数
	std::string left(std::string source,int n)
	{
		if(n<=0)throw(ExpressionExcept("left()的第二个参数不能小于或等于零。"));
		if(n>source.length())n=source.length();
		std::string str;
		for(int i=0;i<n;i++)
		{
			str.push_back(source[i]);
		}
		return str;
	}

	std::string right(std::string source,int n)
	{
		if(n<=0)throw(ExpressionExcept("right()的第二个参数不能小于或等于零。"));
		if(n>source.length())n=0;
		std::string str;
		for(int i=source.length()-n;i<source.length();i++)
		{
			str.push_back(source[i]);
		}
		return str;
	}

	std::string mid(std::string source,int n,int len)
	{
		if(len<=0)throw(ExpressionExcept("mid()的第三个参数不能小于或等于零。"));
		if(n<0)n=0;
		if(n+len>source.length())len=source.length()-n;
		std::string str;
		for(int i=n;i<n+len;i++)
		{
			str.push_back(source[i]);
		}
		return str;
	}

	int len(std::string source)
	{
		return source.length();
	}

	std::string substitute(std::string source,std::string oldstr,std::string newstr)
	{
		std::string ret;
		for(int i=0;i<source.length();i++)
		{
			int j=0;
			for(;j<oldstr.length();j++)
			{
				if(i+j>=source.length())break;
				if(source[i+j]!=oldstr[j])break;
			}
			if(j==oldstr.length())
			{
				for(int k=0;k<newstr.length();k++)
				{
					ret.push_back(newstr[k]);
				}
				i=i+j-1;
			}
			else
			{
				ret.push_back(source[i]);
			}
		}
		return ret;
	}
	//桥梁专业函数
	double kg(double d)
	{
		double ret=0;
		int index=int(d+0.5);
		switch(index)
		{
		case 6:
			ret=0.222;break;
		case 8:
			ret=0.395;break;
		case 10:
			ret=0.617;break;
		case 12:
			ret=0.888;break;
		case 14:
			ret=1.21;break;
		case 16:
			ret=1.58;break;
		case 18:
			ret=2.0;break;
		case 20:
			ret=2.47;break;
		case 22:
			ret=2.98;break;
		case 25:
			ret=3.85;break;
		case 28:
			ret=4.83;break;
		case 32:
			ret=6.31;break;
		case 36:
			ret=7.99;break;
		case 40:
			ret=9.87;break;
		case 50:
			ret=15.42;break;
		}
		return ret;
	}
}