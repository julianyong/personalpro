#pragma once
#include <algorithm>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <vector>
#include <cstring>
#include <string>
#include <ctime>
using namespace std;

extern int origin[40320][9] = { 0 };//存放全排列序列
int init[8] = { 1,2,3,4,5,6,7,8 };
int general_1[2][3] = { { 0,1,2 } ,{ 0,2,1 } };//第2、3行交换的情况
int general_2[6][3] = { { 3,4,5 },{ 3,5,4 },{ 4,3,5 },{ 4,5,3 },{ 5,3,4 },{ 5,4,3 } };//第4、5、6行交换的情况
int general_3[6][3] = { { 6,7,8 },{ 6,8,7 },{ 7,6,8 },{ 7,8,6 },{ 8,7,6 },{ 8,6,7 } };//第7、8、9行交换的情况
int flag;
typedef struct {
	int map[9][9];//待解数独盘面
}MAP;
ofstream fout;
string filepath;
//void Initial();//初始化origin存入以9开头的1~9的全排列序列
//void creatModel(MAP &m, int n);//根据已有模板针对不同的全排列序列生成盘面
//void print(MAP m, int flag);//以盘面为单位将数独终局输入到文件中
int judge_Num(char s[]);//判断n是否合法
int create_Sudoku(int n);//生成n个不重复的终局
void solve_Sudoku(FILE *fp);//解数独

int judge_Num(char s[])//判断参数n是否合法
{
	int len = strlen(s);
	if (len == 0 || len > 7)
		return -1;
	int i;
	int n = 0;
	for (i = 0; i < len; i++)
	{
		if (s[i] < '0' || s[i]>'9')
			return -1;
		else
			n = n * 10 + (s[i] - '0');
	}
	if (n == 0 || n > 1000000)
		return -1;
	else
		return n;

}

void swap(int &a, int &b)//实现两数的数值交换
{
	int tmp = 0;
	tmp = a;
	a = b;
	b = tmp;
}

int kk = 0;
void perm(int flag)//生成1~8的全排列序列
{
	if (flag == 8) {//当low==8时，init就是其中一个排列，将其保存到origin中
		origin[kk][0] = 9;
		for (int i = 0; i < 8; i++) {
			origin[kk][i + 1] = init[i];
		}
		kk++;
		return;
	}
	else {
		for (int i = flag; i < 8; i++) {
			swap(init[flag], init[i]);//将每一个元素与第一个元素交换
			perm(flag + 1);//交换后得到子序列，递归求解
			swap(init[flag], init[i]);//还原init序列
		}
	}
}

void Initial() {//初始化origin
	kk = 0;
	perm(0);
	return;
}

void creatModel(MAP &m, int n)
{
	m.map[0][0] = m.map[1][6] = m.map[2][3] = m.map[3][2] = m.map[4][8] = m.map[5][5] = m.map[6][1] = m.map[7][7] = m.map[8][4] = 9;
	m.map[0][1] = m.map[1][7] = m.map[2][4] = m.map[3][0] = m.map[4][6] = m.map[5][3] = m.map[6][2] = m.map[7][8] = m.map[8][5] = origin[n][1];
	m.map[0][2] = m.map[1][8] = m.map[2][5] = m.map[3][1] = m.map[4][7] = m.map[5][4] = m.map[6][0] = m.map[7][6] = m.map[8][3] = origin[n][2];
	m.map[0][3] = m.map[1][0] = m.map[2][6] = m.map[3][5] = m.map[4][2] = m.map[5][8] = m.map[6][4] = m.map[7][1] = m.map[8][7] = origin[n][3];
	m.map[0][4] = m.map[1][1] = m.map[2][7] = m.map[3][3] = m.map[4][0] = m.map[5][6] = m.map[6][5] = m.map[7][2] = m.map[8][8] = origin[n][4];
	m.map[0][5] = m.map[1][2] = m.map[2][8] = m.map[3][4] = m.map[4][1] = m.map[5][7] = m.map[6][3] = m.map[7][0] = m.map[8][6] = origin[n][5];
	m.map[0][6] = m.map[1][3] = m.map[2][0] = m.map[3][8] = m.map[4][5] = m.map[5][2] = m.map[6][7] = m.map[7][4] = m.map[8][1] = origin[n][6];
	m.map[0][7] = m.map[1][4] = m.map[2][1] = m.map[3][6] = m.map[4][3] = m.map[5][0] = m.map[6][8] = m.map[7][5] = m.map[8][2] = origin[n][7];
	m.map[0][8] = m.map[1][5] = m.map[2][2] = m.map[3][7] = m.map[4][4] = m.map[5][1] = m.map[6][6] = m.map[7][3] = m.map[8][0] = origin[n][8];

}

void print(MAP m, int flag)
{
	if (flag != 0)
	{
		fout << endl;;
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (j == 8)
				fout << m.map[i][j] << endl;
			else
				fout << m.map[i][j] << " ";
		}
	}
}



int create_Sudoku(int n)//生成n个不重复的终局
{ 
	fout.open(filepath, ios::trunc);
	int count = 0;
	MAP m;
	if (origin[0][0] == 0) {//如果origin未初始化，则对origin初始化存入全排列序列
		Initial();
	}
	for (int i = 0; i < 40320; i++) {
		memset(m.map, 0, sizeof(m.map));
		creatModel(m, i);//根据字母-数字对应关系生成数独盘面
		MAP backup;
		for (int j = 0; j < 2; j++) {//实现行顺序变换
			for (int ii = 0; ii < 9; ii++)
			{
				backup.map[0][ii] = m.map[general_1[j][0]][ii];
				backup.map[1][ii] = m.map[general_1[j][1]][ii];
				backup.map[2][ii] = m.map[general_1[j][2]][ii];
			}
			for (int k = 0; k < 6; k++)
			{
				for (int ii = 0; ii < 9; ii++)
				{
					backup.map[3][ii] = m.map[general_2[k][0]][ii];
					backup.map[4][ii] = m.map[general_2[k][1]][ii];
					backup.map[5][ii] = m.map[general_2[k][2]][ii];
				}
				for (int l = 0; l < 6; l++)
				{
					for (int ii = 0; ii < 9; ii++)
					{
						backup.map[6][ii] = m.map[general_3[l][0]][ii];
						backup.map[7][ii] = m.map[general_3[l][1]][ii];
						backup.map[8][ii] = m.map[general_3[l][2]][ii];
					}
					print(backup, count);//以数独盘面为单位输出到文件中
					count++;
					if (count == n)
					{
						fout.close();
						return 1;
					}
				}
			}
		}
	}
	return 0;
}
bool isPlace(int count, MAP &m) {//判断赋值是否符合数独规则
	int row = count / 9;
	int col = count % 9;
	int j;
	for (j = 0; j < 9; ++j) {
		if (m.map[row][j] == m.map[row][col] && j != col) {//在一行内检查合法性
			return false;
		}
	}
	for (j = 0; j < 9; ++j) {
		if (m.map[j][col] == m.map[row][col] && j != row) {//在一列内检查合法性
			return false;
		}
	}
	int tempRow = row / 3 * 3;
	int tempCol = col / 3 * 3;
	for (j = tempRow; j < tempRow + 3; ++j) {
		for (int k = tempCol; k < tempCol + 3; ++k) {
			if (m.map[j][k] == m.map[row][col] && j != row && k != col) {//在九宫格内检查合法性
				return false;
			}
		}
	}
	return true;
}

void backtrace(int count, MAP &m) {//回溯求解数独终局
	if (count == 81) {
		print(m, flag);
		return;
	}
	int row = count / 9;
	int col = count % 9;
	if (m.map[row][col] == 0) {
		for (int i = 1; i <= 9; ++i) {
			m.map[row][col] = i;//赋值
			if (isPlace(count, m)) {//检查赋值是否合法
				backtrace(count + 1, m);//递归进入下一层
			}
		}
		m.map[row][col] = 0;//回溯
	}
	else {
		backtrace(count + 1, m);
	}
}

void solve_Sudoku(FILE *fp)//生成并输出填好的数独终局
{
	fout.open(filepath, ios::trunc);
	MAP m;

	int tmp;
	while (~fscanf(fp, "%d", &tmp)) {//从文件中读出数独题目内容
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (i == 0 && j == 0) {
					m.map[i][j] = tmp;
				}
				else {
					fscanf(fp, "%d", &m.map[i][j]);
				}
			}
		}
		backtrace(0, m);//回溯解数独
		flag = 1;
	}
	fclose(fp);
	fout.close();
}