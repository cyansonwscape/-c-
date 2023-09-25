#pragma once
#include <iostream>
using namespace std;
#include"常量定义.h"
#include <fstream>
#include <vector>
//#include"outputfile.h"


//从文件中读取C语言源代码
void InputCode()
{
	ifstream inputFile;
	inputFile.open(INPUT_FILE, ios::in);
	if (!inputFile)
		cout << "文件打开失败:待分析" << endl;

	while (!inputFile.eof())
	{
		char p = inputFile.get();
		code_vector.push_back(p);
	}
	inputFile.close();
	code_vector.pop_back();   //弹出文件结束标识

	//在控制器显示读入的待分析文件
	/*OutputCode();*/
}

//从文件读取简单赋值语句
//void InputSentence()
//{
//	ifstream inputFile;
//	inputFile.open(INPUT_SENTENCE, ios::in);
//	if (!inputFile)
//		cout << "文件打开失败" << endl;
//
//	while (!inputFile.eof())
//	{
//		char p = inputFile.get();
//		code_vector.push_back(p);
//	}
//	inputFile.close();
//	code_vector.pop_back();//弹出文件结束标识
//}

//从文件中读取关键字、运算符、界限符(注:在读取文件是是以输入流方式读取 即没一个关键词操作符号以空格为间断)
void InputKOB()
{
	ifstream keyFile;
	keyFile.open(KEYWORDS_FILE, ios::in);
	if (!keyFile)
		cout << "文件打开失败：关键字.txt" << endl;
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
		cout << "文件打开失败：运算符.txt" << endl;
	while (!operatorFile.eof())
	{
		string str;
		operatorFile >> str;
		operator_vector.push_back(str);
	}
	operatorFile.close();


	//界符文件的读入
	ifstream boundaryFile;
	boundaryFile.open(BOUNDARY_FILE, ios::in);
	if (!boundaryFile)
		cout << "文件打开失败：界符.txt" << endl;
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

	////在控制台显示读取的数目
	//OutputKOB();
}
