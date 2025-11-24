#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include <stdexcept>
#include <utility>

template<typename T>
class container {
private:
	T* pod;
	size_t vel;
	size_t kap;

	void prosiri();
public:
	explicit container(size_t initkap = 0);
	~container();
	container(const container& drugi);
	container& operator=(const container& drugi);
	container(container&& drugi) noexcept;
	container& operator=(container&& drugi) noexcept;
	void push_back(const T& vrj);
	size_t size() const;
	size_t capacity() const;
	T& at(size_t ind);
	const T& at(size_t ind) const;
	void clear();
	T& operator[](size_t ind);
	const T& operator[](size_t ind) const;
	bool empty() const;
};

#endif