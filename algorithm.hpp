#pragma once
#include <iostream>
#include <vector>
#include "classes.hpp"

void algorithm(std::vector<int>, std::vector<int>);

std::vector<Overseer> nextStep(std::vector<Overseer>, int, std::vector<int>);

std::vector<int> generateJobs(int);

std::vector<int> generateHoles(int, int);
