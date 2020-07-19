/*
Дан текстовый файл. Необходимо создать новый файл и записать в него следующую статистику по исходному файлу:
- количество символов
- количество слов
- количество строк
- количество гласных букв
- количество согласных букв
- количество цифр // — Цифры — это единицы счета от 0 до 9, остальные все — числа.
- количество чисел
	engl var:
- number of characters
- number of words
- number of lines
- number of vowels
- number of consonants
- number of digits
- amount of numbers

textfile.txt - исходник
info.txt - с статистикой
*/
// http://cppstudio.com/uk/post/446/ 
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <algorithm>
#include <fstream>

using namespace std;
#define MENUTOP 0
#define MENULEFT 0
#define BACKGROUND 0
#define FOREGROUND 10
#define SELECTITEM 13
void gotorc(short r, short c) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, { c,r });
}
void Color(unsigned short Back, unsigned short Forg) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	unsigned short c = ((Back & 0x0F) << 4) + (Forg & 0x0F);
	SetConsoleTextAttribute(handle, c);
}
void paintmenu(const char** s, int sizem, int  pm) {
	system("cls");
	gotorc(MENUTOP, MENULEFT);
	Color(BACKGROUND, FOREGROUND);
	cout << "------Menu-------\n";
	for (size_t i = 0; i < sizem; i++)
	{
		gotorc(MENUTOP + i + 1, MENULEFT);
		cout << (i == pm ? Color(BACKGROUND, SELECTITEM), "=>" : "  ");
		cout << s[i] << endl;
		Color(BACKGROUND, FOREGROUND);
	}
}
int menu(const char** s, int sizem, int  pm = 0) {
	char c = 80;
	while (true)
	{
		if (c == 72 || c == 80) paintmenu(s, sizem, pm);
		c = _getch();
		switch (c)
		{
		case 27: //esc
			return -1;
		case 80: //down
			pm++;
			if (pm == sizem) pm = 0;
			break;
		case 72: //up
			if (pm == 0) pm = sizem;
			pm--;
			break;
		case 13: //enter
			return pm;
		}
	}
}
int SymbolsInFile() {
	ifstream fs("textfile.txt"); // связываем файл с потоком
	size_t count_symbols = 0;
	if (fs.is_open()) {
		while (fs.get() && !fs.fail()) {
			++count_symbols;
		}
		fs.close();
	}
	else cout << "Unable to open file" << endl;
	return count_symbols;
}
int WordsInFile() {
	ifstream fs("textfile.txt");
	int count_words = 0;
	char ch;
	fs.seekg(0, ios::beg); // "ios::beg" начало потока
	while (fs) {
		fs.get(ch);
		if (ch == ' ' || ch == '\n')
			count_words++;
	}
	fs.close();
	return count_words - 1;
}
int LinesInFile() {
	ifstream fs("textfile.txt");
	char* str = new char[999]{ 0 };
	int i = 0;
	while (!fs.eof())
	{
		fs.getline(str, 999, '\n');
		i++;
	}
	fs.close();
	delete[]str;
	return i;
}
int VowelsInFile() {
	ifstream fs("textfile.txt");
	int count_vowels = 0;
	char ch;
	fs.seekg(0, ios::beg);
	while (fs) {
		fs.get(ch);
		if (ch == 'A' || ch == 'a' ||
			ch == 'E' || ch == 'e' ||
			ch == 'I' || ch == 'i' ||
			ch == 'O' || ch == 'o' ||
			ch == 'U' || ch == 'u') //A, E, I, O, U
			count_vowels++;
	}
	fs.close();
	return count_vowels;
}
int ConsonantsInFile() {
	ifstream fs("textfile.txt");
	int count_сonsonants = 0;
	char ch;
	fs.seekg(0, ios::beg);
	while (fs) {
		fs.get(ch);
		if (ch == 'B' || ch == 'b' ||
			ch == 'C' || ch == 'c' ||
			ch == 'D' || ch == 'd' ||
			ch == 'F' || ch == 'f' ||
			ch == 'G' || ch == 'g' ||
			ch == 'H' || ch == 'h' ||
			ch == 'J' || ch == 'j' ||
			ch == 'K' || ch == 'k' ||
			ch == 'L' || ch == 'l' ||
			ch == 'M' || ch == 'm' ||
			ch == 'N' || ch == 'n' ||
			ch == 'P' || ch == 'p' ||
			ch == 'Q' || ch == 'q' ||
			ch == 'R' || ch == 'r' ||
			ch == 'S' || ch == 's' ||
			ch == 'T' || ch == 't' ||
			ch == 'V' || ch == 'v' ||
			ch == 'W' || ch == 'w' ||
			ch == 'X' || ch == 'x' ||
			ch == 'Y' || ch == 'y' ||
			ch == 'Z' || ch == 'z') //, , , F, G, H, J, K, L, M, N, P, Q, R, S, T, V, W, X, Y, Z
			count_сonsonants++;
	}
	fs.close();
	return count_сonsonants;
}
int DigitsInFile() {
	ifstream fs("textfile.txt");
	int count_digits = 0;
	char ch;
	fs.seekg(0, ios::beg);
	while (fs) {
		fs.get(ch);
		if (ch == '1' || ch == '2' || ch == '3' || ch == '4' ||
			ch == '5' || ch == '6' || ch == '7' || ch == '8' ||
			ch == '9' || ch == '0') //0123456789
			count_digits++;
	}
	fs.close();
	return count_digits - 1;
}
void WriteInfoInFile() {
	ofstream fs("info.txt");
	fs << "Количество символов = " << SymbolsInFile() << '\n';
	fs << "Количество слов = " << WordsInFile() << '\n';
	fs << "Количество строк = " << LinesInFile() << '\n';
	fs << "Количество гласных букв = " << VowelsInFile() << '\n';
	fs << "Количество согласных букв = " << ConsonantsInFile() << '\n';
	fs << "Количество цифр = " << DigitsInFile() << '\n';
	fs.close();
}

int main() {
	setlocale(LC_ALL, ""); //працює тільки з потоком виведення
	SetConsoleCP(1251); //встановлює потрібну кодову таблицю, на потік введення
	SetConsoleOutputCP(1251); //встановлює потрібну кодову таблицю, на потік виводу.	
	Color(BACKGROUND, FOREGROUND);
	system("cls");
	const char* s[]{
		"- кол-во символов",
		"- кол-во слов",
		"- кол-во строк",
		"- кол-во гласных букв",
		"- кол-во согласных букв",
		"- кол-во цифр",
		"- кол-во чисел",
		"- создать новый файл и записать в него статистику по исходному файлу"
	};
	int sizem = sizeof(s) / 4;
	int pm = 0;
	while (true) {
		pm = menu(s, sizem, pm);
		system("cls");
		switch (pm) {
		case -1: return 0;
		case 0://- количество символов
			cout << "Количество символов = " << SymbolsInFile();
			break;
		case 1://- количество слов
			cout << "Количество слов = " << WordsInFile();
			break;
		case 2://- количество строк
			cout << "Количество строк = " << LinesInFile();
			break;
		case 3://- количество гласных букв
			cout << "Количество гласных букв = " << VowelsInFile();
			break;
		case 4://- количество согласных букв
			cout << "Количество согласных букв = " << ConsonantsInFile();
			break;
		case 5://- количество цифр
			cout << "Количество цифр = " << DigitsInFile();
			break;
		case 6://- количество чисел
			break;
		case 7://- создать новый файл и записать в него следующую статистику по исходному файлу
			WriteInfoInFile();
			cout << "Создан новый файл, записано статистику по исходному файлу";
			break;
		}
		Color(BACKGROUND, 2);
		cout << "\n\nОперацію виконано успішно !\n";
		_getch();
	}
}