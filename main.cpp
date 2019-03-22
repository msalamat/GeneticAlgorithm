#include <iostream>
#include <random>
#include <algorithm>
#include <set>

#include "City.hpp"
#include "Tour.hpp"


bool cmp(const Tour& t1, const Tour& t2) {
	return t1.fitness_level > t2.fitness_level;
}

Tour makeBaby(const Tour& p1, const Tour& p2) {
	std::random_device rd;
	std::mt19937 gen( rd() );
	std::uniform_int_distribution<> dis(0, 29);

	int randNum = dis(gen);
	std::vector<City*> baby;

	for (int i = 0; i != randNum; ++i) {
		baby.push_back(p1.tour.at(i));
	}

	int i = 0;

//	while (baby.size() != 30) { // TODO make into for loop afterwards
//		if(std::find(baby.begin(), baby.begin()+randNum, p2.tour.at(i)) != baby.end()) {
//			baby.push_back(p2.tour.at(i));
//		}
//		++i;
//	}

	for (int i = 0; baby.size() != p1.tour.size(); ++i) {
		if (std::find(baby.begin(), baby.end(), p2.tour.at(i)) == baby.end()) {
			baby.push_back(p2.tour.at(i));
		}
	}

	Tour babyTour{baby};

	return babyTour;
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

	for (auto &i : tourList) {
		i.computeFitnessLevel();
	}

	// this dont work bro
//	auto eliteGuy = std::max_element(tourList.begin(), tourList.end(), [](const auto& champion, const auto& challenger) {
//		return challenger.fitness_level > champion.fitness_level;
//	});

	// sort the tour list. Now the top five are fittest tours
	std::sort(tourList.begin(), tourList.end(), cmp);

	std::uniform_int_distribution<> dis3(0, 29);

	std::vector<Tour> parents;
	std::vector<Tour> newGeneration;

	newGeneration.push_back(tourList.at(0));

	std::set<int> numbersAsSet;

	std::uniform_int_distribution<> dis2(1, 29);

	while (numbersAsSet.size() != 5) {
		numbersAsSet.insert(dis2(gen));
	}

	for (auto i = numbersAsSet.begin(); i != numbersAsSet.end(); ++i) {
		parents.push_back(tourList.at(*i));
	}

	while (newGeneration.size() != 30) {

		std::uniform_int_distribution<> dis4(0, 4);

		int randomParent1 = dis4(gen), randomParent2;

		do {
			randomParent2 = dis4(gen);
		} while (randomParent1 == randomParent2);

		Tour& parent1 = parents.at(randomParent1);
		Tour& parent2 = parents.at(randomParent2);

		Tour baby = makeBaby(parent1, parent2);
		newGeneration.push_back(baby);
	}
	
	std::sort(newGeneration.begin(), newGeneration.end(), cmp);

	for (auto &i : newGeneration) {
		i.computeFitnessLevel();
	}

	return 0;
}






