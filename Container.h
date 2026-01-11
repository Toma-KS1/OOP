#ifndef CONTAINER_H
#define CONTAINER_H

#include <cstddef>

class Container {
private:
    int* niz;
    std::size_t velicina;
    std::size_t kapacitet;

public:
    Container(std::size_t inicijalni_kapacitet = 0);
    Container(const Container& drugi);
    Container(Container&& drugi) noexcept;
    ~Container();
    
    Container& operator=(const Container& drugi); 
    Container& operator=(Container&& drugi) noexcept;
    
    void push_back(int vrijednost);
    std::size_t size() const;
    std::size_t capacity() const;
    const int& at(std::size_t index) const;
    void clear();
    
    void print() const;
    
private:
    void realociraj(std::size_t novi_kapacitet);
};

#endif