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
                        const std::vector<T> &tLeft, const std::vector<T> &tRight, const std::vector<bool> &aislados, std::vector<T> &bs)
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
            if (i == 0)
            {
                b-=leftTemp[j];
            }
            else
            {
                A(k, k-v) = 1;
            }
            if (i == bordeDer)
            {
                b-= rightTemp[j];
            }
            else
            {       
                A(k, k+v) = 1;
            }
            if (j == 0)
            {
                b-= topTemp[i];
            }
            else
            {
                A(k, k-1) = 1;
            }
            if (j == bordeInf)
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

    /*std::cout << "La matri" << std::endl;
    for (size_t i = 0; i < lenA; ++i){
        for (size_t j = 0;j < lenA; ++j){
            std::cout << A(i,j) << "\t";
        }
        std::cout << std::endl;
    }

    std::cout << "La solu b" << std::endl;
    for (size_t i = 0; i < bs.size(); ++i){
        std::cout << bs[i] << "\t";
    }
    std::cout << std::endl;*/

    anpi::Matrix<T> L;
    anpi::liebmann(A, L, bs);

    
    
} //end edp
} // namespace anpi
#endif