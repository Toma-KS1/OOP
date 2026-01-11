#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void reverse_strings(std::vector<std::string>& words) {
    for (std::string& rijec : words) {
        std::reverse(rijec.begin(), rijec.end());
    }
}

void ispisi_vektor(const std::vector<std::string>& words, const std::string& oznaka = "") {
    if (!oznaka.empty()) {
        std::cout << oznaka;
    }
    std::cout << "[";
    for (size_t i = 0; i < words.size(); i++) {
        std::cout << "\"" << words[i] << "\"";
        if (i < words.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

int main() {
    std::vector<std::string> words = {"hello", "world", "c++"};
    
    std::cout << "Original:" << std::endl;
    ispisi_vektor(words);
    
    reverse_strings(words);
    
    std::cout << "\nNaopako:" << std::endl;
    ispisi_vektor(words);
    
    return 0;
}