#ifndef CONTAINER_CPP
#define CONTAINER_CPP

#include "container.h"


template<typename T>
void container<T>::prosiri() {
	if (vel >= kap) {
		size_t novkap = (kap == 0) ? 1 : kap * 2;
		T* novpod = new T[novkap];
		for (size_t i = 0; i < vel; ++i) {
			novpod[i] = pod[i];
		}
		delete[] pod;
		pod = novpod;
		kap = novkap;
		std::cout << "Container prosiren do novog kapaciteta: " << kap << std::endl;
	}
}

template<typename T>
container<T>::container(size_t initkap) : pod(initkap > 0 ? new T[initkap] : nullptr), vel(0), kap(initkap) {
	std::cout << "Pozvan konstruktor: kapacitet =" << kap << std::endl;
}

template<typename T>
container<T>::~container() {
	delete[] pod;
	std::cout << "Pozvan destruktor: velicine = " << vel << ", kapaciteta = " << kap << std::endl;
}

template<typename T>
container<T>::container(const container& drugi) : pod(drugi.kap > 0 ? new T[drugi.kap] : nullptr), vel(drugi.vel), kap(drugi.kap) {
	for (size_t i = 0; i < vel; ++i) {
		pod[i] = drugi.pod[i];
	}
	std::cout << "Pozvana kopija konstruktora velicine = " << vel << ", kapaciteta = " << kap << std::endl;
}

template<typename T>
container<T>& container<T>::operator=(const container& drugi) {
	if (this != &drugi) {
		T* novpod = drugi.kap > 0 ? new T[drugi.kap] : nullptr;
		for (size_t i = 0; i < drugi.vel; ++i) {
			novpod[i] = drugi.pod[i];
		}
		delete[] pod;
		pod = novpod;
		vel = drugi.vel;
		kap = drugi.kap;
	}
		std::cout << "Pozvana kopija velicine = " << vel << ", kapaciteta = " << kap << std::endl;
		return *this;
}

template<typename T>
container<T>::container(container&& drugi) noexcept : pod(drugi.pod), vel(drugi.vel), kap(drugi.kap) {
	drugi.pod = nullptr;
	drugi.vel = 0;
	drugi.capacity = 0;
	std::cout << "Micanje konstruktora pozvano: velicina = " << vel << ", kapaciteta = " << kap << std::endl;
}

template<typename T>
container<T>& container<T>::operator=(container&& drugi) noexcept {
	if (this != &drugi) {
		delete[] pod;
		pod = drugi.pod;
		vel = drugi.vel;
		kap = drugi.kap;
		drugi.pod = nullptr;
		drugi.vel = 0;
		drugi.kap = 0;
	}
	std::cout << "Micanje pozvano: velicina = " << vel << ", kapacitet = " << kap << std::endl;
	return *this;
}

template <typename T>
void container<T>::push_back(const T& vrj) {
	prosiri();
	pod[vel] = vrj;
	vel++;
	std::cout << "push_back: vrijednost = " << vrj << ", velicina = " << vel << ", kapacitet = " << kap << std::endl;
}

template<typename T>
size_t container<T>::size() const {
	return vel;
}

template<typename T>
size_t container<T>::capacity() const {
	return kap;
}

template<typename T>
T& container<T>::at(size_t ind) {
	if (ind >= vel) {
		throw std::out_of_range("Indeks je veci od velicine");
	}
	return pod[ind];
}

template<typename T>
const T& container <T>::at(size_t ind) const {
	if (ind >= vel) {
		throw std::out_of_range("Indeks je veci od velicine");
	}
	return pod[ind];
}

template<typename T>
void container<T>::clear() {
	vel = 0;
	std::cout << "pozvan clear: velicina = 0, kapacitet ostaje = " << kap << std::endl;
}

template<typename T>
T& container<T>::operator[](size_t ind) {
	return pod[ind];
}

template<typename T>
const T& container<T>::operator[](size_t ind) const {
	return pod[ind];
}

template<typename T>
bool container<T>::empty() const {
	return vel == 0;
}

void funkcijaPoVrijednosti(container<int> c) {
	std::cout << "funkcijaPoVrijednosti(): size = " << c.size()
		<< ", capacity = " << c.capacity() << std::endl;
}

// 5. Returning container from function (move constructor used)
container<int> funkcijaPovratniContainer() {
	container<int> temp(2);
	temp.push_back(111);
	temp.push_back(222);
	std::cout << "funkcijaPovratniContainer(): returning container\n";
	return temp; // NRVO or move constructor
}

int main() {

	std::cout << "\n=== 1. Default constructor + adding elements ===\n";
	container<int> c1;
	c1.push_back(10);
	c1.push_back(20);
	c1.push_back(30); // triggers reallocation
	std::cout << "c1: size=" << c1.size() << ", capacity=" << c1.capacity() << "\n";

	std::cout << "\n=== 2. Copy constructor ===\n";
	container<int> c2(c1);
	std::cout << "c2 (copy of c1): size=" << c2.size()
		<< ", capacity=" << c2.capacity() << "\n";

	std::cout << "\n=== 3. Move constructor ===\n";
	container<int> c3(std::move(c1)); // moves resources
	std::cout << "c3 (moved from c1): size=" << c3.size()
		<< ", capacity=" << c3.capacity() << "\n";

	std::cout << "\n=== 4. Pass container by value (copy) ===\n";
	funkcijaPoVrijednosti(c2);

	std::cout << "\n=== 5. Return container from function (move) ===\n";
	container<int> c4 = funkcijaPovratniContainer();
	std::cout << "c4: size=" << c4.size()
		<< ", capacity=" << c4.capacity() << "\n";

	std::cout << "\n=== 6. Memory reallocation demonstration ===\n";
	c4.push_back(333);
	c4.push_back(444);
	c4.push_back(555); // triggers another reallocation
	std::cout << "c4 after adding more: size =" << c4.size()
		<< ", kapacitet =" << c4.capacity() << "\n";

	for (size_t i = 0; i < c4.size(); i++) {
		std::cout << "Index " << i << " -> " << c4.at(i) << "\n";
	}

	std::cout << "Kraj";
	return 0;
}

#endif