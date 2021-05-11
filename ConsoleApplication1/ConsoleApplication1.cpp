#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
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
int getThreadCount() {
	cout << "Введите количество потоков" << endl;
	int threadCount;
	cin >> threadCount;
	return threadCount;
}
int getDisciplineCount() {
	cout << "Введите количество дисцплин" << endl;
	int disciplineCount;
	cin >> disciplineCount;
	return  disciplineCount;
}


int main() {
	initRussianText();
	Disciple disciples[10];
	int threadCount = getThreadCount();
	int disciplineCount = getDisciplineCount();
	for (int i = 0; i < disciplineCount; i++)
	{
		cout << "Введите название дисциплины" << endl;
		string nameofdic;
		cin >> nameofdic;
		disciples[i].name = nameofdic;
		cout << "Введите количество  лекций" << endl;
		int count_of_lec;
		cin >> count_of_lec;
		disciples[i].lec_count = count_of_lec;
		cout << "Введите имя преподователя" << endl;
		string nameofpred;
		cin >> nameofpred;
		disciples[i].lec_name = nameofpred;
		cout << "Введите номер аудитории" << endl;
		string numb1;
		cin >> numb1;
		disciples[i].lec_aud = numb1;
		numb1.clear();
		nameofdic.clear();
		int count_of_sem;
		cout << "Введите количество  семинаров" << endl;
		cin >> count_of_sem;
		disciples[i].sem_count = count_of_sem;
		for (int j = 0; j < count_of_sem; j++)
		{
			cout << "Введите имя преподователя" << endl;
			cin >> nameofpred;

			disciples[i].sem_name[j] = nameofpred;
			cout << "Введите номер аудитории" << endl;
			cin >> numb1;
			disciples[i].sem_aud[j] = numb1;
			nameofpred.clear();
			numb1.clear();
		}
		numb1.clear();
		nameofdic.clear();

		cout << "Введите количество  лабараторных" << endl;
		int count_of_lab;
		cin >> count_of_lab;
		disciples[i].lab_count = count_of_lab;
		for (int j = 0; j < count_of_lab; j++)
		{
			cout << "Введите имя преподователя" << endl;
			cin >> nameofpred;
			disciples[i].lab_name[j] = nameofpred;
			cout << "Введите номер аудитории" << endl;
			cin >> numb1;
			disciples[i].lab_aud[j] = numb1;
			nameofpred.clear();
			numb1.clear();
		}
	}

	auto days = new Day * [12];
	for (int i = 0; i < 12; i++)
		days[i] = new Day[threadCount];

	for (int i = 0; i < 12; i++)
		for (int j = 0; j < threadCount; j++) {
			days[i][j].lec_count = 0;
			days[i][j].lessons_count = 0;
		}

	int d = 0;

	for (int i = 0; i < disciplineCount + 1; i++) {
		for (int j = 0; j < disciples[i].lec_count; j++) {
			if (days[d][0].lec_count < 2) {
				days[d][0].name[days[d][0].lessons_count] = disciples[i].name;
				days[d][0].type[days[d][0].lessons_count] = "Lection";
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

	for (int i = 0; i < disciplineCount + 1; i++) {
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
				days[d][p].type[days[d][p].lessons_count] = "Seminar";
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

	for (int i = 0; i < disciplineCount + 1; i++) {
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
				days[d][p].type[days[d][p].lessons_count] = "Laboratornaya";
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

	outf << "Day"
		<< "\t" << "Type"
		<< "\t" << "Prepod"
		<< "\t" << "Lesson"
		<< "\t" << "Aud"
		<< "\t" << endl;

	for (int k = 0; k < threadCount; k++) {
		outf << "Group " << k + 1 << endl;
		for (int i = 0; i < 12; i++) {
			if (days[i][k].lessons_count != 0)
				switch ((i + 1) % 6) {
				case 1: outf << "Ponedelnik" << "\t";
					break;
				case 2: outf << "Vtornik" << "\t";
					break;
				case 3: outf << "Sreda" << "\t";
					break;
				case 4: outf << "Chetverg" << "\t";
					break;
				case 5: outf << "Pyatnica" << "\t";
					break;
				case 0: outf << "Subbota" << "\t";
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
