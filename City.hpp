//
// Created by Mohammad Salamat on 2019-03-24.
//

#ifndef GENETICALGORITHM_CITY_HPP
#define GENETICALGORITHM_CITY_HPP

#include <string>

class City {

	private:
		int x, y;
		std::string name;

	public:
		City(int x, int y, std::string name) {
			this->x = x;
			this->y = y;
			this->name = name;
		}

		int getX() {
			return this->x;
		}

		int getY() {
			return this->y;
		}

		std::string getName() {
			return this->name;
		}

};


#endif //GENETICALGORITHM_CITY_HPP
