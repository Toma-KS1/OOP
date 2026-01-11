#include <iostream>
#include <cstring>
#include <iomanip>

struct Student {
    char ime[50];
    char JMBAG[11];
    int godina_studija;
    int ETCS_polozeno;
    double prosjek_ocjena;
};

void filtriraj_studente(Student studenti[], std::size_t velicina, 
                     void (*akcija)(Student&), 
                     bool (*filter)(Student&));

void ispisi_studenta(Student& s);
void povecaj_godinu(Student& s);

bool prva_godina_polozen_barem_jedan(Student& s);
bool visok_prosjek(Student& s);
bool polozilo_45_ETCS(Student& s);

int main() {
    const std::size_t broj_studenata = 5;
    Student studenti[broj_studenata] = {
        {"Ana Anic", "1234567890", 1, 0, 4.2},
        {"Ivo Ivic", "2345678901", 1, 30, 3.8},
        {"Marko Maric", "3456789012", 2, 60, 3.2},
        {"Petra Peric", "4567890123", 3, 45, 4.0},
        {"Luka Lukic", "5678901234", 1, 15, 3.6}
    };
    
    std::cout << "Pocetna lista studenata:" << std::endl;
    for (std::size_t i = 0; i < broj_studenata; i++) {
        ispisi_studenta(studenti[i]);
    }
    
    std::cout << "\nStudenti koji su polozili barem jedan ispit u prvoj godini" << std::endl;
    filtriraj_studente(studenti, broj_studenata, ispisi_studenta, prva_godina_polozen_barem_jedan);
    
    std::cout << "\nStudenti s prosjekom veceg od 3.5:" << std::endl;
    filtriraj_studente(studenti, broj_studenata, ispisi_studenta, visok_prosjek);
    
    std::cout << "\nPovecaj broj godina studija studenata koji su polozili barem 45 ETCS:" << std::endl;
    std::cout << "Prije:" << std::endl;
    filtriraj_studente(studenti, broj_studenata, ispisi_studenta, polozilo_45_ETCS);
    
    std::cout << "\nPoslije:" << std::endl;
    filtriraj_studente(studenti, broj_studenata, povecaj_godinu, polozilo_45_ETCS);
    
    std::cout << "\nNakon povecanja godina studija:" << std::endl;
    std::cout << "Svi studenti:" << std::endl;
    for (std::size_t i = 0; i < broj_studenata; i++) {
        ispisi_studenta(studenti[i]);
    }

    return 0;
}

void filtriraj_studente(Student studenti[], std::size_t velicina, 
                     void (*akcija)(Student&), 
                     bool (*filter)(Student&)) {
    for (std::size_t i = 0; i < velicina; i++) {
        if (filter(studenti[i])) {
            akcija(studenti[i]);
        }
    }
}

void ispisi_studenta(Student& s) {
    std::cout << std::left << std::setw(15) << s.ime 
              << std::setw(12) << s.JMBAG 
              << "Godina: " << s.godina_studija 
              << ", ETCS: " << std::setw(3) << s.ETCS_polozeno 
              << ", Prosjek: " << std::fixed << std::setprecision(2) << s.prosjek_ocjena 
              << std::endl;
}

void povecaj_godinu(Student& s) {
    s.godina_studija++;
    std::cout << "Povecana godina studija za " << s.ime << " na " << s.godina_studija << std::endl;
}

bool prva_godina_polozen_barem_jedan(Student& s) {
    return s.godina_studija == 1 && s.ETCS_polozeno > 0;
}

bool visok_prosjek(Student& s) {
    return s.prosjek_ocjena > 3.5;
}

bool polozilo_45_ETCS(Student& s) {
    return s.ETCS_polozeno >= 45;
}