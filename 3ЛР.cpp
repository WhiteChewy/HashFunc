#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <math.h>
#include <random>

using namespace std;

const int MAX(2000); //������ ���-�������
const int STEP(1); //��� ��������;
const int SIZE_KEY(6); //������ �����
const char *filebase = "base.txt";

struct htype
{
	char val[SIZE_KEY]; //�������� �������� ������
	bool empty; //����, ������������ ����� �� ������ ��� ���
} hashtab[MAX];
//��������� ������ ������ � �����, ���������.
void readfromtxt()
{
	ifstream fin;
	fin.open(filebase);
	if (fin)
	{
		for (int i = 0; i < MAX; i++)
		{
			fin >> hashtab[i].val;
			if (strlen(hashtab[i].val) < SIZE_KEY ) hashtab[i].empty = true;
			else hashtab[i].empty = false;
		}
	}
	fin.close();
}
//��������� ������ ������ � ���� ���������
void write2txt()
{
	ofstream fout;
	fout.open(filebase);
	if (fout)
	for (int i = 0; i < MAX; i++)
	{
		fout << hashtab[i].val;
		fout << "\n";
	}
	fout.close();
}
//������������� ���-������� //���������
void htab_init()
{
	for (int i = 0; i < MAX; i++)
	{
		hashtab[i].empty = true; //������ �������
		strcpy_s(hashtab[i].val, "0");
	}
}
//������� ����������� ���������
int h(char *key)
{
	string buff;
	int radix = 10;  //������� ���������
	char buffer[20]; //���������
	int result(0);
	for (int i = 0; i < SIZE_KEY; i++){
		result = result + int(key[i])*int(pow(3.0, i));
	}
	result = int(pow(result, 2.0));
	buff = _itoa(result, buffer, radix);
	buff = buff.substr(3, 4);
	result = atoi(buff.c_str());
	result = result % MAX;
	return result;
}
//������� ������ �������� cur � ���-������� ���������
bool find_htab(char *cur, int &indexSeg)
{
	int i(0);
	do
	{
		indexSeg = ((h(cur) + STEP*i) % MAX) + (((h(cur) + STEP*i) / MAX) % MAX);
		i++;
		if (!strcmp(hashtab[indexSeg].val, cur)) break;
	} while (!hashtab[indexSeg].empty || i > MAX);
	if (!strcmp(hashtab[indexSeg].val, cur)) return true; //�����
	else indexSeg = 0; return false; //�� �����
}
//��������� ���������� �������� cur � ���-������� ���������
bool add2htab(char *cur)
{
	int indexSeg(0);
	if (!find_htab(cur, indexSeg))
	{
		int i(0);
		do
		{
			indexSeg = ((h(cur) + STEP*i) % MAX) + (((h(cur) + STEP*i) / MAX) % MAX);
			i++;
		} while (!hashtab[indexSeg].empty || i > MAX);
		if (hashtab[indexSeg].empty)
		{
			hashtab[indexSeg].empty = false;
			strcpy(hashtab[indexSeg].val, cur);
			return true;
		}
		else return false;
	}
	else return false;
}
//��������� �������� ��������
bool del_htab(char *cur)
{
	int indexSeg;
	if (find_htab(cur, indexSeg))
	{
		hashtab[indexSeg].empty = true;
		strcpy(hashtab[indexSeg].val, "0");
		return true;
	}
	else return false;
}
//��������� �������� ���� ������� � �������
void del_all_htab()
{
	for (int i = 0; i < MAX; i++)
	{
		hashtab[i].empty = true;
		strcpy(hashtab[i].val, "0");
	}
}
//��������� ������ ���-�������
void print_htab()
{
	for (int i = 0; i < MAX; i++)
	{
		if (!hashtab[i].empty)
		{
			cout << i + 1 << ") " << hashtab[i].val << endl;
		}
	}
}
//��������� �������� ����� �����
void key_control(char *key)
{
	bool fail(false);
	do
	{
		fail = false;
		cin.clear();
		cin.sync();
		cin >> key;
		if (!(!isdigit(key[0]) && isdigit(key[1]) && isdigit(key[2]) && isdigit(key[3]) && isdigit(key[4]) && !isdigit(key[5])))
			fail = true;
	} while (cin.fail() || fail || strlen(key) < 6);
}
//��������� �����
void rand_key()
{
	char key[7];
	for (int i = 0; i < MAX; i++)
	{
		key[0] = char(rand() % 25 + 65);
		key[1] = char(rand() % 9 + 48);
		key[2] = char(rand() % 9 + 48);
		key[3] = char(rand() % 9 + 48);
		key[4] = char(rand() % 9 + 48);
		key[5] = char(rand() % 25 + 65);
		key[6] = '\0';
		if (!hashtab[h(key)].empty) continue;
		else  add2htab(key);
	}
}
//��������� ����
void menu()
{
	int choice(0);
	bool end(false);
	int indexSeg(0);
	char val[SIZE_KEY + 1];
	do
	{
		do
		{
			cin.sync();
			cin.clear();
			system("cls");
			cout << " ________________ ���� ________________\n"
				<< "  [1] - �������� �������\n"
				<< "  [2] - ������� �������\n"
				<< "  [3] - ����� �������\n"
				<< "  [4] - ������� ���-�������\n"
				<< "  [5] - ��������� ������� ���������� �������\n"
				<< "  [6] - ������� ��� ������ �� ���-�������\n"
				<< "  [0] - �����\n"
				<< "\n������� �������: ";
			cin >> choice;
		} while (cin.fail() || !(choice >= 0 && choice <= 6));
		switch (choice)
		{
		case 1:
			cout << "__ ����������\n";
			cout << "������� ���� ���� A0000A: ";
			key_control(val);
			add2htab(val) ? cout : cout << "������ �� ���������!\n";
			break;
		case 2:
			cout << "__ ��������\n";
			cout << "������� ���� ���� A0000A: ";
			key_control(val);
			del_htab(val) ? cout << "������ �������!\n" : cout << "������ HE �������!\n";
			break;
		case 3:
			cout << "__ �����\n";
			cout << "������� ���� ���� A0000A: ";
			key_control(val);
			if (find_htab(val, indexSeg))
				cout << indexSeg + 1 << ") " << hashtab[indexSeg].val << endl;
			break;
		case 4:
			cout << "__ ����� ���-������� __\n";
			print_htab();
			break;
		case 5:
			cout << "__ ���������� ������� ���������� ������� __\n";
			rand_key();
			break;
		case 6:
			cout << "__ �������� ���� ������� __\n";
			del_all_htab();
			break;
		case 0:
			end = true;
			break;
		}
		cout << endl;
		system("pause");
	} while (!end);
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	htab_init();
	readfromtxt();
	menu();
	write2txt();
	return 0;
}