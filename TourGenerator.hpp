//
// Created by Mohammad Salamat on 2019-03-24.
//

#ifndef GENETICALGORITHM_TOURGENERATOR_HPP
#define GENETICALGORITHM_TOURGENERATOR_HPP

#include "City.hpp"
#include "Tour.hpp"

#include <random>
#include <set>
#include <algorithm>

class TourGenerator {

	public:
		std::vector<Tour> genesis;
		std::vector<City> MasterList;

		TourGenerator(std::vector<City> masterList);

		void print();
		void calculate();

	private:
		const int PARENT_POOL_SIZE = 5;
		const int TOUR_SIZE = 30;
		const int CITIES_IN_TOUR = 32;
		const int MAX_ITERATIONS = 1000;
		const int MAP_BOUNDARY = 1000;
		const double MUTATION_RATE = 15;
		const double IMPROVEMENT_FACTOR = 0.3;

		double genesisFitness;
		double finalFitness;
		double overallIncrease;

		std::random_device rd;

		/**
		 * Takes two "parent" tours and makes a baby Tour out of them
		 *
		 * @return A new baby Tour
		 */
		Tour crossover(const Tour&, const Tour&);

		/**
		 * Creates a tour for a new generation by randomly crossing over with
		 * strong parents.
		 */
		void generateTours(std::vector<Tour>&, std::vector<Tour>&);

		/**
		 * Generates the initial, genesis tour.
		 */
		void genesisTour();

		/**
		 * Randomly switches up a tour's city positions inside of it
		 */
		void mutate(Tour&);

		/**
		 * Prints the routes taken of the first tour of the genesis generation and
		 * the elite tour in the very last generation.
		 *
		 * @param t1 the genesis tour
		 * @param t2 the final tour
		 */
		void printRoutesTaken(const std::vector<Tour>& t1, const std::vector<Tour>& t2);

		/**
		 * Prints some statistics for how the experiment went.
		 */
		void printStats(double, double, double, double);

		/**
		 * Finds out whether the first fitness is greater than the second
		 * @param t1 First Tour
		 * @param t2 Second Tour
		 * @return bool - whether the first tour has a higher fitness than the second
		 */
		static bool cmp(Tour& t1, Tour& t2) {
			return t1.getFitness() > t2.getFitness();
		}
};


#endif //GENETICALGORITHM_TOURGENERATOR_HPP
