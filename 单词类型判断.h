#pragma once
#include <vector>
#include <string>
#include"��������.h"


//��������
void DigitAnalysis(const string word)
{
	Word new_word;
	new_word.word_type = "digit";
	new_word.word_value = word;

	word_vector.push_back(new_word);
	return;
}
//���������
void OperatorAnalysis(const string word)
{
	//�ж��Ƿ�Ϊ�����
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

//�������
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

//�����ؼ��ֻ��ʶ��
void LetterAnalysis(const string word)
{
	//�ж��Ƿ�Ϊ�ؼ���
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

	//����ĸ��ͷ�Ĳ��ǹؼ��֣����Ǳ�ʶ��
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

//������
void ErrorAnalysis(const string word)
{
	Word new_word;
	new_word.word_type = "error";
	new_word.word_value = word;

	word_vector.push_back(new_word);
	return;
}