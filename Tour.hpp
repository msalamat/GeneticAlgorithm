//
// Created by Mohammad Salamat on 2019-03-24.
//

#ifndef GENETICALGORITHM_TOUR_HPP
#define GENETICALGORITHM_TOUR_HPP

#include "City.hpp"

#include <vector>

#include <iostream>
#include <cmath>

class Tour {
	public:
		std::vector<City*> tour;
		Tour(std::vector<City*> tour) : tour(tour){}

		Tour() = default;

		/**
		 * Computes the fitness level of a tour
		 */
		void computeFitnessLevel();

		double getFitness() {
			return this->fitness_level;
		}

	private:
		double fitness_level = 0;

};


#endif //GENETICALGORITHM_TOUR_HPP
