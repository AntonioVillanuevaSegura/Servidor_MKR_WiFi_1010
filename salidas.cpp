#include "salidas.h"
//**********************************************************************************************
void configura_salidas(uint8_t primero,uint8_t ultimo){//Configura los PINs como salidas
  
  if (primero<ultimo){//SWAP si primero es menor a ultimo
    int tmp=primero;
    primero=ultimo;
    ultimo=tmp;
  }

  for (uint8_t  pins=primero;pins>=ultimo;ultimo--){
    pinMode(pins, OUTPUT);// Configura el modo de este PIN si es un LED como OUTPUT    
  }
}
//**********************************************************************************************
