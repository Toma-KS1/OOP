#include <iostream>

int nesto(int x, int low, int high)
{
	if (x < low)
		return low;
	if (x > high)
		return high;
	if (x > low && x < high)
		return x;


}









double nesto(double n, int low, int high)
{
	if (n < low)
		return low;
	if (n > high)
		return high;
	if (n > low && n < high)
		return n;





}

int main() 
{
	int low = 0;
	int high = 100;
	int a = nesto(0, low, high);
	std::cout << "rezultat je " << a << std::endl;
	auto b = nesto(-1.9, low, high);
	std::cout << "rezultat je " << b << std::endl;
	auto c = nesto(105, low, high);
	std::cout << "rezultat je " << c << std::endl;
	auto d = nesto(105.5, low, high);
	std::cout << "rezultat je " << d << std::endl;
	auto e = nesto(3, low, high);
	std::cout << "rezultat je " << e << std::endl;
	auto f = nesto(3.5, low, high);
	std::cout << "rezultat je " << f << std::endl;


}










