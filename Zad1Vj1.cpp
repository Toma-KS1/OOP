#include <iostream>
#include <iomanip>
int main()
{
	bool flag;
	std::cout << "unesi " << true << " - " << false << std::endl;
	std::cin >> flag;
	std::cout << std::noboolalpha << flag << std::endl;
	int a = 255;
	std::cout << "hex " << std::hex << a << std::endl;
	std::cout << "dec " << std::dec << a << std::endl;
	std::cout << "oct " << std::oct << a << std::endl;
	double pi = 3.141592;
	std::cout << "pi = " << std::fixed << std::nouppercase;
	std::cout << std::setprecision(3) << std::setw(20);
	std::cout << std::setfill('1');
	std::cout << pi << std::endl;
}
