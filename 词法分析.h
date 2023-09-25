#pragma once

#include <iostream>
#include "常量定义.h"
#include "单词类型判断.h"

//分析当前字符属于哪一类
int Distribute(const char ch);
bool IsOpreator(const string word);
//using namespace std;

// 函数说明:总控程序
//当数字打头却不全部是数字时显示错误
//当注释符号"//"不在开头时会出现无法识别的错误

void Controller()
{
	int flag;
	int flag_dian;
	for (int begin = 0; begin < code_vector.size();)
	{
		string word = "";
		int end = begin + 1;
		int type = Distribute(code_vector[begin]);

		word += code_vector[begin];

		//增加一个判断为形式如“ajh dsioj”的单词类型
		if (code_vector[begin] == '\"')
		{
			while (code_vector[end] != '\"'&& code_vector[end] != '\n')
			{
				word += code_vector[end];
				end++;
			}

			word += code_vector[end];
			if (code_vector[end] == '\"')
			{
				StringAnalysis(word);

			}
			else
			{
				ErrorAnalysis(word);
			}
			end++;
			begin = end;

			continue;
		}



		if (type == LETTER)
		{
			for (; end < code_vector.size(); ++end)
			{
				if (Distribute(code_vector[end]) != BOUNDARY && Distribute(code_vector[end]) != OPERATOR)
				{
					word += code_vector[end];
				}
				else
				{
					break;
				}
			}
			LetterAnalysis(word);//标识符或关键字
		}
		else if (type == DIGIT)
		{
			//for循环当为数字或者字母的时候则继续读取————>改为当下一位不是分隔符时则继续读取


			flag = 1;
			flag_dian = 0;
			for (; end < code_vector.size(); ++end)
			{
				if (Distribute(code_vector[end]) == DIGIT)
				{
					/*word += code_vector[end];*/
				}
				else if (code_vector[end] == '.')
				{
					flag_dian++;
				}
				else
				{
					if (Distribute(code_vector[end]) != BOUNDARY && Distribute(code_vector[end]) != OPERATOR)
					{
						flag = 0;
					}
				}

				if (flag_dian > 1)
				{
					flag = 0;
				}

				//当是界符或者运算符的时候停止计入
				if (Distribute(code_vector[end]) == BOUNDARY || Distribute(code_vector[end]) == OPERATOR)
				{
					break;
				}
				else
				{
					word += code_vector[end];
				}

			}

		/*	cout << word << '\t' << flag << endl;*/
			if (flag == 1)
			{
				DigitAnalysis(word);//无符号数
			}
			else
			{
				ErrorAnalysis(word);//错误输入处理
			}
		}
		else if (type == BOUNDARY)
		{
			BoundaryAnalysis(word);
		}
		else
		{
			for (; end < code_vector.size(); ++end)
			{
				//当下一位不是数字、界符、单词的时候继续判断是否为多为操作符号
				if (Distribute(code_vector[end]) != DIGIT && Distribute(code_vector[end]) != LETTER && Distribute(code_vector[end]) != BOUNDARY)
				{
					//一直判断直到最后一位为等号
					if (code_vector[end] != '=')
						word += code_vector[end];
					else
					{//当为等号的双位符号时
						word += code_vector[end];
						if (IsOpreator(word))
						{ //是操作符则记录结束
							++end;
							break;
						}
						else
						{
							word = word.substr(0, word.length() - 1);
							break;
						}
					}
				}
				else
				{
					break;
				}
			}
			OperatorAnalysis(word);
		}


		begin = end;
	}
}

int Distribute(const char ch)
{
	char c_tmp[] = { ch,'\0' };
	string ch_tmp = c_tmp;

	//判断是否是字母
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_')
		return LETTER;

	//判断是否为数字
	if (ch >= '0' && ch <= '9')
		return DIGIT;

	//判断是否为运算符
	for (const string str : operator_vector)
	{
		if (str == ch_tmp)
			return OPERATOR;
	}

	//判断是否为界符
	for (const string str : boundary_vector)
	{
		if (str == ch_tmp)
			return BOUNDARY;
	}
}

//判断当前字符串是否是运算符
bool IsOpreator(const string word)
{
	for (const string str : operator_vector)
	{
		if (str == word)
			return true;
	}
	return false;
}
