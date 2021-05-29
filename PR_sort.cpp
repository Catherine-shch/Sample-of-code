#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
using namespace std;
class Camp_archive {
public:
	string surname;
	string name;
	string middle_name;
	int year;
	int squad_number;
	string date;
	int shift_number;
	Camp_archive() {
		year = 0;
		squad_number = 0;
		shift_number = 0;
		date = "12.02.2021";
		surname = "";
		name = "";
		middle_name = "";
	}
	Camp_archive(int new_year, int new_squad_number, string new_surname, string new_name, string
		new_middle_name, string new_date, int new_shift_number) {
		year = new_year;
		squad_number = new_squad_number;
		shift_number = new_shift_number;
		surname = new_surname;
		name = new_name;
		middle_name = new_middle_name;
		date = new_date;
	}
};
bool operator >(const Camp_archive& lhs, const Camp_archive& rhs) {
	if (lhs.year == rhs.year) {
		if (lhs.squad_number == rhs.squad_number) {
			if (lhs.shift_number == rhs.shift_number) {
				if (lhs.surname == rhs.surname) {
					if (lhs.name == rhs.name) {
						return (lhs.middle_name == rhs.middle_name);
					}
					else return (lhs.name > rhs.name);
				}
				else return (lhs.surname > rhs.surname);
			}
			else return (lhs.shift_number > rhs.shift_number);
		}
		else return (lhs.squad_number > rhs.squad_number);
	}
	else return (lhs.year > rhs.year);
}
bool operator <(const Camp_archive& lhs, const Camp_archive& rhs) {
	return (rhs > lhs);
}
bool operator >=(const Camp_archive& lhs, const Camp_archive& rhs) {
	return !(rhs > lhs);
}
bool operator <=(const Camp_archive& lhs, const Camp_archive& rhs) {
	return !(rhs < lhs);
}
ofstream& operator <<(ofstream& stream, const Camp_archive& archive) {
	stream << archive.year << " " << archive.squad_number << " " << archive.surname << " " << archive.name << " "
		<< archive.middle_name << " " << archive.date << " " << archive.shift_number << "\n";
	return stream;
}
Camp_archive parser(const string& line) {
	int pointer = 0;
	string string_year = "";
	while (line[pointer] != ' ') {
		string_year += line[pointer];
		++pointer;
	}
	int int_year = stoi(string_year);
	++pointer;
	string string_squad_number = "";
	while (line[pointer] != ' ') {
		string_squad_number += line[pointer];
		++pointer;
	}
	int int_squad_number = stoi(string_squad_number);
	++pointer;
	string string_surname = "";
	while (line[pointer] != ' ') {
		string_surname += line[pointer];
		++pointer;
	}
	++pointer;
	string string_name = "";
	while (line[pointer] != ' ') {
		string_name += line[pointer];
		++pointer;
	}
	++pointer;
	string string_middle_name = "";
	while (line[pointer] != ' ') {
		string_middle_name += line[pointer];
		++pointer;
	}
	++pointer;
	string string_date = "";
	while (line[pointer] != ' ') {
		string_date += line[pointer];
		++pointer;
	}
	++pointer;
	string string_shift_number = "";
	string_shift_number += line[pointer];
	int int_shift_number = stoi(string_shift_number);
	return Camp_archive(int_year, int_squad_number, string_surname, string_name, string_middle_name,
		string_date, int_shift_number);
}
template<class T>
void selection_sort(vector<T>& a, int size) {
	int min_index;
	T x;
	for (int i = 0; i < size - 1; ++i) {
		min_index = i;
		x = a[i];
		for (int j = i + 1; j < size; ++j) {
			if (a[j] < x) {
				min_index = j;
				x = a[j];
			}
		}
		a[min_index] = a[i];
		a[i] = x;
	}
}
template<typename T>
void insert_sort(vector<T>& a, int size) {
	int j;
	T x;
	for (int i = 0; i < size; ++i) {
		x = a[i];
		for (j = i - 1; j >= 0 && a[j] > x; --j) {
			a[j + 1] = a[j];
		}
		a[j + 1] = x;
	}
}
template<typename T>
void shaker_sort(vector<T>& a, int size) {
	int j, k = size - 1;
	int lb = 0, ub = size - 1;
	T x;
	do {
		for (j = ub; j > lb; --j) {
			if (a[j - 1] > a[j]) {
				x = a[j - 1];
				a[j - 1] = a[j];
				a[j] = x;
				k = j;
			}
		}
		lb = k;
		for (j = lb; j <= ub; ++j) {
			if (a[j - 1] > a[j]) {
				x = a[j - 1];
				a[j - 1] = a[j];
				a[j] = x;
				k = j;
			}
		}
		ub = k - 1;
	} while (lb < ub);
}
int main()
{
	ifstream file("C:\\Users\\Екатерина\\dbb50000.txt");
	Camp_archive x;
	vector <Camp_archive> mas;
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			istringstream iss(line);
			mas.push_back(parser(line));
		}
	}
	else cout << "File not exist";
	vector<Camp_archive> sort_selection = mas;
	vector<Camp_archive> sort_inserts = mas;
	vector<Camp_archive> sort_shaker = mas;
	int start_time = clock();
	selection_sort<Camp_archive>(sort_selection, 50000);
	int end_time = clock();
	int search_time = end_time - start_time;
	cout << "selection:" << ((float)search_time) / CLOCKS_PER_SEC << "\n";
	start_time = clock();
	insert_sort<Camp_archive>(sort_inserts, 50000);
	end_time = clock();
	search_time = end_time - start_time;
	cout << "insert:" << ((float)search_time) / CLOCKS_PER_SEC << "\n";
	start_time = clock();
	shaker_sort<Camp_archive>(sort_shaker, 50000);
	end_time = clock();
	search_time = end_time - start_time;
	cout << "shaker:" << ((float)search_time) / CLOCKS_PER_SEC << "\n";
	ofstream out;
	out.open("C:\\Users\\Екатерина\\outdbb50000.txt");
	for (int i = 0; i < sort_shaker.size(); ++i) {
		out << sort_shaker[i];
	}
}