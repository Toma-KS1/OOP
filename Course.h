#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>

class Course {
private:
    std::string ime_kolegija;
    std::string sifra_kolegija;
    int ECTS_bodovi;
    
public:
    Course(const std::string& ime_kolegija = "", 
           const std::string& sifra_kolegija = "", 
           int ECTS_bodovi = 0);
    
    std::string getIme_Kolegija() const;
    std::string getSifra_Kolegija() const;
    int getECTS_Bodovi() const;
    

    void setIme_Kolegija(const std::string& ime_kolegija);
    void setSifra_Kolegija(const std::string& sifra_kolegija);
    void setECTS_Bodovi(int ECTS_bodovi);

    friend std::ostream& operator<<(std::ostream& os, const Course& course);
    friend std::istream& operator>>(std::istream& is, Course& course);
};

#endif