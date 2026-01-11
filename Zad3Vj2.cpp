#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

double** alocirajmatricu(int red, int stupac);
void dealocirajmatricu(double** matrica, int red);
double** unesimatricu(int& red, int& stupac);
double** generirajmatricu(int red, int stupac, double a, double b);
double** zbrojimatrice(double** A, double** B, int red, int stupac);
double** oduzmimatrice(double** A, double** B, int red, int stupac);
double** pomnozimatrice(double** A, int redA, int stupacA, double** B, int redB, int stupacB);
double** transponirajmatricu(double** matrica, int red, int stupac);
void ispisimatricu(double** matrica, int red, int stupac);

int main() {
    srand(time(0));
    
    double** matrica1 = nullptr;
    double** matrica2 = nullptr;
    double** rezultat = nullptr;
    int red1 = 0, stupac1 = 0, red2 = 0, stupac2 = 0;
    
    cout << "PRIMJER" << endl;
    
    red1 = 3; stupac1 = 3;
    red2 = 3; stupac2 = 3;
    
    matrica1 = generirajmatricu(red1, stupac1, 1.0, 10.0);
    matrica2 = generirajmatricu(red2, stupac2, 1.0, 10.0);
    
    cout << "matrica 1:" << endl;
    ispisimatricu(matrica1, red1, stupac1);
    
    cout << "\nmatrica 2:" << endl;
    ispisimatricu(matrica2, red2, stupac2);

    rezultat = zbrojimatrice(matrica1, matrica2, red1, stupac1);
    cout << "\nmatrica 1 + matrica 2:" << endl;
    ispisimatricu(rezultat, red1, stupac1);
    dealocirajmatricu(rezultat, red1);

    rezultat = oduzmimatrice(matrica1, matrica2, red1, stupac1);
    cout << "\nmatrica 1 - matrica 2:" << endl;
    ispisimatricu(rezultat, red1, stupac1);
    dealocirajmatricu(rezultat, red1);
    
    rezultat = transponirajmatricu(matrica1, red1, stupac1);
    cout << "\nTransponirana matrica 1:" << endl;
    ispisimatricu(rezultat, stupac1, red1);
    dealocirajmatricu(rezultat, stupac1);
    
    dealocirajmatricu(matrica1, red1);
    dealocirajmatricu(matrica2, red2);
    
    return 0;
}

double** alocirajmatricu(int red, int stupac) {
    double** matrica = new double*[red];
    
    for(int i = 0; i < red; i++) {
        matrica[i] = new double[stupac];
    }
    
    return matrica;
}

void dealocirajmatricu(double** matrica, int red) {
    for(int i = 0; i < red; i++) {
        delete[] matrica[i];
    }
    
    delete[] matrica;
}

double** unesimatricu(int& red, int& stupac) {
    cout << "Unesi broj redova: ";
    cin >> red;
    cout << "Unesi broj stupaca: ";
    cin >> stupac;
    
    double** matrica = alocirajmatricu(red, stupac);
    
    cout << "Unesi brojeve:" << endl;
    for(int i = 0; i < red; i++) {
        for(int j = 0; j < stupac; j++) {
            cout << "Broj [" << i << "][" << j << "]: ";
            cin >> matrica[i][j];
        }
    }
    
    return matrica;
}

double** generirajmatricu(int red, int stupac, double a, double b) {
    double** matrica = alocirajmatricu(red, stupac);
    
    for(int i = 0; i < red; i++) {
        for(int j = 0; j < stupac; j++) {
            matrica[i][j] = a + (rand() / (RAND_MAX + 1.0)) * (b - a);
        }
    }
    
    return matrica;
}

double** zbrojimatrice(double** A, double** B, int red, int stupac) {
    double** rezultat = alocirajmatricu(red, stupac);
    
    for(int i = 0; i < red; i++) {
        for(int j = 0; j < stupac; j++) {
            rezultat[i][j] = A[i][j] + B[i][j];
        }
    }
    
    return rezultat;
}

double** oduzmimatrice(double** A, double** B, int red, int stupac) {
    double** rezultat = alocirajmatricu(red, stupac);
    
    for(int i = 0; i < red; i++) {
        for(int j = 0; j < stupac; j++) {
            rezultat[i][j] = A[i][j] - B[i][j];
        }
    }
    
    return rezultat;
}

double** pomnozimatrice(double** A, int redA, int stupacA, double** B, int redB, int stupacB) {
    if(stupacA != redB) {
        cout << "Dimenzije nisu ispravne." << endl;
        return nullptr;
    }
    
    double** rezultat = alocirajmatricu(redA, stupacB);
    
    for(int i = 0; i < redA; i++) {
        for(int j = 0; j < stupacB; j++) {
            rezultat[i][j] = 0.0;
            for(int k = 0; k < stupacA; k++) {
                rezultat[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    return rezultat;
}

double** transponirajmatricu(double** matrica, int red, int stupac) {
    double** rezultat = alocirajmatricu(stupac, red);
    
    for(int i = 0; i < red; i++) {
        for(int j = 0; j < stupac; j++) {
            rezultat[j][i] = matrica[i][j];
        }
    }
    
    return rezultat;
}

void ispisimatricu(double** matrica, int red, int stupac) {
    cout << fixed << setprecision(4);
    
    for(int i = 0; i < red; i++) {
        for(int j = 0; j < stupac; j++) {
            cout << setw(10) << matrica[i][j] << " ";
        }
        cout << endl;
    }
}