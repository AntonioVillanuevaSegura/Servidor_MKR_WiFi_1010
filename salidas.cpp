#include "salidas.h"
//**********************************************************************************************
void configura_salidas(){//Configura los PINs del 0-7 como salidas , gestion de LEDs o Reles
  
  for (uint8_t pin = 0;pin <=7; pin++) {
     pinMode(pin, OUTPUT);
  }

}
//**********************************************************************************************
