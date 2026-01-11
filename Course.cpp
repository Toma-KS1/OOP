#include "Course.h"
#include <iostream>
#include <limits>

Course::Course(const std::string& ime_kolegija, 
               const std::string& sifra_kolegija, 
               int ECTS_bodovi)
    : ime_kolegija(ime_kolegija), sifra_kolegija(sifra_kolegija), ECTS_bodovi(ECTS_bodovi) {
}

std::string Course::getIme_Kolegija() const {
    return ime_kolegija;
}

std::string Course::getSifra_Kolegija() const {
    return sifra_kolegija;
}

int Course::getECTS_Bodovi() const {
    return ECTS_bodovi;
}

void Course::setIme_Kolegija(const std::string& ime_kolegija) {
    this->ime_kolegija = ime_kolegija;
}

void Course::setSifra_Kolegija(const std::string& sifra_kolegija) {
    this->sifra_kolegija = sifra_kolegija;
}

void Course::setECTS_Bodovi(int ECTS_bodovi) {
    if (ECTS_bodovi >= 0) {
        this->ECTS_bodovi = ECTS_bodovi;
    }
}

std::ostream& operator<<(std::ostream& os, const Course& course) {
    os << "Naziv: " << course.ime_kolegija << "\n"
       << "Sifra: " << course.sifra_kolegija << "\n"
       << "ECTS: " << course.ECTS_bodovi << "\n"
       << "-------------------";
    return os;
}

std::istream& operator>>(std::istream& is, Course& course) {
    std::cout << "Unesite naziv kolegija: ";
    std::getline(is, course.ime_kolegija);
    
    std::cout << "Unesite sifru kolegija: ";
    std::getline(is, course.sifra_kolegija);
    
    std::cout << "Unesite broj ECTS bodova: ";
    is >> course.ECTS_bodovi;

    while (course.ECTS_bodovi < 0) {
        std::cout << "ECTS bodovi ne mogu biti negativni, unesite ponovno: ";
        is >> course.ECTS_bodovi;
    }
    
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return is;
}