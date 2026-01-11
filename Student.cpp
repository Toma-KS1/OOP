#include "Student.h"
#include <iostream>
#include <limits>
#include <iomanip>

int Student::getCurrentEnrolledEcts() const {
    return calculateCurrentEcts();
}

Course* Student::findEnrolledCourse(const std::string& course_code) {
    for (size_t i = 0; i < enrolled_count; i++) {
        if (enrolled_courses[i].getSifra_Kolegija() == course_code) {
            return &enrolled_courses[i];
        }
    }
    return nullptr;
}

const Course* Student::findEnrolledCourse(const std::string& sifra_kolegija) const {
    for (size_t i = 0; i < enrolled_count; i++) {
        if (enrolled_courses[i].getSifra_Kolegija() == sifra_kolegija) {
            return &enrolled_courses[i];
        }
    }
    return nullptr;
}

void Student::removeEnrolledCourse(const std::string& sifra_kolegija) {
    int index = -1;
    for (size_t i = 0; i < enrolled_count; i++) {
        if (enrolled_courses[i].getSifra_Kolegija() == sifra_kolegija) {
            index = i;
            break;
        }
    }
    
    if (index == -1) return;
    
    if (enrolled_count == 1) {
        delete[] enrolled_courses;
        enrolled_courses = nullptr;
        enrolled_count = 0;
    } else {
        Course* new_enrolled = new Course[enrolled_count - 1];
        size_t new_index = 0;
        
        for (size_t i = 0; i < enrolled_count; i++) {
            if (i != static_cast<size_t>(index)) {
                new_enrolled[new_index++] = enrolled_courses[i];
            }
        }
        
        delete[] enrolled_courses;
        enrolled_courses = new_enrolled;
        enrolled_count--;
    }
}

void Student::addCompletedCourse(const Course& course) {
    Course* new_completed = new Course[completed_count + 1];
    
    for (size_t i = 0; i < completed_count; i++) {
        new_completed[i] = completed_courses[i];
    }
    
    new_completed[completed_count] = course;
    
    delete[] completed_courses;
    completed_courses = new_completed;
    completed_count++;
}

void Student::updateProsjek(double nova_ocjena) {
    if (completed_count > 0) {
        prosjek = (prosjek * (completed_count - 1) + nova_ocjena) / completed_count;
    } else {
        prosjek = nova_ocjena;
    }
}

void Student::moveCourseToCompleted(const std::string& sifra_kolegija, double ocjena) {
    Course* course = findEnrolledCourse(sifra_kolegija);
    if (!course) return;
    
    Course completed_course = *course;
    
    removeEnrolledCourse(sifra_kolegija);
    
    addCompletedCourse(completed_course);
    
    ects_polozeno += completed_course.getECTS_Bodovi();
    
    updateProsjek(ocjena);
}

bool Student::canAddCourse(const Course& course) const {
    int current_ects = calculateCurrentEcts();
    return (current_ects + course.getECTS_Bodovi()) <= UniversityConstants::MAX_ECTS_PER_YEAR;
}

int Student::total_students = 0;

Student& Student::operator+=(const Course& course) {
    if (isEnrolledInCourse(course.getSifra_Kolegija())) {
        std::cout << "Pogreska: Student " << name << " je vec upisan na kolegij " 
                  << course.getIme_Kolegija() << std::endl;
        return *this;
    }
    
    int new_total_ects = calculateCurrentEcts() + course.getECTS_Bodovi();
    if (new_total_ects > UniversityConstants::MAX_ECTS_PER_YEAR) {
        std::cout << "Pogreska: Upis kolegija " << course.getIme_Kolegija()
                  << " (" << course.getECTS_Bodovi() << " ECTS) bi prekoracio maksimalnih "
                  << UniversityConstants::MAX_ECTS_PER_YEAR << " ECTS po godini.\n";
        std::cout << "Trenutno ECTS u tijeku: " << calculateCurrentEcts() << "\n";
        return *this;
    }
    
    Course* new_enrolled = new Course[enrolled_count + 1];
    
    for (size_t i = 0; i < enrolled_count; i++) {
        new_enrolled[i] = enrolled_courses[i];
    }
    
    new_enrolled[enrolled_count] = course;
    
    delete[] enrolled_courses;
    enrolled_courses = new_enrolled;
    enrolled_count++;
    
    std::cout << "Student " << name << " upisan na kolegij: " 
              << course.getIme_Kolegija() << " (" << course.getECTS_Bodovi() << " ECTS)" << std::endl;
    
    return *this;
}

Student& Student::operator++() {
    if (ects_polozeno >= UniversityConstants::REQUIRED_ECTS_PER_YEAR) {
        if (year < 5) {
            year++;
            std::cout << "Student " << name << " napreduje u " << year << ". godinu.\n";
            
        } else {
            std::cout << "Student " << name << " je vec u posljednjoj godini studija.\n";
        }
    } else {
        int Potrebno = UniversityConstants::REQUIRED_ECTS_PER_YEAR - ects_polozeno;
        std::cout << "Student " << name << " ne moze napredovati. Nedostaje " 
                  << Potrebno << " ECTS bodova.\n";
        std::cout << "Potrebno: " << UniversityConstants::REQUIRED_ECTS_PER_YEAR 
                  << ", Imate: " << ects_polozeno << "\n";
    }
    
    return *this;
}

Student::Student(int id, const std::string& name, 
                 const std::string& study_program, int year,
                 int ects_polozeno, double prosjek)
    : id(id), name(name), study_program(study_program), 
      year(year), ects_polozeno(ects_polozeno), prosjek(prosjek),
      enrolled_courses(nullptr), enrolled_count(0),
      completed_courses(nullptr), completed_count(0) {
    total_students++;
}

Student::Student(const Student& drugi)
    : id(drugi.id), name(drugi.name), study_program(drugi.study_program),
      year(drugi.year), ects_polozeno(drugi.ects_polozeno), prosjek(drugi.prosjek),
      enrolled_count(drugi.enrolled_count), completed_count(drugi.completed_count) {
    
    if (enrolled_count > 0) {
        enrolled_courses = new Course[enrolled_count];
        for (size_t i = 0; i < enrolled_count; i++) {
            enrolled_courses[i] = drugi.enrolled_courses[i];
        }
    } else {
        enrolled_courses = nullptr;
    }
    
    if (completed_count > 0) {
        completed_courses = new Course[completed_count];
        for (size_t i = 0; i < completed_count; i++) {
            completed_courses[i] = drugi.completed_courses[i];
        }
    } else {
        completed_courses = nullptr;
    }
    
    total_students++;
    std::cout << "Kopiraj konstruktor za " << name << std::endl;
}

Student::Student(Student&& drugi) noexcept
    : id(drugi.id), name(std::move(drugi.name)), 
      study_program(std::move(drugi.study_program)),
      year(drugi.year), ects_polozeno(drugi.ects_polozeno), prosjek(drugi.prosjek),
      enrolled_courses(drugi.enrolled_courses), enrolled_count(drugi.enrolled_count),
      completed_courses(drugi.completed_courses), completed_count(drugi.completed_count) {
    
    drugi.enrolled_courses = nullptr;
    drugi.enrolled_count = 0;
    drugi.completed_courses = nullptr;
    drugi.completed_count = 0;
    
    total_students++;
    std::cout << "Move konstruktor za " << name << std::endl;
}

Student::~Student() {
    delete[] enrolled_courses;
    delete[] completed_courses;
    total_students--;
    std::cout << "Destructor za " << name << std::endl;
}

Student& Student::operator=(const Student& drugi) {
    std::cout << "Copy assignment za " << name << std::endl;
    
    if (this != &drugi) {
        delete[] enrolled_courses;
        delete[] completed_courses;
        
        id = drugi.id;
        name = drugi.name;
        study_program = drugi.study_program;
        year = drugi.year;
        ects_polozeno = drugi.ects_polozeno;
        prosjek = drugi.prosjek;
        enrolled_count = drugi.enrolled_count;
        completed_count = drugi.completed_count;
        
        if (enrolled_count > 0) {
            enrolled_courses = new Course[enrolled_count];
            for (size_t i = 0; i < enrolled_count; i++) {
                enrolled_courses[i] = drugi.enrolled_courses[i];
            }
        } else {
            enrolled_courses = nullptr;
        }
        
        if (completed_count > 0) {
            completed_courses = new Course[completed_count];
            for (size_t i = 0; i < completed_count; i++) {
                completed_courses[i] = drugi.completed_courses[i];
            }
        } else {
            completed_courses = nullptr;
        }
    }
    return *this;
}

Student& Student::operator=(Student&& drugi) noexcept {
    std::cout << "Move assignment za " << name << std::endl;
    
    if (this != &drugi) {
        delete[] enrolled_courses;
        delete[] completed_courses;
        
        id = drugi.id;
        name = std::move(drugi.name);
        study_program = std::move(drugi.study_program);
        year = drugi.year;
        ects_polozeno = drugi.ects_polozeno;
        prosjek = drugi.prosjek;
        enrolled_courses = drugi.enrolled_courses;
        enrolled_count = drugi.enrolled_count;
        completed_courses = drugi.completed_courses;
        completed_count = drugi.completed_count;
        
        drugi.enrolled_courses = nullptr;
        drugi.enrolled_count = 0;
        drugi.completed_courses = nullptr;
        drugi.completed_count = 0;
    }
    return *this;
}

int Student::get_total_students() {
    return total_students;
}

int Student::getId() const {
    return id;
}

std::string Student::getName() const {
    return name;
}

std::string Student::getStudyProgram() const {
    return study_program;
}

int Student::getYear() const {
    return year;
}

int Student::getEcts_Polozeno() const {
    return ects_polozeno;
}

double Student::getProsjek() const {
    return prosjek;
}

size_t Student::getEnrolledCount() const {
    return enrolled_count;
}

size_t Student::getCompletedCount() const {
    return completed_count;
}

Course* Student::getEnrolledCourses() const {
    return enrolled_courses;
}

Course* Student::getCompletedCourses() const {
    return completed_courses;
}

void Student::setId(int id) {
    this->id = id;
}

void Student::setName(const std::string& name) {
    this->name = name;
}

void Student::setStudyProgram(const std::string& study_program) {
    this->study_program = study_program;
}

void Student::setYear(int year) {
    if (year >= 1 && year <= 5) {
        this->year = year;
    }
}

void Student::setEcts_Polozeno(int ects) {
    if (ects >= 0) {
        this->ects_polozeno = ects;
    }
}

void Student::setProsjek(double prosjek) {
    if (prosjek >= 0.0 && prosjek <= 5.0) {
        this->prosjek = prosjek;
    }
}


std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << "ID: " << student.id << "\n"
       << "Ime: " << student.name << "\n"
       << "Studij: " << student.study_program << "\n"
       << "Godina: " << student.year << "\n"
       << "ECTS bodovi: " << student.ects_polozeno << "\n"
       << "Prosjek: " << std::fixed << std::setprecision(2) << student.prosjek << "\n"
       << "Upisanih kolegija: " << student.enrolled_count << "\n"
       << "Polozenih kolegija: " << student.completed_count << "\n";
    return os;
}

std::istream& operator>>(std::istream& is, Student& student) {
    std::cout << "Unesite ID studenta: ";
    is >> student.id;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Unesite ime studenta: ";
    std::getline(is, student.name);
    
    std::cout << "Unesite studijski program: ";
    std::getline(is, student.study_program);
    
    std::cout << "Unesite godinu studija (1-5): ";
    is >> student.year;
    
    while (student.year < 1 || student.year > 5) {
        std::cout << "Pogresna godina. Unesite ponovno (1-5): ";
        is >> student.year;
    }

    std::cout << "Unesite osvojene ECTS bodove: ";
    is >> student.ects_polozeno;
    
    std::cout << "Unesite prosjek ocjena (0.0-5.0): ";
    is >> student.prosjek;
    
    while (student.prosjek < 0.0 || student.prosjek > 5.0) {
        std::cout << "Pogresan prosjek, Unesite ponovno (0.0-5.0): ";
        is >> student.prosjek;
    }
    
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return is;
}

void Student::realocirajUpisaneKolegije(size_t novi_kapacitet) {
}

void Student::realocirajZavrseneKolegije(size_t novi_kapacitet) {
}

void Student::kopirajKolegije(const Student& other) {
}

void Student::izbrisiKolegije() {
}