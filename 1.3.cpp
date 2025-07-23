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

    Student(unsigned int id, const char* name, const int* gradesInput, Group* group = nullptr)
        : id(id), group(group)
    {
        familyName = new char[strlen(name) + 1];
        strcpy(familyName, name);

        grades = new int[SUBJECT_COUNT];
        for (int i = 0; i < SUBJECT_COUNT; ++i)
            grades[i] = gradesInput[i];
    }

    Student(const Student& other)
        : id(other.id), group(other.group)
    {
        familyName = new char[strlen(other.familyName) + 1];
        strcpy(familyName, other.familyName);

        grades = new int[SUBJECT_COUNT];
        for (int i = 0; i < SUBJECT_COUNT; ++i)
            grades[i] = other.grades[i];
    }

    ~Student() {
        delete[] familyName;
        delete[] grades;
    }

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

    bool operator<(const Student& other) const {
        return strcmp(familyName, other.familyName) < 0;
    }

    bool operator>(const Student& other) const {
        return strcmp(familyName, other.familyName) > 0;
    }

    friend ostream& operator<<(ostream& os, const Student& s);
};

ostream& operator<<(ostream& os, const Student& s) {
    os << "ID: " << s.id << ", Name: " << s.familyName << ", Grades: ";
    for (int i = 0; i < SUBJECT_COUNT; ++i)
        os << s.grades[i] << (i < SUBJECT_COUNT - 1 ? ", " : "");
    return os;
}

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

int main() {
    Group group(101);

    int grades1[] = {90, 85, 80, 95, 88};
    int grades2[] = {78, 82, 88, 90, 76};
    int grades3[] = {65, 70, 72, 68, 74};

    Student* s1 = new Student(1002, "Ivanchenko", grades1);
    Student* s2 = new Student(1001, "Shevchenko", grades2);
    Student* s3 = new Student(1004, "Bondarenko", grades3);

    group.addStudent(s1);
    group.addStudent(s2);
    group.addStudent(s3);

    cout << "Before sorting:\n";
    group.printGroup();

    group.sortByName();

    cout << "\nAfter sorting by name:\n";
    group.printGroup();

    int foundCount = 0;
    Student** evenIdStudents = group.findEvenIdStudents(foundCount);

    cout << "\nStudents with even IDs:\n";
    for (int i = 0; i < foundCount; ++i)
        cout << "  " << *evenIdStudents[i] << endl;

    delete[] evenIdStudents;
    delete s1;
    delete s2;
    delete s3;

    return 0;
}
