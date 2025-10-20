#include <iostream>

int* funk(int* niz, int n) {
	int* noviniz = new int[n];
	noviniz[0] = niz[0];
	noviniz[1] = niz[1];
	for (int i = 2; i < n; i++) {
		noviniz[i] = noviniz[i - 1] + noviniz[i - 2];
	}
	return noviniz;
}
int main() {
	int niz[] = { 1,1 };
	int n = 7;
	int* noviniz = funk(niz, n);
	for (int i = 0; i < n; i++) {
		std::cout << noviniz[i] << std::endl;
	}
	delete[] noviniz;
}