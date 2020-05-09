/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "db.h"

PGconn* dbconnect(char* servidor, int puerto, char* nombredb, char* usuario, char* password){
    PGconn* conexion = NULL;
    
    char* uri=(char*) calloc(255,sizeof(char));
    snprintf(uri,250,"host='%s' port='%d' dbname='%s' user='%s' password='%s'", servidor, puerto, nombredb, usuario, password);
    conexion=PQconnectdb(uri);
    if(PQstatus(conexion) == CONNECTION_BAD){
        fprintf(stderr,"\n Error al conectar al servidor: %s", PQerrorMessage(conexion));
        conexion = NULL;
    }
    
    return conexion;
}

void dbclose(PGconn* conexion){
    PQfinish(conexion);
}

void dbfree(PGresult* resultado){
    PQclear(resultado);
}

PGresult* dbquery(PGconn* conexion, char* consulta){
       
    return PQexec(conexion, consulta);
}


long dbnumrows(PGresult* resultado){
    long cantidad=0;
    char* tuplas = NULL;
    if(resultado != NULL){
        tuplas= PQcmdTuples(resultado);
        cantidad = atol(tuplas);
    }
    return cantidad;
}

char* dbresult(PGresult* resultado, int fila, int columna){
    char* valor = NULL;
    if(resultado != NULL){
        valor=PQgetvalue(resultado, fila, columna);
    }
    return valor;
}