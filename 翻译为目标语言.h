#pragma once
#include <iostream>
using namespace std;
#include"��������.h"
#include <fstream>
#include <vector>
#include <string>
#include "��׺���ʽת��.h"


//���ʽ������ӣ�����׺���ʽ��ջ�е����ݽ�����ֵ���ұ�����ָ���ĵ�ַ֮��
void TranslateArithmetic(Word resultplace) {
	bool iftest = false;

	if(iftest){ cout << "��ʼ����" << endl; }
	int i = 0;//����������׺���ʽ�Ķ�ջ
	vector<Word> num;//��������
	num.clear();
	int index = 0;//������¼��ʱ�洢������
	while (i < postfixexpression_vector.size()) {
		/*cout<< postfixexpression_vector[i].word_value <<endl;*/
		if (postfixexpression_vector[i].word_type == "digit" || postfixexpression_vector[i].word_type == "token")
		{
			num.push_back(postfixexpression_vector[i]);
			i++;
			continue;
		}
		if (postfixexpression_vector[i].word_value == "+")
		{
			Word newword = {"temporary","temporarysave"+to_string(index)};
			index++;
			cout << "MOV\tAX,"   << num[num.size() - 2].word_value << endl;
			cout << "ADD\tAX," << num[num.size() - 1].word_value << endl;
			cout << "MOV\t" << newword.word_value <<",AX" << endl;
			objectstringkeep = "MOV\tAX," + num[num.size() - 2].word_value + "\n";
			objectcode_vector.push_back(objectstringkeep);
			objectstringkeep = "ADD\tAX," + num[num.size() - 1].word_value + "\n";
			objectcode_vector.push_back(objectstringkeep);
			objectstringkeep = "MOV\t" + newword.word_value+",AX" + "\n";
			objectcode_vector.push_back(objectstringkeep);
			num.pop_back();
			num.pop_back();
			num.push_back(newword);
			i++;
			continue;
		}
		if (postfixexpression_vector[i].word_value == "-")
		{
			Word newword = { "temporary","temporarysave" + to_string(index) };
			index++;
			cout << "MOV\tAX," << num[num.size() - 2].word_value << endl;
			cout << "SUB\tAX," << num[num.size() - 1].word_value << endl;
			cout << "MOV\t" << newword.word_value << ",AX" << endl;
			objectstringkeep = "MOV\tAX," + num[num.size() - 2].word_value + "\n";
			objectcode_vector.push_back(objectstringkeep);
			objectstringkeep = "SUB\tAX," + num[num.size() - 1].word_value + "\n";
			objectcode_vector.push_back(objectstringkeep);
			objectstringkeep = "MOV\t" + newword.word_value + ",AX" + "\n";
			objectcode_vector.push_back(objectstringkeep);

			num.pop_back();
			num.pop_back();
			num.push_back(newword);
			i++;
			continue;
		}
		if (postfixexpression_vector[i].word_value == "*")
		{
			Word newword = { "temporary","temporarysave" + to_string(index) };
			index++;
			cout << "MOV\tAX," << num[num.size() - 2].word_value << endl;
			cout << "MOV\tBX," << num[num.size() - 1].word_value << endl;
			cout << "MUL\tBX" << endl;
			cout << "MOV\t" << newword.word_value << ",AX" << endl;

			objectstringkeep = "MOV\tAX," + num[num.size() - 2].word_value + "\n";
			objectcode_vector.push_back(objectstringkeep);
			objectstringkeep = "MOV\tBX," + num[num.size() - 1].word_value + "\n";
			objectcode_vector.push_back(objectstringkeep);
			objectstringkeep = "MUL\tBX\n";
			objectcode_vector.push_back(objectstringkeep);
			objectstringkeep = "MOV\t" + newword.word_value + ",AX" + "\n";
			objectcode_vector.push_back(objectstringkeep);

			num.pop_back();
			num.pop_back();
			num.push_back(newword);
			i++;
			continue;
		}
		if (postfixexpression_vector[i].word_value == "/")
		{
			Word newword = { "temporary","temporarysave" + to_string(index) };
			index++;
			cout << "MOV\tAX," << num[num.size() - 2].word_value << endl;
			cout << "CWD" << endl;
			cout << "MOV\tBX," << num[num.size() - 1].word_value << endl;
			cout << "DIV\tBX" << endl;
			cout << "MOV\t" << newword.word_value << ",AX" << endl;
			objectstringkeep = "MOV\tAX," + num[num.size() - 2].word_value + "\n";
			objectcode_vector.push_back(objectstringkeep);
			objectstringkeep = "CWD\n";
			objectcode_vector.push_back(objectstringkeep);
			objectstringkeep = "MOV\tBX," + num[num.size() - 1].word_value + "\n";
			objectcode_vector.push_back(objectstringkeep);
			objectstringkeep = "DIV\tBX\n";
			objectcode_vector.push_back(objectstringkeep);
			objectstringkeep = "MOV\t" + newword.word_value + ",AX" + "\n";
			objectcode_vector.push_back(objectstringkeep);
			num.pop_back();
			num.pop_back();
			num.push_back(newword);
			i++;
			continue;
		}
		
		cout << "���ʽ����ʱ���ִ���" << endl;
		break;
	}
	cout << "MOV\tAX," << num[0].word_value << endl;
	cout << "MOV\t" << resultplace.word_value << ",AX" << endl;
	objectstringkeep = "MOV\tAX," + num[0].word_value + "\n";
	objectcode_vector.push_back(objectstringkeep);
	objectstringkeep = "MOV\t" + resultplace.word_value + ",AX" + "\n";
	objectcode_vector.push_back(objectstringkeep);

}
//Ŀ�꣺�ܹ����cout�е��ַ����Լ������ͱ��ʽ��
// Ŀǰ��ɣ��ܹ�����ַ�����
//ĿǰǷȱ�����ڱ����������//������õ����ӳ���ķ���ʵ�����ֱ�����д��
void TranslateCout(vector<Word> coutsentence)
{
	vector<Word> temporarysave;//����������ľ�
	for (int j = 0; j < coutsentence.size(); j++)
	{
		temporarysave.push_back(coutsentence[j]);
	}
	//���Ҿ����е��ַ���
	int i=0;
	while (i < temporarysave.size())
	{
		Word nowword = temporarysave[i];
		if (nowword.word_type == "string")
		{
			Wordforstring newstring = { temporarysave[i].word_type,temporarysave[i].word_value,stringkeeper_vector.size() };
			stringkeeper_vector.push_back(newstring);
			cout << "LEA  DX, string" + to_string(newstring.index) << endl;
			cout << "MOV  AH, 9"  << endl;
			cout << "INT  21H"  << endl;
			objectstringkeep = "LEA  DX, string" + to_string(newstring.index) + "\n";
			objectcode_vector.push_back(objectstringkeep);
			objectstringkeep = "MOV  AH, 9\n";
			objectcode_vector.push_back(objectstringkeep);
			objectstringkeep ="INT  21H \n";
			objectcode_vector.push_back(objectstringkeep);
		}
		else
		{
			if (nowword.word_type == "token")
			{
				cout << "MOV \tAX,"+ nowword.word_value << endl;
				cout << "CALL\tCOUTD"  << endl;//����coutd����
				objectstringkeep = "MOV \tAX," + nowword.word_value + "\n";
				objectcode_vector.push_back(objectstringkeep);
				objectstringkeep = "CALL\tCOUTD\n";
				objectcode_vector.push_back(objectstringkeep);
			}
			else
			{
				if (nowword.word_value == "endl")
				{
					cout << "LEA  DX, endl"  << endl;
					cout << "MOV  AH, 9" << endl;
					cout << "INT  21H" << endl;
					objectstringkeep = "LEA  DX, endl\n";
					objectcode_vector.push_back(objectstringkeep);
					objectstringkeep = "MOV  AH, 9\n";
					objectcode_vector.push_back(objectstringkeep);
					objectstringkeep = "INT  21H \n";
					objectcode_vector.push_back(objectstringkeep);
				}
			}
		}
		i++;
	}
}
//���ڱ���������ʼ���ķ���
void TranslateDefineVariable(vector<Word> definevariable)
{
	vector<Word> temporarysave;//����������ľ�
	for (int j = 0; j < definevariable.size(); j++)
	{
		temporarysave.push_back(definevariable[j]);
	}
	//���Ҿ����е��ַ���
	int i = 0;
	
	if (temporarysave[0].word_value == "int"){
		Variable avariable = { temporarysave[1].word_value,false,0,"int"};//���֣��Ƿ񱻸����ʼ����ʼֵ������
		variable_vector.push_back(avariable);
	}else{
		cout << "����䲻�Ǳ����������" << endl;
		return;
	}
	if (temporarysave[2].word_value == ";"){
		return;
		
	}
	if (temporarysave[2].word_value == "=")
	{
		//���ñ����ĳ�ʼ������Ϊ�Ѿ���ʼ��
		int i = 0;
		for (i = 0; i < variable_vector.size();i++) {
			if (variable_vector[i].name == temporarysave[1].word_value)
			{
				variable_vector[i].ifinit = true;
			}
		}
		//���Ⱥź�ı��ʽ��ȡ����
		vector<Word> expressiontemporary;//����������ľ�
		expressiontemporary.clear();
		for (i = 3; i < temporarysave.size(); i++)
		{
			//���ʽ��ȡ
			expressiontemporary.push_back(temporarysave[i]);
		}
		//�����׺���ʽ
		Makepostfixexpression(expressiontemporary);
		//������ʽ������洢�ڱ�����;
		TranslateArithmetic(temporarysave[1]);
		return;
	}

	cout << "������ʼ���������" << endl;
	return;
}
//���ڸ�ֵ���ķ���
void TranslateAssignment(vector<Word> Assignment){

	vector<Word> temporarysave;//����������ľ�
	for (int j = 0; j < Assignment.size(); j++)
	{
		temporarysave.push_back(Assignment[j]);
	}
	//���ұ����Ƿ��Ѿ�����
	bool ifdefinedvariable = false;
	int i = 0;
	for (i = 0; i < variable_vector.size(); i++) {
		if (variable_vector[i].name == temporarysave[0].word_value)
		{
			ifdefinedvariable = true;
		}
	}
	if (ifdefinedvariable == false)
	{
		cout << "�ñ����ڸ�ֵǰδ����"+ temporarysave[0].word_value << endl;
		return;
	}

	if (temporarysave[1].word_value == "=")
	{
		//���Ⱥź�ı��ʽ��ȡ����
		vector<Word> expressiontemporary;//����������ľ�
		expressiontemporary.clear();
		for (i = 2; i < temporarysave.size(); i++)
		{
			//���ʽ��ȡ
			expressiontemporary.push_back(temporarysave[i]);
		}
		//�����׺���ʽ
		Makepostfixexpression(expressiontemporary);
		//������ʽ������洢�ڱ�����;
		TranslateArithmetic(temporarysave[0]);
		return;

	}


	cout << "error:�����ڸ�ֵ��ʱ����ִ��󣺿���ԭ��ʹ���˻�δ����ĸ�ֵ����" << endl;
	return;
}
//����forѭ�����
void Translateforsen(vector<Word> forsen) {
	bool ifshowminsentence = false;

	vector<Word> temporarysave;//����������ľ�
	vector<int> branchcount;//������������еķֺŵĸ�����λ��
	vector<Word> Arithmetic;//��������Ƚ�����еļ���ʽ
	int i;
	temporarysave.clear();
	for (int j = 0; j < forsen.size(); j++)
	{
		temporarysave.push_back(forsen[j]);
	}
	if (temporarysave[0].word_value != "for")
	{
		cout << "forѭ�����û��for��ͷ��" << endl;
	}
	for (i = 0; i < temporarysave.size(); i++)
	{
		if (temporarysave[i].word_value == ";") {
			branchcount.push_back(i);
		}
	}
	//for( ; ; ){ ; ; ; ; }
	//�����һ���ֺ��е���ֵ,,���ڿ��ܵ�һ���ֺ�ǰΪ���ţ��������⴦��
	if (temporarysave[branchcount[0] - 1].word_value != "(")
	{
		//�����ź�ı��ʽ��ȡ����
		vector<Word> expressiontemporary;//����������ľ�
		expressiontemporary.clear();
		for (i = 2; i <=branchcount[0]; i++)
		{
			//���ʽ��ȡ
			expressiontemporary.push_back(temporarysave[i]);
		}
		if (expressiontemporary[0].word_type == "keyword")
		{
			if (ifshowminsentence) { cout << "�׸�����Ϊ������:�����Ϊint" << endl; }
			//��������䷭��
			TranslateDefineVariable(expressiontemporary);
		}
		else
		{
			TranslateAssignment(expressiontemporary);
		}
		//����
		if (ifshowminsentence)
		{
			cout<<"��һ�����ʽΪ:" ;
				for (int j = 0; j < expressiontemporary.size(); j++)
			{
	           cout << expressiontemporary[j].word_value  ;
            }
				cout << endl;
		}
	}
	//���ж�ǰ���õ�һ����־λ��
	int number = flag_vector.size();
	string flagname0 = "flag" + to_string(number) + "0";
	string flagname1 = "flag" + to_string(number) + "1";
	flag_vector.push_back(flagname0);
	cout << flagname0 <<":" << endl;
	objectstringkeep = flagname0 + ":\n";
	objectcode_vector.push_back(objectstringkeep);
	//����ڶ����ֺŵ��������ֺ�֮����ж����
	
	//����ȽϷ���֮ǰ����
	if (ifshowminsentence){
		cout << "�����ж���俪ʼ����" << endl;
		cout << "����ǰһ����ʽ��ֵ" << endl;
	}
	Arithmetic.clear();
	Word compareop;
	Word waitcompare0 = { "waitcompare","waitcompare0" };//���������һ�����ʽ�Ľ��
	Word waitcompare1 = { "waitcompare","waitcompare1" };//��������ڶ������ʽ�Ľ��
	for (i = branchcount[0]+1; temporarysave[i].word_value!="<"&&temporarysave[i].word_value != ">"&&temporarysave[i].word_value != "=="&&temporarysave[i].word_value != "<=" && temporarysave[i].word_value != ">="; i++)
	{
		//���ʽ��ȡ
		Arithmetic.push_back(temporarysave[i]);
	}
	Arithmetic.push_back(temporarysave[branchcount[0]]);//���һ�����ʽ֮�м���һ���ֺű�ʾ����
	compareop.word_type = temporarysave[i].word_type;
	compareop.word_value = temporarysave[i].word_value;
	//����
	if (ifshowminsentence)
	{
		cout << "��2.2�����ʽΪ:";
		for (int j = 0; j < Arithmetic.size(); j++)
		{
			cout << Arithmetic[j].word_value;
		}
		cout << endl;
	}
	//���ʽ��׺���ʽ��ֵ
	Makepostfixexpression(Arithmetic);
	//��׺���ʽ����=
	TranslateArithmetic(waitcompare0);
	if (ifshowminsentence) { cout << "���ں�һ����ʽ��ֵ" << endl; }
	//��һ����ʽ��ֵ
	Arithmetic.clear();
	i++;
	for (; temporarysave[i].word_value!=";"; i++)
	{
		//���ʽ��ȡ
		Arithmetic.push_back(temporarysave[i]);
	}
	Arithmetic.push_back(temporarysave[branchcount[0]]);//���2�����ʽ֮�м���һ���ֺű�ʾ����
	//���ʽ��׺���ʽ��ֵ
	Makepostfixexpression(Arithmetic);
	//��׺���ʽ����=
	TranslateArithmetic(waitcompare1);
	//����
	if (ifshowminsentence)
	{
		cout << "��2.2�����ʽΪ:";
		for (int j = 0; j < Arithmetic.size(); j++)
		{
			cout << Arithmetic[j].word_value ;
		}
		cout << endl;
	}
	//��ʼ����ȽϷ���
	cout << "MOV\tAX,waitcompare0"<<endl;
	cout << "CMP\tAX,waitcompare1"<<endl;
	objectstringkeep = "MOV\tAX,waitcompare0\n";
	objectcode_vector.push_back(objectstringkeep);
	objectstringkeep = "CMP\tAX,waitcompare1\n";
	objectcode_vector.push_back(objectstringkeep);


	if (compareop.word_value == "<") {
		//�����ڵ�����ת
		/*cout << "JL\t" << flagname1<<endl;*/
		cout << "JGE\t" << flagname1 << endl;
		objectstringkeep = "JGE\t" + flagname1+"\n";
		objectcode_vector.push_back(objectstringkeep);
	}else{

		if (compareop.word_value == "<=") {
			//��������ת
			/*cout << "JLE\t" << flagname1 << endl;*/
			cout << "JG\t" << flagname1 << endl;
			objectstringkeep = "JG\t" + flagname1 + "\n";
			objectcode_vector.push_back(objectstringkeep);
		}
		else {

			if (compareop.word_value == ">") {
				//��С�ڵ�����ת
				/*cout << "JG\t" << flagname1 << endl;*/
				cout << "JLE\t" << flagname1 << endl;
				objectstringkeep ="JLE\t" + flagname1 + "\n";
				objectcode_vector.push_back(objectstringkeep);
			}
			else {

				if (compareop.word_value == ">=") {
					//��С����ת
				/*	cout << "JGE\t" << flagname1 << endl;*/
					cout << "JL\t" << flagname1 << endl;
					objectstringkeep = "JL\t" + flagname1 + "\n";
					objectcode_vector.push_back(objectstringkeep);
				}
				else {

					if (compareop.word_value == "==") {
						//����������ת
					/*	cout << "JE\t" << flagname1 << endl;*/
						cout << "JNE\t" << flagname1 << endl;
						objectstringkeep = "JNE\t" + flagname1 + "\n";
						objectcode_vector.push_back(objectstringkeep);
					}
					else {
						cout << "����δ����ķ���" << endl;
						return;
					}
				}
			}
		}
	}

	//�����������ı��ʽ
	vector<Word> branchsentence;//����������ľ�
	int number_branch = 2;
	while (number_branch<branchcount.size()) {
		//�����ֿշֺ�ʱʲô�಻��
		if (temporarysave[branchcount[number_branch] - 1].word_value == "{" || temporarysave[branchcount[number_branch] - 1].word_value == ";") {
			cout << "���ֿշֺ�" << endl;
			number_branch++;
			continue;
		}
		//��һ�����ʽ��ǰһλδ{��Ϊ���⴦��
		if (number_branch == 2)
		{
			branchsentence.clear();
			for (i = 0; i < temporarysave.size(); i++)
			{
				if (temporarysave[i].word_value == "{") {
					break;
				}
			}
			if (ifshowminsentence)
			{
				cout << "�ҵ�������" << endl;
			}
			for (i++; temporarysave[i].word_value != ";";i++)
			{
				branchsentence.push_back(temporarysave[i]);
			}
			branchsentence.push_back(temporarysave[i]);
			if (branchsentence[0].word_type == "keyword")
			{
				if (ifshowminsentence)
				{
					cout << "�׸�����Ϊ������:�����Ϊint" << endl;
				}
				//��������䷭��
				TranslateDefineVariable(branchsentence);
			}
			else
			{
				TranslateAssignment(branchsentence);
			}
			number_branch++;
			continue;
		}
		else
		{
			branchsentence.clear();
			for (i=branchcount[number_branch-1]+1; temporarysave[i].word_value != ";"; i++)
			{
				branchsentence.push_back(temporarysave[i]);
			}
			branchsentence.push_back(temporarysave[i]);
			if (branchsentence[0].word_type == "keyword")
			{
				if (ifshowminsentence){ cout << "�׸�����Ϊ������:�����Ϊint" << endl; }
				
				//��������䷭��
				TranslateDefineVariable(branchsentence);
			}
			else
			{
				TranslateAssignment(branchsentence);
			}

			//����
			if (ifshowminsentence)
			{
				cout << "��" << number_branch << "�����ʽΪ:";
				for (int j = 0; j < branchsentence.size(); j++)
				{
					cout << branchsentence[j].word_value;
				}
				cout << endl;
			}


			number_branch++;
			continue;
		}

	
	}

	//������������ʽ  ; )
	if (temporarysave[branchcount[1] +1].word_value == ")" ){
		cout << "���������ʽΪ��" << endl;
	}
	else {

		branchsentence.clear();
		for (i = branchcount[1] + 1; temporarysave[i].word_value != ")"; i++)
		{
			branchsentence.push_back(temporarysave[i]);
		}
		branchsentence.push_back(temporarysave[branchcount[1]]);//��ӷֺ�
		if (branchsentence[0].word_type == "keyword")
		{
			if (ifshowminsentence) { cout << "�׸�����Ϊ������:�����Ϊint" << endl; }
			//��������䷭��
			TranslateDefineVariable(branchsentence);
		}
		else
		{
			TranslateAssignment(branchsentence);
		}

		//����
		if (ifshowminsentence)
		{
			cout << "�� 3�����ʽΪ:";
			for (int j = 0; j < branchsentence.size(); j++)
			{
				cout << branchsentence[j].word_value;
			}
			cout << endl;
		}

	}
	//��ת����һ����־λ
	cout << "JMP\t"<<flagname0 << endl;
	objectstringkeep = "JMP\t" + flagname0 + "\n";
	objectcode_vector.push_back(objectstringkeep);
	//���ж�ǰ���õڶ�����־λ��
	cout << flagname1<<":" << endl;	
	objectstringkeep = flagname1 + ":\n";
	objectcode_vector.push_back(objectstringkeep);
}

void TranslateAllSentence(){
	for (int i = 0; i < sentence_vector.size(); i++)
	{
		if (AnalyseAssignment(sentence_vector[i]) == true)
		{
			cout << "���" << i << "Ϊ��ֵ�����߳�ʼ����ֵ���" << endl;
			if (sentence_vector[i][0].word_type == "keyword")
			{
				TranslateDefineVariable(sentence_vector[i]);
			}
			else
			{
				TranslateAssignment(sentence_vector[i]);
			}
			
			continue;
		}
		if (AnalyseForSentence(sentence_vector[i]) == true)
		{
			cout << "���" << i << "Ϊfor���" << endl;
			Translateforsen(sentence_vector[i]);
			continue;
		}
		if (AnalyseOutputsentence(sentence_vector[i]) == true)
		{
			cout << "���" << i << "Ϊcout���" << endl;
			TranslateCout(sentence_vector[i]);
			continue;
		}
		if (AnalyseDefine(sentence_vector[i]) == true)
		{
			cout << "���" << i << "Ϊ����������" << endl;
			TranslateDefineVariable(sentence_vector[i]);
			continue;
		}
	}



}







