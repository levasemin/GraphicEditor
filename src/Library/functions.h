#pragma once
#include <iostream>
#include <math.h>

float get_determinant(float *array, int n);
int doublecmp(float number1, float number2);

std::pair<float, float> solve_quadtratic(float a, float b, float c);
