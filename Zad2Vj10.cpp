#include "math_utils.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
#include <iomanip>

std::vector<math_utils::Point> loadPointsFromFile(const std::string& filename) {
    std::vector<math_utils::Point> tocke;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Ne moze se otvoriti file '" << filename << "'" << std::endl;
        std::cerr << "Kreiranje sample file sa tockama..." << std::endl;
        
        std::ofstream createFile(filename);
        if (createFile) {
            createFile << "1.0 2.0\n";
            createFile << "-3.0 4.0\n";
            createFile << "5.0 -6.0\n";
            createFile << "-7.0 -8.0\n";
            createFile << "9.0 10.0\n";
            createFile << "0.0 0.0\n";
            createFile << "2.5 3.5\n";
            createFile << "-1.0 3.0\n";
            createFile << "4.0 -2.0\n";
            createFile << "-3.0 -4.0\n";
            createFile.close();
            std::cout << "Sample file kreiran. Ponovno pokreni program." << std::endl;
        }
        return tocke;
    }
    
    double x, y;
    while (file >> x >> y) {
        tocke.push_back(math_utils::Point(x, y));
    }
    
    file.close();
    return tocke;
}

int main() {
    const std::string filename = "tocke.txt";
    
    std::cout << "Citanje tocaka iz '" << filename << "'..." << std::endl;
    std::vector<math_utils::Point> tocke = loadPointsFromFile(filename);
    
    if (tocke.empty()) {
        std::cerr << "Nema tocaka ili file nije pronaden." << std::endl;
        return 1;
    }

    std::cout << "Ucitano " << tocke.size() << " tocaka." << std::endl << std::endl;
    
    math_utils::ispisiTocke(tocke, "Originalne tocke iz file");
    
    std::cout << "1. Sortiranje tocaka po distanci od ishodista (0,0):" << std::endl;
    std::sort(tocke.begin(), tocke.end(),
              [](const math_utils::Point& a, const math_utils::Point& b) {
                  double distA = math_utils::distance(a, math_utils::Point(0.0, 0.0));
                  double distB = math_utils::distance(b, math_utils::Point(0.0, 0.0));
                  return distA < distB;
              });
    math_utils::ispisiTocke(tocke, "Tocke sortirane po udaljenosti od ishodista");
    
    std::cout << "2. Racunaj tocke u prvom kvadrantu (x > 0, y > 0):" << std::endl;
    size_t firstQuadrantCount = std::count_if(tocke.begin(), tocke.end(),
                                             [](const math_utils::Point& p) {
                                                 return p.x > 0 && p.y > 0;
                                             });
    std::cout << "   tocke u prvom kvadrantu: " << firstQuadrantCount << std::endl << std::endl;
    
    std::cout << "3. Racunanje centroida:" << std::endl;
    math_utils::Point center = math_utils::centroid(tocke);
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "   Centroid: (" << center.x << ", " << center.y << ")" << std::endl;
    
    double centroidDist = math_utils::distance(center, math_utils::Point(0.0, 0.0));
    std::cout << "   Distanca od ishodista do centroida: " << std::setprecision(3) 
              << centroidDist << std::endl << std::endl;
    
    std::cout << "4. Micanje svih tocaka za (5, 3):" << std::endl;
    std::vector<math_utils::Point> shiftedPoints = tocke;
    std::transform(shiftedPoints.begin(), shiftedPoints.end(),
                   shiftedPoints.begin(),
                   [](const math_utils::Point& p) {
                       return math_utils::Point(p.x + 5.0, p.y + 3.0);
                   });
    math_utils::ispisiTocke(shiftedPoints, "Maknute tocke (original + (5,3))");
    
    std::cout << "5. Izbrisi tocke sa obe koordinate negativne (x < 0 i y < 0):" << std::endl;
    std::vector<math_utils::Point> filteredPoints = tocke;
    
    auto newEnd = std::remove_if(filteredPoints.begin(), filteredPoints.end(),
                                [](const math_utils::Point& p) {
                                    return p.x < 0 && p.y < 0;
                                });
    
    filteredPoints.erase(newEnd, filteredPoints.end());
    
    std::cout << "   Izbrisano " << (tocke.size() - filteredPoints.size()) 
              << " tocke sa obje koordinate negativne." << std::endl;
    math_utils::ispisiTocke(filteredPoints, "Tocke nakon brisanja negativnih koordinata");
    
    std::cout << "6. Printanje konacnih tocaka koristenjeme std::ostream_iterator:" << std::endl;
    std::cout << "Konacne tocke (" << filteredPoints.size() << "):" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    
    std::cout << "Formatirano ispisivanje:" << std::endl;
    std::for_each(filteredPoints.begin(), filteredPoints.end(),
                  [](const math_utils::Point& p) {
                      std::cout << "  (" << std::setw(6) << p.x << ", " 
                                << std::setw(6) << p.y << ")" << std::endl;
                  });
    
    std::cout << "\nKao parovi koordinata (koristeci ostream_iterator): ";
    std::copy(filteredPoints.begin(), 
              filteredPoints.end(),
              std::ostream_iterator<math_utils::Point>(std::cout, " "));
    std::cout << std::endl;
    
    std::cout << "\nIspis sa custom formatom: ";
    std::transform(filteredPoints.begin(), filteredPoints.end(),
                   std::ostream_iterator<std::string>(std::cout, " "),
                   [](const math_utils::Point& p) {
                       std::ostringstream oss;
                       oss << "[" << p.x << "," << p.y << "]";
                       return oss.str();
                   });
    std::cout << std::endl;
    
    std::cout << "\nRezime" << std::endl;
    std::cout << "Ukupno tocke: " << tocke.size() << std::endl;
    std::cout << "Tocke u prvom kvadrantu: " << firstQuadrantCount << std::endl;
    std::cout << "Tocke nakon brisanja negativnih koordinata: " << filteredPoints.size() << std::endl;
    std::cout << "Centroid: (" << center.x << ", " << center.y << ")" << std::endl;
    
    return 0;
}

namespace math_utils {
    std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x << "," << p.y << ")";
        return os;
    }
}