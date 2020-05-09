/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   db.h
 * Author: omarg
 *
 * Created on 7 de mayo de 2020, 23:40
 */

#ifndef DB_H
#define DB_H

#ifdef __cplusplus
extern "C" {
#endif

#define DBSERVER "10.0.2.15"
#define DBPORT 5432
#define DBNAME "psudb"
#define DBUSER "psu"
#define DBPASSWORD "Aguadulce1513"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <postgresql/libpq-fe.h>

    /**
     * Abre la conexion a la BDD
     * @param servidor
     * @param puerto
     * @param nombredb
     * @param usuario
     * @param password
     * @return 
     */
    PGconn* dbconnect(char* servidor, int puerto, char* nombredb, char* usuario, char* password);
    
    /**
     * Cierre la conexion a la BDD
     * @param conexion
     */
    void dbclose(PGconn* conexion);
    
    /**
     * Consultas a la bdd
     * @param conexion
     * @param consulta
     * @return resultado de la consulta
     */
    PGresult* dbquery(PGconn* conexion, char* consulta);

    /**
     * 
     * @param resultado
     * @return 
     */
    long dbnumrows(PGresult* resultado);
    
    /**
     * 
     * @param resultado
     * @param fila
     * @param columna
     * @return El valor correspondiente a fila/columna sobre set de resultado
     */
    char* dbresult(PGresult* resultado, int fila, int columna);
    /**
     * para liberar memoria
     * @param resultado
     */
    void dbfree(PGresult* resultado);
#ifdef __cplusplus
}
#endif

#endif /* DB_H */

