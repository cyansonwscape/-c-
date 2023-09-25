#pragma once
#include <iostream>
using namespace std;
#include"��������.h"
#include <fstream>
#include <vector>
#include <string>




//�﷨���� ��
//������һ�����ʽ���﷨
//���ʽ ��=���ʽ �������������=-*/������  E ->E op T    
// ���ʽ ��=����							 E ->T
// ����   ��= ����                           T ->����
// ����   ��= ��ʶ��						 T ->��ʶ��
//����   ��=�����ʽ��						 T ->(E)
//����Ϊ���ڱ��ʽ�ĸ���
//E -> T E'
//E'-> op T E'
//E'-> ��
//T ->����
//T ->��ʶ��
//T ->(E)
//����ΪFISRST����FOLLOW���ϵļ���
//First��E��={���֣���ʶ����( }
//First��E'��={op����}
//First��T��={�������֣���ʶ�� }
//Follw(E)={),#}
//Follw(E')={),#}
//Follw(T)={op,),#}
// 
//SELECT(E -> T E')			={�������֣���ʶ��}
//SELECT(E'-> op T E')		={op}
//SELECT(E'-> ��)			={),#}
//SELECT(T ->����)			={����}
//SELECT(T ->��ʶ��)		={��ʶ��}
//SELECT(T ->(E))			={(}
//Ԥ�������
//		����	��ʶ��	op		(			)		#
// E	T E'	T E'			T E'
// E'                  opTE'			    ��     ��
// T	����	��ʶ��			(E)	
//


//���ڱ��ʽ�����﷨����(���Ҷ��ڷָ���ʽ�ĵ�һ��ʽ�ӽ��з���)
bool AnalyseExprexxion(vector<Word> expression) {
	vector<Word> temporarysave;//����������ľ�
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
			cout << "����ʧ��,ԭ��:i��������" << endl;
			break;
		}
		//ȡ��ջ����Ԫ��
		Word nowstcakchar = stack_expression[stack_expression.size() - 1];
		//�ҵ����������ĵ�һ����ĸ
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
		//����һ���������Ե����
		if (iftest_grammer) {
			cout << i << "\t" << "nowstcakchar:" << nowstcakchar.word_value << "\twaitanalys\t" << waitanalys.word_value << endl;
		}

		if(nowstcakchar.word_value=="E") {

			if (waitanalys.word_type=="digit") {
				//����
				stack_expression.pop_back();
				//ѹ�� E'T
				stack_expression.push_back(stackinput_E2);
				stack_expression.push_back(stackinput_T);
				//�˳��˴�ѭ��
				continue;
			}
			else
			{
//		����	��ʶ��	op		(			)		#
// E	T E'	T E'			T E'
				if (waitanalys.word_type == "token") {
					//����
					stack_expression.pop_back();
					//ѹ�� E'T
					stack_expression.push_back(stackinput_E2);
					stack_expression.push_back(stackinput_T);
					//�˳��˴�ѭ��
					continue;
				}
				else
				{
					if (waitanalys.word_value == "(") {
						//����
						stack_expression.pop_back();
						//ѹ�� E'T
						stack_expression.push_back(stackinput_E2);
						stack_expression.push_back(stackinput_T);
						//�˳��˴�ѭ��
						continue;
					}
					else
					{
						//����ʧ��
						cout << "����ʧ��,ԭ��:�������﷨����" << endl;
						break;
					}

				}

			}

			

		}
		if (nowstcakchar.word_value == "E2")
		{
			//		����	��ʶ��	op		(			)		#
			// E'   opTE'								��     ��
			if (waitanalys.word_type == "operator") {
				//����
				stack_expression.pop_back();
				//ѹ�� E'T op
				stack_expression.push_back(stackinput_E2);
				stack_expression.push_back(stackinput_T);
				stack_expression.push_back(stackinput_op);
				//�˳��˴�ѭ��
				continue;
			}
			else
			{
				if (waitanalys.word_value == ")") {
					//����
					stack_expression.pop_back();
					//�˳��˴�ѭ��
					continue;
				}
				else
				{
					if (waitanalys.word_value == "#") {
						stack_expression.pop_back();
						//�˳��˴�ѭ��
						continue;
					}
					else
					{
						//����ʧ��
						cout << "����ʧ��,ԭ��:�������﷨����" << endl;
						break;
					}

				}

			}

		}
		if (nowstcakchar.word_value == "T")
		{
			//		����	��ʶ��	op		(			)		#
			// T	����	��ʶ��			(E)	
			if (waitanalys.word_type == "digit") {
				//����
				stack_expression.pop_back();
				//ѹ�� digit
				stack_expression.push_back(stackinput_digit);
				//�˳��˴�ѭ��
				continue;
			}
			else
			{
				if (waitanalys.word_type == "token") {
					//����
					stack_expression.pop_back();
					//ѹ�� tokrn
					stack_expression.push_back(stackinput_token);
					//�˳��˴�ѭ��
					continue;
				}
				else
				{
					if (waitanalys.word_value == "(") {
						//����
						stack_expression.pop_back();
						//ѹ�� )E(
						stack_expression.push_back(stackinput_rk);
						stack_expression.push_back(stackinput_E);
						stack_expression.push_back(stackinput_lk);
						//�˳��˴�ѭ��
						continue;
					}
					else
					{
						//����ʧ��
						cout << "����ʧ��,ԭ��:�������﷨����" << endl;
						break;
					}
				}
			}

		}
		if (nowstcakchar.word_value == "digit")
		{
			if (waitanalys.word_type == "digit")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "token")
		{
			if (waitanalys.word_type == "token")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "(")
		{
			if (waitanalys.word_value == "(")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == ")")
		{
			if (waitanalys.word_value == ")")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "op")
		{
			if (waitanalys.word_value == "+"|| waitanalys.word_value == "-" || waitanalys.word_value == "*" || waitanalys.word_value == "/")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		cout << "����ʧ��,ԭ��:�޷����ڴ��������е��׸��ַ����з���" << endl;
		break;
	}

	
	if (stack_expression.size() == 0)
	{
		cout << "�����ɹ�:���ʽ" << endl;
		return true;
	}
	else
	{
		return false;
	}


}
//���ڸ�ֵ�����﷨����
//
//C ->��ʶ�� = E;
//C-> ������ ��ʶ�� = E;
//E -> T E'
//E'-> op T E'
//E'-> ��
//T ->����
//T ->��ʶ��
//T ->(E)
//����ΪFISRST����FOLLOW���ϵļ���
//First(C)={��ʶ��,������}
//First��E��={���֣���ʶ����( }
//First��E'��={op����}
//First��T��={�������֣���ʶ�� }
// 
//Follow(C)={#,} 
//Follw(E)={ ; , ) , }
//Follw(E')={) , ;}
//Follw(T)={op , ) , ; }
// 
//SELECT(C ->��ʶ�� = E;)			={��ʶ��}
//SELECT(C-> ������ ��ʶ�� = E;)	={������}
//SELECT(E -> T E')					={�������֣���ʶ��}
//SELECT(E'-> op T E')				={op}
//SELECT(E'-> ��)					={) , ;}
//SELECT(T ->����)					={����}
//SELECT(T ->��ʶ��)				={��ʶ��}
//SELECT(T ->(E))					={(}
//Ԥ�������
//		������					����					��ʶ��			op				(			)		 ;			#
// C	������ ��ʶ�� = E;								��ʶ�� = E;
// E	T E'					T E'													T E'
// E'                                                                   opTE'			 ��					��
// T							����					��ʶ��							(E)	
//
bool AnalyseAssignment(vector<Word> assignment) {
	vector<Word> temporarysave;//����������ľ�
	for (int j = 0; j < assignment.size(); j++)
	{
			temporarysave.push_back(assignment[j]);
	
	}
	//ջ��ʼ��
	stack_expression.clear();
	stack_expression.push_back(stackinput_C);
	int i = 0;//�����������������е�λ��
	while (stack_expression.size() != 0)
	{
		if (i > temporarysave.size())
		{
			cout << "����ʧ��,ԭ��:i��������" << endl;
			break;
		}
		//ȡ��ջ����Ԫ��
		Word nowstcakchar = stack_expression[stack_expression.size() - 1];
		//�ҵ����������ĵ�һ����ĸ
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

		//����һ���������Ե����
		if (iftest_grammer) {
			cout << i << "\t" << "nowstcakchar:" << nowstcakchar.word_value << "\twaitanalys\t" << waitanalys.word_value << endl;
		}
		if (nowstcakchar.word_value == "C") {
			//cout << nowstcakchar.word_value << endl;
			if (waitanalys.word_type == "keyword") {
				//������ ��ʶ�� = E;
				//����
				stack_expression.pop_back();
				//ѹ�� 
				stack_expression.push_back(stackinput_branch);
				stack_expression.push_back(stackinput_E);
				stack_expression.push_back(stackinput_equal);
				stack_expression.push_back(stackinput_token);
				stack_expression.push_back(stackinput_keyword);
				//�˳��˴�ѭ��
				continue;
			}
			else
			{
				//		����	��ʶ��	op		(			)		#
				// E	T E'	T E'			T E'
				if (waitanalys.word_type == "token") {
					//��ʶ�� = E;
					//����
					stack_expression.pop_back();
					//ѹ�� 
					stack_expression.push_back(stackinput_branch);
					stack_expression.push_back(stackinput_E);
					stack_expression.push_back(stackinput_equal);
					stack_expression.push_back(stackinput_token);
					//�˳��˴�ѭ��
					continue;
				}
				else
				{
						//����ʧ��
					if(iftest_grammer)
						cout << "����ʧ��,ԭ��:�������﷨����" << endl;
						break;
				}

			}



		}
		if (nowstcakchar.word_value == "E") {
			if(iftest_grammer)
			cout << nowstcakchar.word_value << endl;

			if (waitanalys.word_type == "digit") {
				//����
				stack_expression.pop_back();
				//ѹ�� E'T
				stack_expression.push_back(stackinput_E2);
				stack_expression.push_back(stackinput_T);
				//�˳��˴�ѭ��
				continue;
			}
			else
			{
				//		����	��ʶ��	op		(			)		#
				// E	T E'	T E'			T E'
				if (waitanalys.word_type == "token") {
					//����
					stack_expression.pop_back();
					//ѹ�� E'T
					stack_expression.push_back(stackinput_E2);
					stack_expression.push_back(stackinput_T);
					//�˳��˴�ѭ��
					continue;
				}
				else
				{
					if (waitanalys.word_value == "(") {
						//����
						stack_expression.pop_back();
						//ѹ�� E'T
						stack_expression.push_back(stackinput_E2);
						stack_expression.push_back(stackinput_T);
						//�˳��˴�ѭ��
						continue;
					}
					else
					{
						//����ʧ��
						if (iftest_grammer)
						cout << "����ʧ��,ԭ��:�������﷨����" << endl;
						break;
					}

				}

			}



		}
		if (nowstcakchar.word_value == "E2")
		{
			if (iftest_grammer)
			cout << nowstcakchar.word_value << endl;
			//		����	��ʶ��	op		(			)		#
			// E'   opTE'								��     ��
			if (waitanalys.word_type == "operator") {
				//����
				stack_expression.pop_back();
				//ѹ�� E'T op
				stack_expression.push_back(stackinput_E2);
				stack_expression.push_back(stackinput_T);
				stack_expression.push_back(stackinput_op);
				//�˳��˴�ѭ��
				continue;
			}
			else
			{
				if (waitanalys.word_value == ")") {
					//����
					stack_expression.pop_back();
					//�˳��˴�ѭ��
					continue;
				}
				else
				{
					if (waitanalys.word_value == ";") {
						stack_expression.pop_back();
						//�˳��˴�ѭ��
						continue;
					}
					else
					{
						//����ʧ��
						if (iftest_grammer)
						cout << "����ʧ��,ԭ��:�������﷨����" << endl;
						break;
					}

				}

			}

		}
		if (nowstcakchar.word_value == "T")
		{
			//		����	��ʶ��	op		(			)		#
			// T	����	��ʶ��			(E)	
			if (waitanalys.word_type == "digit") {
				//����
				stack_expression.pop_back();
				//ѹ�� digit
				stack_expression.push_back(stackinput_digit);
				//�˳��˴�ѭ��
				continue;
			}
			else
			{
				if (waitanalys.word_type == "token") {
					//����
					stack_expression.pop_back();
					//ѹ�� tokrn
					stack_expression.push_back(stackinput_token);
					//�˳��˴�ѭ��
					continue;
				}
				else
				{
					if (waitanalys.word_value == "(") {
						//����
						stack_expression.pop_back();
						//ѹ�� )E(
						stack_expression.push_back(stackinput_rk);
						stack_expression.push_back(stackinput_E);
						stack_expression.push_back(stackinput_lk);
						//�˳��˴�ѭ��
						continue;
					}
					else
					{
						//����ʧ��
						if (iftest_grammer)
						cout << "����ʧ��,ԭ��:�������﷨����" << endl;
						break;
					}
				}
			}

		}
		if (nowstcakchar.word_value == "digit")
		{
			if (waitanalys.word_type == "digit")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "token")
		{
			if (waitanalys.word_type == "token")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "(")
		{
			if (waitanalys.word_value == "(")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == ")")
		{
			if (waitanalys.word_value == ")")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "op")
		{
			if (waitanalys.word_value == "+" || waitanalys.word_value == "-" || waitanalys.word_value == "*" || waitanalys.word_value == "/")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "=")
		{
			
			if (waitanalys.word_value == "=")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}
		}
		if (nowstcakchar.word_value == ";")
		{

			if (waitanalys.word_value == ";")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}
		}
		if (nowstcakchar.word_value == "keyword")
		{
			if (waitanalys.word_type == "keyword")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}




		if (iftest_grammer)
		cout << "����ʧ��,ԭ��:�޷����ڴ��������е��׸��ַ����з���" << endl;
		return false;
		break;
	}

	if (stack_expression.size() == 0)
	{
		if (iftest_grammer)
		cout << "�����ɹ�:��ֵ���" << endl;
		return true;
	}
	else
	{
		if (iftest_grammer)
		cout << "����ʧ��,ԭ��:��ֵ���" << endl;
		return false;
	}

}
//���ڱȽ������﷨����
//
//B ->E �ȽϷ���  E;
//E -> T E'
//E'-> op T E'
//E'-> ��
//T ->����
//T ->��ʶ��
//T ->(E)
//����ΪFISRST����FOLLOW���ϵļ���
//First(B)={���֣���ʶ����( }
//First��E��={���֣���ʶ����( }
//First��E'��={op����}
//First��T��={�������֣���ʶ�� }
// 
//Follow(B)={#,} 
//Follw(E)={ ; , ) ,�ȽϷ���}
//Follw(E')={) , ;	,	�ȽϷ���}
//Follw(T)={op , ) , ;	��	�ȽϷ��� }
// 
//SELECT(B -> E �ȽϷ���  E;)		={���֣���ʶ����( }
//SELECT(E -> T E')					={�������֣���ʶ��}
//SELECT(E'-> op T E')				={op}
//SELECT(E'-> ��)					={) , ;	,	�ȽϷ���}
//SELECT(T ->����)					={����}
//SELECT(T ->��ʶ��)				={��ʶ��}
//SELECT(T ->(E))					={(}
//Ԥ�������
//		������				����		�ȽϷ���			��ʶ��					op				(				)		 ;	 #
// B	E �ȽϷ���  E;									 E �ȽϷ���  E;							 E �ȽϷ���  E;
// E	T E'												T E'									T E'
// E'									  ��										opTE'			 ��				        ��
// T						����							��ʶ��									(E)	
//
void AnalyseCompare(vector<Word> Compare) {
	vector<Word> temporarysave;//����������ľ�
	for (int j = 0; j < Compare.size(); j++)
	{
		temporarysave.push_back(Compare[j]);
	}
	//ջ��ʼ��
	stack_expression.clear();
	stack_expression.push_back(stackinput_B);
	int i = 0;//�����������������е�λ��
	while (stack_expression.size() != 0)
	{
		if (i > temporarysave.size())
		{
			cout << "����ʧ��,ԭ��:i��������" << endl;
			break;
		}
		//ȡ��ջ����Ԫ��
		Word nowstcakchar = stack_expression[stack_expression.size() - 1];
		//�ҵ����������ĵ�һ����ĸ
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
				//E �ȽϷ���  E;
				//����
				stack_expression.pop_back();
				//ѹ�� 
				stack_expression.push_back(stackinput_branch);
				stack_expression.push_back(stackinput_E);
				stack_expression.push_back(stackinput_compareop);
				stack_expression.push_back(stackinput_E);
				//�˳��˴�ѭ��
				continue;
			}
			else
			{
				if (waitanalys.word_type == "token") {
					//E �ȽϷ���  E;
					//����
					stack_expression.pop_back();
					//ѹ�� 
					stack_expression.push_back(stackinput_branch);
					stack_expression.push_back(stackinput_E);
					stack_expression.push_back(stackinput_compareop);
					stack_expression.push_back(stackinput_E);
					//�˳��˴�ѭ��
					continue;
				}
				else
				{
					if (waitanalys.word_type == "(") {
						//E �ȽϷ���  E;
						//����
						stack_expression.pop_back();
						//ѹ�� 
						stack_expression.push_back(stackinput_branch);
						stack_expression.push_back(stackinput_E);
						stack_expression.push_back(stackinput_compareop);
						stack_expression.push_back(stackinput_E);
						//�˳��˴�ѭ��
						continue;
					}
					else
					{
						//����ʧ��
						cout << "����ʧ��,ԭ��:�������﷨����" << endl;
						break;
					}
				}

			}



		}
		if (nowstcakchar.word_value == "E") {
			cout << nowstcakchar.word_value << endl;

			if (waitanalys.word_type == "digit") {
				//����
				stack_expression.pop_back();
				//ѹ�� E'T
				stack_expression.push_back(stackinput_E2);
				stack_expression.push_back(stackinput_T);
				//�˳��˴�ѭ��
				continue;
			}
			else
			{
				//		����	��ʶ��	op		(			)		#
				// E	T E'	T E'			T E'
				if (waitanalys.word_type == "token") {
					//����
					stack_expression.pop_back();
					//ѹ�� E'T
					stack_expression.push_back(stackinput_E2);
					stack_expression.push_back(stackinput_T);
					//�˳��˴�ѭ��
					continue;
				}
				else
				{
					if (waitanalys.word_value == "(") {
						//����
						stack_expression.pop_back();
						//ѹ�� E'T
						stack_expression.push_back(stackinput_E2);
						stack_expression.push_back(stackinput_T);
						//�˳��˴�ѭ��
						continue;
					}
					else
					{
						//����ʧ��
						cout << "����ʧ��,ԭ��:�������﷨����" << endl;
						break;
					}

				}

			}



		}
		if (nowstcakchar.word_value == "E2")
		{
			cout << nowstcakchar.word_value << endl;
			if (waitanalys.word_value == "+" || waitanalys.word_value == "-" || waitanalys.word_value == "*" || waitanalys.word_value == "/") {
				//����
				stack_expression.pop_back();
				//ѹ�� E'T op
				stack_expression.push_back(stackinput_E2);
				stack_expression.push_back(stackinput_T);
				stack_expression.push_back(stackinput_op);
				//�˳��˴�ѭ��
				continue;
			}
			else
			{
				if (waitanalys.word_value == ")") {
					//����
					stack_expression.pop_back();
					//�˳��˴�ѭ��
					continue;
				}
				else
				{
					if (waitanalys.word_value == ";") {
						stack_expression.pop_back();
						//�˳��˴�ѭ��
						continue;
					}
					else
					{
						if (waitanalys.word_value == ">" || waitanalys.word_value == "<" || waitanalys.word_value == ">=" || waitanalys.word_value == "<=" || waitanalys.word_value == "==") {
							stack_expression.pop_back();
							//�˳��˴�ѭ��
							continue;
						}
						else
						{
							//����ʧ��
							cout << "����ʧ��,ԭ��:�������﷨����" << endl;
							break;
						}
					}

				}

			}

		}
		if (nowstcakchar.word_value == "T")
		{
			//		����	��ʶ��	op		(			)		#
			// T	����	��ʶ��			(E)	
			if (waitanalys.word_type == "digit") {
				//����
				stack_expression.pop_back();
				//ѹ�� digit
				stack_expression.push_back(stackinput_digit);
				//�˳��˴�ѭ��
				continue;
			}
			else
			{
				if (waitanalys.word_type == "token") {
					//����
					stack_expression.pop_back();
					//ѹ�� tokrn
					stack_expression.push_back(stackinput_token);
					//�˳��˴�ѭ��
					continue;
				}
				else
				{
					if (waitanalys.word_value == "(") {
						//����
						stack_expression.pop_back();
						//ѹ�� )E(
						stack_expression.push_back(stackinput_rk);
						stack_expression.push_back(stackinput_E);
						stack_expression.push_back(stackinput_lk);
						//�˳��˴�ѭ��
						continue;
					}
					else
					{
						//����ʧ��
						cout << "����ʧ��,ԭ��:�������﷨����" << endl;
						break;
					}
				}
			}

		}
		if (nowstcakchar.word_value == "digit")
		{
			if (waitanalys.word_type == "digit")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "token")
		{
			if (waitanalys.word_type == "token")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "(")
		{
			if (waitanalys.word_value == "(")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == ")")
		{
			if (waitanalys.word_value == ")")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "op")
		{
			if (waitanalys.word_value == "+" || waitanalys.word_value == "-" || waitanalys.word_value == "*" || waitanalys.word_value == "/")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "=")
		{

			if (waitanalys.word_value == "=")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}
		}
		if (nowstcakchar.word_value == ";")
		{

			if (waitanalys.word_value == ";")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}
		}
		if (nowstcakchar.word_value == "keyword")
		{
			if (waitanalys.word_type == "keyword")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "compareop")
		{
			if (waitanalys.word_value == ">" || waitanalys.word_value == "<" || waitanalys.word_value == ">=" || waitanalys.word_value == "<=" || waitanalys.word_value == "==")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		cout << "����ʧ��,ԭ��:�޷����ڴ��������е��׸��ַ����з���" << endl;
		break;
	}

	if (stack_expression.size() == 0)
	{
		cout << "�����ɹ�:�Ƚ����" << endl;
	}



}
//����for�����﷨����
// 
//A-> for ( L ; M ; N) { O } 
//L->��ʶ�� = E
//L-> ������ ��ʶ�� = E
//L->��
//M->E �ȽϷ���  E
//N->��ʶ�� = E
//N->��
//O->L;O
//O->��
//E -> T E'
//E'-> op T E'
//E'-> ��
//T ->����
//T ->��ʶ��
//T ->(E)
//����ΪFISRST����FOLLOW���ϵļ���
//First(A)={for }
//First(L)={��ʶ���������֣��� }
//First(M)={���֣���ʶ����( }
//First(N)={��ʶ������}
//First(O)={��ʶ���������֣��� }
//First(E)={���֣���ʶ����( }
//First(E')={op����}
//First(T)={�������֣���ʶ�� }
// 
//Follow(A)		={#,	}
//Follow(L)		={";",	}
//Follow(M)		={";",	}
//Follow(N)		={")",	}
//Follow(O)		={"}",	}
//Follw(E)		={�ȽϷ���,")",";"}
//Follw(E')		={�ȽϷ���,")",";"}
//Follw(T)		={op,�ȽϷ���,")"}
// 
//SELECT(A-> for ( L ; M ; N) { O } ) ={for}
//SELECT(L->��ʶ�� = E)				={��ʶ��}
//SELECT(L-> ������ ��ʶ�� = E)		={������}
//SELECT(L->��)						={";"}
//SELECT(M->E �ȽϷ���  E)			={���֣���ʶ����(}
//SELECT(N->��ʶ�� = E)				={��ʶ��}
//SELECT(N->��)						={")"}
//SELECT(O->L;O)					={��ʶ���������֣�";"}
//SELECT(O->��)						={"}"}
//SELECT(E -> T E')					={�������֣���ʶ��}
//SELECT(E'-> op T E')				={op}
//SELECT(E'-> ��)					={) , ;	,	�ȽϷ���}
//SELECT(T ->����)					={����}
//SELECT(T ->��ʶ��)				={��ʶ��}
//SELECT(T ->(E))					={(}
//Ԥ�������
//		������				����		�ȽϷ���			��ʶ��					op				(				)		 ;	   {		}        for				#
// A																																			for ( L ; M ; N) { O }
// L	������ ��ʶ�� = E									��ʶ�� = E														 ��
// M					E �ȽϷ���  E					E �ȽϷ���  E							E �ȽϷ���  E
// N														��ʶ�� = E												��
// O	L;O													L;O																 L;O		    ��
// E						T E'						   T E'									T E'
// E'									  ��										opTE'			 ��				        ��
// T						����							��ʶ��									(E)	
//
bool AnalyseForSentence(vector<Word> forsentence)
{
	vector<Word> temporarysave;//����������ľ�
	for (int j = 0; j < forsentence.size(); j++)
	{
		temporarysave.push_back(forsentence[j]);
	}
	//ջ��ʼ��
	stack_expression.clear();
	stack_expression.push_back(stackinput_A);
	int i = 0;//�����������������е�λ��
	while (stack_expression.size() != 0)
	{
		if (i > temporarysave.size())
		{
			cout << "����ʧ��,ԭ��:i��������" << endl;
			return false;
			break;
		}
		//ȡ��ջ����Ԫ��
		Word nowstcakchar = stack_expression[stack_expression.size() - 1];
		//�ҵ����������ĵ�һ����ĸ
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
				//����
				stack_expression.pop_back();
				//ѹ�� 
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
				//�˳��˴�ѭ��
				continue;
			}
			else{
				//����ʧ��
				if (iftest_grammer)
				cout << "����ʧ��,ԭ��:�������﷨����" << endl;
				break;
			}
		}
		if (nowstcakchar.word_value == "L") {
			//cout << nowstcakchar.word_value << endl;
			if (waitanalys.word_type == "keyword") {
				//������ ��ʶ�� = E
				//����
				stack_expression.pop_back();
				//ѹ�� 
				stack_expression.push_back(stackinput_E);
				stack_expression.push_back(stackinput_equal);
				stack_expression.push_back(stackinput_token);
				stack_expression.push_back(stackinput_keyword);
				//�˳��˴�ѭ��
				continue;
			}
			else
			{
				if (waitanalys.word_type == "token") {
					//��ʶ�� = E
					//����
					stack_expression.pop_back();
					//ѹ�� 
					stack_expression.push_back(stackinput_E);
					stack_expression.push_back(stackinput_equal);
					stack_expression.push_back(stackinput_token);
					//�˳��˴�ѭ��
					continue;
				}
				else
				{
					if (waitanalys.word_type == ";") {
						// ��
						//����
						stack_expression.pop_back();
						//�˳��˴�ѭ��
						continue;
					}
					else
					{
						//����ʧ��
						cout << "����ʧ��,ԭ��:�������﷨����" << endl;
						break;
					}
				}

			}



		}
		if (nowstcakchar.word_value == "M") {
			if (waitanalys.word_type == "keyword") {
				//E �ȽϷ���  E
				//����
				stack_expression.pop_back();
				//ѹ�� 
				stack_expression.push_back(stackinput_E);
				stack_expression.push_back(stackinput_compareop);
				stack_expression.push_back(stackinput_E);
				//�˳��˴�ѭ��
				continue;
			}
			else
			{
				if (waitanalys.word_type == "token") {
					//E �ȽϷ���  E
					//����
					stack_expression.pop_back();
					//ѹ�� 
					stack_expression.push_back(stackinput_E);
					stack_expression.push_back(stackinput_compareop);
					stack_expression.push_back(stackinput_E);
					//�˳��˴�ѭ��
					continue;
				}
				else
				{
					if (waitanalys.word_type == "(") {
						//E �ȽϷ���  E
						//����
						stack_expression.pop_back();
						//ѹ�� 
						stack_expression.push_back(stackinput_E);
						stack_expression.push_back(stackinput_compareop);
						stack_expression.push_back(stackinput_E);
						//�˳��˴�ѭ��
						continue;
					}
					else
					{
						//����ʧ��
						cout << "����ʧ��,ԭ��:�������﷨����" << endl;
						break;
					}
				}

			}



		}
		if (nowstcakchar.word_value == "N") {
				if (waitanalys.word_type == "token") {
					//��ʶ�� = E
					//����
					stack_expression.pop_back();
					//ѹ�� 
					stack_expression.push_back(stackinput_E);
					stack_expression.push_back(stackinput_equal);
					stack_expression.push_back(stackinput_token);
					//�˳��˴�ѭ��
					continue;
				}
				else
				{
					if (waitanalys.word_type == ")") {
						// ��
						//����
						stack_expression.pop_back();
						//�˳��˴�ѭ��
						continue;
					}
					else
					{
						//����ʧ��
						cout << "����ʧ��,ԭ��:�������﷨����" << endl;
						break;
					}
				}
		}
		if (nowstcakchar.word_value == "O") {
			if (waitanalys.word_type == "keyword") {
				//L;O
				//����
				stack_expression.pop_back();
				//ѹ�� 
				stack_expression.push_back(stackinput_O);
				stack_expression.push_back(stackinput_branch);
				stack_expression.push_back(stackinput_L);
				//�˳��˴�ѭ��
				continue;
			}
			else
			{
				if (waitanalys.word_type == "token") {
					//L;O
					//����
					stack_expression.pop_back();
					//ѹ�� 
					stack_expression.push_back(stackinput_O);
					stack_expression.push_back(stackinput_branch);
					stack_expression.push_back(stackinput_L);
					//�˳��˴�ѭ��
					continue;
				}
				else
				{
					if (waitanalys.word_value == ";") {
						//L;O
						//����
						stack_expression.pop_back();
						//ѹ�� 
						stack_expression.push_back(stackinput_O);
						stack_expression.push_back(stackinput_branch);
						stack_expression.push_back(stackinput_L);
						//�˳��˴�ѭ��
						continue;
					}
					else
					{
						if (waitanalys.word_value == "}") {
							//��
							//����
							stack_expression.pop_back();
							//�˳��˴�ѭ��
							continue;
						}
						else
						{
							//����ʧ��
							cout << "����ʧ��,ԭ��:�������﷨����" << endl;
							break;
						}
					}
				}
			}
		}

		if (nowstcakchar.word_value == "E") {
			if (waitanalys.word_type == "digit") {
				//����
				stack_expression.pop_back();
				//ѹ�� E'T
				stack_expression.push_back(stackinput_E2);
				stack_expression.push_back(stackinput_T);
				//�˳��˴�ѭ��
				continue;
			}
			else
			{
				//		����	��ʶ��	op		(			)		#
				// E	T E'	T E'			T E'
				if (waitanalys.word_type == "token") {
					//����
					stack_expression.pop_back();
					//ѹ�� E'T
					stack_expression.push_back(stackinput_E2);
					stack_expression.push_back(stackinput_T);
					//�˳��˴�ѭ��
					continue;
				}
				else
				{
					if (waitanalys.word_value == "(") {
						//����
						stack_expression.pop_back();
						//ѹ�� E'T
						stack_expression.push_back(stackinput_E2);
						stack_expression.push_back(stackinput_T);
						//�˳��˴�ѭ��
						continue;
					}
					else
					{
						//����ʧ��
						cout << "����ʧ��,ԭ��:�������﷨����" << endl;
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
				//����
				stack_expression.pop_back();
				//ѹ�� E'T op
				stack_expression.push_back(stackinput_E2);
				stack_expression.push_back(stackinput_T);
				stack_expression.push_back(stackinput_op);
				//�˳��˴�ѭ��
				continue;
			}
			else
			{
				if (waitanalys.word_value == ")") {
					//����
					stack_expression.pop_back();
					//�˳��˴�ѭ��
					continue;
				}
				else
				{
					if (waitanalys.word_value == ";") {
						stack_expression.pop_back();
						//�˳��˴�ѭ��
						continue;
					}
					else
					{
						if (waitanalys.word_value == ">" || waitanalys.word_value == "<" || waitanalys.word_value == ">=" || waitanalys.word_value == "<=" || waitanalys.word_value == "==") {
							stack_expression.pop_back();
							//�˳��˴�ѭ��
							continue;
						}
						else
						{
							//����ʧ��
							cout << "����ʧ��,ԭ��:�������﷨����" << endl;
							break;
						}
					}

				}

			}

		}
		if (nowstcakchar.word_value == "T")
		{
			//		����	��ʶ��	op		(			)		#
			// T	����	��ʶ��			(E)	
			if (waitanalys.word_type == "digit") {
				//����
				stack_expression.pop_back();
				//ѹ�� digit
				stack_expression.push_back(stackinput_digit);
				//�˳��˴�ѭ��
				continue;
			}
			else
			{
				if (waitanalys.word_type == "token") {
					//����
					stack_expression.pop_back();
					//ѹ�� tokrn
					stack_expression.push_back(stackinput_token);
					//�˳��˴�ѭ��
					continue;
				}
				else
				{
					if (waitanalys.word_value == "(") {
						//����
						stack_expression.pop_back();
						//ѹ�� )E(
						stack_expression.push_back(stackinput_rk);
						stack_expression.push_back(stackinput_E);
						stack_expression.push_back(stackinput_lk);
						//�˳��˴�ѭ��
						continue;
					}
					else
					{
						//����ʧ��
						cout << "����ʧ��,ԭ��:�������﷨����" << endl;
						break;
					}
				}
			}

		}
		if (nowstcakchar.word_value == "digit")
		{
			if (waitanalys.word_type == "digit")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "token")
		{
			if (waitanalys.word_type == "token")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "(")
		{
			if (waitanalys.word_value == "(")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == ")")
		{
			if (waitanalys.word_value == ")")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "op")
		{
			if (waitanalys.word_value == "+" || waitanalys.word_value == "-" || waitanalys.word_value == "*" || waitanalys.word_value == "/")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "=")
		{

			if (waitanalys.word_value == "=")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}
		}
		if (nowstcakchar.word_value == ";")
		{

			if (waitanalys.word_value == ";")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}
		}
		if (nowstcakchar.word_value == "keyword")
		{
			if (waitanalys.word_type == "keyword")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "compareop")
		{
			if (waitanalys.word_value == ">" || waitanalys.word_value == "<" || waitanalys.word_value == ">=" || waitanalys.word_value == "<=" || waitanalys.word_value == "==")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}

		if (nowstcakchar.word_value == "{")
		{
			if (waitanalys.word_value == "{")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "}")
		{
			if (waitanalys.word_value == "}")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "for")
		{
			if (waitanalys.word_value == "for")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}


		if (iftest_grammer)
		cout << "����ʧ��,ԭ��:�޷����ڴ��������е��׸��ַ����з���" << endl;
		return false;
		break;
	}

	if (stack_expression.size() == 0)
	{
		if (iftest_grammer)
		cout << "�����ɹ�:for���" << endl;
		return true;
	}
	else
	{
		return false;
	}

}
//������������﷨����
//R-> cout M ;
//M-> ��
//M-> <<M' 
//M'-> E M
//M'-> �ַ��� M
//M'-> endl M
//E -> T E'
//E'-> op T E'
//E'-> ��
//T ->����
//T ->��ʶ��
//T ->(E)
//First(R)={cout}
//First(M)={ << , ��}
//First(M')={���֣���ʶ����( ,�ַ���,endl}
//First(E)={���֣���ʶ����( }
//First(E')={op����}
//First(T)= {���֣���ʶ����(  }
//Follow(R)		={# }
//Follow(M)		={;}
//Follow(M')	={;}
//Follw(E)		={")", << , ; }
//Follw(E')		={")", << , ; }
//Follw(T)		={op,")", << , ; }
//
//SECLECT(R-> cout M ;)		={cout}
//SECLECT(M-> ��)			={;}
//SECLECT(M-> <<M')			={<<}
//SECLECT(M'-> E M)			={���֣���ʶ����(}
//SECLECT(M'-> �ַ��� M)	={�ַ���}
//SECLECT(M'-> endl M)		={endl}
//SECLECT(E -> T E')		={���֣���ʶ����(  }
//SECLECT(E'-> op T E')		={op}
//SECLECT(E'-> ��)			={")", << , ; }
//SECLECT(T ->����)			={����}
//SECLECT(T ->��ʶ��)		={��ʶ��}
//SECLECT(T ->(E))			={(E)}
//           ��ʶ��		 �ַ���		����		cout			endl			<<			op		(			)		;		#
// R											cout M ;
// M																			<<M'									��
// M'		 E M		�ַ���M	    E M							endl M								E M
// E		 T E'					T E'															T E'
// E'																			��			opTE'				��		��
// T		��ʶ��					����																(E)
bool AnalyseOutputsentence(vector<Word> outputsentence) 
{
	vector<Word> temporarysave;//����������ľ�
	for (int j = 0; j < outputsentence.size(); j++)
	{
		temporarysave.push_back(outputsentence[j]);
	}
	//ջ��ʼ��
	stack_expression.clear();
	stack_expression.push_back(stackinput_R);
	int i = 0;//�����������������е�λ��
	while (stack_expression.size() != 0)
	{
		if (i > temporarysave.size())
		{
			cout << "����ʧ��,ԭ��:i��������" << endl;
			break;
		}
		//ȡ��ջ����Ԫ��
		Word nowstcakchar = stack_expression[stack_expression.size() - 1];
		//�ҵ����������ĵ�һ����ĸ
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
				//����
				stack_expression.pop_back();
				//ѹ�� 
				stack_expression.push_back(stackinput_branch);
				stack_expression.push_back(stackinput_M);;
				stack_expression.push_back(stackinput_cout);
				//�˳��˴�ѭ��
				continue;
			}
			else {
				//����ʧ��
				if (iftest_grammer)
				cout << "����ʧ��,ԭ��:�������﷨����" << endl;
				break;
			}
		}
		if (nowstcakchar.word_value == "M") {
		if (waitanalys.word_value == "<<") {
				//	<<M'
				//����
				stack_expression.pop_back();
				//ѹ�� 
				stack_expression.push_back(stackinput_M2);
				stack_expression.push_back(stackinput_output);
				//�˳��˴�ѭ��
				continue;
			}
			else
			{
				if (waitanalys.word_value == ";") {
					//	��
					//����
					stack_expression.pop_back();
					//�˳��˴�ѭ��
					continue;
				}
				else
				{
					//����ʧ��
					if (iftest_grammer)
					cout << "����ʧ��,ԭ��:�������﷨����" << endl;
					break;
				}

			}



		}
		if (nowstcakchar.word_value == "M2") {
			if (waitanalys.word_type == "token") {
				// E M	
				//����
				stack_expression.pop_back();
				//ѹ�� 
				stack_expression.push_back(stackinput_M);
				stack_expression.push_back(stackinput_E);
				//�˳��˴�ѭ��
				continue;
			}
			else{
				if (waitanalys.word_type == "string") {
					// �ַ���M	
					//����
					stack_expression.pop_back();
					//ѹ�� 
					stack_expression.push_back(stackinput_M);
					stack_expression.push_back(stackinput_string);
					//�˳��˴�ѭ��
					continue;
				}
				else{
					if (waitanalys.word_type == "digit") {
						//  E M		
						//����
						stack_expression.pop_back();
						//ѹ�� 
						stack_expression.push_back(stackinput_M);
						stack_expression.push_back(stackinput_E);
						//�˳��˴�ѭ��
						continue;
					}
					else{
						if (waitanalys.word_value == "endl") {
							// endl M	
							//����
							stack_expression.pop_back();
							//ѹ�� 
							stack_expression.push_back(stackinput_M);
							stack_expression.push_back(stackinput_endl);
							//�˳��˴�ѭ��
							continue;
						}
						else{
							if (waitanalys.word_value == "(") {
								// E M	
								//����
								stack_expression.pop_back();
								//ѹ�� 
								stack_expression.push_back(stackinput_M);
								stack_expression.push_back(stackinput_E);
								//�˳��˴�ѭ��
								continue;
							}
							else {
								//����ʧ��
								if (iftest_grammer)
								cout << "����ʧ��,ԭ��:�������﷨����" << endl;
								break;
							}
						}
					}
				}
			}
		}
		if (nowstcakchar.word_value == "E") {
			if (waitanalys.word_type == "digit") {
				//����
				stack_expression.pop_back();
				//ѹ�� T E'
				stack_expression.push_back(stackinput_E2);
				stack_expression.push_back(stackinput_T);
				//�˳��˴�ѭ��
				continue;
			}
			else{
				if (waitanalys.word_type == "token") {
					//����
					stack_expression.pop_back();
					//ѹ�� E'T
					stack_expression.push_back(stackinput_E2);
					stack_expression.push_back(stackinput_T);
					//�˳��˴�ѭ��
					continue;
				}
				else
				{
					if (waitanalys.word_value == "(") {
						//����
						stack_expression.pop_back();
						//ѹ�� E'T
						stack_expression.push_back(stackinput_E2);
						stack_expression.push_back(stackinput_T);
						//�˳��˴�ѭ��
						continue;
					}
					else
					{
						//����ʧ��
						if (iftest_grammer)
						cout << "����ʧ��,ԭ��:�������﷨����" << endl;
						break;
					}

				}

			}



		}
		if (nowstcakchar.word_value == "E2")
		{
			if (waitanalys.word_value == "+" || waitanalys.word_value == "-" || waitanalys.word_value == "*" || waitanalys.word_value == "/") {
				//����
				stack_expression.pop_back();
				//ѹ�� E'T op
				stack_expression.push_back(stackinput_E2);
				stack_expression.push_back(stackinput_T);
				stack_expression.push_back(stackinput_op);
				//�˳��˴�ѭ��
				continue;
			}
			else{
				if (waitanalys.word_value == ")") {
					//����
					stack_expression.pop_back();
					//�˳��˴�ѭ��
					continue;
				}
				else{
					if (waitanalys.word_value == ";") {
						stack_expression.pop_back();
						//�˳��˴�ѭ��
						continue;
					}
					else{
						if (waitanalys.word_value == "<<") {
							stack_expression.pop_back();
							//�˳��˴�ѭ��
							continue;
						}
						else
						{
							//����ʧ��
							if (iftest_grammer)
							cout << "����ʧ��,ԭ��:�������﷨����" << endl;
							break;
						}
					}

				}

			}

		}
		if (nowstcakchar.word_value == "T")
		{
			if (waitanalys.word_type == "digit") {
				//����
				stack_expression.pop_back();
				//ѹ�� digit
				stack_expression.push_back(stackinput_digit);
				//�˳��˴�ѭ��
				continue;
			}
			else{
				if (waitanalys.word_type == "token") {
					//����
					stack_expression.pop_back();
					//ѹ�� tokrn
					stack_expression.push_back(stackinput_token);
					//�˳��˴�ѭ��
					continue;
				}
				else{
					if (waitanalys.word_value == "(") {
						//����
						stack_expression.pop_back();
						//ѹ�� )E(
						stack_expression.push_back(stackinput_rk);
						stack_expression.push_back(stackinput_E);
						stack_expression.push_back(stackinput_lk);
						//�˳��˴�ѭ��
						continue;
					}
					else{
						//����ʧ��
						if (iftest_grammer)
						cout << "����ʧ��,ԭ��:�������﷨����" << endl;
						break;
					}
				}
			}

		}

		if (nowstcakchar.word_value == "digit")
		{
			if (waitanalys.word_type == "digit")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "token")
		{
			if (waitanalys.word_type == "token")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "(")
		{
			if (waitanalys.word_value == "(")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == ")")
		{
			if (waitanalys.word_value == ")")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "op")
		{
			if (waitanalys.word_value == "+" || waitanalys.word_value == "-" || waitanalys.word_value == "*" || waitanalys.word_value == "/")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "=")
		{

			if (waitanalys.word_value == "=")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}
		}
		if (nowstcakchar.word_value == ";")
		{

			if (waitanalys.word_value == ";")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}
		}
		if (nowstcakchar.word_value == "keyword")
		{
			if (waitanalys.word_type == "keyword")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "cout")
		{
			if (waitanalys.word_value == "cout")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "endl")
		{
			if (waitanalys.word_value == "endl")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "<<")
		{
			if (waitanalys.word_value == "<<")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "string")
		{
			if (waitanalys.word_type == "string")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}


		if (iftest_grammer)
		cout << "����ʧ��,ԭ��:�޷����ڴ��������е��׸��ַ����з���" << endl;
		break;
	}

	if (stack_expression.size() == 0)
	{
		if (iftest_grammer)
		cout << "�����ɹ�:������" << endl;
		return true;
	}
	else
	{
		return false;
	}

}
//���ڶ��������﷨����
//
//C -> ������ ��ʶ�� ;
bool AnalyseDefine(vector<Word> define) {
	vector<Word> temporarysave;//����������ľ�
	for (int j = 0; j < define.size(); j++)
	{
		temporarysave.push_back(define[j]);
	}
	//ջ��ʼ��
	stack_expression.clear();
	stack_expression.push_back(stackinput_C);
	int i = 0;//�����������������е�λ��
	while (stack_expression.size() != 0)
	{
		if (i > temporarysave.size())
		{
			cout << "����ʧ��,ԭ��:i��������" << endl;
			break;
		}
		//ȡ��ջ����Ԫ��
		Word nowstcakchar = stack_expression[stack_expression.size() - 1];
		//�ҵ����������ĵ�һ����ĸ
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
				//������ ��ʶ�� ;
				//����
				stack_expression.pop_back();
				//ѹ�� 
				stack_expression.push_back(stackinput_branch);
				stack_expression.push_back(stackinput_token);
				stack_expression.push_back(stackinput_keyword);
				//�˳��˴�ѭ��
				continue;
			}
			else
			{
				//����ʧ��
				cout << "����ʧ��,ԭ��:�������﷨����" << endl;
				break;
			}
		}

		if (nowstcakchar.word_value == "digit")
		{
			if (waitanalys.word_type == "digit")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "token")
		{
			if (waitanalys.word_type == "token")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "(")
		{
			if (waitanalys.word_value == "(")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == ")")
		{
			if (waitanalys.word_value == ")")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "op")
		{
			if (waitanalys.word_value == "+" || waitanalys.word_value == "-" || waitanalys.word_value == "*" || waitanalys.word_value == "/")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}
		if (nowstcakchar.word_value == "=")
		{

			if (waitanalys.word_value == "=")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}
		}
		if (nowstcakchar.word_value == ";")
		{

			if (waitanalys.word_value == ";")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}
		}
		if (nowstcakchar.word_value == "keyword")
		{
			if (waitanalys.word_type == "keyword")
			{
				//����
				stack_expression.pop_back();
				i++;
				//�˳��˴�ѭ��
				continue;
			}

		}



		cout << "����ʧ��,ԭ��:�޷����ڴ��������е��׸��ַ����з���" << endl;
		break;
	}

	if (stack_expression.size() == 0)
	{
		if(iftest_grammer)
		cout << "�����ɹ�:��ʼ���������" << endl;
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
			cout << "���" << i << "Ϊ��ֵ�����߳�ʼ����ֵ���"<<endl;
			continue;
		}
		if (AnalyseForSentence(sentence_vector[i]) == true)
		{
			cout << "���" << i << "Ϊfor���" << endl;
			continue;
		}
		if (AnalyseOutputsentence(sentence_vector[i]) == true)
		{
			cout << "���" << i << "Ϊcout���" << endl;
			continue;
		}
		if (AnalyseDefine(sentence_vector[i]) == true)
		{
			cout << "���" << i << "Ϊ����������" << endl;
			continue;
		}


		cout << "���" << i << "�﷨��������" << endl;
		return false;



	}
	return true;

}











