#include <iostream>

int& funk(int niz[], int i){
    return niz[i];
}

int main(){
    int niz[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int i = 6;
    for (int j = 0; j < sizeof(niz) / sizeof(niz[0]); j++){
        std::cout << niz[j] << ' ';
    }
    funk(niz, i)++;
    for (int j = 0; j < sizeof(niz) / sizeof(niz[0]); j++){
        std::cout << niz[j] << ' ';
    }
    return 0;
}