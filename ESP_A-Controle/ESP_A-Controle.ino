#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "ESP-B_Carrinho";
const char *password = "";                // Se houver uma senha para o ponto de acesso, coloque-a aqui.
const IPAddress serverIP(192, 168, 4, 1); // IP do servidor ESP8266
const uint16_t serverPort = 80;           // Porta do servidor ESP8266

WiFiClient client;
void conecta()
{
  // Conectando-se ao WiFi
  Serial.print("Conectando-se a ");
  Serial.println(ssid);

  WiFi.begin(ssid);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
  delay(1000);
}

void setup()
{
  Serial.begin(9600);
  conecta();
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    if (client.connect(serverIP, serverPort))
    { // Estabelece conexão TCP
      Serial.println("Enviando mensagem pro servidor...");

      String request = ""; // Construir a solicitação HTTP

      char key = 0; // Tecla pressionada (inicialmente vazia)
      while (key == 0)
      {
        
        if (Serial.available() > 0)
        {
          key = Serial.read();
          
        }
        else{
          continue;
        }
        if(key == 10) {key = 0;continue;}

        if (key == 'w')
        {
          request = "w";
        }
        else if (key == 'a')
        {
          request = "a";
        }
        else if (key == 's')
        {
          request = "s";
        }
        else if (key == 'd')
        {
          request = "d";
        }
        else
        {
          Serial.print("INVALIDO CHAR = ");
          Serial.println((int)key);
          key = 0;
        }
      }

      if (!request.equals(""))
      {
        Serial.println("Enviando solicitação para o carrinho...");
        client.println(request);
        delay(1000); // Aguarde para garantir que a solicitação seja enviada completamente
      }

      String response = "";
      long timeout = millis() + 5000; // Define um timeout de 5 segundos
      while (millis() < timeout)
      {
        while (client.available())
        {
          char dt = char(client.read());
          response += dt;
        }
      }

      if (response.length() > 0)
      {
        Serial.println("Resposta do servidor:");
        Serial.println(response);
      }
      else
      {
        Serial.println("ERROR");
      }

      client.stop(); // Fecha a conexão TCP
    }

    delay(100); // Espere 10 segundos antes de enviar a próxima mensagem
  }
  else
  {
    Serial.println("NÃO CONECTADO");
    delay(1000);
    conecta();
  }
}