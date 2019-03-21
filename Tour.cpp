//
// Created by Mohammad Salamat on 2019-03-13.
//

#include <iostream>
#include <cmath>
#include "Tour.hpp"

void Tour::computeFitnessLevel() {
	double distance = 0;
	double x1, x2, y1, y2;

	// std::cout << "distance: " << std::endl;

	for (auto it = tour.begin(); it != tour.end()-1;) {
		x1 = (*it)->getX();
		y1 = (*it)->getY();
		it++;
		x2 = (*it)->getX();
		y2 = (*it)->getY();
		distance += sqrt( pow((x2 - x1), 2) + pow((y2 - y1), 2) );
		//std::cout << distance << " ( (" <<x1<<"," <<y1<<") -> (" <<x2 <<","<<y2<<  ") )" << std::endl;

	}

	this->fitness_level = (1 / distance) * 100000;

	//std::cout << "fitness " << fitness_level << std::endl;
}
