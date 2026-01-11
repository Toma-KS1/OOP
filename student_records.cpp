#include "student_records.h"
#include <fstream>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <sstream>

namespace student_records {

    int bodoviUOcjenu(int bodovi) {
        if (bodovi < 0 || bodovi > 100) return 0;

        if (bodovi >= 85) return 5;
        else if (bodovi >= 70) return 4;
        else if (bodovi >= 55) return 3;
        else if (bodovi >= 40) return 2;
        else return 1;
    }

    double izracunajProsjecnuOcjenu(const std::vector<Student>& studenti) {
        if (studenti.empty()) return 0.0;
        
        int total = std::accumulate(studenti.begin(), studenti.end(), 0,
                                   [](int suma, const Student& s) {
                                       return suma + s.getBodovi();
                                   });
        
        return static_cast<double>(total) / static_cast<double>(studenti.size());
    }

    std::vector<Student> ucitajStudenteIzFile(const std::string& filename) {
        std::vector<Student> studenti;
        std::ifstream file(filename);
        
        if (!file.is_open()) {
            std::cerr << "Error: Ne moze se otvoriti file '" << filename << "'" << std::endl;
            std::cerr << "Kreiranje sample file..." << std::endl;
            
            std::ofstream createFile(filename);
            if (createFile) {
                createFile << "Ana,Anic,78\n";
                createFile << "Ivan,Ivic,45\n";
                createFile << "Marko,Maric,92\n";
                createFile << "Petra,Peric,32\n";
                createFile << "Luka,Lukic,67\n";
                createFile << "Maja,Majic,54\n";
                createFile << "Josip,Jusic,81\n";
                createFile << "Sara,Saric,39\n";
                createFile << "Tomislav,Tomislavic,73\n";
                createFile << "Ema,Emic,88\n";
                createFile.close();
                std::cout << "Sample file kreiran. Pokreni ponovno." << std::endl;
            }
            return studenti;
        }
        
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string Ime, Prezime;
            int bodovi;
            char comma;
            
            if (std::getline(iss, Ime, ',') &&
                std::getline(iss, Prezime, ',') &&
                (iss >> bodovi)) {
                studenti.push_back(Student(Ime, Prezime, bodovi));
            }
        }
        
        file.close();
        return studenti;
    }

    void Student::print() const {
        std::cout << std::left << std::setw(15) << Prezime + ", " + Ime
                  << std::right << std::setw(5) << bodovi
                  << std::setw(10) << "Ocjena: " << bodoviUOcjenu(bodovi) << std::endl;
    }

    void ispisiIzvjestaj(const std::vector<Student>& studenti) {
        if (studenti.empty()) {
            std::cout << "Nema studenata za prikazati." << std::endl;
            return;
        }
        
        std::cout << "\n" << std::string(50, '=') << std::endl;
        std::cout << "Izvjestaj (" << studenti.size() << " studenata)" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        
        std::cout << std::left << std::setw(25) << "Ime studenta"
                  << std::right << std::setw(10) << "Bodovi"
                  << std::setw(15) << "Ocjena" << std::endl;
        std::cout << std::string(50, '-') << std::endl;
        
        for (const auto& student : studenti) {
            std::cout << std::left << std::setw(25) 
                      << student.getPrezime() + ", " + student.getIme()
                      << std::right << std::setw(10) << student.getBodovi()
                      << std::setw(15) << bodoviUOcjenu(student.getBodovi()) << std::endl;
        }
    }

    void demonstrirajSveOperacije() {
        std::cout << "Izvjestaj" << std::endl;
        
        std::cout << "\nPrimjer bodova u ocjenu:" << std::endl;
        std::vector<int> testBodovi = {25, 42, 58, 75, 89, 100, 35};
        for (int bodovi : testBodovi) {
            std::cout << bodovi << " points -> Grade " << bodoviUOcjenu(bodovi) << std::endl;
        }
    }
}