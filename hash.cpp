#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <locale.h>
#include <random>
#include <chrono>
#include <list>
#include <functional>
#include <set>

using namespace std;
class Camp_archive {
public:
	string name;
	int year;
	int squad_number;
	string date;
	int shift_number;
	size_t hash;
	Camp_archive() {
		year = 0;
		squad_number = 0;
		shift_number = 0;
		date = "12.02.2021";
		name = "";
		hash = 0;
	}
	Camp_archive(int new_year, int new_squad_number, string new_name, string new_date,
		int new_shift_number, size_t new_hash) {
		year = new_year;
		squad_number = new_squad_number;
		shift_number = new_shift_number;
		name = new_name;
		date = new_date;
		hash = new_hash;
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
	stream << archive.year << " " << archive.squad_number << " " <<
		archive.name << " " << archive.date << " " << archive.shift_number << "\n";

	return stream;
}
ostream& operator<<(ostream& stream, const Camp_archive& archive) {
	stream << archive.year << " " << archive.squad_number << " " <<
		archive.name << " " << archive.date << " " << archive.shift_number << "\n";

	return stream;
}
//hash
size_t bad_hash(const string& key) {
	size_t hash = 0;
	size_t len_fr_st = 0;
	for (char cur : key) {
		++len_fr_st;
		hash += len_fr_st *cur * (7 + cur) * 5 + cur * (cur % len_fr_st);
	}
	return hash;
}

size_t best_hash(const string& key) {
	size_t hash = 0;
	size_t len_fr_st = 0;
	for (auto cur : key) {
		++len_fr_st;
		hash += (((len_fr_st * (9973 + cur) - cur ^ 67) + 28657 % cur) + 71) << (cur % len_fr_st);
	}
	return hash;
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
	return Camp_archive(int_year, int_squad_number, string_name, string_date, int_shift_number, best_hash(string_name));
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
		if (a[i].name == key) {
		search.push_back(a[i]);
		return search;
	}

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
	const int middle = start + ((end - start) / 2);
	if (a[middle].name == key) {
		search_result.push_back(a[middle]);
		return search_result;
		/*left = middle - 1;
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
		*/
		return search_result;
	}
	else if (a[middle].name > key)
		return binary_search(a, start, middle - 1, key);
	return binary_search(a, middle + 1, end, key);
}
// hash

class HashTable
{
	int default_size = 0;
	double rehash_size = 0.8;
	int size = 0; //Заполнение
	list <pair<string, Camp_archive>> *mas;
	function <size_t(const string)> f_hash;
public:
	HashTable(function <size_t(const string)> h, int s) {
		default_size = s;
		f_hash = h;
		mas = new  list <pair<string, Camp_archive>>[default_size];
	}
	void Insert(string key, Camp_archive data) {
		size_t h1 = f_hash(key) % default_size;
		mas[h1].remove_if([=](pair<string, Camp_archive> d) {return d.first == key; }); //удаление идентичной записи
		mas[h1].push_back(pair<string, Camp_archive> (key, data));
		++size;
		if (static_cast<double>(size) / default_size >= rehash_size) Rehash();
	}
	bool Find(string key) {
		size_t h1 = f_hash(key) % default_size; //хэш, ячейка
		for (auto cur : mas[h1]) {
			if (cur.first == key) return true;
		}
		return false;
	}
	void Rehash() {
		auto * new_mas = new list <pair<string, Camp_archive>>[default_size * 2];
		for (size_t i = 0; i < default_size; ++i){
			for (auto cur : mas[i]) {
				size_t h1 = f_hash(cur.first) % (default_size * 2);
				new_mas[h1].push_back(cur);
			}
		}
		delete[] mas;
		default_size *= 2;
		mas = new_mas;
	}
	~HashTable() {
		delete[] mas;
	}
};


int main()
{
	setlocale(LC_ALL, "rus");
	ifstream file("C:\\Users\\Екатерина\\db100000.txt");
	int size = 100000;
	//int pr = 80000;
	random_device rd;
	mt19937 prng{ rd() };
	uniform_int_distribution <> dist(size/100 * 95, size - 1);
	int random_selection = dist(prng);
	cout << random_selection <<"\n";
	Camp_archive x;
	HashTable f_bad(bad_hash,size) ;
	HashTable f_best(best_hash, size);
	vector <Camp_archive> mas;
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			//if (pr == 0) break;
			//--pr;
			istringstream iss(line);
			mas.push_back(parser(line));
		}
	}
	else cout << "File not exist";
	for (auto cur : mas) {
		f_bad.Insert(cur.name, cur);
		f_best.Insert(cur.name, cur);
	}
	set <size_t> coll1;
	set <size_t> coll2;
	set <string> repeat_name;
	for (auto cur : mas) {
		repeat_name.insert(cur.name);
		coll1.insert(bad_hash(cur.name));
		coll2.insert(best_hash(cur.name));
	}
	string key = mas[random_selection].name;
	cout << "collision in bad_hash: " << mas.size() - coll1.size() <<"\n";
	cout << "collision in best_hash: " << mas.size() - coll2.size() <<"\n";
	cout << "number of repetitions: " << mas.size() - repeat_name.size() << "\n";
	auto t1 = chrono::high_resolution_clock::now();
	f_bad.Find(key);
	auto t2 = chrono::high_resolution_clock::now();
	cout << "bad hash:		  " << chrono::duration_cast<chrono::duration<double>>(t2 - t1).count() << "\n";

	t1 = chrono::high_resolution_clock::now();
	f_best.Find(key);
	t2 = chrono::high_resolution_clock::now();
	cout << "best hash:		    " << chrono::duration_cast<chrono::duration<double>>(t2 - t1).count() << "\n";

	//linear_seach

	t1 = chrono::high_resolution_clock::now();
	vector<Camp_archive> search = linear_search(mas, 0, size, key);
	t2 = chrono::high_resolution_clock::now();
	cout << "linear search:"<< chrono::duration_cast<chrono::duration<double>>(t2 - t1).count() << "\n";

	vector<Camp_archive> sort_selection = mas;

	//binary search in sorted array
	t1 = chrono::high_resolution_clock::now();
	binary_search(sort_selection, 0, size - 1, key);
	t2 = chrono::high_resolution_clock::now();
	cout << "binary search in sorted array:" <<chrono::duration_cast<chrono::duration<double>>(t2 - t1).count() << "\n";

}