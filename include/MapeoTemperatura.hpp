/**
 * Copyright (C) 2018
 * Área Académica de Ingeniería en Computadoras, ITCR, Costa Rica
 *
 * This file is part of the numerical analysis lecture CE3102 at TEC
 *
 * @Author: Erick Cordero
 * @Date  : 05.06.2018
 */

#include <cmath>
#include <limits>
#include <functional>
#include <iostream>
#include <algorithm>
#include <omp.h>

#include "Exception.hpp"
#include "Matrix.hpp"

#ifndef ANPI_MAPEO
#define ANPI_MAPEO

namespace anpi
{

/**
   *Mapea los valores lineales y de interpolación cúbica
   *
   * @param[in] JOBZ = val; valores de entrada 
   * @param[in] IPLO = 'U':  Triangular superior;
   * @param[out]INFO es un int
                = 0:  successful exit   
                < 0:  if INFO = -i, el i-ésimo argumento tiene un valor no permitido
                > 0:  if INFO = i, el algoritmo no converge
   */
template <typename T>
void mapeo(const std::vector<T>& val, const size_t tamano, std::vector<T>& valores)
{
    //asigancion de valores iniciales
    valores = std::vector<T>(0,tamano);

    size_t Tval = val.size();
    if(Tval == 1){
        for(size_t i = 0; i < tamano; ++i){
            valores.push_back(val[0]);
        }
    }
    else if (Tval == 2){
        T valPrev;
        for(size_t i = 0; i < tamano; ++i){
            T tmp = (val[1]-val[0])/(tamano-1);
            valPrev = val[0] +  tmp*i;
            valores.push_back(valPrev);

        }
    }
    else{
        //falta interpolación cúbica
        std::cout << "falta interpolación cúbica" << std::endl;
    }
    
}

} // namespace anpi

#endif