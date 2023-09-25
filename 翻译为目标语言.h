#pragma once
#include <iostream>
using namespace std;
#include"常量定义.h"
#include <fstream>
#include <vector>
#include <string>
#include "后缀表达式转化.h"


//表达式翻译句子，将后缀表达式堆栈中的数据进行求值并且保存在指定的地址之中
void TranslateArithmetic(Word resultplace) {
	bool iftest = false;

	if(iftest){ cout << "开始翻译" << endl; }
	int i = 0;//用来遍历后缀表达式的堆栈
	vector<Word> num;//保存数字
	num.clear();
	int index = 0;//用来记录暂时存储的数量
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
		
		cout << "表达式翻译时出现错误" << endl;
		break;
	}
	cout << "MOV\tAX," << num[0].word_value << endl;
	cout << "MOV\t" << resultplace.word_value << ",AX" << endl;
	objectstringkeep = "MOV\tAX," + num[0].word_value + "\n";
	objectcode_vector.push_back(objectstringkeep);
	objectstringkeep = "MOV\t" + resultplace.word_value + ",AX" + "\n";
	objectcode_vector.push_back(objectstringkeep);

}
//目标：能够输出cout中的字符串以及变量和表达式；
// 目前完成：能够输出字符串；
//目前欠缺：对于变量的输出；//这里采用调用子程序的方法实现数字变量的写入
void TranslateCout(vector<Word> coutsentence)
{
	vector<Word> temporarysave;//保存待分析的句
	for (int j = 0; j < coutsentence.size(); j++)
	{
		temporarysave.push_back(coutsentence[j]);
	}
	//查找句子中的字符串
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
				cout << "CALL\tCOUTD"  << endl;//调用coutd函数
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
//对于变量定义或初始化的翻译
void TranslateDefineVariable(vector<Word> definevariable)
{
	vector<Word> temporarysave;//保存待分析的句
	for (int j = 0; j < definevariable.size(); j++)
	{
		temporarysave.push_back(definevariable[j]);
	}
	//查找句子中的字符串
	int i = 0;
	
	if (temporarysave[0].word_value == "int"){
		Variable avariable = { temporarysave[1].word_value,false,0,"int"};//名字，是否被赋予初始，初始值，类型
		variable_vector.push_back(avariable);
	}else{
		cout << "该语句不是变量定义语句" << endl;
		return;
	}
	if (temporarysave[2].word_value == ";"){
		return;
		
	}
	if (temporarysave[2].word_value == "=")
	{
		//将该变量的初始化设置为已经初始化
		int i = 0;
		for (i = 0; i < variable_vector.size();i++) {
			if (variable_vector[i].name == temporarysave[1].word_value)
			{
				variable_vector[i].ifinit = true;
			}
		}
		//将等号后的表达式提取出来
		vector<Word> expressiontemporary;//保存待分析的句
		expressiontemporary.clear();
		for (i = 3; i < temporarysave.size(); i++)
		{
			//表达式提取
			expressiontemporary.push_back(temporarysave[i]);
		}
		//计算后缀表达式
		Makepostfixexpression(expressiontemporary);
		//翻译表达式并将其存储在变量里;
		TranslateArithmetic(temporarysave[1]);
		return;
	}

	cout << "变量初始化定义出错" << endl;
	return;
}
//对于赋值语句的翻译
void TranslateAssignment(vector<Word> Assignment){

	vector<Word> temporarysave;//保存待分析的句
	for (int j = 0; j < Assignment.size(); j++)
	{
		temporarysave.push_back(Assignment[j]);
	}
	//查找变量是否已经定义
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
		cout << "该变量在赋值前未定义"+ temporarysave[0].word_value << endl;
		return;
	}

	if (temporarysave[1].word_value == "=")
	{
		//将等号后的表达式提取出来
		vector<Word> expressiontemporary;//保存待分析的句
		expressiontemporary.clear();
		for (i = 2; i < temporarysave.size(); i++)
		{
			//表达式提取
			expressiontemporary.push_back(temporarysave[i]);
		}
		//计算后缀表达式
		Makepostfixexpression(expressiontemporary);
		//翻译表达式并将其存储在变量里;
		TranslateArithmetic(temporarysave[0]);
		return;

	}


	cout << "error:变量在赋值的时候出现错误：可能原因使用了还未定义的赋值符号" << endl;
	return;
}
//翻译for循环语句
void Translateforsen(vector<Word> forsen) {
	bool ifshowminsentence = false;

	vector<Word> temporarysave;//保存待分析的句
	vector<int> branchcount;//用来计算句子中的分号的个数与位置
	vector<Word> Arithmetic;//用来保存比较语句中的计算式
	int i;
	temporarysave.clear();
	for (int j = 0; j < forsen.size(); j++)
	{
		temporarysave.push_back(forsen[j]);
	}
	if (temporarysave[0].word_value != "for")
	{
		cout << "for循环语句没有for开头？" << endl;
	}
	for (i = 0; i < temporarysave.size(); i++)
	{
		if (temporarysave[i].word_value == ";") {
			branchcount.push_back(i);
		}
	}
	//for( ; ; ){ ; ; ; ; }
	//计算第一个分号中的数值,,由于可能第一个分号前为括号，所以特殊处理
	if (temporarysave[branchcount[0] - 1].word_value != "(")
	{
		//将括号后的表达式提取出来
		vector<Word> expressiontemporary;//保存待分析的句
		expressiontemporary.clear();
		for (i = 2; i <=branchcount[0]; i++)
		{
			//表达式提取
			expressiontemporary.push_back(temporarysave[i]);
		}
		if (expressiontemporary[0].word_type == "keyword")
		{
			if (ifshowminsentence) { cout << "首个单词为保留字:大概率为int" << endl; }
			//将定义语句翻译
			TranslateDefineVariable(expressiontemporary);
		}
		else
		{
			TranslateAssignment(expressiontemporary);
		}
		//测试
		if (ifshowminsentence)
		{
			cout<<"第一个表达式为:" ;
				for (int j = 0; j < expressiontemporary.size(); j++)
			{
	           cout << expressiontemporary[j].word_value  ;
            }
				cout << endl;
		}
	}
	//在判断前设置第一个标志位置
	int number = flag_vector.size();
	string flagname0 = "flag" + to_string(number) + "0";
	string flagname1 = "flag" + to_string(number) + "1";
	flag_vector.push_back(flagname0);
	cout << flagname0 <<":" << endl;
	objectstringkeep = flagname0 + ":\n";
	objectcode_vector.push_back(objectstringkeep);
	//处理第二个分号到第三个分号之间的判断语句
	
	//处理比较符号之前的数
	if (ifshowminsentence){
		cout << "对于判断语句开始计算" << endl;
		cout << "对于前一半表达式求值" << endl;
	}
	Arithmetic.clear();
	Word compareop;
	Word waitcompare0 = { "waitcompare","waitcompare0" };//用来保存第一个表达式的结果
	Word waitcompare1 = { "waitcompare","waitcompare1" };//用来保存第二个表达式的结果
	for (i = branchcount[0]+1; temporarysave[i].word_value!="<"&&temporarysave[i].word_value != ">"&&temporarysave[i].word_value != "=="&&temporarysave[i].word_value != "<=" && temporarysave[i].word_value != ">="; i++)
	{
		//表达式提取
		Arithmetic.push_back(temporarysave[i]);
	}
	Arithmetic.push_back(temporarysave[branchcount[0]]);//向第一个表达式之中加入一个分号表示结束
	compareop.word_type = temporarysave[i].word_type;
	compareop.word_value = temporarysave[i].word_value;
	//测试
	if (ifshowminsentence)
	{
		cout << "第2.2个表达式为:";
		for (int j = 0; j < Arithmetic.size(); j++)
		{
			cout << Arithmetic[j].word_value;
		}
		cout << endl;
	}
	//表达式后缀表达式求值
	Makepostfixexpression(Arithmetic);
	//后缀表达式翻译=
	TranslateArithmetic(waitcompare0);
	if (ifshowminsentence) { cout << "对于后一半表达式求值" << endl; }
	//后一半表达式求值
	Arithmetic.clear();
	i++;
	for (; temporarysave[i].word_value!=";"; i++)
	{
		//表达式提取
		Arithmetic.push_back(temporarysave[i]);
	}
	Arithmetic.push_back(temporarysave[branchcount[0]]);//向第2个表达式之中加入一个分号表示结束
	//表达式后缀表达式求值
	Makepostfixexpression(Arithmetic);
	//后缀表达式翻译=
	TranslateArithmetic(waitcompare1);
	//测试
	if (ifshowminsentence)
	{
		cout << "第2.2个表达式为:";
		for (int j = 0; j < Arithmetic.size(); j++)
		{
			cout << Arithmetic[j].word_value ;
		}
		cout << endl;
	}
	//开始处理比较符号
	cout << "MOV\tAX,waitcompare0"<<endl;
	cout << "CMP\tAX,waitcompare1"<<endl;
	objectstringkeep = "MOV\tAX,waitcompare0\n";
	objectcode_vector.push_back(objectstringkeep);
	objectstringkeep = "CMP\tAX,waitcompare1\n";
	objectcode_vector.push_back(objectstringkeep);


	if (compareop.word_value == "<") {
		//当大于等于跳转
		/*cout << "JL\t" << flagname1<<endl;*/
		cout << "JGE\t" << flagname1 << endl;
		objectstringkeep = "JGE\t" + flagname1+"\n";
		objectcode_vector.push_back(objectstringkeep);
	}else{

		if (compareop.word_value == "<=") {
			//当大于跳转
			/*cout << "JLE\t" << flagname1 << endl;*/
			cout << "JG\t" << flagname1 << endl;
			objectstringkeep = "JG\t" + flagname1 + "\n";
			objectcode_vector.push_back(objectstringkeep);
		}
		else {

			if (compareop.word_value == ">") {
				//当小于等于跳转
				/*cout << "JG\t" << flagname1 << endl;*/
				cout << "JLE\t" << flagname1 << endl;
				objectstringkeep ="JLE\t" + flagname1 + "\n";
				objectcode_vector.push_back(objectstringkeep);
			}
			else {

				if (compareop.word_value == ">=") {
					//当小于跳转
				/*	cout << "JGE\t" << flagname1 << endl;*/
					cout << "JL\t" << flagname1 << endl;
					objectstringkeep = "JL\t" + flagname1 + "\n";
					objectcode_vector.push_back(objectstringkeep);
				}
				else {

					if (compareop.word_value == "==") {
						//当不等于跳转
					/*	cout << "JE\t" << flagname1 << endl;*/
						cout << "JNE\t" << flagname1 << endl;
						objectstringkeep = "JNE\t" + flagname1 + "\n";
						objectcode_vector.push_back(objectstringkeep);
					}
					else {
						cout << "出现未定义的符号" << endl;
						return;
					}
				}
			}
		}
	}

	//处理大括号里的表达式
	vector<Word> branchsentence;//保存待分析的句
	int number_branch = 2;
	while (number_branch<branchcount.size()) {
		//当出现空分号时什么多不做
		if (temporarysave[branchcount[number_branch] - 1].word_value == "{" || temporarysave[branchcount[number_branch] - 1].word_value == ";") {
			cout << "出现空分号" << endl;
			number_branch++;
			continue;
		}
		//第一个表达式的前一位未{作为特殊处理
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
				cout << "找到大括号" << endl;
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
					cout << "首个单词为保留字:大概率为int" << endl;
				}
				//将定义语句翻译
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
				if (ifshowminsentence){ cout << "首个单词为保留字:大概率为int" << endl; }
				
				//将定义语句翻译
				TranslateDefineVariable(branchsentence);
			}
			else
			{
				TranslateAssignment(branchsentence);
			}

			//测试
			if (ifshowminsentence)
			{
				cout << "第" << number_branch << "个表达式为:";
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

	//处理第三个表达式  ; )
	if (temporarysave[branchcount[1] +1].word_value == ")" ){
		cout << "第三个表达式为空" << endl;
	}
	else {

		branchsentence.clear();
		for (i = branchcount[1] + 1; temporarysave[i].word_value != ")"; i++)
		{
			branchsentence.push_back(temporarysave[i]);
		}
		branchsentence.push_back(temporarysave[branchcount[1]]);//添加分号
		if (branchsentence[0].word_type == "keyword")
		{
			if (ifshowminsentence) { cout << "首个单词为保留字:大概率为int" << endl; }
			//将定义语句翻译
			TranslateDefineVariable(branchsentence);
		}
		else
		{
			TranslateAssignment(branchsentence);
		}

		//测试
		if (ifshowminsentence)
		{
			cout << "第 3个表达式为:";
			for (int j = 0; j < branchsentence.size(); j++)
			{
				cout << branchsentence[j].word_value;
			}
			cout << endl;
		}

	}
	//跳转至第一个标志位
	cout << "JMP\t"<<flagname0 << endl;
	objectstringkeep = "JMP\t" + flagname0 + "\n";
	objectcode_vector.push_back(objectstringkeep);
	//在判断前设置第二个标志位置
	cout << flagname1<<":" << endl;	
	objectstringkeep = flagname1 + ":\n";
	objectcode_vector.push_back(objectstringkeep);
}

void TranslateAllSentence(){
	for (int i = 0; i < sentence_vector.size(); i++)
	{
		if (AnalyseAssignment(sentence_vector[i]) == true)
		{
			cout << "语句" << i << "为赋值语句或者初始化赋值语句" << endl;
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
			cout << "语句" << i << "为for语句" << endl;
			Translateforsen(sentence_vector[i]);
			continue;
		}
		if (AnalyseOutputsentence(sentence_vector[i]) == true)
		{
			cout << "语句" << i << "为cout语句" << endl;
			TranslateCout(sentence_vector[i]);
			continue;
		}
		if (AnalyseDefine(sentence_vector[i]) == true)
		{
			cout << "语句" << i << "为定义变量语句" << endl;
			TranslateDefineVariable(sentence_vector[i]);
			continue;
		}
	}



}







