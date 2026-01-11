#include <iostream>
#include <functional>

void pokazijednakost() {
    auto jeParno = [](int x) -> bool { return x % 2 == 0; };
    auto jeNeparno = [](int x) -> bool { return x % 2 != 0; };
    
    std::cout << "Testiraj jednakosti:" << std::endl;
    std::cout << "5 je parno: " << std::boolalpha << jeParno(5) << std::endl;
    std::cout << "5 je neparno: " << std::boolalpha << jeNeparno(5) << std::endl;
    std::cout << "8 je parno: " << std::boolalpha << jeParno(8) << std::endl;
}

void pokazitransofrmaciju() {
    auto udvostruciBroj = [](int x) -> int { return x * 2; };
    auto prepoloviBroj = [](int x) -> int { return x / 2; };
    
    std::cout << "Testiraj transofrmacije:" << std::endl;
    std::cout << "Duplo od 5: " << udvostruciBroj(5) << std::endl;
    std::cout << "Pola od 10: " << prepoloviBroj(10) << std::endl;
}

void transformirajParnoNeparno(int niz[], int velicina) {
    auto jeParno = [](int x) -> bool { return x % 2 == 0; };
    auto udvostruciBroj = [](int x) -> int { return x * 2; };
    auto prepoloviBroj = [](int x) -> int { return x / 2; };
    
    std::cout << "\n1. Transformacija niza (parno -> prepolovi, neparno -> udvostruci):" << std::endl;
    std::cout << "Original: ";
    for (int i = 0; i < velicina; i++) {
        std::cout << niz[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Transformirano: ";
    for (int i = 0; i < velicina; i++) {
        if (jeParno(niz[i])) {
            std::cout << prepoloviBroj(niz[i]) << " ";
        } else {
            std::cout << udvostruciBroj(niz[i]) << " ";
        }
    }
    std::cout << std::endl;
}

void racunajSumuIProdukt(int arr[], int size) {
    int suma = 0;
    int produkt = 1;
    
    auto dodajSumi = [&suma](int x) -> void { suma += x; };
    
    auto dodajProduktu = [&produkt](int x) -> void { produkt *= x; };

    std::cout << "\n2. Izracunaj sumu i produkt:" << std::endl;
    std::cout << "Niz: ";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
        dodajSumi(arr[i]);
        dodajProduktu(arr[i]);
    }
    std::cout << std::endl;
    std::cout << "Sum: " << suma << std::endl;
    std::cout << "Product: " << produkt << std::endl;
}

int sumaVecaOdPraga(int niz[], int velicina, int prag) {
    int rezultat = 0;
    
    auto dodajAkoVeceOdPraga = [prag, &rezultat](int x) -> void {
        if (x > prag) {
            rezultat += x;
        }
    };

    for (int i = 0; i < velicina; i++) {
        dodajAkoVeceOdPraga(niz[i]);
    }
    
    return rezultat;
}

int main() {
    int niz[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(niz) / sizeof(niz[0]);

    std::cout << "Testiranje lambda izraza" << std::endl;

    pokazijednakost();
    pokazitransofrmaciju();
    
    transformirajParnoNeparno(niz, size);
    
    racunajSumuIProdukt(niz, size);
    
    std::cout << "\n3. Izracunaj sumu brojeva vecih od praga:" << std::endl;
    int prag = 5;
    int pragSuma = sumaVecaOdPraga(niz, size, prag);
    std::cout << "Niz: ";
    for (int i = 0; i < size; i++) {
        std::cout << niz[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Suma brojeva > " << prag << ": " << pragSuma << std::endl;
    
    return 0;
}