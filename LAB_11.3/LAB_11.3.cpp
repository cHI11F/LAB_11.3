#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <locale>
#include <algorithm>

using namespace std;

struct Student {
    string surname;
    int course;
    string specialty;
    double physics_grade;
    double math_grade;
    double programming_grade;
};

bool compareStudents(const Student& a, const Student& b) {
    if (a.course != b.course)
        return a.course < b.course;
    if (a.specialty != b.specialty)
        return a.specialty < b.specialty;
    return a.surname > b.surname;
}

void inputStudentData(Student& student, int number) {
    cout << "Student's surname " << number << ": ";
    cin >> student.surname;

    cout << "Course: ";
    cin >> student.course;

    cout << "Specialty: ";
    cin.ignore();
    getline(cin, student.specialty);

    cout << "Physics grade: ";
    cin >> student.physics_grade;
    cout << "Math grade: ";
    cin >> student.math_grade;
    cout << "Programming grade: ";
    cin >> student.programming_grade;
}

void inputStudentsData(vector<Student>& students, int number_of_students) {
    for (int i = 0; i < number_of_students; ++i) {
        Student new_student;
        inputStudentData(new_student, i + 1);
        students.push_back(new_student);
    }
}

void printStudentsTable(const vector<Student>& students) {
    cout << setw(5) << "№" << setw(15) << "Surname" << setw(7) << "Course" << setw(15) << "Specialty"
        << setw(10) << "  Physics" << setw(10) << "    Math" << setw(15) << "     Programming" << endl;
    for (size_t i = 0; i < students.size(); ++i) {
        cout << setw(5) << i + 1 << setw(15) << students[i].surname << setw(7) << students[i].course
            << setw(15) << students[i].specialty << setw(10) << students[i].physics_grade
            << setw(10) << students[i].math_grade << setw(15) << students[i].programming_grade << endl;
    }
}

void sortStudents(vector<Student>& students) {
    sort(students.begin(), students.end(), compareStudents);
}

void buildIndexArray(const vector<Student>& students, vector<int>& indexArray) {
    indexArray.resize(students.size());
    for (int i = 0; i < students.size(); ++i) {
        indexArray[i] = i;
    }

    sort(indexArray.begin(), indexArray.end(), [&](int a, int b) {
        return compareStudents(students[a], students[b]);
        });
}

bool binarySearch(const vector<Student>& students, const string& surname, int course, const string& specialty) {
    int left = 0;
    int right = students.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (students[mid].surname == surname && students[mid].course == course && students[mid].specialty == specialty) {
            return true;
        }
        else if (students[mid].surname < surname) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return false;
}

void saveStudentsData(const vector<Student>& students, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << setw(5) << "№" << setw(15) << "Surname" << setw(7) << "Course" << setw(15) << "Specialty"
            << setw(10) << "  Physics" << setw(10) << "    Math" << setw(15) << "     Programming" << endl;
        for (size_t i = 0; i < students.size(); ++i) {
            file << setw(5) << i + 1 << setw(15) << students[i].surname << setw(7) << students[i].course
                << setw(15) << students[i].specialty << setw(10) << students[i].physics_grade
                << setw(10) << students[i].math_grade << setw(15) << students[i].programming_grade << endl;
        }
        cout << "Data has been saved to " << filename << endl;
    }
    else {
        cout << "Unable to open file." << endl;
    }
}

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");
    vector<Student> students;
    int number_of_students;
    string filename;

    cout << "Enter the path to the notebook (e.g., D:\\blocknote_laba\\eleven_twelve.txt): ";
    getline(cin, filename);

        cout << "Number of students: ";
    cin >> number_of_students;

    inputStudentsData(students, number_of_students);

    sortStudents(students);

    printStudentsTable(students);

    saveStudentsData(students, filename);

    string search_surname;
    int search_course;
    string search_specialty;

    cout << "\nEnter student's surname for search: ";
    cin >> search_surname;

    cout << "Student's course: ";
    cin >> search_course;

    cout << "Student's specialty: ";
    cin.ignore();
    getline(cin, search_specialty);

    if (binarySearch(students, search_surname, search_course, search_specialty)) {
        cout << "The student is enrolled in the specified course and specialty." << endl;
    }
    else {
        cout << "The student is NOT enrolled in the specified course and specialty." << endl;
    }

    return 0;
}