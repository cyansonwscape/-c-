#pragma once
#include <vector>
#include <string>
#include"常量定义.h"


//分析数字
void DigitAnalysis(const string word)
{
	Word new_word;
	new_word.word_type = "digit";
	new_word.word_value = word;

	word_vector.push_back(new_word);
	return;
}
//分析运算符
void OperatorAnalysis(const string word)
{
	//判断是否为运算符
	for (string str : operator_vector)
	{
		if (str == word)
		{
			Word new_word;
			new_word.word_type = "operator";
			new_word.word_value = word;

			word_vector.push_back(new_word);
			return;
		}
	}
}

//分析界符
void BoundaryAnalysis(const string word)
{
	Word new_word;
	new_word.word_type = "boundary";
	if (word == "\n")
		new_word.word_value = "enter";
	else if (word == " ")
		new_word.word_value = "space";
	else if (word == "\t")
		new_word.word_value = "tab";
	else
		new_word.word_value = word;
	word_vector.push_back(new_word);
	return;
}

//分析关键字或标识符
void LetterAnalysis(const string word)
{
	//判断是否为关键字
	for (string str : keywords_vector)
	{
		if (str == word)
		{
			Word new_word;
			new_word.word_type = "keyword";
			new_word.word_value = word;

			word_vector.push_back(new_word);
			return;
		}
	}

	//以字母开头的不是关键字，就是标识符
	Word new_word;
	new_word.word_type = "token";
	new_word.word_value = word;

	word_vector.push_back(new_word);
	return;
}

void StringAnalysis(const string word) {
	Word new_word;
	new_word.word_type = "string";
	new_word.word_value = word;

	word_vector.push_back(new_word);
	return;
}

//错误处理
void ErrorAnalysis(const string word)
{
	Word new_word;
	new_word.word_type = "error";
	new_word.word_value = word;

	word_vector.push_back(new_word);
	return;
}