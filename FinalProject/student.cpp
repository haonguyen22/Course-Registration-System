#include "student.h"
#include "Header.h"
#include "console.h"
#include "Semester.h"
#include "DKMon.h"
#include "course.h"
#include "staff.h"
#include "SchoolYear.h"

void AddTailStudent(ListSV*& ds, SinhVien sv)
{
	ListSV* s = new ListSV;
	s->info = sv;
	s->pNext = NULL;
	if (ds == NULL)
		ds = s;
	else
	{
		ListSV* k = ds;
		while (k->pNext != NULL)
			k = k->pNext;
		k->pNext = s;
	}
}
int CheckClass(ListLop dsl, string a, int n)
{
	for (int i = 0; i < n; ++i)
	{
		if (dsl.l[i].Ma==a)
			if (i == 0) return -1; 
			else return i;
	}
	return 0; 
}
void WriteFileStudent(ListLop& dsl,const SchoolYear&Y)
{
	ofstream file;
	file.open(Y.DSSinhVien, ios::out);
	ListSV* k;
	for (int i = 0; i < dsl.n; ++i)
	{
		for (k = dsl.l[i].pHead; k != NULL; k = k->pNext)
		{
			file << dsl.l[i].Ma << endl;
			file << k->info.ID << endl << k->info.pass << endl; 
			file << k->info.FirstName << endl << k->info.LastName << endl << k->info.Gender << endl << k->info.DateOfBirth << endl << k->info.SocialID << endl;
			file << k->info.begin[0] << " " << k->info.begin[1] << " " << k->info.begin[2] << " " << endl << k->info.YearStudent << endl << k->info.Semester << endl;
		}
	}
	file.close();
}
void ReadFileStudent(ListLop& dsl, const SchoolYear&Y)
{
	ifstream file;
	file.open(Y.DSSinhVien, ios::in);
	string s;
	int STTLop;
	char a[10];
	SinhVien sv;
	int KT;
	while (!file.eof())
	{
		getline(file, s);
		if (s.size() == 0) break;
		strcpy_s(a, 10, s.c_str());
		KT = CheckClass(dsl, a, dsl.n);
		if (KT == -1) STTLop = 0;
		else STTLop = KT;
		sv.Class = s;
		getline(file, s);	sv.ID = s;
		getline(file, s);	sv.pass = s;
		getline(file, s);	sv.FirstName = s;
		getline(file, s);	sv.LastName = s;
		getline(file, s);	sv.Gender = s;
		getline(file, s);	sv.DateOfBirth = s;
		getline(file, s);	sv.SocialID = s;
		for (int i = 0; i < 3; i++) file >> sv.begin[i];
		file >> sv.YearStudent;
		file >> sv.Semester;
		AddTailStudent(dsl.l[STTLop].pHead, sv);
	}
	file.close();
}
void ViewEnrollCourses(SinhVien& S, int se, const SchoolYear& Y)
{
	system("cls");
	ListCourses l = ReadListCourses(se, Y);
	if (l.head == NULL)
	{
		cout << "Chua dang ky mon nao!";
		return;
	}
	ListCourses list = courseOfStudent(l, S, se, Y);
	gotoxy(0, 32);
	int STT = 0;
	if (list.head == NULL)
		cout << "chua dang ki mon nao!" << endl;
	else
	{
		gotoxy(20, 3); cout << "+--------------------------------------------------------------------------------------------------------------------------------------+" << endl;
		gotoxy(20, 4); cout << char(124) << "  " << setw(10) << left << "Ma mon hoc" << char(124) << "  " << setw(30) << left << "Ten mon hoc" << char(124) << "  " << setw(25) << left << "Ten GV" << char(124) << "  " << setw(8) << left << "So TC" << char(124) << "  " << setw(15) << "So sinh vien" << char(124) << "  " << setw(20) << left << "       Lich hoc";
		gotoxy(155, 4); cout << char(124) << endl;
		gotoxy(20, 5); cout << "+--------------------------------------------------------------------------------------------------------------------------------------+" << endl;

		NodeCourse* temp1 = list.head;
		while (temp1 != NULL)
		{
			gotoxy(20, 6 + STT); cout << char(124) << "  " << setw(10) << left << temp1->course.ID << char(124) << "  " << setw(30) << left << temp1->course.Name << char(124) << "  " << setw(25) << left << temp1->course.TeacherName << char(124) << "  " << setw(8) << left << temp1->course.NumOfCredits << char(124) << "  " << setw(15) << temp1->course.MaxNumOfStudents << char(124) << "  ";
			cout << "T" << temp1->course.Session1.thu << " - " << temp1->course.Session1.shift << TimeShift(temp1->course.Session1.shift) << "  " << "T" << temp1->course.Session2.thu << " - " << temp1->course.Session2.shift << TimeShift(temp1->course.Session2.shift);
			gotoxy(155, 6 + STT++); cout << char(124) << endl;
			temp1 = temp1->next;
		}
		gotoxy(20, 6 + STT); cout << "+--------------------------------------------------------------------------------------------------------------------------------------+" << endl;
		gotoxy(15, 6 + STT + 1);

	}
}
void EraserEnrollCourses(SinhVien& S, ListCourses l, int se, const SchoolYear& Y, bool& f)
{
	Time t = getTime();
	Time* arrTime = ReadTimeRegistration(Y);
	char check = isTimeIn(t, arrTime[0], arrTime[1]);
	if (check != 0)
	{
		if (check == 1) cout << "Da qua";
		else if (check == -1) cout << "Chua den";
		cout << " thoi gian dang ky hoc phan!" << endl;
		cout << setfill(' ') << setw(70);
		cout << "Thoi gian dang ky hoc phan tu ";
		cout << arrTime[0].hour << ":";
		if (arrTime[0].minute < 10) cout << "0";
		cout << arrTime[0].minute << ":";
		if (arrTime[0].second < 10) cout << "0";
		cout << arrTime[0].second;
		cout << " ngay " << arrTime[0].day << "/" << arrTime[0].month << "/" << arrTime[0].year << " den ";
		cout << arrTime[1].hour << ":";
		if (arrTime[1].minute < 10) cout << "0";
		cout << arrTime[1].minute << ":";
		if (arrTime[1].second < 10) cout << "0";
		cout << arrTime[1].second;
		cout << " ngay " << arrTime[1].day << "/" << arrTime[1].month << "/" << arrTime[1].year;
		return;
	}
	ViewEnrollCourses(S, se, Y);
	char id[10];
	f = true;
	int i;
	cout << "nhap id mon can huy dang ki: ";
	string ID;
	getline(cin, ID);
	strcpy_s(id, ID.c_str());
	if (CheckCourses(l, id) == false)
	{
		f = false;
	}
	else
	{
		ListCourses temp = courseOfStudent(l, S, se, Y);
		if (CheckCourses(temp, id) == false)
			f = false;
		else
		{
			SinhVien s;
			fstream file, file1;
			file.open(to_string(se) + Y.StudentOfSubject, ios::in);
			file1.open("temp.txt", ios::out);
			char ch[10] = "\0", CH[10] = "\n";
			file.getline(ch, 10);
			while (!file.eof())
			{
				file1 << ch << endl;
				while (CheckCourses(l, CH) == false)
				{
					file.getline(CH, 10);
					if (CheckCourses(l, CH) == true || strcmp(CH, "\0") == 0) break;
					else
					{
						s.Class = CH;
						getline(file, s.ID);
						getline(file, s.pass);
						getline(file, s.FirstName);
						getline(file, s.LastName);
						getline(file, s.Gender);
						getline(file, s.DateOfBirth);
						getline(file, s.SocialID);
						for (i = 0; i < 3; ++i)
						{
							file >> s.begin[i];
						}
						file.ignore();
						file >> s.YearStudent;
						file.ignore();
						file >> s.Semester;
						file.ignore();
						if (s.ID == S.ID && strcmp(ch, id) == 0)
							continue;
						else
						{
							file1 << s.Class << endl;
							file1 << s.ID << endl;
							file1 << s.pass << endl;
							file1 << s.FirstName << endl;
							file1 << s.LastName << endl;
							file1 << s.Gender << endl;
							file1 << s.DateOfBirth << endl;
							file1 << s.SocialID << endl;
							file1 << s.begin[0] << " " << s.begin[1] << " " << s.begin[2] << endl;
							file1 << s.YearStudent << endl;
							file1 << s.Semester << endl;
						}

					}
				}
				strcpy_s(ch, 10, CH);
				strcpy_s(CH, 10, "\n");
			}
			file.close();
			file1.close();
			remove((to_string(se) + Y.StudentOfSubject).c_str());
			rename("temp.txt", (to_string(se) + Y.StudentOfSubject).c_str());
		}
	}
}
void viewScoreBoardOfStudent(const SinhVien& S, ListCourses l, int se, const SchoolYear& Y)
{
	ListCourses list = courseOfStudent(l, S, se, Y);
	if (list.head == NULL)
		cout << "chua dang ki mon nao!" << endl;
	else
	{
		gotoxy(5, 5); cout << "+---------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
		gotoxy(5, 6); cout << char(124) << "   " << setw(7) << left << "ID" << char(124) << "  " << setw(40) << left << "     Name of course" << char(124) << "  " << setw(40) << left << "         Teacher name" << char(124) << "  " << setw(10) << "  Credit" << char(124) << setw(8) << "  Other" << char(124) << setw(10) << " MidTerm " << char(124) << setw(8) << "  Final" << char(124) << setw(8) << " Total" << char(124) << endl;
		gotoxy(5, 7); cout << "+---------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
		NodeCourse* temp1 = list.head;
		int t = 1;
		DiemMonHoc score;
		while (temp1 != NULL)
		{
			score = ReadfileCSVScore(S, Y, se, temp1->course.ID);
			gotoxy(5, 7 + t);
			cout << char(124)<<" " << setw(9) << left << temp1->course.ID << char(124) << "  " << setw(40) << left << temp1->course.Name << char(124) << "  " << setw(40) << left << temp1->course.TeacherName << char(124) << "  " << setw(10) << temp1->course.NumOfCredits << char(124) << setw(8) << score.Other << char(124) << setw(10) << score.MidTerm << char(124) << setw(8) << score.Final << char(124) << setw(8) << score.Total << char(124) << endl;
			temp1 = temp1->next;
			++t;
		}
		gotoxy(5, 7 + t); cout << "+---------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
	}
}