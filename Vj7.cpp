#include "StudentOffice.h"
#include "Course.h"
#include <iostream>

int main() {
    std::cout << "TEST\n\n";
    
    StudentOffice office;
    
    Student student1(101, "Ana Anic", "Racunarstvo", 1);
    Student student2(102, "Marko Maric", "Racunarstvo", 1);
    Student student3(103, "Ivana Ivic", "Elektrotehnika", 2);
    
    office.dodajStudenta(student1);
    office.dodajStudenta(student2);
    office.dodajStudenta(student3);
    
    office.prikaziDostupneKolegije();
    
    std::cout << "\nUPIS STUDENATA NA KOLEGIJE\n";
    
    std::cout << "\nUpis studenta " << student1.getName() << ":\n";
    office.enroll_student(student1, "OOP-101");
    office.enroll_student(student1, "BP-201");
    office.enroll_student(student1, "PMA-301");
    office.enroll_student(student1, "WEB-102");
    
    std::cout << "\nPokusaj prekoracenja ECTS limita:\n";
    for (int i = 0; i < 15; i++) {
        if (!office.enroll_student(student1, "MAT-202")) {
            break;
        }
    }
    
    std::cout << "\nUpis studenta " << student2.getName() << ":\n";
    office.enroll_student(student2, "OOP-101");
    office.enroll_student(student2, "BP-201");
    
    std::cout << "\nUpis studenta " << student3.getName() << ":\n";
    office.enroll_student(student3, "SQL-101");
    office.enroll_student(student3, "OS-202");
    
    office.prikaziSveStudente();
    
    std::cout << "\n=== TEST 2: PREMJEŠTANJE STUDENTA NA DRUGI KOLEGIJ ===\n";
    
    std::cout << "\nPrije premještanja:\n";
    student1.printEnrolledCourses();
    
    office.moveStudent(student1, "WEB-102", "MAT-202");
    
    std::cout << "\nNakon premještanja:\n";
    student1.printEnrolledCourses();
    
    std::cout << "\nTest nevaljanog premještanja:\n";
    office.moveStudent(student1, "NEPOSTOJECI", "OOP-101");
    office.moveStudent(student1, "OOP-101", "BP-201");
    
    std::cout << "\nOBRADA ISPITNIH REZULTATA\n";
    
    std::vector<std::pair<std::string, double>> exam_results = {
        {"OOP-101", 4.5},
        {"BP-201", 3.0},
        {"PMA-301", 2.5},
        {"MAT-202", 1.5}
    };
    
    office.process_exam_results(student1, exam_results);
    
    std::cout << "\nStatus studenta " << student1.getName() << " nakon ispita:\n";
    std::cout << student1 << "\n";
    student1.printEnrolledCourses();
    student1.printCompletedCourses();
    
    std::cout << "\nAKTUALIZACIJA GODINE STUDIJA\n";
    
    std::cout << "\nPrvi pokusaj napredovanja (student ima " 
              << student1.getEcts_Polozeno() << " ECTS):\n";
    office.update_student_years();
    
    std::cout << "\nDodavanje ECTS bodova studentu " << student1.getName() << ":\n";
    
    office.enroll_student(student1, "SQL-101");
    office.enroll_student(student1, "SPA-101");
    office.enroll_student(student1, "OS-202");
    office.enroll_student(student1, "LIN-201");
    office.enroll_student(student1, "WEB-102");
    
    std::vector<std::pair<std::string, double>> more_exams = {
        {"SQL-101", 4.0},
        {"SPA-101", 3.5},
        {"OS-202", 4.0},
        {"LIN-201", 3.0},
        {"WEB-102", 4.5}
    };
    
    office.process_exam_results(student1, more_exams);
    

    std::cout << "\nDodavanje zadnjeg kolegija za dostici 45+ ECTS:\n";
    office.enroll_student(student1, "MAT-202");
    
    std::vector<std::pair<std::string, double>> final_exam = {
        {"MAT-202", 4.0}
    };
    
    office.process_exam_results(student1, final_exam);
    
    std::cout << "\nDrugi pokusaj napredovanja (student ima " 
              << student1.getEcts_Polozeno() << " ECTS):\n";
    office.update_student_years();
    
    std::cout << "\nTEST 5: SIMULACIJA CIJELOG ISPITNOG ROKA\n";
    
    student2.setEcts_Polozeno(0);
    
    office.enroll_student(student2, "WEB-102");
    office.enroll_student(student2, "SQL-101");
    office.enroll_student(student2, "SPA-101");
    office.enroll_student(student2, "OS-202");
    
    std::cout << "\nPrije simulacije:\n";
    student2.printEnrolledCourses();
    
    office.simulate_exam_period();
    
    std::cout << "\nNakon simulacije:\n";
    std::cout << student2 << "\n";
    student2.printCompletedCourses();
    
    std::cout << "\n=== TEST 6: KRAJ GODINE ===\n";
    office.end_of_year_processing();
    
    return 0;
}