#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <windows.h>

using namespace std;

typedef struct {
	string name;

	int lec_count;
	string lec_aud;
	string lec_name;

	int sem_count;
	string sem_aud[10];
	string sem_name[10];

	int lab_count;
	string lab_aud[10];
	string lab_name[10];
} Disciple;

typedef struct {
	int lec_count;
	int lessons_count;
	string name[4];
	string type[4];
	string aud[4];
	string lessons[4];
} Day;

void initRussianText() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}
int getCount(string message) {
	cout << message << endl;
	int count;
	cin >> count;
	return  count;
}
string getName(string message) {
	cout << message << endl;
	string name;
	cin >> name;
	return name;
}

vector<Disciple> getDisciples(int count) {
	vector<Disciple> disciples(count);
	for (int i = 0; i < count; i++)
	{
		disciples[i].name = getName("Введите название дисциплины");
		disciples[i].lec_count = getCount("Введите количество лекций");
		disciples[i].lec_name = getName("Введите имя преподователя");
		disciples[i].lec_aud = getName("Введите номер аудитории");
		disciples[i].sem_count = getCount("Введите количество  семинаров");
		for (int j = 0; j < disciples[i].sem_count; j++)
		{
			disciples[i].sem_name[j] = getName("Введите имя преподователя");
			disciples[i].sem_aud[j] = getName("Введите номер аудитории");
		}
		disciples[i].lab_count = getCount("Введите количество  лабараторных");
		for (int j = 0; j < disciples[i].lab_count; j++)
		{
			disciples[i].lab_name[j] = getName("Введите имя преподователя");
			disciples[i].lab_aud[j] = getName("Введите номер аудитории");
		}

	}
	return disciples;
}

int main() {
	initRussianText();
	int threadCount = getCount("Введите количество потоков");
	int disciplineCount = getCount("Введите количество дисцплин");
	vector<Disciple> disciples = getDisciples(disciplineCount);

	auto days = new Day * [12];
	for (int i = 0; i < 12; i++) {
		days[i] = new Day[threadCount];
		for (int j = 0; j < threadCount; j++) {
			days[i][j].lec_count = 0;
			days[i][j].lessons_count = 0;
		}
	}

	int d = 0;
	int LECTION_COUNT = 2;
	for (int i = 0; i < disciplineCount; i++) {
		for (int j = 0; j < disciples[i].lec_count; j++) {
			if (days[d][0].lec_count < LECTION_COUNT) {
				days[d][0].name[days[d][0].lessons_count] = disciples[i].name;
				days[d][0].type[days[d][0].lessons_count] = "Лекция";
				days[d][0].aud[days[d][0].lessons_count] = disciples[i].lec_aud;
				days[d][0].lessons[days[d][0].lessons_count] = disciples[i].lec_name;
				days[d][0].lec_count++;
				days[d][0].lessons_count++;
			}
			else {
				j--;
				d++;
			}
		}
	}

	for (int i = 0; i < 12; i++)
		for (int j = 0; j < threadCount; j++)
			days[i][j] = days[i][0];

	d = 0;
	int p = 0;

	for (int i = 0; i < disciplineCount; i++) {
		for (int j = 0; j < disciples[i].sem_count; j++) {
			int flag = 0;
			for (int k = 0; k < threadCount; k++) {
				for (int a = 0; a < days[d][k].lessons_count; a++)
					if (disciples[i].sem_name[j] == days[d][k].name[a]
						|| disciples[i].sem_aud[j] == days[d][k].aud[a])
						flag++;
			}
			if ((days[d][p].lessons_count < 4) && (!flag)) {
				days[d][p].name[days[d][p].lessons_count] = disciples[i].name;
				days[d][p].type[days[d][p].lessons_count] = "Семинар";
				days[d][p].aud[days[d][p].lessons_count] = disciples[i].sem_aud[j];
				days[d][p].lessons[days[d][p].lessons_count] = disciples[i].sem_name[j];
				days[d][p].lessons_count++;
			}
			else {
				j--;
				p++;
				if (p == threadCount) {
					d++;
					p = 0;
				}
			}
		}
	}

	d = 0;
	p = 0;

	for (int i = 0; i < disciplineCount; i++) {
		for (int j = 0; j < disciples[i].lab_count; j++) {
			int flag = 0;
			for (int k = 0; k < threadCount; k++) {
				for (int a = 0; a < days[d][k].lessons_count; a++)
					if (disciples[i].lab_name[j] == days[d][k].name[a]
						|| disciples[i].lab_aud[j] == days[d][k].aud[a])
						flag++;
			}
			if ((days[d][p].lessons_count < 4) && (!flag)) {
				days[d][p].name[days[d][p].lessons_count] = disciples[i].name;
				days[d][p].type[days[d][p].lessons_count] = "Лабораторная";
				days[d][p].aud[days[d][p].lessons_count] = disciples[i].lab_aud[j];
				days[d][p].lessons[days[d][p].lessons_count] = disciples[i].lab_name[j];
				days[d][p].lessons_count++;
			}
			else {
				j--;
				p++;
				if (p == threadCount) {
					d++;
					p = 0;
				}
			}
		}
	}

	ofstream outf("table.xls");

	outf << "День"
		<< "\t" << "Тип"
		<< "\t" << "Препод."
		<< "\t" << "Дисциплина"
		<< "\t" << "Ауд."
		<< "\t" << endl;

	for (int k = 0; k < threadCount; k++) {
		outf << "Группа " << k + 1 << endl;
		for (int i = 0; i < 12; i++) {
			if (days[i][k].lessons_count != 0)
				switch ((i + 1) % 6) {
				case 1: outf << "Понедельник" << "\t";
					break;
				case 2: outf << "Вторник" << "\t";
					break;
				case 3: outf << "Среда" << "\t";
					break;
				case 4: outf << "Четверг" << "\t";
					break;
				case 5: outf << "Пятница" << "\t";
					break;
				case 0: outf << "Суббота" << "\t";
					break;
				}
			for (int j = 0; j < days[i][k].lessons_count; j++) {
				if (j != 0)
					outf << "-" << "\t";
				outf << days[i][k].type[j] << "\t"
					<< days[i][k].lessons[j] << "\t"
					<< days[i][k].name[j] << "\t"
					<< days[i][k].aud[j] << endl;
			}
		}
	}

	ShellExecuteA(0, "open", "EXCEL.EXE", "table.xls", ".", SW_SHOW);

	system("pause");

	return 0;
}
