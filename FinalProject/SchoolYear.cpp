#include"Header.h"
#include"SchoolYear.h"
#include"student.h"

unsigned int nam()
{
	fstream file;
	file.open(FILESCHOOLYEAR, ios::in);
	if (file.is_open())
	{
		unsigned int a = 0, b = 0;
		file >> a;
		file >> b;
		file.ignore();
		while (!file.eof())
		{
			SchoolYear c;
			getline(file, c.DsGiaoVien);
			getline(file, c.DSLop);
			getline(file, c.DSSinhVien);
			getline(file, c.Filecsv);
			getline(file, c.ListCourses);
			getline(file, c.sesmester);
			getline(file, c.StudentOfSubject);
			getline(file, c.TimeDKHP);
			file >> a >> b;
			file.ignore();
		}
		file.close();
		return b;
	}
	else return 0;
}

void CreateSchoolYear(SchoolYear& S)
{
	unsigned int n = nam();
	if (n == 0)
	{
		cout << "nhap nam hoc: (ex:2020)  ";
		Time t = getTime();
		S.NameSchoolYear = to_string(t.year) + " " + to_string(t.year + 1);
		string temp1 = to_string(t.year) + "_" + to_string(t.year + 1) + ".txt";
		S.DsGiaoVien += temp1;
		S.DSLop += temp1;
		S.DSSinhVien += temp1;
		S.Filecsv += to_string(t.year) + "_" + to_string(t.year + 1) + ".csv";
		S.ListCourses += temp1;
		S.sesmester += temp1;
		S.StudentOfSubject += temp1;
		S.TimeDKHP += temp1;
	}
	else
	{
		SchoolYear Y;
		string temp = to_string(n) + " " + to_string(n + 1);
		string temp1 = to_string(n) + "_" + to_string(n + 1) + ".txt";
		Y.NameSchoolYear = temp;
		Y.DsGiaoVien += temp1;
		Y.DSLop += temp1;
		Y.DSSinhVien += temp1;
		Y.Filecsv += to_string(n) + "_" + to_string(n + 1) + ".csv";
		Y.ListCourses += temp1;
		Y.sesmester += temp1;
		Y.StudentOfSubject += temp1;
		Y.TimeDKHP += temp1;
		S = Y;
	}
	fstream file;
	file.open(FILESCHOOLYEAR, ios::app);
	file << S.NameSchoolYear << endl;
	file << S.DsGiaoVien << endl;
	file << S.DSLop << endl;
	file << S.DSSinhVien << endl;
	file << S.Filecsv << endl;
	file << S.ListCourses << endl;
	file << S.sesmester << endl;
	file << S.StudentOfSubject << endl;
	file << S.TimeDKHP << endl;
	file.close();
}


SchoolYear present(const string& S)
{
	fstream file;
	file.open(S, ios::in);
	SchoolYear c;
	if (file.is_open())
	{
		unsigned int a = 0, b = 0;
		file >> a;
		file >> b;
		c.NameSchoolYear = to_string(a) + " " + to_string(b);
		file.ignore();
		while (!file.eof())
		{
			getline(file, c.DsGiaoVien);
			getline(file, c.DSLop);
			getline(file, c.DSSinhVien);
			getline(file, c.Filecsv);
			getline(file, c.ListCourses);
			getline(file, c.sesmester);
			getline(file, c.StudentOfSubject);
			getline(file, c.TimeDKHP);
			file >> a >> b;
			file.ignore();
		}
		return c;
	}
	return c;
	file.close();
}
 
void inputDL(const string& fileName1, const string& fileName2)
{
	fstream file1; 
	fstream file2;
	file1.open(fileName1, ios::in);
	file2.open("temp.txt", ios::out);
	string a;
	if (file1.is_open())
	{
		getline(file1, a, '\n');
		while (!file1.eof())
		{
			file2 << a << endl;
			getline(file1, a, '\n');
		}
	}
	file2.close();
	file1.close();
	remove(fileName2.c_str());
	rename("temp.txt", fileName2.c_str());

}

void taoDLgia(const SchoolYear& Y)
{
	SchoolYear y1 = present("DLgia.txt");
	inputDL(y1.DsGiaoVien, Y.DsGiaoVien);
	inputDL(y1.DSLop, Y.DSLop);
	inputDL(y1.DSSinhVien, Y.DSSinhVien);
	inputDL(y1.Filecsv, Y.Filecsv);
	inputDL(y1.ListCourses, Y.ListCourses);
	inputDL(y1.sesmester, Y.sesmester);
	inputDL(y1.StudentOfSubject, Y.StudentOfSubject);
	inputDL(y1.TimeDKHP, Y.TimeDKHP);
}

void ExportFileEmpty(const string& str)
{
	fstream file;
	file.open(str, ios::out);
	file.close();
}

void exportFileToImport(const SchoolYear& Y)
{
	ExportFileEmpty(Y.DsGiaoVien);
	ExportFileEmpty(Y.DSLop);
	ExportFileEmpty(Y.DSSinhVien);
	ExportFileEmpty(Y.Filecsv);
	ExportFileEmpty(Y.ListCourses);
	ExportFileEmpty(Y.sesmester);
	ExportFileEmpty(Y.StudentOfSubject);
	ExportFileEmpty(Y.TimeDKHP);
}