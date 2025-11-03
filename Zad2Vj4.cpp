#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

void input_vector(vector<int>& v) {
	int i = 1;
	while (i != 0) {
		cout << "Unesi broj";
		cin >> i;
		if (i == 0) {
			return;
		}
		v.push_back(i);
	}





}

void print_vector(const vector<int>& v) {
	for (int broj : v) {
		cout << broj << " ";
	}





}

int main() {

	std::vector<int> v;
	input_vector(v);
	print_vector(v);
	vector<int> a;
	for (int broj : v) {
		if (find(a.begin(), a.end(), broj) == a.end()) {
			a.push_back(broj);
		}
	}
	v = a;
	print_vector(v);
	sort(a.begin(), a.end(), [](int a, int b) {
		return abs(a) < abs(b);
	});
	v = a;
	print_vector(v);

	return 0;



}