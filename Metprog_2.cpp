#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <locale.h>
#include <map>
#include <random>
#include <chrono>

using namespace std;
class Camp_archive {
public:
	string name;
	int year;
	int squad_number;
	string date;
	int shift_number;
	Camp_archive() {
		year = 0;
		squad_number = 0;
		shift_number = 0;
		date = "12.02.2021";
		name = "";
	}
	Camp_archive(int new_year, int new_squad_number, string new_name, string new_date, int new_shift_number) {

		year = new_year;
		squad_number = new_squad_number;
		shift_number = new_shift_number;
		name = new_name;
		date = new_date;
	}
};
	bool operator >(const Camp_archive& lhs, const Camp_archive& rhs) {
		return lhs.name > rhs.name;
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
	bool operator ==(const Camp_archive& lhs, const Camp_archive& rhs) {
		return (lhs.name == rhs.name);
	}
	ofstream& operator <<(ofstream& stream, const Camp_archive& archive) {
		stream << archive.year << " " << archive.squad_number << " " << archive.name << " " << archive.date << " " << archive.shift_number << "\n";
		return stream;
	}
	ostream& operator<<(ostream& stream, const Camp_archive& archive) {
		stream << archive.year << " " << archive.squad_number << " " << archive.name << " " << archive.date << " " << archive.shift_number << "\n";
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
		string string_name = "";
		while (line[pointer] != ' ') {
			string_name += line[pointer];
			++pointer;
		}
		++pointer;
		string_name += " ";
		while (line[pointer] != ' ') {
			string_name += line[pointer];
			++pointer;
		}
		++pointer;
		string_name += " ";
		while (line[pointer] != ' ') {
			string_name += line[pointer];
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
		return Camp_archive(int_year, int_squad_number, string_name, string_date, int_shift_number);

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
	template<class T>
	vector<Camp_archive> linear_search(vector<T>& a, int start, int size, string key)
	{
		vector<Camp_archive> search = {};
		for (int i = start; i < size; i++)
		{
			if (a[i].name == key)
				search.push_back(a[i]);
		}
		if (start >= size) return search;
	}
	
	template<class T> 
	vector<Camp_archive> binary_search(vector<T>& a, int start, int end, string key)
	{
		vector<Camp_archive> search_result;
		int left, right;
		if (start > end)
			return search_result;
		const int middle = start + ((end  - start) / 2);
		if (a[middle].name == key) {
			search_result.push_back(a[middle]);
			left = middle - 1;
			right = middle + 1;
			if (left >= start) {
				while (a[left].name == key) {
					search_result.push_back(a[left]);
					--left;
					if (left < start) break;
				}
			}
			if (right <= end) {
				while (a[right].name == key) {
					search_result.push_back(a[right]);
					++right;
					if (right > end) break;
				}
			}
			return search_result;
		}
		else if (a[middle].name > key)
			return binary_search(a, start, middle - 1, key);
		return binary_search(a, middle + 1, end, key);
	}


	int main()
	{
		setlocale(LC_ALL, "rus");
		ifstream file("C:\\Users\\Екатерина\\db10000.txt");
		int size = 10000;
		random_device rd;
		mt19937 prng{ rd() };
		uniform_int_distribution <> dist(0, size - 1);
		int random_selection = dist(prng);
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

		//linear_seach
		string key = mas[random_selection].name;
		auto t1 = chrono::high_resolution_clock::now();
		vector<Camp_archive> search = linear_search(mas, 0, size, key);
		auto t2 = chrono::high_resolution_clock::now();
		cout << "linear search:" <<chrono::duration_cast<chrono::duration<double>>(t2 - t1).count() << "\n";
		for (auto c : search) cout << c;
		vector<Camp_archive> sort_selection = mas;
	
		//selection sort + binary search
		t1 = chrono::high_resolution_clock::now();
		selection_sort<Camp_archive>(sort_selection, size);
		vector < Camp_archive> answer = binary_search(sort_selection, 0, size - 1, key);
		t2 = chrono::high_resolution_clock::now();
		cout << "selection sort + binary search:" << chrono::duration_cast<chrono::duration<double>>(t2 - t1).count() << "\n";
		for (auto c : answer) cout << c;

		//binary search in sorted array
		t1 = chrono::high_resolution_clock::now();
		answer =  binary_search(sort_selection, 0, size - 1, key);
		t2 = chrono::high_resolution_clock::now();
		cout << "binary search in sorted array:" << chrono::duration_cast<chrono::duration<double>>(t2 - t1).count() << "\n";
		for (auto c : answer) cout << c;

		ofstream out;
		out.open("C:\\Users\\Екатерина\\outdb10000.txt");
		for (int i = 0; i < sort_selection.size(); ++i) {
			out << sort_selection[i];
		}
		
		//multimap
		multimap <string, Camp_archive> archieve = {};
		for (int i = 0; i < mas.size(); ++i) {
			archieve.insert({ mas[i].name, mas[i] });
		}
		t1 = chrono::high_resolution_clock::now();
		pair<multimap<string, Camp_archive>::iterator, multimap<string, Camp_archive>::iterator> p = archieve.equal_range(key);
		t2 = chrono::high_resolution_clock::now();
		cout << "search in multimap:" << chrono::duration_cast<chrono::duration<double>>(t2 - t1).count() << "\n";
		for (multimap<string, Camp_archive>::iterator it = p.first; it != p.second; ++it) cout << it->second;
	}
