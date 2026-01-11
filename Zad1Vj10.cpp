#include "number_operations.h"
#include <vector>

int main() {
    OperacijeNaBrojevima::demonstrirajSveOperacije();
    
    std::cout << "\n\nUnos Brojeva" << std::endl;
    
    std::vector<int> korisnikBrojevi;
    int velicina;
    
    std::cout << "Koliko prirodnih brojeva zelite unijeti? ";
    std::cin >> velicina;

    if (velicina <= 0) {
        std::cout << "Neispravna velicina. Koristit ce default brojeve." << std::endl;
        korisnikBrojevi = {5, 8, 3, 16, 7, 2, 9, 4, 11, 1};
    } else {
        std::cout << "Unesi " << velicina << " prirodnih brojeva:" << std::endl;
        for (int i = 0; i < velicina; ++i) {
            int broj;
            std::cin >> broj;
            korisnikBrojevi.push_back(broj);
        }
    }
    
    std::cout << "\nRezultati za brojeve:" << std::endl;
    
    // 1. First odd
    auto prviNeparni = OperacijeNaBrojevima::nadiPrviNeparni(korisnikBrojevi);
    std::cout << "1. Prvi neparni broj: ";
    if (prviNeparni.has_value()) {
        std::cout << prviNeparni.value() << std::endl;
    } else {
        std::cout << "Nema neparnih brojeva." << std::endl;
    }
    
    std::cout << "2. Ukupno neparnih brojeva: " 
              << OperacijeNaBrojevima::izbrojiNeparneBrojeve(korisnikBrojevi) << std::endl;
    
    std::cout << "3. Prosjek neparnih brojeva: " 
              << OperacijeNaBrojevima::izracunajProsjekNeparnih(korisnikBrojevi) << std::endl;
    
    std::vector<int> modificiraniBrojevi = korisnikBrojevi;
    OperacijeNaBrojevima::zamijeniPotencijeOdDva(modificiraniBrojevi);
    std::cout << "4. Nakon modificiranja: ";
    for (size_t i = 0; i < modificiraniBrojevi.size(); ++i) {
        std::cout << modificiraniBrojevi[i];
        if (i < modificiraniBrojevi.size() - 1) std::cout << " ";
    }
    std::cout << std::endl;
    
    std::cout << "5. Sortirano parno pa neparno:" << std::endl;
    OperacijeNaBrojevima::ispisiSortiranoParnoPaNeparno(korisnikBrojevi);
    
    return 0;
}