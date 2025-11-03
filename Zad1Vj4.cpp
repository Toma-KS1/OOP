#include <iostream>
#include <vector>
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

int main(){

	std::vector<int> v;
	input_vector(v);
	print_vector(v);


	return 0;



}

