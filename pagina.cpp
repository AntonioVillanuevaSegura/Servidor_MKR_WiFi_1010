/*
 * Pagina WeEB del servidor web Arduino, MKR WiFi 1010
 */
#include "pagina.h"
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
  client.println("<h1 align='center'>ICARO</h1><h3 align='center'>Servidor web control salidas</h3>");

  //client.print("<font size=7> Enciende LED"+String(pin)+" <a href=\"/"+String(pin)+"_ON"+"\">AQUI</a> LED ON<br></font>");
  //client.print("<font size=7> Apaga LED"+String(pin)+" <a href=\"/"+String(pin)+"_OFF"+"\">AQUI</a> LED OFF<br></font>");

  //Crea botones .parametros se envian a traves de ?
  for (uint8_t pin=0;pin<=7;pin++){//Crea los elementos para Encender/Apagar los LEDS con los numeros
    client.println("<div style='text-align:center;'>");

    client.println("<button onClick=location.href=\"/"+String(pin)+"_ON"+"\" style='margin:auto;background-color: #24A807;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:65px;'>");
    client.println("ON "+String(pin));//Texto en boton
    client.println("</button>");
    
    client.println("<button onClick=location.href=\"/"+String(pin)+"_OFF"+"\" style='margin:auto;background-color: #BA0B25;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:65px;'>");
    client.println("OFF "+String(pin));//Texto en boton
    client.println("</button>");
    
    client.println("<br /><br />");
    
    //client.println("<b>LED = ");
    //client.println("</b><br />");
    client.println("</b></body>");
    client.println("</html>");
    client.println();//FIN HTTP    
  }
  
//  break;
}