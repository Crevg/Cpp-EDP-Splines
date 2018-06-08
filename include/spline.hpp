#include <cmath>
#include <limits>
#include <functional>
#include <iostream>
#include <algorithm>

#include "Exception.hpp"
#include "Matrix.hpp"

#ifndef ANPI_SPLINE
#define ANPI_SPLINE

namespace anpi
{

template <typename T>
void spline(const std::vector<T> &v, std::vector<T> &sol, std::vector<T> &x)
{
    int n = v.size() - 1;
    x = std::vector<T> (4*n,0);

    std::cout << "n: " << n << std::endl;
    anpi::Matrix<T> A = anpi::Matrix<T>(4*(n),4*(n), 0.0);

    //se ocupan 4n ecuaciones 

    /* Las primeras dos vienen de los casos extremos f0(0) = d1 = v[0]
     *  y fn(n) = an*n³ + bn*n² + cn*n + dn = v[n]
     * */

   //f0(0)
    // A(0,3) = 1; // es trivial no se pone en la matriz

    x[3] = v[0]; // trivial d1


    //fn(n)

    A(1,4*n-1) = 1; //dn
    A(1,4*n-2) = n; //cn
    A(1,4*n-3) = n*n; //bn
    A(1,4*n-4) = n*n*n; //an
    sol.push_back(v[n]);

    /* las siguientes dos son dos casos arbitrarios escogidos
     * la solución de la segunda derivada en los extremos
     * es 0.
     * */

    //f0''(0) = 0 = 2b1
    //A(2, 1) = 2; //es trivial no se pone en la matriz

    x[1] = 0; // trivial b1 = 0

    // fn''(n) = 0 = 6*an*n + 2*bn
    //A(3, 4*n-4) = 6*n; 
    //A(3, 4*n-3) = 2; //es trivial bn = -9an
    //sol.push_back(0);

    /* En todos los nodos intermedios, las soluciones deben ser iguales 
     * tanto en la función de la izquierda como en la función de la derecha 
     * salen 2n-2 ecuaciones */
    size_t k = 4;
    for (size_t i = 1; i < n; ++i, k+=2){
        // fi-1(i) =  fi(i) = ax³ + bx² + cx + d
        A(k, 4*(i-1))   =  A(k+1, 4*(i))    = i*i*i; //a
        A(k, 4*(i-1)+1) =  A(k+1, 4*(i) +1) = i*i; //b
        A(k, 4*(i-1)+2) =  A(k+1, 4*(i) +2) = i; //c
        A(k, 4*(i-1)+3) =  A(k+1, 4*(i) +3) = 1; //d
        sol.push_back(v[i]);
        sol.push_back(v[i]);
    }

    /*
     * Las siguientes n-1 ecuaciones vienen igual que las anteriores 
     * de igualdad en los nodos pero esta vez con las derivadas
     * de las funciones
     * */

    for (int i = 1; i < n; ++i, ++k){
        // fi-1'(i) =  fi'(i) = 3x²a + 2xb + c
        A(k, 4*(i-1))   = 3*i*i;
        A(k, 4*(i))     = -3*i*i; //ai
        A(k, 4*(i-1)+1) = 2*i;
        A(k, 4*(i) +1)  = -2*i; //bi
        A(k, 4*(i-1)+2) = 1;
        A(k, 4*(i) +2)  = -1; //ci
        if (i == n){
            A(k, 4*i) -= 9* A(k, 4*(i) +1) ;
        }
        sol.push_back(0);
        sol.push_back(0);
    }

    /*
     * Las siguientes n-1 ecuaciones vienen igual que las anteriores 
     * de igualdad en los nodos pero esta vez con las segundas derivadas
     * de las funciones
     * */

    for (int i = 1; i < n; ++i, ++k){
        // fi-1''(i) =  fi''(i) = 6xa + 2b + c
        A(k, 4*(i-1))   = 6*i; 
        A(k, 4*(i))     = -6*i; //ai
        std::cout << -6*i << std::endl;
        A(k, 4*(i-1)+1) = 2;
        A(k, 4*(i) +1)  = -2; //bi
        if (i == n){
            A(k, 4*i) -= 9*A(k, 4*(i) +1);
        }
        sol.push_back(0);
        sol.push_back(0);
    }
    

    //trivial bn = -9n
    for (int i = 0; i < 4*n; ++i){
        A(i, 4*n-4) -= 9*A(i,4*n-3);
     }

    anpi::Matrix<T> B = anpi::Matrix<T>(A.rows()-3, A.cols()-3, 0.0);
    
    for (size_t i = 0, k = 0; i < A.rows(); ++i){
        if (i != 0 && i != 2 && i != 3){
            for(size_t j = 0, l = 0; j <A.cols(); ++j){
                if (j!= 1 && j!= 3 && j!=A.cols()-3){
                    B(k,l) = A(i,j);
                    ++l;
                }
            }
            ++k; 
        } // end if
    }

    for (size_t i = 0; i < B.rows(); ++i){
        for (size_t j = 0; j < B.cols(); ++j){
            std::cout << B(i,j) << "\t";
        }
        std::cout << "---" << sol[i] << std::endl;
    }
}

} // namespace anpi

#endif
