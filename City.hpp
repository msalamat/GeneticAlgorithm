//
// Created by Mohammad Salamat on 2019-03-12.
//

#ifndef GENETICALGORITHM_CITY_HPP
#define GENETICALGORITHM_CITY_HPP

#include <vector>
#include <string>

class City {

	private:
		int x, y;
		std::string name;

	public:
		City(int x, int y, std::string name);


		// getters and setters
		int getX() {
			return this->x;
		}

		int getY() {
			return this->y;
		}

		std::string getName() {
			return this->name;
		}

		void setX(int x) {
			this->x = x;
		}

		void setY(int y) {
			this->y = y;
		}

		void setName(std::string name) {
			this->name = name;
		}

};


#endif //GENETICALGORITHM_CITY_HPP
