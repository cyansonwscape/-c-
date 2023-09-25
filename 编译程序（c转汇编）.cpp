// 编译程序（c转汇编）.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;
#include "常量定义.h"
#include "文件读取.h"
#include "词法分析.h"
#include "分割句子.h"
#include"语法分析.h"
#include"翻译为目标语言.h"
#include"后缀表达式转化.h"
#include"输出文件.h"
int main()
{
	//读取关键字
	InputKOB();

	//输出界符种类
	/*for (int i = 0; i < operator_vector.size(); i++)
	{
		cout << i << ' ' << operator_vector[i] << endl;
	}*/
	//for (int i = 0; i < boundary_vector.size(); i++)
	//{
	//	cout<<i<<' ' << boundary_vector[i] << endl;
	//}


	//读取输入文件
	InputCode();
	//进行词法分析
	Controller();
//	for (int i = 0; i < word_vector.size(); i++)
//{
//	cout<<i<<'\t' << word_vector[i].word_value<<'\t'<<word_vector[i].word_type << endl;
//}
	SegmentingSentences();

	//int i = sentence_vector.size();
	//cout << endl;
	//cout <<"句子的个数为:"<<i << endl;
	cout << endl;
for (int i = 0; i < sentence_vector.size(); i++)
{
	cout << "句子:" << i<<"   ";
  	for (int j = 0; j < sentence_vector[i].size(); j++)
{
	cout << sentence_vector[i][j].word_value ;
}
	cout << endl;
}
//AnalyseAssignment(sentence_vector[0]);
//cout << endl << endl;
//AnalyseExprexxion(sentence_vector[1]);
//cout << endl << endl;
//AnalyseCompare(sentence_vector[2]);
//cout << endl << endl;
//AnalyseForSentence(sentence_vector[3]);
//cout << endl << endl;
//AnalyseOutputsentence(sentence_vector[4]);
//cout << endl << endl;
//AnalyseDefine(sentence_vector[5]);
//cout << endl << endl;
//TranslateCout(sentence_vector[5]);
//TranslateCout(sentence_vector[6]);
//TranslateCout(sentence_vector[7]);
//TranslateCout(sentence_vector[8]);
//
//	for (int i = 0; i < stringkeeper_vector.size(); i++)
//{
//	cout<<"string"+to_string(i) << '\t' << stringkeeper_vector[i].word_value  << endl;
//}
//cout << endl << endl;
////表达式语法分析
//AnalyseExprexxion(sentence_vector[9]);
////表达式后缀表达式求值
//Makepostfixexpression(sentence_vector[9]);
////后缀表达式翻译=
//Word testword = { "token","Z" };
//TranslateArithmetic(testword);
//
//cout << endl << endl;
////表达式语法分析
//AnalyseExprexxion(sentence_vector[10]);
////表达式后缀表达式求值
//Makepostfixexpression(sentence_vector[10]);
////后缀表达式翻译=
//TranslateArithmetic(testword);
//cout << endl << endl;
////表达式语法分析
//AnalyseExprexxion(sentence_vector[11]);
////表达式后缀表达式求值
//Makepostfixexpression(sentence_vector[11]);
////后缀表达式翻译=
//TranslateArithmetic(testword);
//cout << endl << endl;
//AnalyseAssignment(sentence_vector[0]);
//cout << endl;
//TranslateDefineVariable(sentence_vector[0]);
//
//
//TranslateAssignment(sentence_vector[12]);


//cout << endl << endl;
//AnalyseDefine(sentence_vector[3]);
//TranslateDefineVariable(sentence_vector[3]);
//cout << endl << endl;
//AnalyseForSentence(sentence_vector[4]);
//Translateforsen(sentence_vector[4]);
//cout << endl << endl;
//AnalyseOutputsentence(sentence_vector[5]);
//TranslateCout(sentence_vector[5]);
//for (int i = 0; i < objectcode_vector.size(); i++) {
//
//	cout << objectcode_vector[i];
//}
//
//OutputTranlatedCodeToFile();

AnalyseAllSentence();
TranslateAllSentence();


//for (int i = 0; i < objectcode_vector.size(); i++) {
//
//	cout << objectcode_vector[i];
//}
OutputTranlatedCodeToFile();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
