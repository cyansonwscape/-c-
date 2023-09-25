#pragma once

#include <iostream>
#include "��������.h"
#include "���������ж�.h"

//������ǰ�ַ�������һ��
int Distribute(const char ch);
bool IsOpreator(const string word);
//using namespace std;

// ����˵��:�ܿس���
//�����ִ�ͷȴ��ȫ��������ʱ��ʾ����
//��ע�ͷ���"//"���ڿ�ͷʱ������޷�ʶ��Ĵ���

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

		//����һ���ж�Ϊ��ʽ�硰ajh dsioj���ĵ�������
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
			LetterAnalysis(word);//��ʶ����ؼ���
		}
		else if (type == DIGIT)
		{
			//forѭ����Ϊ���ֻ�����ĸ��ʱ���������ȡ��������>��Ϊ����һλ���Ƿָ���ʱ�������ȡ


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

				//���ǽ�������������ʱ��ֹͣ����
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
				DigitAnalysis(word);//�޷�����
			}
			else
			{
				ErrorAnalysis(word);//�������봦��
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
				//����һλ�������֡���������ʵ�ʱ������ж��Ƿ�Ϊ��Ϊ��������
				if (Distribute(code_vector[end]) != DIGIT && Distribute(code_vector[end]) != LETTER && Distribute(code_vector[end]) != BOUNDARY)
				{
					//һֱ�ж�ֱ�����һλΪ�Ⱥ�
					if (code_vector[end] != '=')
						word += code_vector[end];
					else
					{//��Ϊ�Ⱥŵ�˫λ����ʱ
						word += code_vector[end];
						if (IsOpreator(word))
						{ //�ǲ��������¼����
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

	//�ж��Ƿ�����ĸ
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_')
		return LETTER;

	//�ж��Ƿ�Ϊ����
	if (ch >= '0' && ch <= '9')
		return DIGIT;

	//�ж��Ƿ�Ϊ�����
	for (const string str : operator_vector)
	{
		if (str == ch_tmp)
			return OPERATOR;
	}

	//�ж��Ƿ�Ϊ���
	for (const string str : boundary_vector)
	{
		if (str == ch_tmp)
			return BOUNDARY;
	}
}

//�жϵ�ǰ�ַ����Ƿ��������
bool IsOpreator(const string word)
{
	for (const string str : operator_vector)
	{
		if (str == word)
			return true;
	}
	return false;
}
