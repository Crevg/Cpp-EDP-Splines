/**
 * Copyright (C) 2018
 * Área Académica de Ingeniería en Computadoras, TEC, Costa Rica
 *
 * This file is part of the CE3102 Numerical Analysis lecture at TEC
 *
 * @Author: 
 * @Date  : 24.02.2018
 */

#include <cstdlib>
#include <iostream>
#include <boost/program_options.hpp>
namespace po = boost::program_options;

int main(int ac, char* av[])
{
  //declare vars
  int top, bot, left, right, hori, vert, grid;
  bool visualize, flow;
  bool i[4]= {true, true,true,true}; //aislar tblr;
  std::string fileName;
  //init vars 
  top = bot = left = right = 0;
  hori = vert = 50;
  grid = 5;
  flow = false;
  visualize = true;

  //def options
  po::options_description desc("Optiones");  
  desc.add_options()
            ("help", "produce help message" )
            ("t,t", po::value<int>(), "Indica temperatura en borde superior")
            ("b,b", po::value<int>(), "Indica temperatura en borde inferior")
            ("l,l", po::value<int>(), "Indica temperatura en borde izquierdo")
            ("d,d", po::value<int>(), "Indica temperatura en borde izquierdo")
            ("i,i", po::value<std::string>(), "Borde a aislar")
            ("p,p", po::value<std::string>(),"Nombre del archivo con el perfil término")
            ("h,h", po::value<int>(), "Pixeles horizontales")
            ("v,v", po::value<int>(), "Pixeles verticales")
            ("q,q", "Desactivar visualización")
            ("f,f", "Activa el cálculo de flujo de calor")
            ("g,g", po::value<int>(), "Tamaño de rejilla")
        ;
  try{
    po::variables_map map;
    po::store(po::parse_command_line(ac,av,desc), map);
    po::notify(map);
      
    if (map.count("help")) {
          std::cout << desc << "\n";
          return 0;
      }
    if (map.count("t")){
      top = map["t"].as<int>();
      i[0] = false;
    }
    if (map.count("b")){
      bot = map["b"].as<int>();
      i[1] = false;
    }
    if (map.count("l")){
      left = map["l"].as<int>();
      i[2] = false;
    }
    if (map.count("d")){
      right = map["d"].as<int>();
      i[3] = false;
    }

    if (map.count("h")){
      hori = map["h"].as<int>();
    }
    
    if (map.count("v")){
      vert = map["v"].as<int>();
    }

     if (map.count("g")){
      grid = map["g"].as<int>();
    }

    if (map.count("p")){
      fileName = map["p"].as<std::string>();
    }
    if (map.count("q")){
      visualize = false;
    }
    if (map.count("f")){
      flow = true;
    }
    if (map.count("i")){
      std::string aislados = map["i"].as<std::string>();
      size_t len = aislados.length();
      if (len == 0){
        std::cout << "Error: si indica la option -i debe indicar al menos 1 borde para aislar";
        std::cout << std::endl;
      }else{
        for (size_t j = 0; j < len; ++j){
          if (aislados[j] != 't' && aislados[j] != 'b' &&  aislados[j] != 'l' && aislados[j] != 'd'){
            std::cout << "Error: Borde invalido para aislar, debe ser 't', 'b', 'l' o 'd'" << std::endl;
            return -1;
          }
        }   // end for 
        if (aislados.find('t') != std::string::npos){
          i[0] = true;
        }
        if (aislados.find('b') != std::string::npos){
          i[1] = true;
        }
        if (aislados.find('l') != std::string::npos){
          i[2] = true;
        }
        if (aislados.find('d') != std::string::npos){
          i[3] = true;
        }                  
      } // end if else len == 0
    } // end maps i

  }catch(std::exception e){
    std::cout << "Invalid option" << std::endl;
    return -1;
  }
  std::cout << "T\tB\tL\tD" <<std::endl;
  std::cout << top << i[0] << "\t" << bot << i[1]<<"\t"<< left << i[2]<<"\t" << right<< i[3]<<"\t" << std::endl;

  std::cout << "Filename: " << fileName << std::endl;
  std::cout << "H \t V \t G" << std::endl;
  std::cout << hori << "\t" << vert << "\t" << grid << std::endl;
  std::cout << "Visu: " << visualize << "\nFlow: " << flow << std::endl;



    

  return 0;
}