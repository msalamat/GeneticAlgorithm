#include <iostream>
#include <random>

#include "City.hpp"
#include "Tour.hpp"

int main() {


	// The program starts by creating a group of cities
	std::vector<City> MasterList;

	std::string str("ABCDEFGHIJKLMNOPQRST");

	std::random_device rd;
	std::mt19937 gen( rd() );
	std::uniform_int_distribution<> dis(  0, 1000);

	for (int i = 0; i < 20; ++i) {
		MasterList.emplace_back(dis(gen), dis(gen), str.substr(static_cast<unsigned long>(i), 1));
	}

	std::vector<Tour> tourList;

	for (int i = 0; i < 10; ++i) {
		std::vector<int> cityIndicies = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
		std::vector<City*> cityList;

		while(!cityIndicies.empty()) {
			std::uniform_int_distribution<> dissssss(0, (int) cityIndicies.size()-1);
			int randomNumber = dissssss(gen);
			cityList.push_back( &MasterList.at(   cityIndicies.at(randomNumber)    ));
			cityIndicies.erase(cityIndicies.begin() + randomNumber);
		}

		// store my freshly made tour
		Tour tour{cityList};
		tourList.push_back(tour);
	}

	std::cout << tourList.at(0).tour.at(0)->getName();

	return 0;
}