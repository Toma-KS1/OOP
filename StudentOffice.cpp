#include "StudentOffice.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>

StudentOffice::StudentOffice() {
    std::srand(std::time(0));
    
    dostupni_kolegiji.push_back(Course("Objektno orjentirano programiranje", "OOP-101", 5));
    dostupni_kolegiji.push_back(Course("Baze podataka", "BP-201", 5));
    dostupni_kolegiji.push_back(Course("Primjenjena i numericka matematika", "PMA-301", 5));
    dostupni_kolegiji.push_back(Course("Izrada web aplikacija", "WEB-102", 5));
    dostupni_kolegiji.push_back(Course("Izrada mobilnih aplikacija", "MOB-101", 5));
    dostupni_kolegiji.push_back(Course("Praktikum iz SQL-a", "SQL-101", 5));
    dostupni_kolegiji.push_back(Course("Operativni sustavi", "OS-202", 5));
    dostupni_kolegiji.push_back(Course("Diskretna matematika", "MAT-202", 5));
    dostupni_kolegiji.push_back(Course("Strukturno programiranje i algoritmi", "SPA-101", 5));
    dostupni_kolegiji.push_back(Course("Odabrani alati i naredbe u Linuxu", "LIN-201", 5));
}

void StudentOffice::dodajStudenta(Student& student) {
    studenti.push_back(&student);
    std::cout << "Student " << student.getName() << " dodan u referadu.\n";
}

void StudentOffice::izbrisiStudenta(int student_id) {
    auto it = std::remove_if(studenti.begin(), studenti.end(),
        [student_id](Student* s) { return s->getId() == student_id; });

    if (it != studenti.end()) {
        std::cout << "Student ID " << student_id << " uklonjen iz referade.\n";
        studenti.erase(it, studenti.end());
    }
}

Student* StudentOffice::nadiStudenta(int student_id) {
    for (Student* student : studenti) {
        if (student->getId() == student_id) {
            return student;
        }
    }
    return nullptr;
}

void StudentOffice::prikaziSveStudente() const {
    std::cout << "\nSVI STUDENTI\n";
    if (studenti.empty()) {
        std::cout << "Nema studenata.\n";
        return;
    }

    for (const Student* student : studenti) {
        std::cout << *student << "\n";
        student->printEnrolledCourses();
        student->printCompletedCourses();
        std::cout << "\n";
    }
}

void StudentOffice::dodajDostupneKolegije(const Course& course) {
    dostupni_kolegiji.push_back(course);
}

void StudentOffice::prikaziDostupneKolegije() const {
    std::cout << "\nDOSTUPNI KOLEGIJI\n";
    for (size_t i = 0; i < dostupni_kolegiji.size(); i++) {
        std::cout << i + 1 << ". " << dostupni_kolegiji[i].getIme_Kolegija()
                  << " (" << dostupni_kolegiji[i].getSifra_Kolegija() << ")"
                  << " - " << dostupni_kolegiji[i].getECTS_Bodovi() << " ECTS\n";
    }
}

Course* StudentOffice::nadiKolegij(const std::string& course_code) {
    for (auto& course : dostupni_kolegiji) {
        if (course.getSifra_Kolegija() == course_code) {
            return &course;
        }
    }
    return nullptr;
}

void StudentOffice::moveStudent(Student& student, 
                               const std::string& iz_sifre_kolegija, 
                               const std::string& na_sifru_kolegija) {
    if (!student.isEnrolledInCourse(iz_sifre_kolegija)) {
        std::cout << "Student " << student.getName() 
                  << " nije upisan na kolegij " << iz_sifre_kolegija << "\n";
        return;
    }
    
    Course* to_course = nadiKolegij(na_sifru_kolegija);
    if (!to_course) {
        std::cout << "Kolegij " << na_sifru_kolegija << " ne postoji.\n";
        return;
    }
    
    if (student.isEnrolledInCourse(na_sifru_kolegija)) {
        std::cout << "Student " << student.getName() 
                  << " je vec upisan na kolegij " << na_sifru_kolegija << "\n";
        return;
    }
    
    if (!canStudentEnrollMoreEcts(student, to_course->getECTS_Bodovi())) {
        std::cout << "Student " << student.getName() 
                  << " ne moze upisati kolegij " << na_sifru_kolegija
                  << " zbog prekoracenja ECTS limita.\n";
        return;
    }
    
    Course* from_course_ptr = student.findEnrolledCourse(iz_sifre_kolegija);
    if (from_course_ptr) {
        Course course_to_move = std::move(*from_course_ptr);
        
        student.removeEnrolledCourse(iz_sifre_kolegija);
        
        course_to_move = *to_course;
        
        student.enrollCourse(course_to_move);
        
        std::cout << "Student " << student.getName() 
                  << " premjesten s " << iz_sifre_kolegija 
                  << " na " << na_sifru_kolegija << "\n";
    }
}

bool StudentOffice::enroll_student(Student& student, const std::string& sifra_kolegija) {
    Course* course = nadiKolegij(sifra_kolegija);
    if (!course) {
        std::cout << "Kolegij " << sifra_kolegija << " ne postoji.\n";
        return false;
    }
    
    if (student.isEnrolledInCourse(sifra_kolegija)) {
        std::cout << "Student " << student.getName() 
                  << " je vec upisan na kolegij " << sifra_kolegija << "\n";
        return false;
    }
    
    if (!canStudentEnrollMoreEcts(student, course->getECTS_Bodovi())) {
        std::cout << "Student " << student.getName() 
                  << " ne moze upisati kolegij " << sifra_kolegija
                  << " (" << course->getECTS_Bodovi() << " ECTS).\n";
        std::cout << "Trenutno ECTS u tijeku: " << student.calculateCurrentEcts() << "\n";
        std::cout << "Maksimalno dozvoljeno: " << UniversityConstants::MAX_ECTS_PER_YEAR << "\n";
        return false;
    }
    
    student.enrollCourse(*course);
    return true;
}


void StudentOffice::process_exam_results(
    Student& student, 
    const std::vector<std::pair<std::string, double>>& exam_results) {
    
    std::cout << "\nObrada ispitnih rezultata za studenta " << student.getName() << ":\n";
    
    for (const auto& result : exam_results) {
        const std::string& course_code = result.first;
        double grade = result.second;
        
        process_single_exam_result(student, course_code, grade);
    }
    
    std::cout << "Obrada rezultata zavrsena.\n";
}

void StudentOffice::update_student_years() {
    std::cout << "\nAKTUALIZACIJA GODINE STUDIJA\n";
    
    int promoted_count = 0;
    
    for (Student* student : studenti) {
        if (student->getEcts_Polozeno() >= UniversityConstants::REQUIRED_ECTS_PER_YEAR) {
            if (student->getYear() < 5) {
                int old_year = student->getYear();
                student->setYear(old_year + 1);
                promoted_count++;
                
                std::cout << "Student " << student->getName() 
                          << " napredovao iz " << old_year 
                          << ". u " << student->getYear() << ". godinu.\n";
                std::cout << "ECTS bodova: " << student->getEcts_Polozeno() 
                          << "/" << UniversityConstants::REQUIRED_ECTS_PER_YEAR << "\n";
            } else {
                std::cout << "Student " << student->getName() 
                          << " je vec u zavrsnoj godini.\n";
            }
        } else {
            int needed = UniversityConstants::REQUIRED_ECTS_PER_YEAR - student->getEcts_Polozeno();
            std::cout << "Student " << student->getName() 
                      << " ostaje u " << student->getYear() 
                      << ". godini. Nedostaje " << needed << " ECTS.\n";
        }
    }
    
    std::cout << "Ukupno napredovalo studenata: " << promoted_count << "/" 
              << studenti.size() << "\n";
}

bool StudentOffice::canStudentEnrollMoreEcts(const Student& student, int additional_ects) const {
    int current_ects = student.calculateCurrentEcts();
    return (current_ects + additional_ects) <= UniversityConstants::MAX_ECTS_PER_YEAR;
}

void StudentOffice::process_single_exam_result(Student& student, 
                                              const std::string& course_code, 
                                              double grade) {
    if (!student.isEnrolledInCourse(course_code)) {
        std::cout << "  Greska: Student nije upisan na " << course_code << "\n";
        return;
    }
    
    if (grade < 1.0 || grade > 5.0) {
        std::cout << "  Greska: Nevaljana ocjena " << grade << " za " << course_code << "\n";
        return;
    }
    
    if (grade >= 2.0) {
        student.moveCourseToCompleted(course_code, grade);
        std::cout << "  Polozeno: " << course_code << " sa ocjenom " 
                  << std::fixed << std::setprecision(1) << grade << "\n";
    } else {
        std::cout << "  Nije polozio: " << course_code << " (ocjena " 
                  << std::fixed << std::setprecision(1) << grade << ")\n";
    }
}

void StudentOffice::simulate_exam_period() {
    std::cout << "\n=== SIMULACIJA ISPITNOG ROKA ===\n";
    
    for (Student* student : studenti) {
        std::cout << "\nStudent: " << student->getName() << "\n";
        generate_random_exam_results(*student);
    }
}

void StudentOffice::generate_random_exam_results(Student& student) {
    Course* enrolled = student.getEnrolledCourses();
    size_t count = student.getEnrolledCount();
    
    if (count == 0) {
        std::cout << "  Nema upisanih kolegija.\n";
        return;
    }
    
    std::vector<std::pair<std::string, double>> exam_results;
    
    for (size_t i = 0; i < count; i++) {
        std::string course_code = enrolled[i].getSifra_Kolegija();
        
        double grade = 1.0 + static_cast<double>(rand()) / RAND_MAX * 4.0;
        grade = static_cast<int>(grade * 2 + 0.5) / 2.0;
        
        exam_results.push_back({course_code, grade});
    }
    
    process_exam_results(student, exam_results);
}

void StudentOffice::end_of_year_processing() {
    std::cout << "\n=== KRAJ GODINE - PROCESIRANJE ===\n";
    
    update_student_years();
    
    for (Student* student : studenti) {
        std::cout << "Student " << student->getName() 
                  << " pocinje novu godinu s 0 upisanih kolegija.\n";
    }
}

void Student::enrollCourse(const Course& course) {
    if (isEnrolledInCourse(course.getSifra_Kolegija())) {
        std::cout << "Student " << name << " je vec upisan na kolegij " 
                  << course.getIme_Kolegija() << std::endl;
        return;
    }
    
    if (!canAddCourse(course)) {
        std::cout << "Student " << name << " ne moze upisati kolegij " 
                  << course.getIme_Kolegija() << " zbog ECTS limita.\n";
        return;
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
}

void Student::completeCourse(const std::string& sifra_kolegija, double ocjena) {
    Course* course = findEnrolledCourse(sifra_kolegija);
    if (!course) {
        std::cout << "Student " << name << " nije upisan na kolegij s kodom " 
                  << sifra_kolegija << std::endl;
        return;
    }
    
    Course completed_course = *course;
    
    removeEnrolledCourse(sifra_kolegija);
    
    addCompletedCourse(completed_course);
    
    ects_polozeno += completed_course.getECTS_Bodovi();
    
    updateProsjek(ocjena);
    
    std::cout << "Student " << name << " polozio kolegij: " 
              << completed_course.getIme_Kolegija() << " sa ocjenom " 
              << std::fixed << std::setprecision(1) << ocjena << std::endl;
}

bool Student::isEnrolledInCourse(const std::string& sifra_kolegija) const {
    for (size_t i = 0; i < enrolled_count; i++) {
        if (enrolled_courses[i].getSifra_Kolegija() == sifra_kolegija) {
            return true;
        }
    }
    return false;
}

bool Student::hasCompletedCourse(const std::string& sifra_kolegija) const {
    for (size_t i = 0; i < completed_count; i++) {
        if (completed_courses[i].getSifra_Kolegija() == sifra_kolegija) {
            return true;
        }
    }
    return false;
}

void Student::printEnrolledCourses() const {
    std::cout << "\n=== UPISANI KOLEGIJI za " << name << " ===\n";
    if (enrolled_count == 0) {
        std::cout << "Nema upisanih kolegija.\n";
    } else {
        for (size_t i = 0; i < enrolled_count; i++) {
            std::cout << i + 1 << ". " << enrolled_courses[i].getIme_Kolegija()
                      << " (" << enrolled_courses[i].getSifra_Kolegija() << ")"
                      << " - " << enrolled_courses[i].getECTS_Bodovi() << " ECTS\n";
        }
        std::cout << "Ukupno ECTS u tijeku: " << calculateCurrentEcts() << "\n";
    }
}

void Student::printCompletedCourses() const {
    std::cout << "\n=== POLOZENI KOLEGIJI za " << name << " ===\n";
    if (completed_count == 0) {
        std::cout << "Nema polozenih kolegija.\n";
    } else {
        for (size_t i = 0; i < completed_count; i++) {
            std::cout << i + 1 << ". " << completed_courses[i].getIme_Kolegija()
                      << " (" << completed_courses[i].getSifra_Kolegija() << ")"
                      << " - " << completed_courses[i].getECTS_Bodovi() << " ECTS\n";
        }
        std::cout << "Ukupno ECTS bodova: " << ects_polozeno << "\n";
    }
}

int Student::calculateCurrentEcts() const {
    int total = 0;
    for (size_t i = 0; i < enrolled_count; i++) {
        total += enrolled_courses[i].getECTS_Bodovi();
    }
    return total;
}

Student Student::operator++(int) {
    Student temp = *this;
    ++(*this);
    return temp;
}