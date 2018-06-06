/**
 * Copyright (C) 2018
 * Área Académica de Ingeniería en Computadoras, ITCR, Costa Rica
 *
 * This file is part of the numerical analysis lecture CE3102 at TEC
 *
 * @Author: 
 * @Date  : 03.03.2018
 */

#include <cmath>
#include <limits>
#include <functional>
#include <iostream>
#include <algorithm>

#include "Exception.hpp"
#include "Matrix.hpp"

#ifndef ANPI_LIEBMANN
#define ANPI_LIEBMANN

namespace anpi
{

template <typename T>
void liebmann(const Matrix<T> &A,
              Matrix<T> &L, std::vector<T> b)
{
  size_t m = A.rows();
  size_t n = A.cols();
  T Aiplus1j, Aiminus1j, Aijminus1, Aijplus1;
  L = anpi::Matrix<T>(m,n,0.0);
  
  size_t k = 0;
  for (size_t i = 0; i < m; ++i,++k){
    for (size_t j = 0; j < n; ++j){
      Aiplus1j = Aiminus1j = Aijminus1 = Aijplus1 = 0.0; 
      if (i != 0){
        Aiminus1j = A[i-1][j];
      }
      if (j != 0){
        Aijminus1 = A[i][j-1];
      }
      if (i != m){
        Aiplus1j = A[i+1][j];
      }
      if (j != n){
        Aijplus1 = A[i][j+1];
      }
      L[i][j] = (Aiplus1j + Aiminus1j + Aijplus1 + Aijminus1 - b[k] )/4;
    }
  
  }

    std::cout << "La matri LIebman" << std::endl;
    for (size_t i = 0; i < L.rows(); ++i){
        for (size_t j = 0;j < L.cols(); ++j){
            std::cout << L(i,j) << "\t";
        }
        std::cout << std::endl;
    }

}
} // namespace anpi

#endif
