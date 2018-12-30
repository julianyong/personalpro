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

extern int origin[40320][9] = { 0 };//���ȫ��������
int init[8] = { 1,2,3,4,5,6,7,8 };
int general_1[2][3] = { { 0,1,2 } ,{ 0,2,1 } };//��2��3�н��������
int general_2[6][3] = { { 3,4,5 },{ 3,5,4 },{ 4,3,5 },{ 4,5,3 },{ 5,3,4 },{ 5,4,3 } };//��4��5��6�н��������
int general_3[6][3] = { { 6,7,8 },{ 6,8,7 },{ 7,6,8 },{ 7,8,6 },{ 8,7,6 },{ 8,6,7 } };//��7��8��9�н��������
int flag;
typedef struct {
	int map[9][9];//������������
}MAP;
ofstream fout;
string filepath;
//void Initial();//��ʼ��origin������9��ͷ��1~9��ȫ��������
//void creatModel(MAP &m, int n);//��������ģ����Բ�ͬ��ȫ����������������
//void print(MAP m, int flag);//������Ϊ��λ�������վ����뵽�ļ���
int judge_Num(char s[]);//�ж�n�Ƿ�Ϸ�
int create_Sudoku(int n);//����n�����ظ����վ�
void solve_Sudoku(FILE *fp);//������

int judge_Num(char s[])//�жϲ���n�Ƿ�Ϸ�
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

void swap(int &a, int &b)//ʵ����������ֵ����
{
	int tmp = 0;
	tmp = a;
	a = b;
	b = tmp;
}

int kk = 0;
void perm(int flag)//����1~8��ȫ��������
{
	if (flag == 8) {//��low==8ʱ��init��������һ�����У����䱣�浽origin��
		origin[kk][0] = 9;
		for (int i = 0; i < 8; i++) {
			origin[kk][i + 1] = init[i];
		}
		kk++;
		return;
	}
	else {
		for (int i = flag; i < 8; i++) {
			swap(init[flag], init[i]);//��ÿһ��Ԫ�����һ��Ԫ�ؽ���
			perm(flag + 1);//������õ������У��ݹ����
			swap(init[flag], init[i]);//��ԭinit����
		}
	}
}

void Initial() {//��ʼ��origin
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



int create_Sudoku(int n)//����n�����ظ����վ�
{ 
	fout.open(filepath, ios::trunc);
	int count = 0;
	MAP m;
	if (origin[0][0] == 0) {//���originδ��ʼ�������origin��ʼ������ȫ��������
		Initial();
	}
	for (int i = 0; i < 40320; i++) {
		memset(m.map, 0, sizeof(m.map));
		creatModel(m, i);//������ĸ-���ֶ�Ӧ��ϵ������������
		MAP backup;
		for (int j = 0; j < 2; j++) {//ʵ����˳��任
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
					print(backup, count);//����������Ϊ��λ������ļ���
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
bool isPlace(int count, MAP &m) {//�жϸ�ֵ�Ƿ������������
	int row = count / 9;
	int col = count % 9;
	int j;
	for (j = 0; j < 9; ++j) {
		if (m.map[row][j] == m.map[row][col] && j != col) {//��һ���ڼ��Ϸ���
			return false;
		}
	}
	for (j = 0; j < 9; ++j) {
		if (m.map[j][col] == m.map[row][col] && j != row) {//��һ���ڼ��Ϸ���
			return false;
		}
	}
	int tempRow = row / 3 * 3;
	int tempCol = col / 3 * 3;
	for (j = tempRow; j < tempRow + 3; ++j) {
		for (int k = tempCol; k < tempCol + 3; ++k) {
			if (m.map[j][k] == m.map[row][col] && j != row && k != col) {//�ھŹ����ڼ��Ϸ���
				return false;
			}
		}
	}
	return true;
}

void backtrace(int count, MAP &m) {//������������վ�
	if (count == 81) {
		print(m, flag);
		return;
	}
	int row = count / 9;
	int col = count % 9;
	if (m.map[row][col] == 0) {
		for (int i = 1; i <= 9; ++i) {
			m.map[row][col] = i;//��ֵ
			if (isPlace(count, m)) {//��鸳ֵ�Ƿ�Ϸ�
				backtrace(count + 1, m);//�ݹ������һ��
			}
		}
		m.map[row][col] = 0;//����
	}
	else {
		backtrace(count + 1, m);
	}
}

void solve_Sudoku(FILE *fp)//���ɲ������õ������վ�
{
	fout.open(filepath, ios::trunc);
	MAP m;

	int tmp;
	while (~fscanf(fp, "%d", &tmp)) {//���ļ��ж���������Ŀ����
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
		backtrace(0, m);//���ݽ�����
		flag = 1;
	}
	fclose(fp);
	fout.close();
}