#pragma once
#include<stack>
#include <iostream>
using namespace std;
#include "��������.h"

//���ʷ������Ľ����Ϊһ��һ���ľ���
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

	//��//��ŵ��ʵ�����vector<Word>word_vector;֮�ж�ȡ����
	//�ԣ���{ }�ж��Ƿ�Ϊһ�����Ӳ��ҽ����Ӵ洢��
	//�жϾ��ӽ���������1.����;�Ҳ������ֹ�{
	//					2.����      }
	//�����ڶ�ȡ���ӵĹ���֮��ȥ��ע�ͺͿո񣨽�����⣺�Ʊ����tabû��ʶ�����Գ���ʶ�����
	//���ַ���ת��Ϊstrin���Ϳ���ֱ�ӱȽ�
	//string zhushi = "//";
	//if (zhushi == "//") {
	//	cout << zhushi;
	//}
	
	int annotation_flag = 0;//��ע�ͷ���������ʾ�Ƿ���ע�ͷ��ŵ���ע�ͷ��ŵ�ʱ��������ݲ���ȡ
	int count_sen = 0;//���������ж��ٸ�����
	int littlebracket_flag = 0;
	int bigbracket_flag = 0;
	bool have_bigbracket = 0;//����ͳ���Ƿ���ڹ�������
	vector<Word> temporarysave;

	for (int i = 0; i < word_vector.size(); i++) {
		//���²�����������ע����Ϣ
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
			//���������ж��Ƿ�Ϊ�ֺš������š�С����
			if (word_vector[i].word_value == "(") { littlebracket_flag++; }
			if (word_vector[i].word_value == "{") { bigbracket_flag++; have_bigbracket = true; }
			if (word_vector[i].word_value == ")") { littlebracket_flag--; }
			if (word_vector[i].word_value == "}") { bigbracket_flag--; }


			//�������ֺ�";"���Ҵ�����"}"ʱ���ӿ��ܽ���
			if (word_vector[i].word_value == ";" && have_bigbracket == false && littlebracket_flag == 0)
			{
				sentence_vector.push_back(temporarysave);
				//�����ʱ����һ�����ӵ�vector
				temporarysave.clear();
				have_bigbracket = 0;
				littlebracket_flag = 0;
				bigbracket_flag = 0;
				count_sen++;
			}

			if (word_vector[i].word_value == "}" && bigbracket_flag == 0 && littlebracket_flag == 0)
			{
				sentence_vector.push_back(temporarysave);
				//�����ʱ����һ�����ӵ�vector
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
