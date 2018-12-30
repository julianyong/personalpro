#pragma warning(disable:4996)
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <windows.h>
#include <process.h>
#include <vector>
#include <cstring>
#include <string>
#include <ctime>
#include "Sudoku.h"
/* �������� ѧ�ţ�1120161789
ʵ�ֹ��ܣ�1 ��N��1 <= N <= 1000000���������վ�������ļ���
2 ���ļ��ж�ȡ�����оֲ������� */
//9*9���������Ͻǵ����̶ֹ���8 + 9�� % 9 + 1 = 9
using namespace std;


int main(int argc, char* argv[])
{
	double totaltime;
	clock_t start, finish;
	start = clock();

	filepath = argv[0];
	int l = filepath.length() - 10;
	filepath.erase(l);
	filepath += "sudoku.txt";//�������·�����ɾ���·��
	if (argv[1][1] == 'c')//������cʱ��Ҫ���� N �������վ֡�
	{
		int N = judge_Num(argv[2]);//judgeNum()�жϲ����Ƿ����Ҫ��
		if (N == -1)
			printf("\nWrong:Please Input Correctly!\n");
		else {
			create_Sudoku(N);
		}
		finish = clock();
		totaltime = ((double)(finish)-(double)(start)) / CLOCKS_PER_SEC;
		cout << "����������ʱ��Ϊ��" << totaltime << "��" << endl;
	}
	else
	{
		if (argv[1][1] == 's') //��������sʱ�����ļ��ж�ȡ�����о֣�����������
		{
			FILE *fp;
			fp = fopen(argv[2], "r");
			if (fp == NULL) {
				printf("\nWrong:File Open Failed!\n");
			}
			else
				solve_Sudoku(fp);
			finish = clock();
			totaltime = ((double)(finish)-(double)(start)) / CLOCKS_PER_SEC;
			cout << "����������ʱ��Ϊ��" << totaltime << "��" << endl;
		}
	}
	return 0;
}