/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: omarg
 *
 * Created on 2 de mayo de 2020, 21:28
 */

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "db.h"
#include <string.h>
#include <sstream>
#include <time.h>

using namespace std;

void cleanTable();
void populateTable();
void ponderar();
void Integrantes();

int main()
{
  ponderar();
  Integrantes();
  return 0;
}

//función de practica
void cleanTable(){
    
    string linea;
    linea = "TRUNCATE TABLE puntajes CASCADE;";
//    linea = "BEGIN TRANSACTION;                     "
//            "DROP TABLE IF EXISTS puntajes CASCADE; "
//            "CREATE TABLE puntajes(                 "
//            "pk bigserial NOT NULL,                 "
//            "rut int NOT NULL,                      "
//            "nem int NOT NULL,                      "
//            "ranking int NOT NULL,                  "
//            "matematica int NOT NULL,               "
//            "lenguaje int NOT NULL,                 "
//            "ciencia int NOT NULL,                  "
//            "historia int NOT NULL,                 "
//            "UNIQUE	 (rut),                     "
//            "PRIMARY KEY (pk)                       "
//            ");                                     ";
    PGconn* conexion = dbconnect((char *)DBSERVER,DBPORT,(char *)DBNAME,(char *)DBUSER,(char *)DBPASSWORD);
    PGresult* resultado = dbquery(conexion, (char *)linea.c_str());
    dbfree(resultado);
    dbclose(conexion);
    cout<<"La BDD ha sido limpiada \n";
}

//función de practica
void populateTable(){
    //ofstream file;
  //file.open("archivo.csv");
  cleanTable();
  cout<<"Generando datos, esto puede tomar más de 20 minutos. \n";
  for(int i=14000000; i<=19648406;i++){
  	int NEM= 475 + rand() %276;
  	int RKN= 475 + rand() %276;
  	int MAT= 475 + rand() %276;
  	int LEN= 475 + rand() %276;
  	int CIE= 475 + rand() %276;
        int HIS= 475 + rand() %276;
        string linea;
    
  	linea = "INSERT INTO puntajes (rut, nem, ranking, matematica, lenguaje, ciencia, historia) VALUES ('" + to_string(i) + "','" + to_string(NEM) + "','" + to_string(RKN) + "','" + to_string(MAT) + "','" + to_string(LEN) + "','" + to_string(CIE) + "','" + to_string(HIS) + "');";

        PGconn* conexion = dbconnect((char *)DBSERVER,DBPORT,(char *)DBNAME,(char *)DBUSER,(char *)DBPASSWORD);
        
        PGresult* resultado = dbquery(conexion, (char *)linea.c_str());
        dbfree(resultado);
        dbclose(conexion);
        
  }
  cout<<"Los datos han sido generados satisfactoriamente. \n";
  //file.close();
}

void ponderar(){
    
    clock_t inicio, fin;
    double duracion;
    cout<<"Ponderando puntajes \n";
    inicio = clock();
    ofstream ponderado;
    ponderado.open("ponderado.csv");
    PGconn* conexion = dbconnect((char *)DBSERVER,DBPORT,(char *)DBNAME,(char *)DBUSER,(char *)DBPASSWORD);
    string linea = "select rut, round((nem+ranking+matematica+lenguaje+ciencias+historia)/6.0,2) as ponderado from puntajes;";  
    PGresult* resultado = dbquery(conexion, (char *)linea.c_str());
    long filas = dbnumrows(resultado); 
    cout<<"Total de personas: "<<filas <<" personas"<<"\n";
    for(int i = 0; i<filas;i++){
        string rut = dbresult(resultado,i,0);
        string pond = dbresult(resultado,i,1);
        ponderado<<rut<<";"<<pond<<"\n";
    }
    fin = clock();
    duracion = (double)(fin-inicio)/CLOCKS_PER_SEC;
    //cout<<PQgetvalue(resultado,0,1)<<"\n";
    cout<<"Operacion finalizada en: "<< duracion <<" segundos \n";
    ponderado.close();
    dbfree(resultado);
    dbclose(conexion);
}

void Integrantes(){
    cout<<"Tarea 2 desarrollada por \n"<<"- Omar Gutiérrez \n"<<"- Gina Garrido \n"<<"- Abraham Aguilera \n";
}



