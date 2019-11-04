
# GeneticAlgorithm

A variation of the genetic algorithm. We commit selective breeding to find the best path in our tours.

## Installation

### Cloning the repo

```shell
$ git clone https://github.com/msalamat/GeneticAlgorithm.git
$ cd GeneticAlgorithm/
```

### Plumbing for the program

- Note: You should probably have CMake installed on your computer to be a good plumber here.

```shell
$ mkdir build/ && cd build/
$ cmake ..
$ make
```

### Running the program

```shell
$ ./GeneticAlgorithm
```

- If you don't have CMake, compile and run the old fashioned way. Make sure g++ is installed (tested on GCC 8.3.0)

```shell
$ g++ -Wall -Wextra -pedantic *.cpp -o GeneticAlgorithm
$ ./GeneticAlgorithm
```
