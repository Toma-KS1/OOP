#include "container.h"
#include <iostream>
#include <utility>

Container ContainerPoVrijednosti(Container container) {
    std::cout << "Primljen container: ";
    container.print();
    
    container.push_back(999);
    std::cout << "Nakon dodavanja elementa: ";
    container.print();

    return container;
}

Container stvoriContainer() {
    Container temp(2);
    
    temp.push_back(100);
    temp.push_back(200);
    temp.push_back(300);
    
    std::cout << "Stvoren container: ";
    temp.print();
    
    return temp;
}

void demonstrirajContainerFunkcije() {
    
    std::cout << "\n1. Kreiraj defaultni container i dodaj elemente:" << std::endl;
    Container c1;
    std::cout << "Pocetno stanje ";
    c1.print();
    
    for (int i = 1; i <= 5; i++) {
        c1.push_back(i * 10);
        std::cout << "Nakon push_back(" << i * 10 << ") - ";
        c1.print();
    }

    std::cout << "\n2. Kopiranje containera preko copy konstruktora:" << std::endl;
    Container c2(c1);
    std::cout << "Kopiran container ";
    c2.print();
    
    c1.push_back(60);
    std::cout << "Nakon modifikacije originala c1: ";
    c1.print();
    std::cout << "Kopija c2 (neizmijenjena): ";
    c2.print();
    
    std::cout << "\n3. Koristenje move konstruktora:" << std::endl;
    std::cout << "Prije move, c1: ";
    c1.print();
    
    Container c3 = std::move(c1);
    std::cout << "Nakon Container c3 = std::move(c1):" << std::endl;
    std::cout << "c1 (maknut od): ";
    c1.print();
    std::cout << "c3 (maknut na): ";
    c3.print();
    
    std::cout << "\n4. Prosljedivanje containera funkciji po vrijednosti" << std::endl;
    Container c4;
    c4.push_back(1);
    c4.push_back(2);
    c4.push_back(3);
    
    std::cout << "Prije funkcije, c4: ";
    c4.print();
    
    Container rezultat = ContainerPoVrijednosti(c4);
    
    std::cout << "Poslije funkcije" << std::endl;
    std::cout << "Originalni c4: ";
    c4.print();
    std::cout << "Rezultat funkcije: ";
    rezultat.print();
    
    std::cout << "\n5. Vracanje containera iz funkcije " << std::endl;
    Container c5 = stvoriContainer();
    std::cout << "Vracen container iz stvoriContainer(): ";
    c5.print();
    
    std::cout << "\n6. Realokaciju memorije dodavanjem elemenata preko kapaciteta" << std::endl;
    Container c6(2);
    std::cout << "Stvoren sa kapacitetom od 2: ";
    c6.print();
    
    std::cout << "Dodavanje elemenata:" << std::endl;
    for (int i = 1; i <= 10; i++) {
        c6.push_back(i * 100);
        std::cout << "  Dodan " << i * 100 << " - velicina: " << c6.size() 
                  << ", kapacitet: " << c6.capacity() << std::endl;
    }
    
    std::cout << "\n7. Ispis svih elemenata containera s indeksima i vrijednostima" << std::endl;
    std::cout << "Container c6:" << std::endl;
    for (std::size_t i = 0; i < c6.size(); i++) {
        std::cout << "  [" << i << "] = " << c6.at(i) << std::endl;
    }
    
}

int main() {
    demonstrirajContainerFunkcije();
    
    return 0;
}