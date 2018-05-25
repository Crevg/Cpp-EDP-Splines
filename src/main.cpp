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
#include <fstream>
#include <iostream>
#include <boost/program_options.hpp>
#include <string>
namespace po = boost::program_options;

std::string findEdge(std::string line){
      if (line == "top"){
        return "t";
      }else if (line == "bottom"){
        return "b";
      }else if (line == "left"){
        return "l";
      }else if(line == "right"){
        return "d";
      }else{
        return "";
      }
}

int main(int ac, char* av[])
{
  /**************DECLARA E INICIALIZA LAS VARIABLES *****************/
  int topMin, botMin, leftMin, rightMin, topMax, botMax, leftMax, rightMax, hori, vert, grid;
  bool visualize, flow;
  bool i[4]= {true, true,true,true}; //aislar tblr;
  std::string fileName;

  topMin = botMin = leftMin = rightMin = topMax = botMax = leftMax = rightMax = 0;
  hori = vert = 50;
  grid = 5;
  flow = false;
  visualize = true;

  std::string line, borde;
  borde == "";
  size_t valueMin;
  size_t valueMax;
  std::vector<size_t> values;
  bool notEOF = true;
  std::ifstream inFile;

  /***************DEFINE LAS OPCIONES *********************************/
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
            ("g,g", po::value<int>(), "Tamaño de rejilla");
  po::variables_map map;
  try{
    po::store(po::parse_command_line(ac,av,desc), map);
    po::notify(map);
  }catch(std::exception e){
    std::cerr << "Opción inválida o repetida" << std::endl;
    return -1;
  }

  /******************COMIENZA A INTERPRETAR LOS COMANDOS *************************/
  if (map.count("help")) {
        std::cout << desc << "\n";
        return 0;
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

  /************LEE EL ARCHIVO**********************/

  inFile.open(fileName);
  if (!inFile){
    std::cerr << "No se puede abrir el archivo" << std::endl;
    return -1;
  }
  

  /****ENCUENTRA EL PRIMER BORDE *****/
  if (inFile >> line){
    borde = findEdge(line);
    if (borde == ""){
      std::cerr << "Debe indicar un borde válido" << std::endl;
      return -1;
    }
    std::cout << line << std::endl;
  }else{
    std::cerr << "El archivo está vacío" << std::endl;
    return -1;
  }

 
  /****ENCUENTRA LOS VALORES DE TEMPERATURA PARA TODOS LOS BORDES */ 
  do{
    if (!(inFile >> line)){
      notEOF = false;
      line = "EOF";
    }
    std::cout << line << std::endl;
    try{
      valueMax = std::stoi(line);
      if (borde == ""){ 
        std::cerr << "Debe indicar un borde válido" << std::endl;
        return -1;
      }
      values.push_back(valueMax);
    }catch(std::exception e){
      if (values.size() == 0){ //no se indico temp para el borde (error)
        std::cerr << "Debe indicar al menos 1 valor de temperatura para el borde" << std::endl;
        return -1;
      }else if(values.size() == 1){ // solo un valor de temp dado (dos iguales)
        valueMin = valueMax = values[0];
      }else if (values.size() == 2){ //dos valores dados (ordenar min y max)
        if (values[0] > values[1]){
          valueMin = values[1];
          valueMax = values[0];
        }else{
          valueMin = values[0];
          valueMax = values[1];
        }
      }else{ //values.size() > 2  osea se indicaron mas de dos (interpolación)
          std::cout << "HACER INTERPOLACIÓN" << std::endl;        
          /* lineas para evitar warnings borrar al hacer interpolacion */ 
          valueMin = values[0];
          valueMax = values[1];
      }
      /*setear los valores a los bordes */
      if (borde == "t"){
        topMin = valueMin;
        topMax = valueMax;
        i[0] = false;
      }else if (borde == "b"){
        botMin = valueMin;
        botMax = valueMax;
        i[1] = false;
      }else if (borde == "l"){
        leftMin = valueMin;
        leftMax = valueMax;
        i[2] = false;
      }else if (borde == "d"){
        rightMin = valueMin;
        rightMax = valueMax;
        i[3] = false;
      }else{
        std::cerr << "ocurrio un error inesperado" << std::endl;
        return -1;
      }
      values.clear();
      if (!notEOF){
        break;
      }
      borde = findEdge(line);      
    }//end catch
  }while (notEOF); //end while 
  inFile.close();

  /****************ULTIMA LINEA DEL ARCHIVO ***********************/
  


/***************TERMINA DE INTERPRETAR LOS COMANDOS QUE DEPENDEN DE TEMPERATURA***********/

  if (map.count("t")){
    topMax = topMin = map["t"].as<int>();
    i[0] = false;
  }
  if (map.count("b")){
    botMax = botMin = map["b"].as<int>();
    i[1] = false;
  }
  if (map.count("l")){
    leftMax = leftMin = map["l"].as<int>();
    i[2] = false;
  }
  if (map.count("d")){
    rightMax = rightMin = map["d"].as<int>();
    i[3] = false;
  }
  if (map.count("i")){
    std::string aislados = map["i"].as<std::string>();
    size_t len = aislados.length();
    if (len == 0){
      std::cerr << "Error: si indica la option -i debe indicar al menos 1 borde para aislar" << std::endl;
    }else{
      for (size_t j = 0; j < len; ++j){
        if (aislados[j] != 't' && aislados[j] != 'b' &&  aislados[j] != 'l' && aislados[j] != 'd'){
          std::cerr << "Error: Borde invalido para aislar, debe ser 't', 'b', 'l' o 'd'" << std::endl;
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




  //MOSTRAR VARIABLES PARA PRUEBAS
  
  
  std::cout << "Tm\tTM\tBm\tBM\tLm\tLM\tDm\tDM" <<std::endl;
  std::cout << topMin <<"\t"<< topMax << "\t" << botMin <<"\t"<< botMax<<"\t"<< leftMin <<
              "\t"<< leftMax <<"\t" << rightMin<<"\t" <<  rightMax << std::endl;

  std::cout << "Filename: " << fileName << std::endl;
  std::cout << "H \t V \t G" << std::endl;
  std::cout << hori << "\t" << vert << "\t" << grid << std::endl;
  std::cout << "Visu: " << visualize << "\nFlow: " << flow << std::endl;
  std::cout << "Aislamiento: " << std::endl;
  std::cout << "\tTop: " << i[0] << std::endl;  
  std::cout << "\tBot: " << i[1] << std::endl;
  std::cout << "\tLeft: " << i[2] << std::endl;
  std::cout << "\tRight: " << i[3] << std::endl;
  
  


    

  return 0;
}