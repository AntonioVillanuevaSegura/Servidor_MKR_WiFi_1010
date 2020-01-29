/*
 Antonio Villanueva Segura
 Servidor Wifi con activacion de PINs O Leds  tarjeta MKR WiFi 1010
 https://content.arduino.cc/assets/Pinout-MKRwifi1010_latest.png
 Crea un servidor Web , donde podemos activar diferentes LEDs 0-7 ,desde un
 navegador , por el puerto serie nos reporta informacion de la conexion
 https://www.iconshock.com/
 */

//Configuracion de este programa diversos parametros 
#include "configuracion.h"

#include <SPI.h>
#include <WiFiNINA.h>
#include "salidas.h" //Funciones para la gestion de las salida ,LEDs
#include "pagina.h" //Funciones para la gestion de las salida ,LEDs


//Recupera el nombre del servidor SSID y el password wifi
char ssid[] = SECRET_SSID;        // nombre servidor SSID
char pass[] = SECRET_PASS;    //  pasword (usado en WPA o llave key en WEP)
int keyIndex = 0;                // Numero de indice (key index) para tu red (solo en WEP)

//int led =  LED_BUILTIN;//LED en la tarjeta con direccion 13
int status = WL_IDLE_STATUS;
WiFiServer server(80);//Servidor en el puerto 80

//**********************************************************************************************

void setup() {
  //Inicializa y abre el puerto serie a 9600 bps
  Serial.begin(9600);
  while (!Serial) {//Eliminar si no queremos puerto serie 
    ;//Espera hasta que tengamos una conexion serie por el puerto USB 
  }

  Serial.println("Servidor Web -Access Point-");//Puerto serie

  //pinMode(led, OUTPUT);// Configura el modo de este PIN si es un LED como OUTPUT
  configura_salidas();//Configura los PINs del PRIMERO 13 al ULTIMO 9 como salidas
  //Test LED 13
  //pinMode(6, OUTPUT);
  //digitalWrite( 6,HIGH);//Activa LED
  
  //  Verifica el modulo Wifi 
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("La comunicacion con el modulo Wifi no funciona !");
    // No se continua
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Actualice el firmware WIFI a la ultima version S");
  }

  //Direccion IP por defecto ,recupera del #define IP=192.168.6.1
  WiFi.config(IPAddress(IP));

  // Imprime el nombre de la red  (SSID);
  Serial.print("Creando punto de acceso : ");
  Serial.println(ssid);

  //Creada open network .Cambiar esta linea si quieres crear una red WEP
  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING) {
    Serial.println("Error en la creacion del access point");
    // don't continue
    while (true);//Bucle infinito
  }

  // Espera X segundos antes de la conexion , 10000=10 segundos
  //delay(10000);
  delay(RETARDO);

  // Arranca el servidor web en el puerto 80
  server.begin();

  //Estas conectado imprime el status
  printWiFiStatus();
}

//**********************************************************************************************

void loop() {//Bucle principal 
  // COmpara el estado anterior con el actual 
  if (status != WiFi.status()) {
    //Si ha cambiado , actualizamos la variable estado 
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) {
      // Dispositivo conectado al access point AP 
      Serial.println("Dispositivo conectado al AP");
    } else {
      // Dispositivo desconectado del AP ,volvemos al modo escucha 
      Serial.println("Dispositivo desconectado del AP");
    }
  }
 
  WiFiClient client = server.available();   // Espera clientes disponibles 

  if (client) {                             // Si hay un nuevo cliente
    Serial.println("Nuevo cliente");        // imprime mensaje por el puerto serie 
    String currentLine = "";                // Crea una cadena  String para guardar los datos del cliente 
    while (client.connected()) {            // Queda en bucle mientras el cliente este conectado 
      if (client.available()) {             // Hay cliente ,datos , bytes para leer del cliente ? 
        char c = client.read();             // Entonces leemos un dato un caracter char
        //Serial.write(c);                    // imprime en el puerto serie el dato leido
        if (c == '\n') {                    // ha llegado al final?,fin de linea \n ?
          //Si la linea esta vacia , "blanca", obtenemos dos caractares en una linea
          //Es el final de la solicitud HTTP del cliente , entonces enviamos una respuesta
          
          if (currentLine.length() == 0) {
            //Las cabeceras HTTP siempre empiezan con un codigo de respuesta 
            // p.e (HTTP/1.1 200 OK) +tipo de contenido +una linea en blanco
            paginaWeb(client);
/*
            client.println("HTTP/1.1 200 OK");//INICIO HTTP
            client.println("Content-type:text/html");
            client.println();
            client.println ("ACTIVE O DESACTIVE EL LED <br>");
            
            for (uint8_t pin=0;pin<=7;pin++){//Crea los elementos para Encender/Apagar los LEDS con los numeros
              client.print ("PIN = "+String(pin)+"<br>");

              //Tests 
              //http://diymakers.es/crear-servidor-web-con-arduino/
              //client.println("<button onClick=location.href='./?LED=ON\' style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:65px;'>");
              
              client.print("<font size=7> Enciende LED"+String(pin)+" <a href=\"/"+String(pin)+"_ON"+"\">AQUI</a> LED ON<br></font>");
              client.print("<font size=7> Apaga LED"+String(pin)+" <a href=\"/"+String(pin)+"_OFF"+"\">AQUI</a> LED OFF<br></font>");
            }

            //La respuesta HTTP termina con otra linea en blanco
            client.println();//FIN HTTP
*/
            break;// Salir del bucle que muestra la pagina web
          }else {
            currentLine = "";//Si tenemos nueva linea \n ,limpiamos la linea actual currentLine 
          }
        }
        else if (c != '\r') {    // Si tenemos agun caracter diferente al retorno de carro '\r'
          currentLine += c;      // Escribe el nuevo caracter(char) la linea corriente ,currentLine
        }

        //------------------------------------------------------------------------------------------------------------------------
        //Miramos si la solicitud del cliente , en la linea corriente del navegador, termina con "LED0_ENCENDIDO" o "LED0_APAGADO" 
        //https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Referer
        //if(content.indexOf("Teststring") > 0)
        if(currentLine.endsWith("_ON") && currentLine.indexOf("http")<0) {//Si esta encendido y la linea no contiene informacion http
            Serial.println("LINEA On ORG = "+currentLine); 
            currentLine.remove (currentLine.indexOf('_'));//Busca caracter _ en la linea ,elimina el resto
            currentLine.remove (0,currentLine.indexOf('/')+1);//Busca caracter / en la linea ,elimina el resto            
            //currentLine+='\n';
            Serial.println("LINEA On elimina _ = "+currentLine); 
            Serial.println("Conversion pin = "+String (currentLine.toInt()));             
            digitalWrite( currentLine.toInt(),HIGH);//Activa LED
            currentLine="";//Limpia la linea .
  
          
        }
        if(currentLine.endsWith("_OFF")&& currentLine.indexOf("http")<0){//Esta apagado
            Serial.println("LINEA Off org= "+currentLine); 
            currentLine.remove (currentLine.indexOf('_'));//Busca caracter _ en la linea ,elimina el resto  
            currentLine.remove (0,currentLine.indexOf('/')+1);//Busca caracter / en la linea ,elimina el resto              
            //currentLine+='\n';            
            Serial.println("LINEA Off elimina _= "+currentLine);                    
            digitalWrite( currentLine.toInt(),LOW);//Apaga LED 
            currentLine="";//Limpia la linea .        
        }
        
        //------------------------------------------------------------------------------------------------------------------------        
      }
    }
    // Cerrar la conexion
    client.stop();
    Serial.println("cliente desconectado");
  }
}

//**********************************************************************************************

void printWiFiStatus() {
  //Muestra ,  por el puerto serie  la SSID de la red , donde nos conectamos
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // Muestra la IP en la Wifi
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // Muestra la IP donde debe conectarse el navegador 
  Serial.print(" Para ver esta pagina en accion abrir en un navegador esta direccion http://");
  Serial.println(ip);

}
