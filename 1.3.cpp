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

};

