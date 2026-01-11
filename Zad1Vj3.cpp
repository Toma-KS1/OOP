#include <iostream>
#include <cstddef>

void sortt(int[], std::size_t, bool(*cmp)(int, int));

inline bool ascending(int a, int b) {
	return a < b;
}

inline bool descending(int a, int b) {
	return a > b;
}

void sortt(int niz[], std::size_t vel, bool(*cmp)(int, int)) {
	if (vel <= 1) return;
	for (std::size_t i = 0; i < vel - 1; i++) {
        for (std::size_t j = 0; j < vel - i - 1; j++) {
            if (j + 1 < vel) {
                if (!cmp(niz[j], niz[j + 1])) {
                    int temp = niz[j];
                    niz[j] = niz[j + 1];
                    niz[j + 1] = temp;
				}
			}
		}
	}
}




int main(){
	int niz[] = { 1,2,3,4,5 };
	std::size_t vel = sizeof(niz) / sizeof(niz[0]);
	for (int z = 0; z < vel; z++) {
		std::cout << niz[z] << " ";
	}
	sortt(niz, vel, ascending);
	for (int z = 0; z < vel; z++) {
		std::cout << niz[z] << " ";
	}
	sortt(niz, vel, descending);
	for (int z = 0; z < vel; z++) {
		std::cout << niz[z] << " ";
	}
}