#pragma once
#include <iostream>
using namespace std;
#include "��������.h"
#include "�ļ���ȡ.h"
#include "�ʷ�����.h"
#include "�ָ����.h"
#include"�﷨����.h"
#include"����ΪĿ������.h"
#include"��׺���ʽת��.h"

void OutputTranlatedCodeToFile()
{
	ofstream outputFile;
	outputFile.open(TranlatedCode_File, ios::out);
	if (!outputFile)
		cout << "�ļ���ʧ�ܣ��ʷ��������" << endl;

	/*for (const Word word : word_vector)
	{
		outputFile << "<" << word.word_type << " , " << word.word_value << ">" << '\n';
	}*/
//��������ݶ�
	outputFile << "DATA SEGMENT\n";
	for (int i = 0; i < variable_vector.size(); i++)
	{
		outputFile << variable_vector[i].name << "\tDW\t 0\n";
	}

	outputFile << "endl\tDB\t 13,10,'$';endl���ַ�����ʾ\n";
		for (int i = 0; i < stringkeeper_vector.size(); i++)
		{
			outputFile << "string"+to_string(stringkeeper_vector[i].index) << "\tDB\t" << stringkeeper_vector[i].word_value+",'$'" << ";�����ַ���\n";
		}


		
	for (int i = 0; i < 10; i++)
	{
		//������ʽʱ�ı����ݴ��ַ
		outputFile << "temporarysave"+to_string(i) << "\tDW\t 0;������ʽʱ�ı����ݴ��ַ\n";
	}
	//�Ƚ�ֵ���ݴ��ַ
	outputFile << "waitcompare0"  << "\tDW\t 0;�Ƚ�ֵ���ݴ��ַ\n";
	outputFile << "waitcompare1" << "\tDW\t 0 ;�Ƚ�ֵ���ݴ��ַ\n";
	outputFile << "DATA ENDS\n";
//����ε����
	outputFile << "CODE SEGMENT\n";
	outputFile << "\tASSUME CS:CODE,DS:DATA\n";
	outputFile << "START:\n";
	outputFile << "\tMOV AX,DATA  \n";
	outputFile << "\tMOV DS,AX  \n";
	for (int i = 0; i < objectcode_vector.size(); i++)
	{
		outputFile <<"\t"<< objectcode_vector[i];
	}




	outputFile << "\tJMP forend\t;��ת������\n";




	//����ν�������һ���ӳ����������
	outputFile << "COUTD:  \t; ��˫��AX��Ϊ10 ���Ʋ���ʾ\n";
	outputFile << "PUSH BX; BX, CX, DX ��ջ�������ֳ�\n";
	outputFile << "PUSH CX\n";
	outputFile << "PUSH DX\n";
	outputFile << "MOV BX, 10; ת����10���ƣ�����BX <= 10\n";
	outputFile << "XOR CX, CX; ��� CX\n";
	outputFile << "C0: \nXOR DX, DX; ��� DX\n";
	outputFile << "DIV BX; AX ���� BX, DX <= ����, AX <= ��\n";
	outputFile << "OR DX, 0E30H; DX | 0E30H ��� DH = 0EH DL = 30H + ����\n";
	outputFile << "PUSH DX; �̵�ASCII����ջ\n";
	outputFile << "INC CX; CX �Լ� ���� ��ջʱ����\n";
	outputFile << "CMP AX, 0; �Ƚ�AX �� 0\n";
	outputFile << "JNZ C0; ��AX(��) ��Ϊ 0 �� ��λ������ ��ת��C0 �������м���\n";
	outputFile << "C1: \nPOP AX; ��ջ��AX ��ʱ AH = 0EH AL = ʮ��������ASCII��\n";
	outputFile << "INT 10H; AH = 0EH ��AL �������Ļ\n";
	outputFile << "LOOP C1; CX ��Ϊ0 ����ת��C1������ջ ���\n";
	outputFile << "POP DX; BX, CX, DX ��ջ���ָ��ֳ�\n";
	outputFile << "POP CX\n";
	outputFile << "POP BX\n";
	outputFile << "RET\n";

	outputFile << "forend:\t;������־λ\n";

	outputFile << "\tMOV AH,4CH \n";
	outputFile << "\tINT 21H   \n";
	outputFile << "CODE  ENDS  \n";
	outputFile << "\tEND  START   \n";

	


	outputFile.close();

}