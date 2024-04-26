#include <iostream>
#include <vector>
#include <map>
#include <memory>

struct Student {
    int id;
    std::string name;
    int age;
};

class StudentDatabase {
private:
    std::map<int, std::shared_ptr<Student>> database; 

public:
    void addStudent(int id, const std::string& name, int age) {
        auto student = std::make_shared<Student>(Student{id, name, age});
        database[id] = student;
    }

    void removeStudent(int id) {
        database.erase(id);
    }

    std::shared_ptr<Student> getStudent(int id) {
        auto it = database.find(id);
        if (it != database.end()) {
            return it->second;
        } else {
            return nullptr; 
        }
    }
};

int main() {
    StudentDatabase db;

    db.addStudent(1, "Егор", 22);
    db.addStudent(2, "Иван", 28);
    db.addStudent(3, "Сашка", 21);

    std::shared_ptr<Student> student = db.getStudent(2);
    if (student) {
        std::cout << "Student found: " << student->name << ", Age: " << student->age << std::endl;
    } else {
        std::cout << "Student not found" << std::endl;
    }


    db.removeStudent(2);

    student = db.getStudent(2);
    if (student) {
        std::cout << "Student found: " << student->name << ", Age: " << student->age << std::endl;
    } else {
        std::cout << "Student not found" << std::endl;
    }

}
