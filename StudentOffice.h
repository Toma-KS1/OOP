#ifndef STUDENTOFFICE_H
#define STUDENTOFFICE_H

#include <vector>
#include "Student.h"
#include "Course.h"

class StudentOffice {
private:
    std::vector<Student*> studenti;
    std::vector<Course> dostupni_kolegiji;
    
public:
    StudentOffice();
    
    void dodajStudenta(Student& student);
    void izbrisiStudenta(int student_id);
    Student* nadiStudenta(int student_id);
    void prikaziSveStudente() const;
    
    void dodajDostupneKolegije(const Course& course);
    void prikaziDostupneKolegije() const;
    Course* nadiKolegij(const std::string& sifra_kolegija);
    
    void moveStudent(Student& student, const std::string& iz_sifre_kolegija, 
                     const std::string& na_sifru_kolegija);
    bool enroll_student(Student& student, const std::string& course_code);
    void process_exam_results(Student& student, 
                              const std::vector<std::pair<std::string, double>>& exam_results);
    void update_student_years();
    
    void simulate_exam_period();
    void generate_random_exam_results(Student& student);
    void end_of_year_processing();
    
private:
    bool canStudentEnrollMoreEcts(const Student& student, int dodatni_ects) const;
    void process_single_exam_result(Student& student, 
                                    const std::string& sifra_kolegija, 
                                    double ocjena);
};

#endif