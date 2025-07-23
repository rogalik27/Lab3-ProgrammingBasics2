#include <iostream>
#include <cstring>
using namespace std;

const int MAX_STUDENTS = 50;
const int SUBJECT_COUNT = 5;
class Group;
class Student {
private:
    unsigned int id;
    char* familyName;
    int* grades;
    Group* group;

public:
    Student() : id(0), familyName(nullptr), grades(nullptr), group(nullptr) {}
    unsigned int getId() const { return id; }
    const char* getFamilyName() const { return familyName; }
    int* getGrades() const { return grades; }
    Group* getGroup() const { return group; }

    void setId(unsigned int newId) { id = newId; }

    void setFamilyName(const char* name) {
        delete[] familyName;
        familyName = new char[strlen(name) + 1];
        strcpy(familyName, name);
    }

    void setGrades(const int* gradesInput) {
        delete[] grades;
        grades = new int[SUBJECT_COUNT];
        for (int i = 0; i < SUBJECT_COUNT; ++i)
            grades[i] = gradesInput[i];
    }

    void setGroup(Group* g) { group = g; }

    Student& operator=(const Student& other) {
        if (this != &other) {
            id = other.id;
            setFamilyName(other.familyName);
            setGrades(other.grades);
            group = other.group;
        }
        return *this;
    }
};

class Group {
private:
    int index;
    Student* students[MAX_STUDENTS];
    int count;

public:
    Group() : index(0), count(0) {}

    Group(int index) : index(index), count(0) {}

    void setIndex(int newIndex) { index = newIndex; }
    int getIndex() const { return index; }
    int getCount() const { return count; }

    Student* operator[](int i) const {
        if (i >= 0 && i < count)
            return students[i];
        return nullptr;
    }

    void addStudent(Student* s) {
        if (count < MAX_STUDENTS) {
            students[count++] = s;
            s->setGroup(this);
        }
    }

    void sortByName() {
        for (int i = 0; i < count - 1; ++i) {
            for (int j = i + 1; j < count; ++j) {
                if (*students[i] > *students[j]) {
                    Student* tmp = students[i];
                    students[i] = students[j];
                    students[j] = tmp;
                }
            }
        }
    }

    Student** findEvenIdStudents(int& foundCount) {
        Student** found = new Student*[count];
        foundCount = 0;
        for (int i = 0; i < count; ++i) {
            if (students[i]->getId() % 2 == 0)
                found[foundCount++] = students[i];
        }
        return found;
    }

    void printGroup() const {
        cout << "Group #" << index << ":\n";
        for (int i = 0; i < count; ++i)
            cout << "  " << *students[i] << endl;
    }
};

