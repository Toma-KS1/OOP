#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <map>

enum Zog {
    KUPE,
    SPADE,
    BASTONI,
    DENARI
};

std::string zogUString(Zog z) {
    switch(z) {
        case KUPE: return "Kupe";
        case SPADE: return "Spade";
        case BASTONI: return "Bastoni";
        case DENARI: return "Denari";
        default: return "Unknown";
    }
}

class Karta {
private:
    int broj;
    Zog zog;
    
public:
    Karta(int broj, Zog z) : broj(broj), zog(z) {}

    int dobijBroj() const { return broj; }
    Zog dobijZog() const { return zog; }
    
    std::string uString() const {
        std::string brojStr;
        switch(broj) {
            case 1: brojStr = "As"; break;
            case 2: brojStr = "Duja"; break;
            case 3: brojStr = "Trica"; break;
            default: brojStr = std::to_string(broj);
        }
        return brojStr + " od " + zogUString(zog);
    }
    
    bool operator<(const Karta& drugi) const {
        if (zog != drugi.zog) return zog < drugi.zog;
        return broj < drugi.broj;
    }

    bool operator==(const Karta& other) const {
        return broj == other.broj && zog == other.zog;
    }
};

class Igrac {
private:
    std::string ime;
    std::vector<Karta> ruka;
    int bodovi;
    
public:
    Igrac(const std::string& n) : ime(n), bodovi(0) {}
    
    const std::string& dobijIme() const { return ime; }
    const std::vector<Karta>& dobijRuku() const { return ruka; }
    int dobijBodove() const { return bodovi; }
    
    void dodajKartu(const Karta& karta) {
        ruka.push_back(karta);
    }

    void sortirajRuku() {
        std::sort(ruka.begin(), ruka.end());
    }

    void izbrisiRuku() {
        ruka.clear();
    }
    
    void dodajBodove(int p) {
        bodovi += p;
    }
    
    bool imaNapolitana() const {
        std::map<Zog, std::vector<int>> kartePoZogu;

        for (const Karta& karta : ruka) {
            kartePoZogu[karta.dobijZog()].push_back(karta.dobijBroj());
        }
        
        for (const auto& par : kartePoZogu) {
            const std::vector<int>& brojevi = par.second;
            bool imaAs = false, imaDuju = false, imaTricu = false;

            for (int broj : brojevi) {
                if (broj == 1) imaAs = true;
                if (broj == 2) imaDuju = true;
                if (broj == 3) imaTricu = true;
            }

            if (imaAs && imaDuju && imaTricu) {
                return true;
            }
        }
        
        return false;
    }
    
    int dobijBrojVrsteBodovi() const {
        std::map<int, int> brojiPoBroju;
        
        for (const Karta& karta : ruka) {
            brojiPoBroju[karta.dobijBroj()]++;
        }
        
        int bodovi = 0;
        
        for (int num : {1, 2, 3}) {
            if (brojiPoBroju[num] >= 3) {
                bodovi = brojiPoBroju[num];
            }
        }
        
        return bodovi;
    }
    
    int racunajBodoveAkuzate() {
        bodovi = 0;
        
        if (imaNapolitana()) {
            bodovi += 3;
            std::cout << "  " << ime << " ima Napolitana! (+3 bodova)" << std::endl;
        }

        int vrstaBodovi = dobijBrojVrsteBodovi();
        if (vrstaBodovi > 0) {
            bodovi += vrstaBodovi;
            std::cout << "  " << ime << " ima " << vrstaBodovi << " od jednog broja! (+" << vrstaBodovi << " bodova)" << std::endl;
        }

        return bodovi;
    }
    
    void ispisiRuku() const {
        std::cout << ime << "ruka (" << ruka.size() << " karata):" << std::endl;
        for (size_t i = 0; i < ruka.size(); i++) {
            std::cout << "  " << i+1 << ". " << ruka[i].uString() << std::endl;
        }
    }
};

class Mac {
private:
    std::vector<Karta> karte;
    
public:
    Mac() {
        for (int z = KUPE; z <= DENARI; z++) {
            Zog zog = static_cast<Zog>(z);
            for (int broj = 1; broj <= 10; broj++) {
                karte.push_back(Karta(broj, zog));
            }
        }
    }
    
    void promijesaj() {
        std::srand(std::time(0));
        for (size_t i = 0; i < karte.size(); i++) {
            int j = std::rand() % karte.size();
            std::swap(karte[i], karte[j]);
        }
    }

    Karta dilajKarte() {
        if (karte.empty()) {
            throw std::runtime_error("Nema karata za dijeliti.");
        }

        Karta karta = karte.back();
        karte.pop_back();
        return karta;
    }
    
    bool jePrazno() const {
        return karte.empty();
    }
    
    size_t size() const {
        return karte.size();
    }
};

class TresetaIgra {
private:
    std::vector<Igrac> igraci;
    Mac mac;
    
public:
    void zapocniIgru() {
        int brojIgraca;
        
        while (true) {
            std::cout << "Unesi broj igraca (2 ili 4): ";
            std::cin >> brojIgraca;
            
            if (brojIgraca == 2 || brojIgraca == 4) {
                break;
            }
            std::cout << "Los broj. Unesi 2 ili 4." << std::endl;
        }
        
        std::cin.ignore();
        for (int i = 0; i < brojIgraca; i++) {
            std::string ime;
            std::cout << "Unesi ime za igraca " << i+1 << ": ";
            std::getline(std::cin, ime);
            igraci.push_back(Igrac(ime));
        }

        mac.promijesaj();
        std::cout << "\nPromijesavanje i dijeljenje " << 10
                  << " karta svakom igracu" << std::endl;
        
        int kartePoIgracu = 10;
        
        for (int kartaBroj = 0; kartaBroj < kartePoIgracu; kartaBroj++) {
            for (int igracIdx = 0; igracIdx < brojIgraca; igracIdx++) {
                igraci[igracIdx].dodajKartu(mac.dilajKarte());
            }
        }
        
        for (Igrac& player : igraci) {
            player.sortirajRuku();
        }
    }
    
    void igrajRundu() {
        std::cout << "\nProvjera akuzacija" << std::endl;
        
        for (Igrac& player : igraci) {
            std::cout << "\nProvjera " << player.dobijIme() << ":" << std::endl;
            player.racunajBodoveAkuzate();
        }
        
        std::cout << "\nKonacni rezultat" << std::endl;
        for (const Igrac& player : igraci) {
            std::cout << player.dobijIme() << ": " << player.dobijBodove() << " bodova" << std::endl;
        }
    }
    
    void ispisiSveRuke() const {
        std::cout << "\nRuke svih igraca:" << std::endl;
        for (const Igrac& player : igraci) {
            player.ispisiRuku();
            std::cout << std::endl;
        }
    }
    
    void ispisiStanjeMaca() const {
        std::cout << "Mac ima " << mac.size() << " karta preostalo." << std::endl;
    }
};

int main() {
    std::srand(std::time(0));
    
    std::cout << "TRESETA" << std::endl;
    std::cout << "Pravila akuzate:" << std::endl;
    std::cout << "- Napolitana (As, Duja, Trica istog zoga): 3 bodova" << std::endl;
    std::cout << "- Tri iste karte (barem 3 Asa/Duje/Trice): 3-4 bodova" << std::endl;
    
    TresetaIgra igra;
    
    igra.zapocniIgru();
    
    igra.ispisiSveRuke();
    
    igra.igrajRundu();
    
    std::cout << "\nStatistika igre:" << std::endl;
    igra.ispisiStanjeMaca();
    
    return 0;
}