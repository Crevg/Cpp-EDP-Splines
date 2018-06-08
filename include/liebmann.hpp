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
#include <omp.h>
#include "Exception.hpp"
#include "Matrix.hpp"
#include "SolveLU.hpp"

#ifndef ANPI_LIEBMANN
#define ANPI_LIEBMANN

namespace anpi
{


template <typename T>
void liebmann(const Matrix<T> &A,
              Matrix<T> &L, std::vector<T> b)
{
    unsigned t1, t2;

    t1=clock();

  size_t m = A.rows();
  size_t n = A.cols();
  T Aiplus1j, Aiminus1j, Aijminus1, Aijplus1;
  L = anpi::Matrix<T>(m, n, 0.0);
  anpi::Matrix<T> Atmp = A;
  T eps = std::numeric_limits<T>::epsilon();
  T maxi = std::numeric_limits<T>::max();
  size_t iter = 0;
  size_t i, j, k;

  while (iter < maxi)
  {
    k = 0;
    for (i = 0; i < m; ++i, ++k)
    {
      for (j = 0; j < n; ++j)
      {
        Aiplus1j = Aiminus1j = Aijminus1 = Aijplus1 = 0.0;
        if (i != 0)
        {
          Aiminus1j = L[i - 1][j];
        }
        if (j != 0)
        {
          Aijminus1 = L[i][j - 1];
        }
        if (i != m)
        {
          Aiplus1j = L[i + 1][j];
        }
        if (j != n)
        {
          Aijplus1 = L[i][j + 1];
        }
        L[i][j] = (Aiplus1j + Aiminus1j + Aijplus1 + Aijminus1 - b[k]) / 4;
      }
    }
    if (abs(Atmp(2, 3) - L(2, 3)) <= eps)
    {
      break;
    }
    Atmp = L;
    /*
    std::cout << "La matri Liebman" << std::endl;
    for (size_t i = 0; i < L.rows(); ++i){
        for (size_t j = 0;j < L.cols(); ++j){
            std::cout << L(i,j) << "\t";
        }
        std::cout << std::endl;
    }*/
    ++iter;
  }
  /*std::cout << "Num: " << iter << std::endl;

  std::cout << "La matri Liebman" << std::endl;
  for (size_t i = 0; i < L.rows(); ++i)
  {
    for (size_t j = 0; j < L.cols(); ++j)
    {
      std::cout << L(i, j) << "\t";
    }
    std::cout << std::endl;
  }
*/
  std::cout << "El LU:" << std::endl;
  std::vector<T> x;
  t2=clock();
  double time = (double(t2-t1)/CLOCKS_PER_SEC);
  std::cout << "Tiempo Jacobi: " << time << "\n" << std::endl;

  //anpi::solveLU(L, x, b);
  // for (int i = 0; i < x.size(); ++i){
  //   std::cout << x[i] << "\t";
  // }
  // std::cout << "\n";


}

} // namespace anpi

#endif
