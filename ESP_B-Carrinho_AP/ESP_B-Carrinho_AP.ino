#include <ESP8266WiFi.h>

const char *ssid = "ESP-B_Carrinho";

// Defines a Port
WiFiServer server(80);

void setup()
{
  Serial.begin(9600);

  // Configura o ESP8266 para operar apenas como um Access Point
  WiFi.mode(WIFI_AP);

  // Cria um Access Point sem senha
  WiFi.softAP(ssid);

  // Inicia o servidor na porta 80
  server.begin();

  Serial.println("AP iniciado");
  Serial.print("Endereço IP do AP: ");
  Serial.println(WiFi.softAPIP());
}

void loop()
{
  // Verifica se há algum cliente tentando se conectar
  WiFiClient client = server.available();

  if (client)
  {
    Serial.println("Cliente conectado!");

    // Aguarda até que o cliente envie algum dado
    while (!client.available())
    {
      delay(1);
    }

    // Lê a mensagem enviada pelo cliente
    String message = client.readStringUntil('\r');
    Serial.print("Mensagem recebida: ");
    Serial.println(message);

    // Fecha a conexão com o cliente
    client.println("HTTP/1.1 200 OK\n\n");
    
    client.flush();
    client.stop();
    Serial.println("Fechando Conexão");
  }
}
