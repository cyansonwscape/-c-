#pragma once
#include <iostream>
using namespace std;
#include "常量定义.h"
#include "文件读取.h"
#include "词法分析.h"
#include "分割句子.h"
#include"语法分析.h"
#include"翻译为目标语言.h"
#include"后缀表达式转化.h"

void OutputTranlatedCodeToFile()
{
	ofstream outputFile;
	outputFile.open(TranlatedCode_File, ios::out);
	if (!outputFile)
		cout << "文件打开失败：词法分析输出" << endl;

	/*for (const Word word : word_vector)
	{
		outputFile << "<" << word.word_type << " , " << word.word_value << ">" << '\n';
	}*/
//先输出数据段
	outputFile << "DATA SEGMENT\n";
	for (int i = 0; i < variable_vector.size(); i++)
	{
		outputFile << variable_vector[i].name << "\tDW\t 0\n";
	}

	outputFile << "endl\tDB\t 13,10,'$';endl的字符串表示\n";
		for (int i = 0; i < stringkeeper_vector.size(); i++)
		{
			outputFile << "string"+to_string(stringkeeper_vector[i].index) << "\tDB\t" << stringkeeper_vector[i].word_value+",'$'" << ";常量字符串\n";
		}


		
	for (int i = 0; i < 10; i++)
	{
		//计算表达式时的变量暂存地址
		outputFile << "temporarysave"+to_string(i) << "\tDW\t 0;计算表达式时的变量暂存地址\n";
	}
	//比较值的暂存地址
	outputFile << "waitcompare0"  << "\tDW\t 0;比较值的暂存地址\n";
	outputFile << "waitcompare1" << "\tDW\t 0 ;比较值的暂存地址\n";
	outputFile << "DATA ENDS\n";
//代码段的输出
	outputFile << "CODE SEGMENT\n";
	outputFile << "\tASSUME CS:CODE,DS:DATA\n";
	outputFile << "START:\n";
	outputFile << "\tMOV AX,DATA  \n";
	outputFile << "\tMOV DS,AX  \n";
	for (int i = 0; i < objectcode_vector.size(); i++)
	{
		outputFile <<"\t"<< objectcode_vector[i];
	}




	outputFile << "\tJMP forend\t;跳转至结束\n";




	//代码段结束附加一段子程序用来输出
	outputFile << "COUTD:  \t; 将双字AX化为10 进制并显示\n";
	outputFile << "PUSH BX; BX, CX, DX 入栈，保存现场\n";
	outputFile << "PUSH CX\n";
	outputFile << "PUSH DX\n";
	outputFile << "MOV BX, 10; 转换成10进制，所以BX <= 10\n";
	outputFile << "XOR CX, CX; 清空 CX\n";
	outputFile << "C0: \nXOR DX, DX; 清空 DX\n";
	outputFile << "DIV BX; AX 除以 BX, DX <= 余数, AX <= 商\n";
	outputFile << "OR DX, 0E30H; DX | 0E30H 结果 DH = 0EH DL = 30H + 余数\n";
	outputFile << "PUSH DX; 商的ASCII码入栈\n";
	outputFile << "INC CX; CX 自加 用于 出栈时计数\n";
	outputFile << "CMP AX, 0; 比较AX 与 0\n";
	outputFile << "JNZ C0; 若AX(商) 不为 0 则 高位还有数 跳转到C0 继续进行计算\n";
	outputFile << "C1: \nPOP AX; 出栈到AX 此时 AH = 0EH AL = 十进制数到ASCII码\n";
	outputFile << "INT 10H; AH = 0EH 将AL 输出到屏幕\n";
	outputFile << "LOOP C1; CX 不为0 则跳转到C1继续出栈 输出\n";
	outputFile << "POP DX; BX, CX, DX 出栈，恢复现场\n";
	outputFile << "POP CX\n";
	outputFile << "POP BX\n";
	outputFile << "RET\n";

	outputFile << "forend:\t;结束标志位\n";

	outputFile << "\tMOV AH,4CH \n";
	outputFile << "\tINT 21H   \n";
	outputFile << "CODE  ENDS  \n";
	outputFile << "\tEND  START   \n";

	


	outputFile.close();

}