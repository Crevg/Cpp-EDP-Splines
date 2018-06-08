#include <cmath>
#include <limits>
#include <functional>
#include <iostream>
#include <algorithm>

#include "Exception.hpp"
#include "Matrix.hpp"
#include "MapeoTemperatura.hpp"
#include "liebmann.hpp"
#ifndef ANPI_EDP
#define ANPI_EDP

namespace anpi
{
template <typename T>
void formEDP(anpi::Matrix<T> &A, int h, int v, const std::vector<T> &tTop, const std::vector<T> &tBot,
                        const std::vector<T> &tLeft, const std::vector<T> &tRight, bool aislados[], std::vector<T> &bs)
{ 
    std::vector<T> topTemp, botTemp, leftTemp, rightTemp;

    anpi::mapeo(tTop, v, topTemp);
    anpi::mapeo(tBot, v, botTemp);
    anpi::mapeo(tLeft, h, leftTemp);
    anpi::mapeo(tRight, h, rightTemp);
    size_t lenA = v* h;
    A = anpi::Matrix<T>(lenA, lenA, 0.0);
    std::string solu;
    int k = 0; // filas
    
    k = 0;
    T b;
    size_t bordeDer, bordeInf;
    bordeDer = v-1;
    bordeInf = h-1;
    for (size_t i = 0; i < (size_t)v; ++i)
    {
        b = 0;
        for (size_t j = 0; j <(size_t) h; ++j, ++k)
        {
            A(k, k) = -4;
            if (i == 0 && !aislados[2])
            {
                b-=leftTemp[j];
            }
            else
            {
                A(k, k-v) = 1;
            }
            if (i == bordeDer && !aislados[3])
            {
                b-= rightTemp[j];
            }
            else
            {       
                A(k, k+v) = 1;
            }
            if (j == 0 && !aislados[0])
            {
                b-= topTemp[i];
            }
            else
            {
                A(k, k-1) = 1;
            }
            if (j == bordeInf && !aislados[1])
            {
                b-=botTemp[i];
            }
            else
            {
                A(k, k + 1) = 1;
            
            }
            bs.push_back(b);
            b=0;
        } //for j
    }     //for i
    
} //end edp

} // namespace anpi
#endif