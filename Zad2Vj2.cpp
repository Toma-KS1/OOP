#include <iostream>
#include <vector>
#include <stdexcept>

struct Vector {
    int fizvel;
    int logvel;
    std::vector<int> niz;
    Vector(int fizvel = 0, int logvel = 0) : fizvel(fizvel), logvel(logvel), niz(fizvel) {}
};

Vector* vector_new(int initial_capacity) {
    if (initial_capacity < 0) initial_capacity = 0;
    return new Vector(initial_capacity, 0);
}

void vector_delete(Vector* v) {
    if (!v) return;
    std::vector<int>().swap(v->niz);
    delete v;
}

void vector_push_back(Vector* v, int value) {
    if (!v) return;
    if (v->fizvel == 0) {
        v->fizvel = 1;
        v->niz.resize(v->fizvel);
    }
    if (v->logvel >= v->fizvel) {
        int new_cap = v->fizvel * 2;
        if (new_cap <= 0) new_cap = 1;
        v->niz.resize(new_cap);
        v->fizvel = new_cap;
    }
    v->niz[v->logvel++] = value;
}

void vector_pop_back(Vector* v) {
    if (!v) return;
    if (v->logvel == 0) return;
    v->logvel--;
}

int vector_front(const Vector* v) {
    if (!v || v->logvel == 0) throw std::out_of_range("vector_front na praznom vektoru");
    return v->niz[0];
}

int vector_back(const Vector* v) {
    if (!v || v->logvel == 0) throw std::out_of_range("vector_back na praznom vektoru");
    return v->niz[v->logvel - 1];
}

int vector_size(const Vector* v) {
    if (!v) return 0;
    return v->logvel;
}

int main() {
    Vector* a = vector_new(2);
    vector_push_back(a, 10);
    vector_push_back(a, 20);
    vector_push_back(a, 30);
    std::cout << "Prvi element: " << vector_front(a) << "\n";
    std::cout << "Zadnji element: " << vector_back(a) << "\n";
    std::cout << "Broj elemenata: " << vector_size(a) << "\n";
    vector_pop_back(a);
    std::cout << "Logicka velicina: " << vector_size(a) << "\n";
    vector_delete(a);
    return 0;
}