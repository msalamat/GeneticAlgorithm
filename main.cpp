#include <iostream>
#include <vector>
#include <random>

#include "City.hpp"
#include "TourGenerator.hpp"

std::vector<City> generateMasterlist();

int main() {
	std::vector<City> MasterList = generateMasterlist();
	TourGenerator tg{MasterList};
	tg.calculate();
	tg.print();
	return 0;
}

std::vector<City> generateMasterlist() {
	std::vector<City> MasterList;

	std::string str("ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");

	std::random_device rd;
	std::mt19937 gen( rd() );
	std::uniform_int_distribution<> dis(0, 1000);

	for (int i = 0; i < 32; ++i) {
		MasterList.emplace_back(dis(gen), dis(gen), str.substr(static_cast<unsigned long>(i), 1));
	}

	return MasterList;
}
