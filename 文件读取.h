#pragma once
#include <iostream>
using namespace std;
#include"��������.h"
#include <fstream>
#include <vector>
//#include"outputfile.h"


//���ļ��ж�ȡC����Դ����
void InputCode()
{
	ifstream inputFile;
	inputFile.open(INPUT_FILE, ios::in);
	if (!inputFile)
		cout << "�ļ���ʧ��:������" << endl;

	while (!inputFile.eof())
	{
		char p = inputFile.get();
		code_vector.push_back(p);
	}
	inputFile.close();
	code_vector.pop_back();   //�����ļ�������ʶ

	//�ڿ�������ʾ����Ĵ������ļ�
	/*OutputCode();*/
}

//���ļ���ȡ�򵥸�ֵ���
//void InputSentence()
//{
//	ifstream inputFile;
//	inputFile.open(INPUT_SENTENCE, ios::in);
//	if (!inputFile)
//		cout << "�ļ���ʧ��" << endl;
//
//	while (!inputFile.eof())
//	{
//		char p = inputFile.get();
//		code_vector.push_back(p);
//	}
//	inputFile.close();
//	code_vector.pop_back();//�����ļ�������ʶ
//}

//���ļ��ж�ȡ�ؼ��֡�����������޷�(ע:�ڶ�ȡ�ļ���������������ʽ��ȡ ��ûһ���ؼ��ʲ��������Կո�Ϊ���)
void InputKOB()
{
	ifstream keyFile;
	keyFile.open(KEYWORDS_FILE, ios::in);
	if (!keyFile)
		cout << "�ļ���ʧ�ܣ��ؼ���.txt" << endl;
	while (!keyFile.eof())
	{
		string str;
		keyFile >> str;
		keywords_vector.push_back(str);
	}
	keyFile.close();

	ifstream operatorFile;
	operatorFile.open(OPERATOR_FILE, ios::in);
	if (!operatorFile)
		cout << "�ļ���ʧ�ܣ������.txt" << endl;
	while (!operatorFile.eof())
	{
		string str;
		operatorFile >> str;
		operator_vector.push_back(str);
	}
	operatorFile.close();


	//����ļ��Ķ���
	ifstream boundaryFile;
	boundaryFile.open(BOUNDARY_FILE, ios::in);
	if (!boundaryFile)
		cout << "�ļ���ʧ�ܣ����.txt" << endl;
	while (!boundaryFile.eof())
	{
		char c = boundaryFile.get();
		string str;
		str += c;
	 /*  string str;
		boundaryFile >> str;*/
		boundary_vector.push_back(str);
	}
	boundaryFile.close();
	boundary_vector.pop_back();

	////�ڿ���̨��ʾ��ȡ����Ŀ
	//OutputKOB();
}
