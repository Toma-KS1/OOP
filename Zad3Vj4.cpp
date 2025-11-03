#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

void fix_spaces(std::string& text) {
	if (text.empty()) return;
	auto a = unique(text.begin(), text.end(), [](char a, char b) {return a == ' ' && b == ' '; });
	text.erase(a, text.end());
	size_t poz = 0;
	while ((poz = text.find(" .", poz)) != string::npos) {
		text.erase(poz, 1);
	}
	poz = 0;
	while ((poz = text.find(" ,", poz)) != string::npos) {
		text.erase(poz, 1);
	}
	poz = 0;
	while ((poz = text.find(',', poz)) != string::npos) {
		if (poz + 1 < text.size() && text[poz + 1] != ' ') {
			text.insert(poz + 1, " ");
		}
		poz++;
	}
	if (!text.empty() && text[0] == ' ') {
		text.erase(0, 1);
	}
	if (!text.empty() && text.back() == ' ') {
		text.pop_back();
	}
}

int main() {
	std::string text = "Puno    razmaka   ,i tocka  .";
	cout << text;
	fix_spaces(text);
	cout << text;
	return 0;



}