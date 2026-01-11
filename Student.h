#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include "Course.h"
#include "UniversityConstants.h"

class StudentOffice;

class Student {
private:
    int id;
    std::string name;
    std::string study_program;
    int year;
    int ects_polozeno;
    double prosjek;

    Course* enrolled_courses;
    size_t enrolled_count;
    Course* completed_courses;
    size_t completed_count;
    
    static int total_students;

public:
    Student(int id = 0, const std::string& name = "", 
            const std::string& study_program = "", int year = 1,
            int ects_polozeno = 0, double prosjek = 0.0);
    
     Student(const Student& drugi);

     Student(Student&& drugi) noexcept;

    ~Student();

     Student& operator=(const Student& drugi);

     Student& operator=(Student&& drugi) noexcept;

    static int get_total_students();

    int getId() const;
    std::string getName() const;
    std::string getStudyProgram() const;
    int getYear() const;
    int getEcts_Polozeno() const;
    double getProsjek() const;
    size_t getEnrolledCount() const;
    size_t getCompletedCount() const;
    Course* getEnrolledCourses() const;
    Course* getCompletedCourses() const;
    
    void setId(int id);
    void setName(const std::string& name);
    void setStudyProgram(const std::string& study_program);
    void setYear(int year);
    void setEcts_Polozeno(int ects);
    void setProsjek(double prosjek);

    void enrollCourse(const Course& course);
    void completeCourse(const std::string& course_code, double grade);
    bool isEnrolledInCourse(const std::string& course_code) const;
    bool hasCompletedCourse(const std::string& course_code) const;
    void printEnrolledCourses() const;
    void printCompletedCourses() const;
    int calculateCurrentEcts() const;

    Student& operator+=(const Course& course);
    Student& operator++();
    Student operator++(int);

    int getCurrentEnrolledEcts() const;
    Course* findEnrolledCourse(const std::string& sifra_kolegija);
    const Course* findEnrolledCourse(const std::string& sifra_kolegija) const;
    void removeEnrolledCourse(const std::string& sifra_kolegija);
    void addCompletedCourse(const Course& course);
    void updateProsjek(double nova_ocjena);
    void moveCourseToCompleted(const std::string& sifra_kolegija, double ocjena);
    bool canAddCourse(const Course& course) const;

    friend class StudentOffice;
    
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
    friend std::istream& operator>>(std::istream& is, Student& student);

private:
    void realocirajUpisaneKolegije(size_t novi_kapacitet);
    void realocirajZavrseneKolegije(size_t novi_kapacitet);
    void kopirajKolegije(const Student& drugi);
    void izbrisiKolegije();
};

#endif