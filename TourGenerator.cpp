//
// Created by Mohammad Salamat on 2019-03-24.
//

#include "TourGenerator.hpp"
#include <random>

TourGenerator::TourGenerator(std::vector<City> masterList) : MasterList(masterList){}

void TourGenerator::genesisTour() {

	std::mt19937 gen( rd() );
	std::uniform_int_distribution<> dis(0, MAP_BOUNDARY);

	for (int i = 0; i < TOUR_SIZE; ++i) {

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
		genesis.push_back(tour);
	}

	for (auto &i : genesis) {
		i.computeFitnessLevel();
	}
}

void TourGenerator::generateTours(std::vector<Tour>& newGeneration, std::vector<Tour>& parents) {
	std::mt19937 gen( rd() );

	while ( (int) newGeneration.size() != TOUR_SIZE) {

		std::uniform_int_distribution<> dis4(0, PARENT_POOL_SIZE-1);
		int randomParent1 = dis4(gen), randomParent2;

		do {
			randomParent2 = dis4(gen);
		} while (randomParent1 == randomParent2);

		Tour& parent1 = parents.at(randomParent1);
		Tour& parent2 = parents.at(randomParent2);

		Tour baby = crossover(parent1, parent2);
		newGeneration.push_back(baby);
	}
}

Tour TourGenerator::crossover(const Tour& p1, const Tour& p2) {

	std::mt19937 gen( rd() );
	std::uniform_int_distribution<> dis(0, CITIES_IN_TOUR-1);

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

void TourGenerator::mutate(Tour& t) {

	std::mt19937 gen( rd() );
	std::uniform_int_distribution<> dis(1, 100);

	for (int i = 0; i < (int) t.tour.size()-1; ++i) {
		if (i == TOUR_SIZE-1) {
			if (dis(gen) <= MUTATION_RATE) {
				std::swap(t.tour.at(0), t.tour.at(i));
			}
		}
		if (dis(gen) <= MUTATION_RATE) {
			std::swap(t.tour.at(i), t.tour.at(i+1));
		}
	}
}

void TourGenerator::print() {
	std::cout << std::endl << "Beginning fitness: " << this->genesisFitness << std::endl;
	std::cout << "Final fitness: " << this->finalFitness << std::endl;
	std::cout << "This was a " << this->overallIncrease * 100 << "% gain in fitness level since the genesis tour." << std::endl;
}

void TourGenerator::calculate() {
	genesisTour();
	std::vector<Tour> newGeneration;
	std::vector<Tour> parents;
	std::set<int> numbersAsSet;

	std::vector<Tour> oldGen;
	oldGen.insert(oldGen.end(), genesis.begin(), genesis.end());
	oldGen = genesis;

	double percIncrease = 0;
	double finalFitness = 0;
	int numberOfIterations = 0;

	std::mt19937 gen(rd());

	this->genesisFitness = genesis.at(0).getFitness();

	while (percIncrease < IMPROVEMENT_FACTOR && numberOfIterations++ < MAX_ITERATIONS) {
		std::cout << "Iteration: " << numberOfIterations << std::endl;
		newGeneration.clear();
		parents.clear();
		numbersAsSet.clear();

		newGeneration.push_back(oldGen.at(0));

		std::uniform_int_distribution<> dis2(1, PARENT_POOL_SIZE);

		while ((int) numbersAsSet.size() != PARENT_POOL_SIZE) {
			numbersAsSet.insert(dis2(gen));
		}

		for (auto i = numbersAsSet.begin(); i != numbersAsSet.end(); ++i) {
			parents.push_back(oldGen.at(*i));
		}

		generateTours(newGeneration, parents);

		for (auto it = newGeneration.begin()+1; it != newGeneration.end(); ++it) {
			mutate(*it);
		}

		for (auto &i : newGeneration) {
			i.computeFitnessLevel();
		}

		std::sort(newGeneration.begin(), newGeneration.end(), cmp);

		finalFitness = newGeneration.at(0).getFitness();

		double increase = newGeneration.at(0).getFitness() - genesisFitness;
		percIncrease = increase / genesisFitness;

		printStats(finalFitness, percIncrease, newGeneration.at(0).getFitness(), oldGen.at(0).getFitness());

		oldGen.clear();
		oldGen.insert(oldGen.end(), newGeneration.begin(), newGeneration.end());
	}

	std::cout << std::endl;
	std::cout << "Number of iterations in the end: " << numberOfIterations << std::endl;
	if (numberOfIterations < MAX_ITERATIONS) {
		std::cout << "The improvement factor was indeed achieved." << std::endl;
	} else {
		std::cout << "The improvement factor was not achieved." << std::endl;
	}

	printRoutesTaken(genesis, newGeneration);

	this->overallIncrease = percIncrease;
	this->finalFitness = finalFitness;
}

void TourGenerator::printRoutesTaken(const std::vector<Tour>& t1, const std::vector<Tour>& t2) {

	std::cout << std::endl << "Initial tour: " << std::endl;
	for (int i = 0; i < CITIES_IN_TOUR; ++i) {
		std::cout << std::endl;
		std::cout << "City: "
				  << t1.at(0).tour.at(i)->getName()
				  << " x: " << t1.at(0).tour.at(i)->getX()
				  << " y: " << t1.at(0).tour.at(i)->getY();
		std::cout << std::endl;
	}

	std::cout << std::endl << "Best tour: " << std::endl;
	for (int i = 0; i < CITIES_IN_TOUR; ++i) {
		std::cout << std::endl;
		std::cout << "City: "
				  << t2.at(0).tour.at(i)->getName()
				  << " x: " << t2.at(0).tour.at(i)->getX()
				  << " y: " << t2.at(0).tour.at(i)->getY();
		std::cout << std::endl;
	}
}

void TourGenerator::printStats(double finalFitness, double percIncrease, double newGenFitness, double oldGenFitness) {
	std::cout << "Current fitness for this generation: " << finalFitness << std::endl;
	std::cout << "% increase since genesis tour: " << percIncrease * 100 << std::endl;

	if (newGenFitness > oldGenFitness) {
		std::cout << "There was an improvement from the last generation to this one." << std::endl;
	}
}
