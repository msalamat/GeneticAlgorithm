//
// Created by Mohammad Salamat on 2019-03-13.
//

#ifndef GENETICALGORITHM_TOUR_HPP
#define GENETICALGORITHM_TOUR_HPP

#include "City.hpp"

class Tour {
	public:
		// a list of pointers to cities we want to visit
		std::vector<City*> tour;

		Tour(std::vector<City*> tour) : tour(tour){}

};


#endif //GENETICALGORITHM_TOUR_HPP
