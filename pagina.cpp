/*
 * Pagina WeEB del servidor web Arduino, MKR WiFi 1010
 */
#include "pagina.h"
#include "salidas.h"
void paginaWeb(WiFiClient client){
    //Respuesta http al cliente
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  
  //Página web en formato HTML
  client.println("<html>");
  client.println("<head>");
  client.println("</head>");
  client.println("<body>");
  client.println("<h1 align='center'>ICARO</h1><h2 align='center'>Servidor web control salidas</h2>");

  //Crea botones .parametros se envian a traves de ?
  for (uint8_t pin=0;pin<N_SALIDAS;pin++){//Crea los elementos para Encender/Apagar los LEDS con los numeros
    client.println("<div style='text-align:center;'>");

    client.println("<button onClick=location.href=\"/"+String(pin)+"_ON"+"\" style='margin:auto;background-color: #24A807;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:200px;height: 80px;'>");
    client.println("<font size=\"+4\"> ");
    client.println("ON  "+String(pin));//Texto en boton
    client.println("</font>");    
    client.println("</button>");
    
    client.println("<button onClick=location.href=\"/"+String(pin)+"_OFF"+"\" style='margin:auto;background-color: #BA0B25;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:200px;height: 80px;'>");
    client.println("<font size=\"+4\"> ");
    client.println("OFF "+String(pin));//Texto en boton
    client.println("</font>");    
    client.println("</button>");
    
    client.println("<br /><br />");

    client.println("</b></body>");
    client.println("</html>");
    client.println();//FIN HTTP    
  }
  
//  break;
}
