#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

void CreateBIN(char* fname) {
    ofstream fout(fname, ios::binary);
    if (!fout.is_open()) {
        cout << "Error: could not open file " << fname << " for writing." << endl;
        return;
    }

    char ch;
    double number;

    do {
        cout << "Enter a number: ";
        cin >> number;
        fout.write((char*)&number, sizeof(number));

        // Очищення буфера
        while (cin.get() != '\n');

        cout << "Continue? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
}

void PrintBIN(char* fname) {
    ifstream fin(fname, ios::binary);
    if (!fin.is_open()) {
        cout << "Error: could not open file " << fname << " for reading." << endl;
        return;
    }

    double number;
    cout << "Contents of " << fname << ":\n";
    while (fin.read((char*)&number, sizeof(number))) {
        cout << number << " ";
    }
    cout << endl;
}

void ProcessBIN(char* fname, char* gname) {
    ifstream fin(fname, ios::binary);
    if (!fin.is_open()) {
        cout << "Error: could not open input file " << fname << endl;
        return;
    }

    ofstream fout(gname);
    if (!fout.is_open()) {
        cout << "Error: could not open output file " << gname << endl;
        return;
    }

    double number, maxVal, minVal, sum = 0.0;
    int count = 0;

    // Перевірка на порожній файл
    if (!fin.read((char*)&number, sizeof(number))) {
        cout << "Error: input file is empty." << endl;
        return;
    }

    // Ініціалізація
    maxVal = minVal = number;
    sum += number;
    count++;

    // Обробка решти чисел
    while (fin.read((char*)&number, sizeof(number))) {
        if (number > maxVal) maxVal = number;
        if (number < minVal) minVal = number;
        sum += number;
        count++;
    }

    // Розрахунки та запис результатів
    if (count > 0) {
        double avgMaxMin = (maxVal + minVal) / 2.0;
        double avgAll = sum / count;

        fout << fixed << setprecision(2);
        fout << "Average of max and min: " << avgMaxMin << endl;
        fout << "Average of all numbers: " << avgAll << endl;

        cout << "Results have been saved to " << gname << endl;
    }
}

int main() {
    char fname[100];
    char gname[100];

    cout << "Enter input file name: ";
    cin >> fname;
    CreateBIN(fname);

    PrintBIN(fname);

    cout << "Enter output file name: ";
    cin >> gname;
    ProcessBIN(fname, gname);

    ifstream fin(gname);
    if (!fin.is_open()) {
        cout << "Error: could not open file " << gname << " for reading." << endl;
        return 1;
    }

    cout << "Contents of " << gname << ":\n";
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }

    return 0;
}