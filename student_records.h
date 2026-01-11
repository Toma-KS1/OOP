#ifndef STUDENT_RECORDS_H
#define STUDENT_RECORDS_H

#include <string>
#include <vector>
#include <iostream>

namespace student_records {
    class Student {
    private:
        std::string Ime;
        std::string Prezime;
        int bodovi;
        
    public:
        Student(const std::string& Ime = "", const std::string& Prezime = "", int bodovi = 0)
            : Ime(Ime), Prezime(Prezime), bodovi(bodovi) {}
        
        std::string getIme() const { return Ime; }
        std::string getPrezime() const { return Prezime; }
        int getBodovi() const { return bodovi; }

        void setIme(const std::string& Ime) { this->Ime = Ime; }
        void setPrezime(const std::string& Prezime) { this->Prezime = Prezime; }
        void setBodovi(int bodovi) { this->bodovi = bodovi; }

        void print() const;
    };
    
    int bodoviUOcjenu(int bodovi);
    double izracunajProsjecnuOcjenu(const std::vector<Student>& studenti);
    std::vector<Student> ucitajStudenteIzFile(const std::string& filename);
    void ispisiIzvjestaj(const std::vector<Student>& studenti);
    void demonstrirajSveOperacije();
}

#endif