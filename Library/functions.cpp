#include "functions.h"

float get_determinant(float *array, int n)
{
    return array[0] * (array[n + 1] * array[n * 2 + 2] - array[n + 2] * array[n * 2 + 1])
         - array[1] * (array[n] * array[n * 2 + 2] - array[n + 2] * array[n * 2])
         + array[2] * (array[n] * array[n * 2 + 1] - array[n * 2] * array[n + 1]);
}

int doublecmp(float number1, float number2)
{
    return abs(number1 - number2) <= 0.0001 ? 0 : number1 > number2 ? 1 : -1;
}

std::pair<float, float> solve_quadtratic(float a, float b, float c)
{
    float D = pow(b, 2.f) - 4.f * a * c;
        
    if(doublecmp(D, 0.f) < 0)
    {
        return {NAN, NAN};
    } 

    else 
    {
        D = sqrt(D);
        
        if (doublecmp(D, 0.f) == 0)
        {
            float coeff = (-b + D) / 2.f / a;

            return {coeff, coeff};
        }

        else
        {
            float coeff_1 = (-b + D) / 2.f / a;
            float coeff_2 = (-b - D) / 2.f / a;     

            return {coeff_1, coeff_2};
        }
    }
}