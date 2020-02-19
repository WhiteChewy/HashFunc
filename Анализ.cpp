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
	int radix = 10;  //система счисления
	char buffer[20]; //результат
	int result(0);

	for (int i = 0; i < SIZE_KEY; i++)
		result += int(key[i])*int(pow(3.0, i));
	result = int(pow(result, 2.0));//возведение результата в степень квадрата

	buff = _itoa(result, buffer, radix);//превращение числа в массив
	buff = buff.substr(3, 4);//извлечение подстроки из строки буффера с 3 позиции длинной 4
	result = atoi(buff.c_str());//преобразование из числа в строку скопированием в другую строку
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
				key[j] = char(rand() % 28 + 60);//рандумный символ с кодами от 28 до 60
			else
				key[j] = char(rand() % 9 + 48);//рандумный символ с кодами от 9 до 48
		}
		CurAdress = h(key);
		A[CurAdress] += 1;
	}

	for (int k = 0; k < B; k++)
	{
		fout << A[k];//запись в файл ключей
		fout << "\n";
	}
	fout.close();
	return 0;
}
