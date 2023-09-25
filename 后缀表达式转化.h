#pragma once
#include <iostream>
using namespace std;
#include"��������.h"
#include <fstream>
#include <vector>
#include <string>

//�˺�������׺���ʽת��Ϊ��׺���ʽ
void Makepostfixexpression(vector<Word> expression) {

	bool iftest = false;
	//bool iftest = true;
	vector<Word> temporarysave;//����������ľ�
	for (int j = 0; j < expression.size(); j++)
	{
		temporarysave.push_back(expression[j]);
	}
	//��׺���ʽջ��ʼ��

	if (iftest)
	{
		cout << "��Ҫת����ʽ��Ϊ:";
		for (int i = 0; i < temporarysave.size(); i++) {
			cout << temporarysave[i].word_value ;
		}
		cout << endl;
	}


	stack_expression.clear();
	postfixexpression_vector.clear();
	vector<Word> op;      //[����]���洢�������ջ
	op.clear();
	int i = 0;
	while (i < temporarysave.size()) {
		if (iftest) {
			cout << "��ǰֵΪ:" << temporarysave[i].word_value;
			//�����ĸջ��ֵ
			for (int i = 0; i < postfixexpression_vector.size(); i++) {
				cout << postfixexpression_vector[i].word_value << '\t';
			}
			cout << "���Ŷ�ջΪ��\t";
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
			//���������ʱ������ǰ�����
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
//��������֮ǰ�Ĳ��������Ƴ�������ջ
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
			//����������ջ�ķ� ( �� �� ѹ���ַ�ջ

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
			//����������ջ��* �� / ѹ���ַ�ջ
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
				cout << "��׺���ʽ��ֵ���" << endl;
			}
			break;
	}

		cout << "��׺���ʽ��ֵ����" << endl;
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

