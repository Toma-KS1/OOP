#include "student_records.h"
#include <algorithm>
#include <numeric>
#include <iterator>
#include <iomanip>
#include <vector>
#include <sstream>

int main() {
    const std::string filename = "studenti.txt";
    
    std::cout << "Citanje studenata iz '" << filename << "'..." << std::endl;
    std::vector<student_records::Student> studenti = student_records::ucitajStudenteIzFile(filename);
    
    if (studenti.empty()) {
        std::cerr << "Nema studenata ili file nije pronaden." << std::endl;
        return 1;
    }
    
    std::cout << "Ucitano " << studenti.size() << " studenata." << std::endl;
    
    student_records::ispisiIzvjestaj(studenti);
    
    auto bodoviUOcjenulambda = [](int bodovi) -> int {
        if (bodovi >= 85) return 5;
        else if (bodovi >= 70) return 4;
        else if (bodovi >= 55) return 3;
        else if (bodovi >= 40) return 2;
        else return 1;
    };
    
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "IMPLEMENTIRANJE MAP-FILTER-REDUCE KORISTENJEM STL" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    std::cout << "\n1. FILTER: Brisanje studenata sa manje od 40 bodova..." << std::endl;
    
    auto it = std::remove_if(studenti.begin(), studenti.end(),
                            [](const student_records::Student& s) {
                                return s.getBodovi() < 40;
                            });
    
    size_t removedCount = std::distance(it, studenti.end());
    studenti.erase(it, studenti.end());
    
    std::cout << "   Izbrisano " << removedCount << " studenata sa nedovoljno bodova." << std::endl;
    std::cout << "   Preostalo studenata: " << studenti.size() << std::endl;
    
    std::cout << "\n2. MAP: Pretvaranje bodova u ocjene..." << std::endl;
    
    std::transform(studenti.begin(), studenti.end(),
                   studenti.begin(),
                   [&bodoviUOcjenulambda](const student_records::Student& s) {
                       int grade = bodoviUOcjenulambda(s.getBodovi());
                       return student_records::Student(s.getIme(), 
                                                      s.getPrezime(), 
                                                      grade);
                   });
    
    std::cout << "   Nakon pretvaranja (bodovi u ocjene):" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    for (const auto& student : studenti) {
        std::cout << "   " << student.getPrezime() << ", " << student.getIme()
                  << " -> Grade: " << student.getBodovi() << std::endl;
    }
    
    std::cout << "\n3. REDUCE: Kalkulacija prosjeka ocjena..." << std::endl;
    
    double gradeAverage = std::accumulate(studenti.begin(), studenti.end(), 0.0,
                                         [](double sum, const student_records::Student& s) {
                                             return sum + static_cast<double>(s.getBodovi());
                                         }) / static_cast<double>(studenti.size());
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "   Prosjecna ocjena: " << gradeAverage << std::endl;
    
    std::cout << "\n4. Sortiranje studenata po prezimenu..." << std::endl;
    
    std::sort(studenti.begin(), studenti.end(),
              [](const student_records::Student& a, const student_records::Student& b) {
                  return a.getPrezime() < b.getPrezime();
              });
    
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "Konacni izvjestaj (Sortirano po prezimenu)" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    if (studenti.empty()) {
        std::cout << "Nema studenata za prikaz." << std::endl;
    } else {
        std::cout << "\n" << std::left << std::setw(25) << "Ime Studenta"
                  << std::right << std::setw(15) << "Ocjena" << std::endl;
        std::cout << std::string(40, '-') << std::endl;
        
        for (const auto& student : studenti) {
            std::cout << std::left << std::setw(25)
                      << student.getPrezime() + ", " + student.getIme()
                      << std::right << std::setw(15) << student.getBodovi() << std::endl;
        }
        
        std::cout << "\n" << std::string(40, '-') << std::endl;
        std::cout << "STATISTIKA:" << std::endl;
        std::cout << "Ukupno studenata: " << studenti.size() << std::endl;
        std::cout << "Prosjecna ocjena: " << std::fixed << std::setprecision(2) 
                  << gradeAverage << std::endl;
        
        std::vector<int> gradeCounts(6, 0);
        for (const auto& student : studenti) {
            if (student.getBodovi() >= 1 && student.getBodovi() <= 5) {
                gradeCounts[student.getBodovi()]++;
            }
        }
        
        std::cout << "\nDistribucija ocjena:" << std::endl;
        for (int grade = 5; grade >= 1; --grade) {
            std::cout << "Ocjena " << grade << ": " << gradeCounts[grade] 
                      << " studenta" << std::endl;
        }
    }
    
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "BONUS: Output koristenjem std::ostream_iterator" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    std::cout << "\nStudent lista:" << std::endl;
    std::transform(studenti.begin(), studenti.end(),
                   std::ostream_iterator<std::string>(std::cout, "\n"),
                   [](const student_records::Student& s) {
                       std::ostringstream oss;
                       oss << "  " << s.getPrezime() << ", " << s.getIme()
                           << " - Ocjena: " << s.getBodovi();
                       return oss.str();
                   });
    
    return 0;
}