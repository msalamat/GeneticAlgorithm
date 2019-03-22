#include <iostream>
#include <random>
#include <algorithm>
#include <set>

#include "City.hpp"
#include "Tour.hpp"
// Parent, left, right (PREORDER)
// postorder: application: remaining capacity. calculated by visiting the child first..forgot the rest

// implement iterative version: postorder ,preorder, etc. Highly recommended to go over the iterative
// version of the pre/post/other one order. STUDY IT FOR FINAL EXAM!

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

	for (int i = 0; baby.size() != p1.tour.size(); ++i) {
		if (std::find(baby.begin(), baby.end(), p2.tour.at(i)) == baby.end()) {
			baby.push_back(p2.tour.at(i));
		}
	}

	Tour babyTour{baby};

	return babyTour;
}

void mutate(Tour& t) {

	const int chance = 15;
	std::random_device rd;
	std::mt19937 gen( rd() );
	std::uniform_int_distribution<> dis(1, 100);

	for (int i = 0; i < t.tour.size()-1; ++i) {
		if (i == 31) {
			if (dis(gen) <= chance) {
				std::swap(t.tour.at(0), t.tour.at(i));
			}
		}
		if (dis(gen) <= chance) {
			std::swap(t.tour.at(i), t.tour.at(i+1));
		}
	}
}

int main() {

	Something tg;
	tg.calcuation();
	tg.print();

	std::vector<City> MasterList;

	std::string str("ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");

	std::random_device rd;
	std::mt19937 gen( rd() );
	std::uniform_int_distribution<> dis(0, 1000);

	for (int i = 0; i < 32; ++i) {
		MasterList.emplace_back(dis(gen), dis(gen), str.substr(static_cast<unsigned long>(i), 1));
	}

	std::vector<Tour> oldGen;

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
		oldGen.push_back(tour);
	}

	for (auto &i : oldGen) {
		i.computeFitnessLevel();
	}

	// this no work
//	auto eliteGuy = std::max_element(oldGen.begin(), oldGen.end(), [](const auto& champion, const auto& challenger) {
//		return challenger.fitness_level > champion.fitness_level;
//	});

	// sort the tour list. Now the top five are fittest tours
	std::sort(oldGen.begin(), oldGen.end(), cmp);

	std::uniform_int_distribution<> dis3(0, 29);

	double genFitness = oldGen.at(0).fitness_level;
	double finalFitness = 0;
	double percIncrease = 0;

	std::vector<Tour> newGeneration;

	std::vector<Tour> parents;
	std::set<int> numbersAsSet;
	int timer = 0;

	while (percIncrease < 2.0 && timer++ < 10000000) {
		parents.clear();
		numbersAsSet.clear();

		newGeneration.push_back(oldGen.at(0));

		std::uniform_int_distribution<> dis2(1, 5);

		while (numbersAsSet.size() != 5) {
			numbersAsSet.insert(dis2(gen));
		}

		for (auto &i : oldGen) {
			i.computeFitnessLevel();
		}

		for (auto i = numbersAsSet.begin(); i != numbersAsSet.end(); ++i) {
			parents.push_back(oldGen.at(*i));
		}

		//CROSSOVER
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

		for (auto &i : oldGen) {
			i.computeFitnessLevel();
		}

		for (auto &i : newGeneration) {
			i.computeFitnessLevel();
		}

		// sort the tour just in case
		std::sort(newGeneration.begin(), newGeneration.end(), cmp);

		for (auto it = newGeneration.begin()+1; it != newGeneration.end(); ++it) {
			mutate(*it);
		}

		for (auto &i : newGeneration) {
			i.computeFitnessLevel();
		}

		std::sort(newGeneration.begin(), newGeneration.end(), cmp);

		finalFitness = newGeneration.at(0).fitness_level;

		if (newGeneration.at(0).fitness_level < oldGen.at(0).fitness_level) {
			std::cout << "Uh-oh! That shouldn't happen. Next gen's elite should be >= last gen's elite!" << std::endl;
			std::cout << "oldGen: " << oldGen.at(0).fitness_level << std::endl;
			std::cout << "newGen: " << newGeneration.at(0).fitness_level << std::endl;

		}
		double increase = newGeneration.at(0).fitness_level - genFitness;
		percIncrease = increase / genFitness;

		std::cout << "perc Increase since genesis tour: " << percIncrease * 100 << std::endl;

		oldGen.clear();
		oldGen.insert(oldGen.end(), newGeneration.begin(), newGeneration.end());

		newGeneration.clear();
	}

	std::cout << "Genesis fitness: " << genFitness << std::endl;
	std::cout << "Final fitness: " << finalFitness << std::endl;
	return 0;
}



// the lines of your main method sb inititializing something, then maybe calling some functions on the thing you created, and some kind of printing of the result




