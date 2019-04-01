#include <iostream>
#include <vector>
#include <random>

#include "City.hpp"
#include "TourGenerator.hpp"

const int MAP_BOUNDARY = 1000;
const int NUMBER_OF_CITIES = 32;

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
	std::uniform_int_distribution<> dis(0, MAP_BOUNDARY);

	for (int i = 0; i < NUMBER_OF_CITIES; ++i) {
		MasterList.emplace_back(dis(gen), dis(gen), str.substr(static_cast<unsigned long>(i), 1));
	}

	return MasterList;
}
