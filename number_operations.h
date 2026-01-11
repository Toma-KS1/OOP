#ifndef NUMBER_OPERATIONS_H
#define NUMBER_OPERATIONS_H

#include <vector>
#include <optional>
#include <iostream>

namespace OperacijeNaBrojevima {
    std::optional<int> nadiPrviNeparni(const std::vector<int>& brojevi);
    size_t izbrojiNeparneBrojeve(const std::vector<int>& brojevi);
    double izracunajProsjekNeparnih(const std::vector<int>& brojevi);
    void zamijeniPotencijeOdDva(std::vector<int>& brojevi);
    void ispisiSortiranoParnoPaNeparno(const std::vector<int>& brojevi);

    bool jePotencijaOdDva(int broj);
    void demonstrirajSveOperacije();
}

#endif