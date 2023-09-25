#pragma once
#include <vector>
#include <string>
using namespace std;
//const string OUTPUT_CSTYTLE = "�ʷ��������.txt";
//const string KEYWORDS_CSTYTLE = "�ؼ���.txt";
//const string BOUNDARY_CSTYTLE = "���.txt";
//const string OPERATOR_CSTYTLE = "�����.txt";
//const string INPUT_SENTENCE = "input_sentence.txt";
//const string OUTPUT_SENTENCE = "output_sentence.txt";
//const string OUTPUT_YUFA = "�﷨�������.txt";
//const string OUTPUT_ZHONGDAI = "�м�������.txt";

//��ȡ��CԴ���뱣����vector������
vector <char>code_vector;
//����Ĺؼ��֡�����������������������
vector<string>keywords_vector;
vector<string>operator_vector;
vector<string>boundary_vector;
//��Щ�ǵ����ַ����͵��ж�
const int LETTER = 1; //��ĸ
const int DIGIT = 2;//����
const int OPERATOR = 3;//�����
const int BOUNDARY = 4;//���
const int END = 5;//������
//����������
//const int STRING = 6;//������


//����һЩ�ļ���
const string INPUT_FILE = "������.txt";
const string KEYWORDS_FILE = "�ؼ���.txt";
const string BOUNDARY_FILE = "���.txt";
const string OPERATOR_FILE = "�����.txt";
const string TranlatedCode_File = "������Է������.txt";
//�������ĵ���
typedef struct Word
{
	string word_type;//�������
	string word_value;//����ֵ
}Word;
//��ŵ��ʵ�����
vector<Word>word_vector;
//�ָ�����ĵ�������
vector<vector<Word>> sentence_vector;
//�﷨����ʹ�õ�ջ
vector<Word>stack_expression;
const Word stackinput_B = { "nonterminal","B" };//�Ƚ�����ʼ������
const Word stackinput_C = { "nonterminal","C" };//��ֵ����ʼ������
const Word stackinput_E = {"nonterminal","E"};//���ʽ����ʼ������
const Word stackinput_E2 = {"nonterminal","E2"};
const Word stackinput_T = { "nonterminal","T" };
const Word stackinput_lk = { "boundary","(" };
const Word stackinput_rk = { "boundary",")" };
const Word stackinput_op = { "operator","op" }; //�Ӽ��˳���������
const Word stackinput_digit = { "digit","digit" };
const Word stackinput_token = { "token","token" };
const Word stackinput_keyword = { "keyword","keyword" };
const Word stackinput_equal = { "operator","=" };
const Word stackinput_branch = { "boundary",";" };
const Word stackinput_compareop = { "operator","compareop" };//�Ƚϲ�������

//for�����ʹ��
const Word stackinput_A = { "nonterminal","A" };
const Word stackinput_L = { "nonterminal","L" };
const Word stackinput_M = { "nonterminal","M" };
const Word stackinput_N = { "nonterminal","N" };
const Word stackinput_O = { "nonterminal","O" };
const Word stackinput_biglk = { "boundary","{" };
const Word stackinput_bigrk = { "boundary","}" };
const Word stackinput_for = { "keyword","for" };
//cout���֮��ʹ��
const Word stackinput_R = { "nonterminal","R" };
const Word stackinput_M2 = { "nonterminal","M2" };
const Word stackinput_cout = { "keyword","cout" };
const Word stackinput_endl = { "keyword","endl" };
const Word stackinput_output = { "operator","<<" };
const Word stackinput_string = { "string","string" };

bool iftest_grammer = true;


//���������ַ���
typedef struct Wordforstring
{
	string word_type;//�������
	string word_value;//����ֵ
	int index;//���ʵ�����
}Wordforstring;
//���һ����ջ�������涨����ַ���
vector<Wordforstring> stringkeeper_vector;
//�����������
typedef struct Variable
{
	string name;
	bool ifinit;
	int value;
	string type;
}Variable;
//���һ����ջ�������涨��ı���
vector<Variable> variable_vector;
//��׺���ʽ����ջ
vector<Word> postfixexpression_vector;

//���һ����ջ��������for����flag����
vector<string> flag_vector;


//���һ����ջ������������
vector<string> objectcode_vector;
string objectstringkeep;