#include <iostream>
#include <random>
#include <algorithm>

#include "City.hpp"
#include "Tour.hpp"


bool cmp(Tour t1, Tour t2) {
	return t1.fitness_level > t2.fitness_level;
}

Tour makeBaby(Tour p1, Tour p2) {
	std::random_device rd;
	std::mt19937 gen( rd() );
	std::uniform_int_distribution<> dis(0, 29);
	int randNum = dis(gen);
	std::vector<City*> baby;

	for (int i = 0; i != randNum; ++i) {
		baby.push_back(p1.tour.at(i));
	}

	int i = 0;

	while (baby.size() != 30) {
		if(std::find(baby.begin(), baby.end(), p2.tour.at(i++)) != baby.end()) {
			/* v contains x */


		} else {
			/* v does not contain x */
		}
	}
}

int main() {


	// The program starts by creating a group of cities
	std::vector<City> MasterList;

//	City yuni(1,2,"Yuni");
//	MasterList.push_back(yuni);

	std::string str("ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");

	std::random_device rd;
	std::mt19937 gen( rd() );
	std::uniform_int_distribution<> dis(0, 1000);

	for (int i = 0; i < 32; ++i) {
		MasterList.emplace_back(dis(gen), dis(gen), str.substr(static_cast<unsigned long>(i), 1));
	}

	std::vector<Tour> tourList;

	for (int i = 0; i < 30; ++i) {

		std::vector<int> cityIndicies = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
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

	// compute fitness level for each one
	for (auto &i : tourList) {
		i.computeFitnessLevel();
	}

	// get the top fitness guy
//	auto eliteGuy1 = std::max_element(tourList.begin(), tourList.end(), [](const auto& champion, const auto& challenger) {
//		return challenger.fitness_level > champion.fitness_level;
//	});


	// sort the tour list. Now the top five are fittest tours
	std::sort(tourList.begin(), tourList.end(), cmp);

	std::vector<Tour> eliteGeneration{5};
	std::copy(tourList.begin(), tourList.begin()+5, eliteGeneration.begin());

	// 1. now crossover the top elite peeps
	std::vector<Tour> newGeneration{30};
	std::copy(eliteGeneration.begin(), eliteGeneration.begin()+5, newGeneration.begin());
	int i = 0;

	std::uniform_int_distribution<> dis2(0, static_cast<int>(eliteGeneration.size()-1));
	std::cout << dis2(gen);

	while (newGeneration.size() != 30) {
		int parent1 = dis2(gen), parent2;

		do {
			parent2 = dis2(gen);
		} while (parent2 == parent1);

		Tour baby = makeBaby(eliteGeneration.at(parent1), eliteGeneration.at(parent2));
		newGeneration.push_back(baby);
	}


	return 0;
}






