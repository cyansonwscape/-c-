#pragma once
#include<stack>
#include <iostream>
using namespace std;
#include "常量定义.h"

//将词法分析的结果分为一个一个的句子
void SegmentingSentences() 
{
	//stack <int> stk;
	//for (int i = 0; i < 10; i++) {
	//	stk.push(i);
	//}
	//cout << stk.size() << endl;
	//cout << stk.top() << endl;
	//stk.pop();
	//cout << stk.empty() << endl;

	//在//存放单词的数组vector<Word>word_vector;之中读取数据
	//以；和{ }判断是否为一个句子并且将句子存储在
	//判断句子结束的条件1.出现;且不曾出现过{
	//					2.出现      }
	//并且在读取句子的过程之中去除注释和空格（解决问题：制表符号tab没有识别所以出现识别错误）
	//将字符串转化为strin类型可以直接比较
	//string zhushi = "//";
	//if (zhushi == "//") {
	//	cout << zhushi;
	//}
	
	int annotation_flag = 0;//该注释符号用来表示是否有注释符号当有注释符号的时候改行内容不读取
	int count_sen = 0;//用来计数有多少给句子
	int littlebracket_flag = 0;
	int bigbracket_flag = 0;
	bool have_bigbracket = 0;//用来统计是否存在过大括号
	vector<Word> temporarysave;

	for (int i = 0; i < word_vector.size(); i++) {
		//以下部分用来消除注释信息
		if (word_vector[i].word_value == "//")
		{
			annotation_flag = 1;
		}
		if (word_vector[i].word_value == "enter")
		{
			annotation_flag = 0;
		}
		if (word_vector[i].word_value == "tab" || word_vector[i].word_value == "space" || word_vector[i].word_value == "enter" )
		{
			continue;
		}



		if (annotation_flag == 0)
		{
			temporarysave.push_back(word_vector[i]);
			//以下用来判断是否为分号、大括号、小括号
			if (word_vector[i].word_value == "(") { littlebracket_flag++; }
			if (word_vector[i].word_value == "{") { bigbracket_flag++; have_bigbracket = true; }
			if (word_vector[i].word_value == ")") { littlebracket_flag--; }
			if (word_vector[i].word_value == "}") { bigbracket_flag--; }


			//当遇到分号";"和右大括号"}"时句子可能结束
			if (word_vector[i].word_value == ";" && have_bigbracket == false && littlebracket_flag == 0)
			{
				sentence_vector.push_back(temporarysave);
				//清空暂时保存一个句子的vector
				temporarysave.clear();
				have_bigbracket = 0;
				littlebracket_flag = 0;
				bigbracket_flag = 0;
				count_sen++;
			}

			if (word_vector[i].word_value == "}" && bigbracket_flag == 0 && littlebracket_flag == 0)
			{
				sentence_vector.push_back(temporarysave);
				//清空暂时保存一个句子的vector
				temporarysave.clear();
				have_bigbracket = 0;
				littlebracket_flag = 0;
				bigbracket_flag = 0;
				count_sen++;
			}

			cout << word_vector[i].word_value;
		}
	

	}






}
