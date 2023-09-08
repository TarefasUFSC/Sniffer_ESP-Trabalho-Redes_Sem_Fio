#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "ESP-B_Carrinho";
const char *password = "";                // Se houver uma senha para o ponto de acesso, coloque-a aqui.
const IPAddress serverIP(192, 168, 4, 1); // IP do servidor ESP8266
const uint16_t serverPort = 80;           // Porta do servidor ESP8266

WiFiClient client;
void conecta(){
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
  // Seu código aqui
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("Enviando mensagem pro servidor...");
    // Enviar uma mensagem para o servidor
    client.println("Olá, servidor!");

    // Aguarde uma resposta (opcional)
    String response = "";
    while (client.available())
    {
      char dt = char(client.read());
      response += dt;
      Serial.print("dt");
    }
    
      Serial.println("");
    if (response.length() > 0)
    {
      Serial.println("Resposta do servidor:");
      Serial.println(response);
    }else {
      Serial.println("ERROR");
    }

    delay(5000); // Espere 5 segundos antes de enviar a próxima mensagem
  }else {
    Serial.println("NÃO CONECTADO");
    delay(1000);
    conecta();
  }
}