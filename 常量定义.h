#pragma once
#include <vector>
#include <string>
using namespace std;
//const string OUTPUT_CSTYTLE = "词法分析输出.txt";
//const string KEYWORDS_CSTYTLE = "关键字.txt";
//const string BOUNDARY_CSTYTLE = "界符.txt";
//const string OPERATOR_CSTYTLE = "运算符.txt";
//const string INPUT_SENTENCE = "input_sentence.txt";
//const string OUTPUT_SENTENCE = "output_sentence.txt";
//const string OUTPUT_YUFA = "语法分析输出.txt";
//const string OUTPUT_ZHONGDAI = "中间代码输出.txt";

//读取的C源代码保存在vector数组中
vector <char>code_vector;
//读入的关键字、运算符、界符保存在数组中
vector<string>keywords_vector;
vector<string>operator_vector;
vector<string>boundary_vector;
//这些是单个字符类型的判断
const int LETTER = 1; //字母
const int DIGIT = 2;//数字
const int OPERATOR = 3;//运算符
const int BOUNDARY = 4;//界符
const int END = 5;//结束符
//后增加类型
//const int STRING = 6;//结束符


//定义一些文件名
const string INPUT_FILE = "待分析.txt";
const string KEYWORDS_FILE = "关键字.txt";
const string BOUNDARY_FILE = "界符.txt";
const string OPERATOR_FILE = "运算符.txt";
const string TranlatedCode_File = "汇编语言翻译输出.txt";
//分析出的单词
typedef struct Word
{
	string word_type;//单词类别
	string word_value;//单词值
}Word;
//存放单词的数组
vector<Word>word_vector;
//分割出来的单独句子
vector<vector<Word>> sentence_vector;
//语法分析使用的栈
vector<Word>stack_expression;
const Word stackinput_B = { "nonterminal","B" };//比较语句初始化符号
const Word stackinput_C = { "nonterminal","C" };//赋值语句初始化符号
const Word stackinput_E = {"nonterminal","E"};//表达式语句初始化符号
const Word stackinput_E2 = {"nonterminal","E2"};
const Word stackinput_T = { "nonterminal","T" };
const Word stackinput_lk = { "boundary","(" };
const Word stackinput_rk = { "boundary",")" };
const Word stackinput_op = { "operator","op" }; //加减乘除操作符号
const Word stackinput_digit = { "digit","digit" };
const Word stackinput_token = { "token","token" };
const Word stackinput_keyword = { "keyword","keyword" };
const Word stackinput_equal = { "operator","=" };
const Word stackinput_branch = { "boundary",";" };
const Word stackinput_compareop = { "operator","compareop" };//比较操作符号

//for语句中使用
const Word stackinput_A = { "nonterminal","A" };
const Word stackinput_L = { "nonterminal","L" };
const Word stackinput_M = { "nonterminal","M" };
const Word stackinput_N = { "nonterminal","N" };
const Word stackinput_O = { "nonterminal","O" };
const Word stackinput_biglk = { "boundary","{" };
const Word stackinput_bigrk = { "boundary","}" };
const Word stackinput_for = { "keyword","for" };
//cout语句之中使用
const Word stackinput_R = { "nonterminal","R" };
const Word stackinput_M2 = { "nonterminal","M2" };
const Word stackinput_cout = { "keyword","cout" };
const Word stackinput_endl = { "keyword","endl" };
const Word stackinput_output = { "operator","<<" };
const Word stackinput_string = { "string","string" };

bool iftest_grammer = true;


//用来保存字符串
typedef struct Wordforstring
{
	string word_type;//单词类别
	string word_value;//单词值
	int index;//单词的序数
}Wordforstring;
//设计一个堆栈用来保存定义的字符串
vector<Wordforstring> stringkeeper_vector;
//用来保存变量
typedef struct Variable
{
	string name;
	bool ifinit;
	int value;
	string type;
}Variable;
//设计一个堆栈用来保存定义的变量
vector<Variable> variable_vector;
//后缀表达式保存栈
vector<Word> postfixexpression_vector;

//设计一个堆栈用来保存for语句的flag个数
vector<string> flag_vector;


//设计一个堆栈用来保存代码段
vector<string> objectcode_vector;
string objectstringkeep;