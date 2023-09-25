#pragma once
#include <iostream>
using namespace std;
#include"常量定义.h"
#include <fstream>
#include <vector>
#include <string>




//语法分析 ：
//首先是一个表达式的语法
//表达式 ：=表达式 操作符（运算符=-*/）右项  E ->E op T    
// 表达式 ：=右项							 E ->T
// 右项   ：= 数字                           T ->数字
// 右项   ：= 标识符						 T ->标识符
//右项   ：=（表达式）						 T ->(E)
//以下为对于表达式的改良
//E -> T E'
//E'-> op T E'
//E'-> 空
//T ->数字
//T ->标识符
//T ->(E)
//以下为FISRST集与FOLLOW集合的计算
//First（E）={数字，标识符，( }
//First（E'）={op，空}
//First（T）={（，数字，标识符 }
//Follw(E)={),#}
//Follw(E')={),#}
//Follw(T)={op,),#}
// 
//SELECT(E -> T E')			={（，数字，标识符}
//SELECT(E'-> op T E')		={op}
//SELECT(E'-> 空)			={),#}
//SELECT(T ->数字)			={数字}
//SELECT(T ->标识符)		={标识符}
//SELECT(T ->(E))			={(}
//预测分析表
//		数字	标识符	op		(			)		#
// E	T E'	T E'			T E'
// E'                  opTE'			    空     空
// T	数字	标识符			(E)	
//


//对于表达式进行语法分析(暂且对于分割表达式的第一个式子进行分析)
bool AnalyseExprexxion(vector<Word> expression) {
	vector<Word> temporarysave;//保存待分析的句
	for (int j = 0; j < expression.size(); j++)
		{
			if (expression[j].word_value != ";") {
				temporarysave.push_back(expression[j]);
			}
		}

	stack_expression.clear();
	stack_expression.push_back(stackinput_E);
	int i = 0;
	while (stack_expression.size()!=0)
	{
		if (i >temporarysave.size())
		{
			cout << "分析失败,原因:i超出界限" << endl;
			break;
		}
		//取出栈顶的元素
		Word nowstcakchar = stack_expression[stack_expression.size() - 1];
		//找到待分析串的第一个字母
		Word waitanalys;
		if (i == temporarysave.size())
		{
			waitanalys.word_type = "empty";
			waitanalys.word_value = "#";
		}
		else
		{
			waitanalys.word_type = temporarysave[i].word_type;
			waitanalys.word_value = temporarysave[i].word_value;
		}
		//这是一处用来测试的语句
		if (iftest_grammer) {
			cout << i << "\t" << "nowstcakchar:" << nowstcakchar.word_value << "\twaitanalys\t" << waitanalys.word_value << endl;
		}

		if(nowstcakchar.word_value=="E") {

			if (waitanalys.word_type=="digit") {
				//弹出
				stack_expression.pop_back();
				//压入 E'T
				stack_expression.push_back(stackinput_E2);
				stack_expression.push_back(stackinput_T);
				//退出此次循环
				continue;
			}
			else
			{
//		数字	标识符	op		(			)		#
// E	T E'	T E'			T E'
				if (waitanalys.word_type == "token") {
					//弹出
					stack_expression.pop_back();
					//压入 E'T
					stack_expression.push_back(stackinput_E2);
					stack_expression.push_back(stackinput_T);
					//退出此次循环
					continue;
				}
				else
				{
					if (waitanalys.word_value == "(") {
						//弹出
						stack_expression.pop_back();
						//压入 E'T
						stack_expression.push_back(stackinput_E2);
						stack_expression.push_back(stackinput_T);
						//退出此次循环
						continue;
					}
					else
					{
						//分析失败
						cout << "分析失败,原因:不符合语法规则" << endl;
						break;
					}

				}

			}

			

		}
		if (nowstcakchar.word_value == "E2")
		{
			//		数字	标识符	op		(			)		#
			// E'   opTE'								空     空
			if (waitanalys.word_type == "operator") {
				//弹出
				stack_expression.pop_back();
				//压入 E'T op
				stack_expression.push_back(stackinput_E2);
				stack_expression.push_back(stackinput_T);
				stack_expression.push_back(stackinput_op);
				//退出此次循环
				continue;
			}
			else
			{
				if (waitanalys.word_value == ")") {
					//弹出
					stack_expression.pop_back();
					//退出此次循环
					continue;
				}
				else
				{
					if (waitanalys.word_value == "#") {
						stack_expression.pop_back();
						//退出此次循环
						continue;
					}
					else
					{
						//分析失败
						cout << "分析失败,原因:不符合语法规则" << endl;
						break;
					}

				}

			}

		}
		if (nowstcakchar.word_value == "T")
		{
			//		数字	标识符	op		(			)		#
			// T	数字	标识符			(E)	
			if (waitanalys.word_type == "digit") {
				//弹出
				stack_expression.pop_back();
				//压入 digit
				stack_expression.push_back(stackinput_digit);
				//退出此次循环
				continue;
			}
			else
			{
				if (waitanalys.word_type == "token") {
					//弹出
					stack_expression.pop_back();
					//压入 tokrn
					stack_expression.push_back(stackinput_token);
					//退出此次循环
					continue;
				}
				else
				{
					if (waitanalys.word_value == "(") {
						//弹出
						stack_expression.pop_back();
						//压入 )E(
						stack_expression.push_back(stackinput_rk);
						stack_expression.push_back(stackinput_E);
						stack_expression.push_back(stackinput_lk);
						//退出此次循环
						continue;
					}
					else
					{
						//分析失败
						cout << "分析失败,原因:不符合语法规则" << endl;
						break;
					}
				}
			}

		}
		if (nowstcakchar.word_value == "digit")
		{
			if (waitanalys.word_type == "digit")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "token")
		{
			if (waitanalys.word_type == "token")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "(")
		{
			if (waitanalys.word_value == "(")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == ")")
		{
			if (waitanalys.word_value == ")")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "op")
		{
			if (waitanalys.word_value == "+"|| waitanalys.word_value == "-" || waitanalys.word_value == "*" || waitanalys.word_value == "/")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		cout << "分析失败,原因:无法对于待分析队列的首个字符进行分析" << endl;
		break;
	}

	
	if (stack_expression.size() == 0)
	{
		cout << "分析成功:表达式" << endl;
		return true;
	}
	else
	{
		return false;
	}


}
//对于赋值语句的语法分析
//
//C ->标识符 = E;
//C-> 保留字 标识符 = E;
//E -> T E'
//E'-> op T E'
//E'-> 空
//T ->数字
//T ->标识符
//T ->(E)
//以下为FISRST集与FOLLOW集合的计算
//First(C)={标识符,保留字}
//First（E）={数字，标识符，( }
//First（E'）={op，空}
//First（T）={（，数字，标识符 }
// 
//Follow(C)={#,} 
//Follw(E)={ ; , ) , }
//Follw(E')={) , ;}
//Follw(T)={op , ) , ; }
// 
//SELECT(C ->标识符 = E;)			={标识符}
//SELECT(C-> 保留字 标识符 = E;)	={保留字}
//SELECT(E -> T E')					={（，数字，标识符}
//SELECT(E'-> op T E')				={op}
//SELECT(E'-> 空)					={) , ;}
//SELECT(T ->数字)					={数字}
//SELECT(T ->标识符)				={标识符}
//SELECT(T ->(E))					={(}
//预测分析表
//		保留字					数字					标识符			op				(			)		 ;			#
// C	保留字 标识符 = E;								标识符 = E;
// E	T E'					T E'													T E'
// E'                                                                   opTE'			 空					空
// T							数字					标识符							(E)	
//
bool AnalyseAssignment(vector<Word> assignment) {
	vector<Word> temporarysave;//保存待分析的句
	for (int j = 0; j < assignment.size(); j++)
	{
			temporarysave.push_back(assignment[j]);
	
	}
	//栈初始化
	stack_expression.clear();
	stack_expression.push_back(stackinput_C);
	int i = 0;//用来保存待分析语句中的位置
	while (stack_expression.size() != 0)
	{
		if (i > temporarysave.size())
		{
			cout << "分析失败,原因:i超出界限" << endl;
			break;
		}
		//取出栈顶的元素
		Word nowstcakchar = stack_expression[stack_expression.size() - 1];
		//找到待分析串的第一个字母
		Word waitanalys;
		if (i == temporarysave.size())
		{
			waitanalys.word_type = "empty";
			waitanalys.word_value = "#";
		}
		else
		{
			waitanalys.word_type = temporarysave[i].word_type;
			waitanalys.word_value = temporarysave[i].word_value;
		}

		//这是一处用来测试的语句
		if (iftest_grammer) {
			cout << i << "\t" << "nowstcakchar:" << nowstcakchar.word_value << "\twaitanalys\t" << waitanalys.word_value << endl;
		}
		if (nowstcakchar.word_value == "C") {
			//cout << nowstcakchar.word_value << endl;
			if (waitanalys.word_type == "keyword") {
				//保留字 标识符 = E;
				//弹出
				stack_expression.pop_back();
				//压入 
				stack_expression.push_back(stackinput_branch);
				stack_expression.push_back(stackinput_E);
				stack_expression.push_back(stackinput_equal);
				stack_expression.push_back(stackinput_token);
				stack_expression.push_back(stackinput_keyword);
				//退出此次循环
				continue;
			}
			else
			{
				//		数字	标识符	op		(			)		#
				// E	T E'	T E'			T E'
				if (waitanalys.word_type == "token") {
					//标识符 = E;
					//弹出
					stack_expression.pop_back();
					//压入 
					stack_expression.push_back(stackinput_branch);
					stack_expression.push_back(stackinput_E);
					stack_expression.push_back(stackinput_equal);
					stack_expression.push_back(stackinput_token);
					//退出此次循环
					continue;
				}
				else
				{
						//分析失败
					if(iftest_grammer)
						cout << "分析失败,原因:不符合语法规则" << endl;
						break;
				}

			}



		}
		if (nowstcakchar.word_value == "E") {
			if(iftest_grammer)
			cout << nowstcakchar.word_value << endl;

			if (waitanalys.word_type == "digit") {
				//弹出
				stack_expression.pop_back();
				//压入 E'T
				stack_expression.push_back(stackinput_E2);
				stack_expression.push_back(stackinput_T);
				//退出此次循环
				continue;
			}
			else
			{
				//		数字	标识符	op		(			)		#
				// E	T E'	T E'			T E'
				if (waitanalys.word_type == "token") {
					//弹出
					stack_expression.pop_back();
					//压入 E'T
					stack_expression.push_back(stackinput_E2);
					stack_expression.push_back(stackinput_T);
					//退出此次循环
					continue;
				}
				else
				{
					if (waitanalys.word_value == "(") {
						//弹出
						stack_expression.pop_back();
						//压入 E'T
						stack_expression.push_back(stackinput_E2);
						stack_expression.push_back(stackinput_T);
						//退出此次循环
						continue;
					}
					else
					{
						//分析失败
						if (iftest_grammer)
						cout << "分析失败,原因:不符合语法规则" << endl;
						break;
					}

				}

			}



		}
		if (nowstcakchar.word_value == "E2")
		{
			if (iftest_grammer)
			cout << nowstcakchar.word_value << endl;
			//		数字	标识符	op		(			)		#
			// E'   opTE'								空     空
			if (waitanalys.word_type == "operator") {
				//弹出
				stack_expression.pop_back();
				//压入 E'T op
				stack_expression.push_back(stackinput_E2);
				stack_expression.push_back(stackinput_T);
				stack_expression.push_back(stackinput_op);
				//退出此次循环
				continue;
			}
			else
			{
				if (waitanalys.word_value == ")") {
					//弹出
					stack_expression.pop_back();
					//退出此次循环
					continue;
				}
				else
				{
					if (waitanalys.word_value == ";") {
						stack_expression.pop_back();
						//退出此次循环
						continue;
					}
					else
					{
						//分析失败
						if (iftest_grammer)
						cout << "分析失败,原因:不符合语法规则" << endl;
						break;
					}

				}

			}

		}
		if (nowstcakchar.word_value == "T")
		{
			//		数字	标识符	op		(			)		#
			// T	数字	标识符			(E)	
			if (waitanalys.word_type == "digit") {
				//弹出
				stack_expression.pop_back();
				//压入 digit
				stack_expression.push_back(stackinput_digit);
				//退出此次循环
				continue;
			}
			else
			{
				if (waitanalys.word_type == "token") {
					//弹出
					stack_expression.pop_back();
					//压入 tokrn
					stack_expression.push_back(stackinput_token);
					//退出此次循环
					continue;
				}
				else
				{
					if (waitanalys.word_value == "(") {
						//弹出
						stack_expression.pop_back();
						//压入 )E(
						stack_expression.push_back(stackinput_rk);
						stack_expression.push_back(stackinput_E);
						stack_expression.push_back(stackinput_lk);
						//退出此次循环
						continue;
					}
					else
					{
						//分析失败
						if (iftest_grammer)
						cout << "分析失败,原因:不符合语法规则" << endl;
						break;
					}
				}
			}

		}
		if (nowstcakchar.word_value == "digit")
		{
			if (waitanalys.word_type == "digit")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "token")
		{
			if (waitanalys.word_type == "token")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "(")
		{
			if (waitanalys.word_value == "(")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == ")")
		{
			if (waitanalys.word_value == ")")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "op")
		{
			if (waitanalys.word_value == "+" || waitanalys.word_value == "-" || waitanalys.word_value == "*" || waitanalys.word_value == "/")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "=")
		{
			
			if (waitanalys.word_value == "=")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}
		}
		if (nowstcakchar.word_value == ";")
		{

			if (waitanalys.word_value == ";")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}
		}
		if (nowstcakchar.word_value == "keyword")
		{
			if (waitanalys.word_type == "keyword")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}




		if (iftest_grammer)
		cout << "分析失败,原因:无法对于待分析队列的首个字符进行分析" << endl;
		return false;
		break;
	}

	if (stack_expression.size() == 0)
	{
		if (iftest_grammer)
		cout << "分析成功:赋值语句" << endl;
		return true;
	}
	else
	{
		if (iftest_grammer)
		cout << "分析失败,原因:赋值语句" << endl;
		return false;
	}

}
//对于比较语句的语法分析
//
//B ->E 比较符号  E;
//E -> T E'
//E'-> op T E'
//E'-> 空
//T ->数字
//T ->标识符
//T ->(E)
//以下为FISRST集与FOLLOW集合的计算
//First(B)={数字，标识符，( }
//First（E）={数字，标识符，( }
//First（E'）={op，空}
//First（T）={（，数字，标识符 }
// 
//Follow(B)={#,} 
//Follw(E)={ ; , ) ,比较符号}
//Follw(E')={) , ;	,	比较符号}
//Follw(T)={op , ) , ;	，	比较符号 }
// 
//SELECT(B -> E 比较符号  E;)		={数字，标识符，( }
//SELECT(E -> T E')					={（，数字，标识符}
//SELECT(E'-> op T E')				={op}
//SELECT(E'-> 空)					={) , ;	,	比较符号}
//SELECT(T ->数字)					={数字}
//SELECT(T ->标识符)				={标识符}
//SELECT(T ->(E))					={(}
//预测分析表
//		保留字				数字		比较符号			标识符					op				(				)		 ;	 #
// B	E 比较符号  E;									 E 比较符号  E;							 E 比较符号  E;
// E	T E'												T E'									T E'
// E'									  空										opTE'			 空				        空
// T						数字							标识符									(E)	
//
void AnalyseCompare(vector<Word> Compare) {
	vector<Word> temporarysave;//保存待分析的句
	for (int j = 0; j < Compare.size(); j++)
	{
		temporarysave.push_back(Compare[j]);
	}
	//栈初始化
	stack_expression.clear();
	stack_expression.push_back(stackinput_B);
	int i = 0;//用来保存待分析语句中的位置
	while (stack_expression.size() != 0)
	{
		if (i > temporarysave.size())
		{
			cout << "分析失败,原因:i超出界限" << endl;
			break;
		}
		//取出栈顶的元素
		Word nowstcakchar = stack_expression[stack_expression.size() - 1];
		//找到待分析串的第一个字母
		Word waitanalys;
		if (i == temporarysave.size())
		{
			waitanalys.word_type = "empty";
			waitanalys.word_value = "#";
		}
		else
		{
			waitanalys.word_type = temporarysave[i].word_type;
			waitanalys.word_value = temporarysave[i].word_value;
		}

		
		cout << i << "\t" << "nowstcakchar:";
		for (int m = 0; m < stack_expression.size(); m++)
		{
			cout << stack_expression[m].word_value;
		}
		cout<< "\twaitanalys\t" << waitanalys.word_value << endl;

		if (nowstcakchar.word_value == "B") {
			//cout << nowstcakchar.word_value << endl;
			if (waitanalys.word_type == "keyword") {
				//E 比较符号  E;
				//弹出
				stack_expression.pop_back();
				//压入 
				stack_expression.push_back(stackinput_branch);
				stack_expression.push_back(stackinput_E);
				stack_expression.push_back(stackinput_compareop);
				stack_expression.push_back(stackinput_E);
				//退出此次循环
				continue;
			}
			else
			{
				if (waitanalys.word_type == "token") {
					//E 比较符号  E;
					//弹出
					stack_expression.pop_back();
					//压入 
					stack_expression.push_back(stackinput_branch);
					stack_expression.push_back(stackinput_E);
					stack_expression.push_back(stackinput_compareop);
					stack_expression.push_back(stackinput_E);
					//退出此次循环
					continue;
				}
				else
				{
					if (waitanalys.word_type == "(") {
						//E 比较符号  E;
						//弹出
						stack_expression.pop_back();
						//压入 
						stack_expression.push_back(stackinput_branch);
						stack_expression.push_back(stackinput_E);
						stack_expression.push_back(stackinput_compareop);
						stack_expression.push_back(stackinput_E);
						//退出此次循环
						continue;
					}
					else
					{
						//分析失败
						cout << "分析失败,原因:不符合语法规则" << endl;
						break;
					}
				}

			}



		}
		if (nowstcakchar.word_value == "E") {
			cout << nowstcakchar.word_value << endl;

			if (waitanalys.word_type == "digit") {
				//弹出
				stack_expression.pop_back();
				//压入 E'T
				stack_expression.push_back(stackinput_E2);
				stack_expression.push_back(stackinput_T);
				//退出此次循环
				continue;
			}
			else
			{
				//		数字	标识符	op		(			)		#
				// E	T E'	T E'			T E'
				if (waitanalys.word_type == "token") {
					//弹出
					stack_expression.pop_back();
					//压入 E'T
					stack_expression.push_back(stackinput_E2);
					stack_expression.push_back(stackinput_T);
					//退出此次循环
					continue;
				}
				else
				{
					if (waitanalys.word_value == "(") {
						//弹出
						stack_expression.pop_back();
						//压入 E'T
						stack_expression.push_back(stackinput_E2);
						stack_expression.push_back(stackinput_T);
						//退出此次循环
						continue;
					}
					else
					{
						//分析失败
						cout << "分析失败,原因:不符合语法规则" << endl;
						break;
					}

				}

			}



		}
		if (nowstcakchar.word_value == "E2")
		{
			cout << nowstcakchar.word_value << endl;
			if (waitanalys.word_value == "+" || waitanalys.word_value == "-" || waitanalys.word_value == "*" || waitanalys.word_value == "/") {
				//弹出
				stack_expression.pop_back();
				//压入 E'T op
				stack_expression.push_back(stackinput_E2);
				stack_expression.push_back(stackinput_T);
				stack_expression.push_back(stackinput_op);
				//退出此次循环
				continue;
			}
			else
			{
				if (waitanalys.word_value == ")") {
					//弹出
					stack_expression.pop_back();
					//退出此次循环
					continue;
				}
				else
				{
					if (waitanalys.word_value == ";") {
						stack_expression.pop_back();
						//退出此次循环
						continue;
					}
					else
					{
						if (waitanalys.word_value == ">" || waitanalys.word_value == "<" || waitanalys.word_value == ">=" || waitanalys.word_value == "<=" || waitanalys.word_value == "==") {
							stack_expression.pop_back();
							//退出此次循环
							continue;
						}
						else
						{
							//分析失败
							cout << "分析失败,原因:不符合语法规则" << endl;
							break;
						}
					}

				}

			}

		}
		if (nowstcakchar.word_value == "T")
		{
			//		数字	标识符	op		(			)		#
			// T	数字	标识符			(E)	
			if (waitanalys.word_type == "digit") {
				//弹出
				stack_expression.pop_back();
				//压入 digit
				stack_expression.push_back(stackinput_digit);
				//退出此次循环
				continue;
			}
			else
			{
				if (waitanalys.word_type == "token") {
					//弹出
					stack_expression.pop_back();
					//压入 tokrn
					stack_expression.push_back(stackinput_token);
					//退出此次循环
					continue;
				}
				else
				{
					if (waitanalys.word_value == "(") {
						//弹出
						stack_expression.pop_back();
						//压入 )E(
						stack_expression.push_back(stackinput_rk);
						stack_expression.push_back(stackinput_E);
						stack_expression.push_back(stackinput_lk);
						//退出此次循环
						continue;
					}
					else
					{
						//分析失败
						cout << "分析失败,原因:不符合语法规则" << endl;
						break;
					}
				}
			}

		}
		if (nowstcakchar.word_value == "digit")
		{
			if (waitanalys.word_type == "digit")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "token")
		{
			if (waitanalys.word_type == "token")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "(")
		{
			if (waitanalys.word_value == "(")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == ")")
		{
			if (waitanalys.word_value == ")")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "op")
		{
			if (waitanalys.word_value == "+" || waitanalys.word_value == "-" || waitanalys.word_value == "*" || waitanalys.word_value == "/")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "=")
		{

			if (waitanalys.word_value == "=")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}
		}
		if (nowstcakchar.word_value == ";")
		{

			if (waitanalys.word_value == ";")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}
		}
		if (nowstcakchar.word_value == "keyword")
		{
			if (waitanalys.word_type == "keyword")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "compareop")
		{
			if (waitanalys.word_value == ">" || waitanalys.word_value == "<" || waitanalys.word_value == ">=" || waitanalys.word_value == "<=" || waitanalys.word_value == "==")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		cout << "分析失败,原因:无法对于待分析队列的首个字符进行分析" << endl;
		break;
	}

	if (stack_expression.size() == 0)
	{
		cout << "分析成功:比较语句" << endl;
	}



}
//对于for语句的语法分析
// 
//A-> for ( L ; M ; N) { O } 
//L->标识符 = E
//L-> 保留字 标识符 = E
//L->空
//M->E 比较符号  E
//N->标识符 = E
//N->空
//O->L;O
//O->空
//E -> T E'
//E'-> op T E'
//E'-> 空
//T ->数字
//T ->标识符
//T ->(E)
//以下为FISRST集与FOLLOW集合的计算
//First(A)={for }
//First(L)={标识符，保留字，空 }
//First(M)={数字，标识符，( }
//First(N)={标识符，空}
//First(O)={标识符，保留字，空 }
//First(E)={数字，标识符，( }
//First(E')={op，空}
//First(T)={（，数字，标识符 }
// 
//Follow(A)		={#,	}
//Follow(L)		={";",	}
//Follow(M)		={";",	}
//Follow(N)		={")",	}
//Follow(O)		={"}",	}
//Follw(E)		={比较符号,")",";"}
//Follw(E')		={比较符号,")",";"}
//Follw(T)		={op,比较符号,")"}
// 
//SELECT(A-> for ( L ; M ; N) { O } ) ={for}
//SELECT(L->标识符 = E)				={标识符}
//SELECT(L-> 保留字 标识符 = E)		={保留字}
//SELECT(L->空)						={";"}
//SELECT(M->E 比较符号  E)			={数字，标识符，(}
//SELECT(N->标识符 = E)				={标识符}
//SELECT(N->空)						={")"}
//SELECT(O->L;O)					={标识符，保留字，";"}
//SELECT(O->空)						={"}"}
//SELECT(E -> T E')					={（，数字，标识符}
//SELECT(E'-> op T E')				={op}
//SELECT(E'-> 空)					={) , ;	,	比较符号}
//SELECT(T ->数字)					={数字}
//SELECT(T ->标识符)				={标识符}
//SELECT(T ->(E))					={(}
//预测分析表
//		保留字				数字		比较符号			标识符					op				(				)		 ;	   {		}        for				#
// A																																			for ( L ; M ; N) { O }
// L	保留字 标识符 = E									标识符 = E														 空
// M					E 比较符号  E					E 比较符号  E							E 比较符号  E
// N														标识符 = E												空
// O	L;O													L;O																 L;O		    空
// E						T E'						   T E'									T E'
// E'									  空										opTE'			 空				        空
// T						数字							标识符									(E)	
//
bool AnalyseForSentence(vector<Word> forsentence)
{
	vector<Word> temporarysave;//保存待分析的句
	for (int j = 0; j < forsentence.size(); j++)
	{
		temporarysave.push_back(forsentence[j]);
	}
	//栈初始化
	stack_expression.clear();
	stack_expression.push_back(stackinput_A);
	int i = 0;//用来保存待分析语句中的位置
	while (stack_expression.size() != 0)
	{
		if (i > temporarysave.size())
		{
			cout << "分析失败,原因:i超出界限" << endl;
			return false;
			break;
		}
		//取出栈顶的元素
		Word nowstcakchar = stack_expression[stack_expression.size() - 1];
		//找到待分析串的第一个字母
		Word waitanalys;
		if (i == temporarysave.size())
		{
			waitanalys.word_type = "empty";
			waitanalys.word_value = "#";
		}
		else
		{
			waitanalys.word_type = temporarysave[i].word_type;
			waitanalys.word_value = temporarysave[i].word_value;
		}

		if (iftest_grammer) {
		
			cout << i << "\t" << "nowstcakchar:";
			for (int m = 0; m < stack_expression.size(); m++)
			{
				cout << stack_expression[m].word_value;
			}
			cout << "\twaitanalys\t" << waitanalys.word_value << endl;
		
		}

		

		if (nowstcakchar.word_value == "A") {
			//cout << nowstcakchar.word_value << endl;
			if (waitanalys.word_value == "for") {
				//for ( L ; M ; N) { O }
				//弹出
				stack_expression.pop_back();
				//压入 
				stack_expression.push_back(stackinput_bigrk);
				stack_expression.push_back(stackinput_O);
				stack_expression.push_back(stackinput_biglk);
				stack_expression.push_back(stackinput_rk);
				stack_expression.push_back(stackinput_N);
				stack_expression.push_back(stackinput_branch);
				stack_expression.push_back(stackinput_M);
				stack_expression.push_back(stackinput_branch);
				stack_expression.push_back(stackinput_L);
				stack_expression.push_back(stackinput_lk);
				stack_expression.push_back(stackinput_for);			
				//退出此次循环
				continue;
			}
			else{
				//分析失败
				if (iftest_grammer)
				cout << "分析失败,原因:不符合语法规则" << endl;
				break;
			}
		}
		if (nowstcakchar.word_value == "L") {
			//cout << nowstcakchar.word_value << endl;
			if (waitanalys.word_type == "keyword") {
				//保留字 标识符 = E
				//弹出
				stack_expression.pop_back();
				//压入 
				stack_expression.push_back(stackinput_E);
				stack_expression.push_back(stackinput_equal);
				stack_expression.push_back(stackinput_token);
				stack_expression.push_back(stackinput_keyword);
				//退出此次循环
				continue;
			}
			else
			{
				if (waitanalys.word_type == "token") {
					//标识符 = E
					//弹出
					stack_expression.pop_back();
					//压入 
					stack_expression.push_back(stackinput_E);
					stack_expression.push_back(stackinput_equal);
					stack_expression.push_back(stackinput_token);
					//退出此次循环
					continue;
				}
				else
				{
					if (waitanalys.word_type == ";") {
						// 空
						//弹出
						stack_expression.pop_back();
						//退出此次循环
						continue;
					}
					else
					{
						//分析失败
						cout << "分析失败,原因:不符合语法规则" << endl;
						break;
					}
				}

			}



		}
		if (nowstcakchar.word_value == "M") {
			if (waitanalys.word_type == "keyword") {
				//E 比较符号  E
				//弹出
				stack_expression.pop_back();
				//压入 
				stack_expression.push_back(stackinput_E);
				stack_expression.push_back(stackinput_compareop);
				stack_expression.push_back(stackinput_E);
				//退出此次循环
				continue;
			}
			else
			{
				if (waitanalys.word_type == "token") {
					//E 比较符号  E
					//弹出
					stack_expression.pop_back();
					//压入 
					stack_expression.push_back(stackinput_E);
					stack_expression.push_back(stackinput_compareop);
					stack_expression.push_back(stackinput_E);
					//退出此次循环
					continue;
				}
				else
				{
					if (waitanalys.word_type == "(") {
						//E 比较符号  E
						//弹出
						stack_expression.pop_back();
						//压入 
						stack_expression.push_back(stackinput_E);
						stack_expression.push_back(stackinput_compareop);
						stack_expression.push_back(stackinput_E);
						//退出此次循环
						continue;
					}
					else
					{
						//分析失败
						cout << "分析失败,原因:不符合语法规则" << endl;
						break;
					}
				}

			}



		}
		if (nowstcakchar.word_value == "N") {
				if (waitanalys.word_type == "token") {
					//标识符 = E
					//弹出
					stack_expression.pop_back();
					//压入 
					stack_expression.push_back(stackinput_E);
					stack_expression.push_back(stackinput_equal);
					stack_expression.push_back(stackinput_token);
					//退出此次循环
					continue;
				}
				else
				{
					if (waitanalys.word_type == ")") {
						// 空
						//弹出
						stack_expression.pop_back();
						//退出此次循环
						continue;
					}
					else
					{
						//分析失败
						cout << "分析失败,原因:不符合语法规则" << endl;
						break;
					}
				}
		}
		if (nowstcakchar.word_value == "O") {
			if (waitanalys.word_type == "keyword") {
				//L;O
				//弹出
				stack_expression.pop_back();
				//压入 
				stack_expression.push_back(stackinput_O);
				stack_expression.push_back(stackinput_branch);
				stack_expression.push_back(stackinput_L);
				//退出此次循环
				continue;
			}
			else
			{
				if (waitanalys.word_type == "token") {
					//L;O
					//弹出
					stack_expression.pop_back();
					//压入 
					stack_expression.push_back(stackinput_O);
					stack_expression.push_back(stackinput_branch);
					stack_expression.push_back(stackinput_L);
					//退出此次循环
					continue;
				}
				else
				{
					if (waitanalys.word_value == ";") {
						//L;O
						//弹出
						stack_expression.pop_back();
						//压入 
						stack_expression.push_back(stackinput_O);
						stack_expression.push_back(stackinput_branch);
						stack_expression.push_back(stackinput_L);
						//退出此次循环
						continue;
					}
					else
					{
						if (waitanalys.word_value == "}") {
							//空
							//弹出
							stack_expression.pop_back();
							//退出此次循环
							continue;
						}
						else
						{
							//分析失败
							cout << "分析失败,原因:不符合语法规则" << endl;
							break;
						}
					}
				}
			}
		}

		if (nowstcakchar.word_value == "E") {
			if (waitanalys.word_type == "digit") {
				//弹出
				stack_expression.pop_back();
				//压入 E'T
				stack_expression.push_back(stackinput_E2);
				stack_expression.push_back(stackinput_T);
				//退出此次循环
				continue;
			}
			else
			{
				//		数字	标识符	op		(			)		#
				// E	T E'	T E'			T E'
				if (waitanalys.word_type == "token") {
					//弹出
					stack_expression.pop_back();
					//压入 E'T
					stack_expression.push_back(stackinput_E2);
					stack_expression.push_back(stackinput_T);
					//退出此次循环
					continue;
				}
				else
				{
					if (waitanalys.word_value == "(") {
						//弹出
						stack_expression.pop_back();
						//压入 E'T
						stack_expression.push_back(stackinput_E2);
						stack_expression.push_back(stackinput_T);
						//退出此次循环
						continue;
					}
					else
					{
						//分析失败
						cout << "分析失败,原因:不符合语法规则" << endl;
						break;
					}

				}

			}



		}
		if (nowstcakchar.word_value == "E2")
		{
			if (iftest_grammer)
			cout << nowstcakchar.word_value << endl;
			if (waitanalys.word_value == "+" || waitanalys.word_value == "-" || waitanalys.word_value == "*" || waitanalys.word_value == "/") {
				//弹出
				stack_expression.pop_back();
				//压入 E'T op
				stack_expression.push_back(stackinput_E2);
				stack_expression.push_back(stackinput_T);
				stack_expression.push_back(stackinput_op);
				//退出此次循环
				continue;
			}
			else
			{
				if (waitanalys.word_value == ")") {
					//弹出
					stack_expression.pop_back();
					//退出此次循环
					continue;
				}
				else
				{
					if (waitanalys.word_value == ";") {
						stack_expression.pop_back();
						//退出此次循环
						continue;
					}
					else
					{
						if (waitanalys.word_value == ">" || waitanalys.word_value == "<" || waitanalys.word_value == ">=" || waitanalys.word_value == "<=" || waitanalys.word_value == "==") {
							stack_expression.pop_back();
							//退出此次循环
							continue;
						}
						else
						{
							//分析失败
							cout << "分析失败,原因:不符合语法规则" << endl;
							break;
						}
					}

				}

			}

		}
		if (nowstcakchar.word_value == "T")
		{
			//		数字	标识符	op		(			)		#
			// T	数字	标识符			(E)	
			if (waitanalys.word_type == "digit") {
				//弹出
				stack_expression.pop_back();
				//压入 digit
				stack_expression.push_back(stackinput_digit);
				//退出此次循环
				continue;
			}
			else
			{
				if (waitanalys.word_type == "token") {
					//弹出
					stack_expression.pop_back();
					//压入 tokrn
					stack_expression.push_back(stackinput_token);
					//退出此次循环
					continue;
				}
				else
				{
					if (waitanalys.word_value == "(") {
						//弹出
						stack_expression.pop_back();
						//压入 )E(
						stack_expression.push_back(stackinput_rk);
						stack_expression.push_back(stackinput_E);
						stack_expression.push_back(stackinput_lk);
						//退出此次循环
						continue;
					}
					else
					{
						//分析失败
						cout << "分析失败,原因:不符合语法规则" << endl;
						break;
					}
				}
			}

		}
		if (nowstcakchar.word_value == "digit")
		{
			if (waitanalys.word_type == "digit")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "token")
		{
			if (waitanalys.word_type == "token")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "(")
		{
			if (waitanalys.word_value == "(")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == ")")
		{
			if (waitanalys.word_value == ")")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "op")
		{
			if (waitanalys.word_value == "+" || waitanalys.word_value == "-" || waitanalys.word_value == "*" || waitanalys.word_value == "/")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "=")
		{

			if (waitanalys.word_value == "=")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}
		}
		if (nowstcakchar.word_value == ";")
		{

			if (waitanalys.word_value == ";")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}
		}
		if (nowstcakchar.word_value == "keyword")
		{
			if (waitanalys.word_type == "keyword")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "compareop")
		{
			if (waitanalys.word_value == ">" || waitanalys.word_value == "<" || waitanalys.word_value == ">=" || waitanalys.word_value == "<=" || waitanalys.word_value == "==")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}

		if (nowstcakchar.word_value == "{")
		{
			if (waitanalys.word_value == "{")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "}")
		{
			if (waitanalys.word_value == "}")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "for")
		{
			if (waitanalys.word_value == "for")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}


		if (iftest_grammer)
		cout << "分析失败,原因:无法对于待分析队列的首个字符进行分析" << endl;
		return false;
		break;
	}

	if (stack_expression.size() == 0)
	{
		if (iftest_grammer)
		cout << "分析成功:for语句" << endl;
		return true;
	}
	else
	{
		return false;
	}

}
//对于输出语句的语法分析
//R-> cout M ;
//M-> 空
//M-> <<M' 
//M'-> E M
//M'-> 字符串 M
//M'-> endl M
//E -> T E'
//E'-> op T E'
//E'-> 空
//T ->数字
//T ->标识符
//T ->(E)
//First(R)={cout}
//First(M)={ << , 空}
//First(M')={数字，标识符，( ,字符串,endl}
//First(E)={数字，标识符，( }
//First(E')={op，空}
//First(T)= {数字，标识符，(  }
//Follow(R)		={# }
//Follow(M)		={;}
//Follow(M')	={;}
//Follw(E)		={")", << , ; }
//Follw(E')		={")", << , ; }
//Follw(T)		={op,")", << , ; }
//
//SECLECT(R-> cout M ;)		={cout}
//SECLECT(M-> 空)			={;}
//SECLECT(M-> <<M')			={<<}
//SECLECT(M'-> E M)			={数字，标识符，(}
//SECLECT(M'-> 字符串 M)	={字符串}
//SECLECT(M'-> endl M)		={endl}
//SECLECT(E -> T E')		={数字，标识符，(  }
//SECLECT(E'-> op T E')		={op}
//SECLECT(E'-> 空)			={")", << , ; }
//SECLECT(T ->数字)			={数字}
//SECLECT(T ->标识符)		={标识符}
//SECLECT(T ->(E))			={(E)}
//           标识符		 字符串		数字		cout			endl			<<			op		(			)		;		#
// R											cout M ;
// M																			<<M'									空
// M'		 E M		字符串M	    E M							endl M								E M
// E		 T E'					T E'															T E'
// E'																			空			opTE'				空		空
// T		标识符					数字																(E)
bool AnalyseOutputsentence(vector<Word> outputsentence) 
{
	vector<Word> temporarysave;//保存待分析的句
	for (int j = 0; j < outputsentence.size(); j++)
	{
		temporarysave.push_back(outputsentence[j]);
	}
	//栈初始化
	stack_expression.clear();
	stack_expression.push_back(stackinput_R);
	int i = 0;//用来保存待分析语句中的位置
	while (stack_expression.size() != 0)
	{
		if (i > temporarysave.size())
		{
			cout << "分析失败,原因:i超出界限" << endl;
			break;
		}
		//取出栈顶的元素
		Word nowstcakchar = stack_expression[stack_expression.size() - 1];
		//找到待分析串的第一个字母
		Word waitanalys;
		if (i == temporarysave.size())
		{
			waitanalys.word_type = "empty";
			waitanalys.word_value = "#";
		}
		else
		{
			waitanalys.word_type = temporarysave[i].word_type;
			waitanalys.word_value = temporarysave[i].word_value;
		}


		if (iftest_grammer)
		{
			cout << i << "\t" << "nowstcakchar:";
			for (int m = 0; m < stack_expression.size(); m++)
			{
				cout << stack_expression[m].word_value;
			}
			cout << "\twaitanalys\t" << waitanalys.word_value << endl;
		}




	

		if (nowstcakchar.word_value == "R") {
			if (waitanalys.word_value == "cout") {
				//cout M ;
				//弹出
				stack_expression.pop_back();
				//压入 
				stack_expression.push_back(stackinput_branch);
				stack_expression.push_back(stackinput_M);;
				stack_expression.push_back(stackinput_cout);
				//退出此次循环
				continue;
			}
			else {
				//分析失败
				if (iftest_grammer)
				cout << "分析失败,原因:不符合语法规则" << endl;
				break;
			}
		}
		if (nowstcakchar.word_value == "M") {
		if (waitanalys.word_value == "<<") {
				//	<<M'
				//弹出
				stack_expression.pop_back();
				//压入 
				stack_expression.push_back(stackinput_M2);
				stack_expression.push_back(stackinput_output);
				//退出此次循环
				continue;
			}
			else
			{
				if (waitanalys.word_value == ";") {
					//	空
					//弹出
					stack_expression.pop_back();
					//退出此次循环
					continue;
				}
				else
				{
					//分析失败
					if (iftest_grammer)
					cout << "分析失败,原因:不符合语法规则" << endl;
					break;
				}

			}



		}
		if (nowstcakchar.word_value == "M2") {
			if (waitanalys.word_type == "token") {
				// E M	
				//弹出
				stack_expression.pop_back();
				//压入 
				stack_expression.push_back(stackinput_M);
				stack_expression.push_back(stackinput_E);
				//退出此次循环
				continue;
			}
			else{
				if (waitanalys.word_type == "string") {
					// 字符串M	
					//弹出
					stack_expression.pop_back();
					//压入 
					stack_expression.push_back(stackinput_M);
					stack_expression.push_back(stackinput_string);
					//退出此次循环
					continue;
				}
				else{
					if (waitanalys.word_type == "digit") {
						//  E M		
						//弹出
						stack_expression.pop_back();
						//压入 
						stack_expression.push_back(stackinput_M);
						stack_expression.push_back(stackinput_E);
						//退出此次循环
						continue;
					}
					else{
						if (waitanalys.word_value == "endl") {
							// endl M	
							//弹出
							stack_expression.pop_back();
							//压入 
							stack_expression.push_back(stackinput_M);
							stack_expression.push_back(stackinput_endl);
							//退出此次循环
							continue;
						}
						else{
							if (waitanalys.word_value == "(") {
								// E M	
								//弹出
								stack_expression.pop_back();
								//压入 
								stack_expression.push_back(stackinput_M);
								stack_expression.push_back(stackinput_E);
								//退出此次循环
								continue;
							}
							else {
								//分析失败
								if (iftest_grammer)
								cout << "分析失败,原因:不符合语法规则" << endl;
								break;
							}
						}
					}
				}
			}
		}
		if (nowstcakchar.word_value == "E") {
			if (waitanalys.word_type == "digit") {
				//弹出
				stack_expression.pop_back();
				//压入 T E'
				stack_expression.push_back(stackinput_E2);
				stack_expression.push_back(stackinput_T);
				//退出此次循环
				continue;
			}
			else{
				if (waitanalys.word_type == "token") {
					//弹出
					stack_expression.pop_back();
					//压入 E'T
					stack_expression.push_back(stackinput_E2);
					stack_expression.push_back(stackinput_T);
					//退出此次循环
					continue;
				}
				else
				{
					if (waitanalys.word_value == "(") {
						//弹出
						stack_expression.pop_back();
						//压入 E'T
						stack_expression.push_back(stackinput_E2);
						stack_expression.push_back(stackinput_T);
						//退出此次循环
						continue;
					}
					else
					{
						//分析失败
						if (iftest_grammer)
						cout << "分析失败,原因:不符合语法规则" << endl;
						break;
					}

				}

			}



		}
		if (nowstcakchar.word_value == "E2")
		{
			if (waitanalys.word_value == "+" || waitanalys.word_value == "-" || waitanalys.word_value == "*" || waitanalys.word_value == "/") {
				//弹出
				stack_expression.pop_back();
				//压入 E'T op
				stack_expression.push_back(stackinput_E2);
				stack_expression.push_back(stackinput_T);
				stack_expression.push_back(stackinput_op);
				//退出此次循环
				continue;
			}
			else{
				if (waitanalys.word_value == ")") {
					//弹出
					stack_expression.pop_back();
					//退出此次循环
					continue;
				}
				else{
					if (waitanalys.word_value == ";") {
						stack_expression.pop_back();
						//退出此次循环
						continue;
					}
					else{
						if (waitanalys.word_value == "<<") {
							stack_expression.pop_back();
							//退出此次循环
							continue;
						}
						else
						{
							//分析失败
							if (iftest_grammer)
							cout << "分析失败,原因:不符合语法规则" << endl;
							break;
						}
					}

				}

			}

		}
		if (nowstcakchar.word_value == "T")
		{
			if (waitanalys.word_type == "digit") {
				//弹出
				stack_expression.pop_back();
				//压入 digit
				stack_expression.push_back(stackinput_digit);
				//退出此次循环
				continue;
			}
			else{
				if (waitanalys.word_type == "token") {
					//弹出
					stack_expression.pop_back();
					//压入 tokrn
					stack_expression.push_back(stackinput_token);
					//退出此次循环
					continue;
				}
				else{
					if (waitanalys.word_value == "(") {
						//弹出
						stack_expression.pop_back();
						//压入 )E(
						stack_expression.push_back(stackinput_rk);
						stack_expression.push_back(stackinput_E);
						stack_expression.push_back(stackinput_lk);
						//退出此次循环
						continue;
					}
					else{
						//分析失败
						if (iftest_grammer)
						cout << "分析失败,原因:不符合语法规则" << endl;
						break;
					}
				}
			}

		}

		if (nowstcakchar.word_value == "digit")
		{
			if (waitanalys.word_type == "digit")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "token")
		{
			if (waitanalys.word_type == "token")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "(")
		{
			if (waitanalys.word_value == "(")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == ")")
		{
			if (waitanalys.word_value == ")")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "op")
		{
			if (waitanalys.word_value == "+" || waitanalys.word_value == "-" || waitanalys.word_value == "*" || waitanalys.word_value == "/")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "=")
		{

			if (waitanalys.word_value == "=")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}
		}
		if (nowstcakchar.word_value == ";")
		{

			if (waitanalys.word_value == ";")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}
		}
		if (nowstcakchar.word_value == "keyword")
		{
			if (waitanalys.word_type == "keyword")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "cout")
		{
			if (waitanalys.word_value == "cout")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "endl")
		{
			if (waitanalys.word_value == "endl")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "<<")
		{
			if (waitanalys.word_value == "<<")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "string")
		{
			if (waitanalys.word_type == "string")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}


		if (iftest_grammer)
		cout << "分析失败,原因:无法对于待分析队列的首个字符进行分析" << endl;
		break;
	}

	if (stack_expression.size() == 0)
	{
		if (iftest_grammer)
		cout << "分析成功:输出语句" << endl;
		return true;
	}
	else
	{
		return false;
	}

}
//对于定义语句的语法分析
//
//C -> 保留字 标识符 ;
bool AnalyseDefine(vector<Word> define) {
	vector<Word> temporarysave;//保存待分析的句
	for (int j = 0; j < define.size(); j++)
	{
		temporarysave.push_back(define[j]);
	}
	//栈初始化
	stack_expression.clear();
	stack_expression.push_back(stackinput_C);
	int i = 0;//用来保存待分析语句中的位置
	while (stack_expression.size() != 0)
	{
		if (i > temporarysave.size())
		{
			cout << "分析失败,原因:i超出界限" << endl;
			break;
		}
		//取出栈顶的元素
		Word nowstcakchar = stack_expression[stack_expression.size() - 1];
		//找到待分析串的第一个字母
		Word waitanalys;
		if (i == temporarysave.size())
		{
			waitanalys.word_type = "empty";
			waitanalys.word_value = "#";
		}
		else
		{
			waitanalys.word_type = temporarysave[i].word_type;
			waitanalys.word_value = temporarysave[i].word_value;
		}

		if (iftest_grammer)
		cout << i << "\t" << "nowstcakchar:" << nowstcakchar.word_value << "\twaitanalys\t" << waitanalys.word_value << endl;
		if (nowstcakchar.word_value == "C") {
			if (waitanalys.word_type == "keyword") {
				//保留字 标识符 ;
				//弹出
				stack_expression.pop_back();
				//压入 
				stack_expression.push_back(stackinput_branch);
				stack_expression.push_back(stackinput_token);
				stack_expression.push_back(stackinput_keyword);
				//退出此次循环
				continue;
			}
			else
			{
				//分析失败
				cout << "分析失败,原因:不符合语法规则" << endl;
				break;
			}
		}

		if (nowstcakchar.word_value == "digit")
		{
			if (waitanalys.word_type == "digit")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "token")
		{
			if (waitanalys.word_type == "token")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "(")
		{
			if (waitanalys.word_value == "(")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == ")")
		{
			if (waitanalys.word_value == ")")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "op")
		{
			if (waitanalys.word_value == "+" || waitanalys.word_value == "-" || waitanalys.word_value == "*" || waitanalys.word_value == "/")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}
		if (nowstcakchar.word_value == "=")
		{

			if (waitanalys.word_value == "=")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}
		}
		if (nowstcakchar.word_value == ";")
		{

			if (waitanalys.word_value == ";")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}
		}
		if (nowstcakchar.word_value == "keyword")
		{
			if (waitanalys.word_type == "keyword")
			{
				//弹出
				stack_expression.pop_back();
				i++;
				//退出此次循环
				continue;
			}

		}



		cout << "分析失败,原因:无法对于待分析队列的首个字符进行分析" << endl;
		break;
	}

	if (stack_expression.size() == 0)
	{
		if(iftest_grammer)
		cout << "分析成功:初始化定义语句" << endl;
		return true;
	}
	else {
		return false;
	}


}


bool AnalyseAllSentence()
{
	for (int i = 0;i< sentence_vector.size();i++)
	{
		if (AnalyseAssignment(sentence_vector[i]) == true)
		{
			cout << "语句" << i << "为赋值语句或者初始化赋值语句"<<endl;
			continue;
		}
		if (AnalyseForSentence(sentence_vector[i]) == true)
		{
			cout << "语句" << i << "为for语句" << endl;
			continue;
		}
		if (AnalyseOutputsentence(sentence_vector[i]) == true)
		{
			cout << "语句" << i << "为cout语句" << endl;
			continue;
		}
		if (AnalyseDefine(sentence_vector[i]) == true)
		{
			cout << "语句" << i << "为定义变量语句" << endl;
			continue;
		}


		cout << "语句" << i << "语法分析错误" << endl;
		return false;



	}
	return true;

}











