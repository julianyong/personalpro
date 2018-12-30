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
/* 姓名：杨剑楠 学号：1120161789
实现功能：1 将N（1 <= N <= 1000000）个数独终局输出到文件中
2 从文件中读取数独残局并解数独 */
//9*9数独最左上角的数字固定（8 + 9） % 9 + 1 = 9
using namespace std;


int main(int argc, char* argv[])
{
	double totaltime;
	clock_t start, finish;
	start = clock();

	filepath = argv[0];
	int l = filepath.length() - 10;
	filepath.erase(l);
	filepath += "sudoku.txt";//根据相对路径生成绝对路径
	if (argv[1][1] == 'c')//当输入c时，要生成 N 个数独终局。
	{
		int N = judge_Num(argv[2]);//judgeNum()判断参数是否符合要求
		if (N == -1)
			printf("\nWrong:Please Input Correctly!\n");
		else {
			create_Sudoku(N);
		}
		finish = clock();
		totaltime = ((double)(finish)-(double)(start)) / CLOCKS_PER_SEC;
		cout << "程序总运行时间为：" << totaltime << "秒" << endl;
	}
	else
	{
		if (argv[1][1] == 's') //当输入是s时，从文件中读取数独残局，并解数独。
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
			cout << "程序总运行时间为：" << totaltime << "秒" << endl;
		}
	}
	return 0;
}