#pragma once
#include <iostream>
using namespace std;
#include"常量定义.h"
#include <fstream>
#include <vector>
#include <string>

//此函数将中缀表达式转化为后缀表达式
void Makepostfixexpression(vector<Word> expression) {

	bool iftest = false;
	//bool iftest = true;
	vector<Word> temporarysave;//保存待分析的句
	for (int j = 0; j < expression.size(); j++)
	{
		temporarysave.push_back(expression[j]);
	}
	//后缀表达式栈初始化

	if (iftest)
	{
		cout << "需要转化的式子为:";
		for (int i = 0; i < temporarysave.size(); i++) {
			cout << temporarysave[i].word_value ;
		}
		cout << endl;
	}


	stack_expression.clear();
	postfixexpression_vector.clear();
	vector<Word> op;      //[作用]：存储运算符的栈
	op.clear();
	int i = 0;
	while (i < temporarysave.size()) {
		if (iftest) {
			cout << "当前值为:" << temporarysave[i].word_value;
			//输出字母栈的值
			for (int i = 0; i < postfixexpression_vector.size(); i++) {
				cout << postfixexpression_vector[i].word_value << '\t';
			}
			cout << "符号堆栈为：\t";
			for (int i = 0; i < op.size(); i++) {
				cout << op[i].word_value << '\t';
			}
			cout << endl;
		}

		if (temporarysave[i].word_type == "digit")
		{
			postfixexpression_vector.push_back(temporarysave[i]);
			i++;
			continue;
		}
		if (temporarysave[i].word_type == "token")
		{
			//在这里查找时候有先前定义过
			postfixexpression_vector.push_back(temporarysave[i]);
			i++;
			continue;
		}
		if (temporarysave[i].word_value == "(")
		{
			op.push_back(temporarysave[i]);
			i++;
			continue;
		}
		if (temporarysave[i].word_value == ")")
		{
//将左括号之前的操作符号移除操作堆栈
			if (op.size() != 0)
			{
				while (op[op.size() - 1].word_value != "(")
				{
					postfixexpression_vector.push_back(op[op.size() - 1]);
					op.pop_back();
					if(op.size()==0)
					{
						break;
					}
				}
				
			}
		/*	if (op.size() != 0)
			{*/
				op.pop_back();
			/*}*/
			i++;
			continue;
		}
		if (temporarysave[i].word_value == "+"|| temporarysave[i].word_value == "-")
		{
			//将操作符号栈的非 ( 和 空 压入字符栈

			while (op.size()!=0&&op[op.size()-1].word_value!="(")
			{
				postfixexpression_vector.push_back(op[op.size() - 1]);
				op.pop_back();
			}
			op.push_back(temporarysave[i]);
			i++;
			continue;
		}
		if (temporarysave[i].word_value == "*" || temporarysave[i].word_value == "/")
		{
			//将操作符号栈的* 和 / 压入字符栈
		/*	while (stack[top] == '*' || stack[top] == '/') {
				ex[t] = stack[top];
				top--;
				t++;
			}
			top++;
			stack[top] = ch;*/
			if (op.size() != 0) {
				while (op[op.size() - 1].word_value == "*" || op[op.size() - 1].word_value == "/")
				{
					postfixexpression_vector.push_back(op[op.size() - 1]);
					op.pop_back();
				}
			}
			
			op.push_back(temporarysave[i]);
			i++;
			continue;
		}
		if (temporarysave[i].word_value == ";")
		{
			while (op.size() != 0)
			{
				postfixexpression_vector.push_back(op[op.size() - 1]);
				op.pop_back();
			}
			if (iftest) {
				cout << "后缀表达式求值完毕" << endl;
			}
			break;
	}

		cout << "后缀表达式求值出错" << endl;
		break;
	}
	
	if (iftest)
	{
		for (int i = 0; i < postfixexpression_vector.size(); i++) {
			cout << postfixexpression_vector[i].word_value ;
		}
		cout << endl;
	}
}

