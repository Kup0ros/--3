#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <windows.h>

class Course {
private:
    std::string title;              // Назва факультативу
    std::string instructorName;     // ПІБ викладача
    int semester;                   // Семестр (1, 2 тощо)
    int maxStudents;                // Максимальна місткість групи
    std::string schedule;           // Розклад (дні та час проведення)
    std::vector<std::string> materials; // Список навчальних матеріалів
    bool isOpenForEnrollment;       // Статус запису на курс

public:
    // Конструктор за замовчуванням
    Course()
        : title("Не визначено"), instructorName("Не призначено"),
        semester(1), maxStudents(30), schedule("Не встановлено"),
        isOpenForEnrollment(false) {
        std::cout << "[Конструктор за замовчуванням] Створено пустий курс." << std::endl;
    }

    // Конструктор з параметрами
    Course(std::string t, std::string instr, int sem, int maxStud, std::string sched, bool isOpen = true)
        : title(t), instructorName(instr), semester(sem),
        maxStudents(maxStud), schedule(sched), isOpenForEnrollment(isOpen) {
        std::cout << "[Конструктор з параметрами] Курс \"" << title << "\" успішно ініціалізовано." << std::endl;
    }

    // Деструктор
    ~Course() {
        std::cout << "[Деструктор] Об'єкт курсу \"" << title << "\" видалено з пам'яті." << std::endl;
    }

    // --- Методи для запису полів (Setters) ---
    void setTitle(const std::string& t) { title = t; }
    void setInstructorName(const std::string& instr) { instructorName = instr; }
    void setSemester(int sem) { if (sem > 0) semester = sem; }
    void setMaxStudents(int maxStud) { if (maxStud > 0) maxStudents = maxStud; }
    void setSchedule(const std::string& sched) { schedule = sched; }
    void setEnrollmentStatus(bool status) { isOpenForEnrollment = status; }

    // Додавання матеріалу до курсу
    void addMaterial(const std::string& materialName) {
        materials.push_back(materialName);
    }

    // --- Методи для перегляду полів (Getters) ---
    std::string getTitle() const { return title; }
    std::string getInstructorName() const { return instructorName; }
    int getSemester() const { return semester; }
    int getMaxStudents() const { return maxStudents; }
    std::string getSchedule() const { return schedule; }
    bool getEnrollmentStatus() const { return isOpenForEnrollment; }
    const std::vector<std::string>& getMaterials() const { return materials; }

    // Компонентна функція виведення інформації про курс
    void displayInfo() const {
        std::cout << "\n----------------------------------------\n";
        std::cout << "Курс: " << title << "\n"
            << "Викладач: " << instructorName << "\n"
            << "Семестр: " << semester << "\n"
            << "Ліміт місць: " << maxStudents << "\n"
            << "Розклад: " << schedule << "\n"
            << "Запис: " << (isOpenForEnrollment ? "Відкрито" : "Закрито") << "\n";
        std::cout << "Матеріали курсу:\n";
        if (materials.empty()) {
            std::cout << "  (матеріали ще не додано)\n";
        }
        else {
            for (size_t i = 0; i < materials.size(); ++i) {
                std::cout << "  " << i + 1 << ". " << materials[i] << "\n";
            }
        }
        std::cout << "----------------------------------------\n";
    }

    // Оголошення дружньої функції для експорту короткого аудиторського звіту
    friend void printCourseAuditReport(const Course& c);
};

// Реалізація дружньої функції (має прямий доступ до private-полів)
void printCourseAuditReport(const Course& c) {
    std::cout << "\n[ДРУЖНЯ ФУНКЦІЯ: Аудит курсу]\n";
    std::cout << "Прямий доступ до приватних полів -> Назва: " << c.title
        << " | Викладач: " << c.instructorName
        << " | Семестр: " << c.semester
        << " | Файлів матеріалів: " << c.materials.size()
        << " | Статус набору: " << (c.isOpenForEnrollment ? "АКТИВНИЙ" : "ПРИЗУПИНЕНО")
        << std::endl;
}

int main() {
    // Налаштування кодування для коректного виведення кирилиці в консолі
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "=== Створення курсу через конструктор з параметрами ===\n";
    Course webDev("Розробка Web-систем", "доц. Петренко І. В.", 4, 25, "Вівторок 10:00 - 11:30, Ауд. 312");

    // Використання методів запису
    webDev.addMaterial("Лекція 1: Основи клієнт-серверної архітектури (PDF)");
    webDev.addMaterial("Практична робота 1: Верстка адаптивних інтерфейсів");
    webDev.addMaterial("Методичні вказівки до курсового проєкту");

    // Використання компонентної функції перегляду
    webDev.displayInfo();

    // Виклик дружньої функції
    printCourseAuditReport(webDev);

    std::cout << "\n=== Демонстрація геттерів / сеттерів ===\n";
    std::cout << "Поточний викладач (get): " << webDev.getInstructorName() << std::endl;
    webDev.setInstructorName("проф. Ковальчук О. М.");
    std::cout << "Оновлений викладач (set -> get): " << webDev.getInstructorName() << std::endl;

    std::cout << "\n=== Робота деструктора при виході з області видимості ===\n";
    return 0;
}