/*
 * Parametros de configuracion
 */

//Si queremos que actue como un servidor WIFI independiente
//Si por el contrario queremos que se conecte a un router , poner en comentario //
#define SERVIDOR

//Actua como SERVIDOR wifi independiente 
#ifdef SERVIDOR

  //IP del servidor wifi , ip del navegador
  #define IP 192,168,6,1

  //Nombre y clave del servidor WIFI
  #define SECRET_SSID "icaro"
  #define SECRET_PASS "123456789"
  
#endif

//Se conecta aun ROUTER con SSID y PASSword 
#ifndef SERVIDOR
  //SSID y pasword  de la Box
  #define SECRET_SSID "Bbox-********"
  #define SECRET_PASS "**************"
#endif 

//Retardo para iniciar
#define RETARDO 1000
