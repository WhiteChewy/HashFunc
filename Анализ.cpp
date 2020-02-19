#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <string>
#include <math.h>

using namespace std;

const int B = 2000;
const int SIZE_KEY = 6;

int h(char *key)
{
	string buff;
	int radix = 10;  //������� ���������
	char buffer[20]; //���������
	int result(0);

	for (int i = 0; i < SIZE_KEY; i++)
		result += int(key[i])*int(pow(3.0, i));
	result = int(pow(result, 2.0));//���������� ���������� � ������� ��������

	buff = _itoa(result, buffer, radix);//����������� ����� � ������
	buff = buff.substr(3, 4);//���������� ��������� �� ������ ������� � 3 ������� ������� 4
	result = atoi(buff.c_str());//�������������� �� ����� � ������ ������������� � ������ ������
	result = result % B;

	return result;
}

int main()
{
	char *filename = "Hash-adress.txt";
	ofstream fout;
	fout.open(filename);

	int CurAdress(0);
	int A[B] = {};
	char key[SIZE_KEY];

	for (int i = 0; i < B * 3; i++)
	{
		for (int j = 0; j < SIZE_KEY; j++)
		{
			if (j == 0 || j == 5)
				key[j] = char(rand() % 28 + 60);//��������� ������ � ������ �� 28 �� 60
			else
				key[j] = char(rand() % 9 + 48);//��������� ������ � ������ �� 9 �� 48
		}
		CurAdress = h(key);
		A[CurAdress] += 1;
	}

	for (int k = 0; k < B; k++)
	{
		fout << A[k];//������ � ���� ������
		fout << "\n";
	}
	fout.close();
	return 0;
}
