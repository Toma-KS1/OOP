#include <iostream>
#include <cstddef>

template<typename T>
void sortt(T[], std::size_t, bool(*cmp)(T, T));

inline bool Uzlazno(int a, int b) {
    return a < b;
}

inline bool Silazno(int a, int b) {
    return a > b;
}

inline bool Uzlazno(double a, double b) {
    return a < b;
}

inline bool Silazno(double a, double b) {
    return a > b;
}

template<typename T>
void sortt(T niz[], std::size_t vel, bool(*cmp)(T, T)) {
    if (vel <= 1) return;
    for (std::size_t i = 0; i < vel - 1; i++) {
        for (std::size_t j = 0; j < vel - i - 1; j++) {
            if (!cmp(niz[j], niz[j + 1])) {
                T temp = niz[j];
                niz[j] = niz[j + 1];
                niz[j + 1] = temp;
            }
        }
    }
}

template<typename T>
void ispisiniz(T arr[], std::size_t vel) {
    for (std::size_t i = 0; i < vel; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "Niz intova" << std::endl;
    int intNiz[] = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    std::size_t intVelicina = sizeof(intNiz) / sizeof(intNiz[0]);
    
    std::cout << "Original: ";
    ispisiniz(intNiz, intVelicina);
    
    sortt(intNiz, intVelicina, Uzlazno);
    std::cout << "Uzlazno: ";
    ispisiniz(intNiz, intVelicina);
    
    sortt(intNiz, intVelicina, Silazno);
    std::cout << "Silazno: ";
    ispisiniz(intNiz, intVelicina);
    
    std::cout << "Niz doubleova" << std::endl;
    double doubleNiz[] = {5.5, 3.3, 8.8, 1.1, 9.9, 2.2, 7.7, 4.4, 6.6};
    std::size_t doubleVelicina = sizeof(doubleNiz) / sizeof(doubleNiz[0]);
    
    std::cout << "Original: ";
    ispisiniz(doubleNiz, doubleVelicina);
    
    sortt(doubleNiz, doubleVelicina, Uzlazno);
    std::cout << "Uzlazno: ";
    ispisiniz(doubleNiz, doubleVelicina);
    
    sortt(doubleNiz, doubleVelicina, Silazno);
    std::cout << "Silazno: ";
    ispisiniz(doubleNiz, doubleVelicina);
    
    return 0;
}