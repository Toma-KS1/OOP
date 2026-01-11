#include "number_operations.h"
#include <algorithm>
#include <numeric>
#include <optional>
#include <iostream>
#include <cmath>
#include <vector>
#include <iterator>

namespace OperacijeNaBrojevima {

    bool jePotencijaOdDva(int broj) {
        if (broj <= 0) return false;
        return (broj & (broj - 1)) == 0;
    }

    std::optional<int> nadiPrviNeparni(const std::vector<int>& brojevi) {
        auto it = std::find_if(brojevi.begin(), brojevi.end(),
                               [](int broj) { return broj % 2 != 0; });
        
        if (it != brojevi.end()) {
            return *it;
        }
        return std::nullopt;
    }

    size_t izbrojiNeparneBrojeve(const std::vector<int>& brojevi) {
        return static_cast<size_t>(
            std::count_if(brojevi.begin(), brojevi.end(),
                         [](int broj) { return broj % 2 != 0; })
        );
    }

    double izracunajProsjekNeparnih(const std::vector<int>& brojevi) {
        size_t brojNeparnih = izbrojiNeparneBrojeve(brojevi);
        
        if (brojNeparnih == 0) {
            return 0.0;
        }
        
        int SumaNeparnih = std::accumulate(brojevi.begin(), brojevi.end(), 0,
                                    [](int total, int broj) {
                                        return total + (broj % 2 != 0 ? broj : 0);
                                    });

        return static_cast<double>(SumaNeparnih) / static_cast<double>(brojNeparnih);
    }

    void zamijeniPotencijeOdDva(std::vector<int>& brojevi) {
        std::replace_if(brojevi.begin(), brojevi.end(),
                       [](int broj) { return jePotencijaOdDva(broj); },
                       2);
    }

    void ispisiSortiranoParnoPaNeparno(const std::vector<int>& brojevi) {
        if (brojevi.empty()) {
            std::cout << "Vektor je prazan." << std::endl;
            return;
        }
        
        std::vector<int> parniBrojevi;
        std::vector<int> neparniBrojevi;

        std::copy_if(brojevi.begin(), brojevi.end(),
                    std::back_inserter(parniBrojevi),
                    [](int broj) { return broj % 2 == 0; });
        
        std::copy_if(brojevi.begin(), brojevi.end(),
                    std::back_inserter(neparniBrojevi),
                    [](int broj) { return broj % 2 != 0; });
        
        std::sort(parniBrojevi.begin(), parniBrojevi.end());
        std::sort(neparniBrojevi.begin(), neparniBrojevi.end());
        
        std::cout << "Parni brojevi sortirano: ";
        for (size_t i = 0; i < parniBrojevi.size(); ++i) {
            std::cout << parniBrojevi[i];
            if (i < parniBrojevi.size() - 1) std::cout << " ";
        }
        std::cout << std::endl;
        
        std::cout << "Neparni brojevi sortirano: ";
        for (size_t i = 0; i < neparniBrojevi.size(); ++i) {
            std::cout << neparniBrojevi[i];
            if (i < neparniBrojevi.size() - 1) std::cout << " ";
        }
        std::cout << std::endl;
    }

    void demonstrirajSveOperacije() {
        
        std::vector<int> brojevi = {10, 3, 8, 5, 2, 7, 16, 1, 4, 9, 6};
        
        std::cout << "Originalni brojevi: ";
        for (int num : brojevi) std::cout << num << " ";
        std::cout << std::endl;
        
        std::cout << "\n1. Nadi prvi neparni:" << std::endl;
        std::optional<int> prviNeparni = OperacijeNaBrojevima::nadiPrviNeparni(brojevi);
        if (prviNeparni.has_value()) {
            std::cout << "   Prvi neparni broj: " << prviNeparni.value() << std::endl;
        } else {
            std::cout << "   Nema neparnih brojeva." << std::endl;
        }
        
        std::cout << "\n2. Izbroji neparne brojeve:" << std::endl;
        size_t brojNeparnih = OperacijeNaBrojevima::izbrojiNeparneBrojeve(brojevi);
        std::cout << "   Ukupno neparnih brojeva: " << brojNeparnih << std::endl;
        
        std::cout << "\n3. Izracunaj prosjek neparnih brojeva:" << std::endl;
        double prosjekNeparnih = OperacijeNaBrojevima::izracunajProsjekNeparnih(brojevi);
        std::cout << "   Prosjek neparnih brojeva: " << prosjekNeparnih << std::endl;
        
        std::cout << "   Prosjek kao int (koristenje static_cast): " 
                  << static_cast<int>(prosjekNeparnih) << std::endl;
        
        std::cout << "\n4. Zamijeni potencije broja 2 s brojem 2:" << std::endl;
        std::vector<int> brojeviKopija = brojevi;
        OperacijeNaBrojevima::zamijeniPotencijeOdDva(brojeviKopija);
        std::cout << "   Modificirani brojevi: ";
        for (int broj : brojeviKopija) std::cout << broj << " ";
        std::cout << std::endl;
        
        std::cout << "   Potencije broja 2 u originalu: ";
        for (int broj : brojevi) {
            if (jePotencijaOdDva(broj)) std::cout << broj << " ";
        }
        std::cout << std::endl;
        
        std::cout << "\n5. Ispisi parne pa neparne brojeve sortirano:" << std::endl;
        OperacijeNaBrojevima::ispisiSortiranoParnoPaNeparno(brojevi);
    }
}