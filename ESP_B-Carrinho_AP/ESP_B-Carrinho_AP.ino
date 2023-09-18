#include <ESP8266WiFi.h>

const char *ssid = "ESP-B_Carrinho";

// Defines a Port
WiFiServer server(80);
static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t D9   = 3;
static const uint8_t D10  = 1;
// Variáveis globais para controlar os LEDs
#define pinLEDUp  D1    // Pino para LED Up
#define pinLEDLeft  D2  // Pino para LED Left
#define pinLEDDown  D3  // Pino para LED Down
#define pinLEDRight  D4 // Pino para LED Right

void setup()
{
  Serial.begin(9600);

  // Configura o ESP8266 para operar apenas como um Access Point
  WiFi.mode(WIFI_AP);

  // Cria um Access Point sem senha
  WiFi.softAP(ssid);

  // Inicia o servidor na porta 80
  server.begin();

  // Inicialize os pinos dos LEDs como saídas
  pinMode(pinLEDUp, OUTPUT);
  pinMode(pinLEDLeft, OUTPUT);
  pinMode(pinLEDDown, OUTPUT);
  pinMode(pinLEDRight, OUTPUT);

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
    Serial.println("Recebi msg...");
    // Lê a mensagem enviada pelo cliente (direção)
    String direction = client.readStringUntil('\r');
    Serial.print("Mensagem recebida: ");
    Serial.println(direction);

    // Controla os LEDs com base na direção recebida
    if (direction[0] == 'w')
    {
      digitalWrite(pinLEDUp, HIGH); // Acenda o LED Up
      // Desligue outros LEDs (caso estivessem acesos)
      digitalWrite(pinLEDLeft, LOW);
      digitalWrite(pinLEDDown, LOW);
      digitalWrite(pinLEDRight, LOW);
    }
    else if (direction[0] == 'a')
    {
      digitalWrite(pinLEDLeft, HIGH); // Acenda o LED Left
      // Desligue outros LEDs (caso estivessem acesos)
      digitalWrite(pinLEDUp, LOW);
      digitalWrite(pinLEDDown, LOW);
      digitalWrite(pinLEDRight, LOW);
    }
    else if (direction[0] == 's')
    {
      digitalWrite(pinLEDDown, HIGH); // Acenda o LED Down
      // Desligue outros LEDs (caso estivessem acesos)
      digitalWrite(pinLEDUp, LOW);
      digitalWrite(pinLEDLeft, LOW);
      digitalWrite(pinLEDRight, LOW);
    }
    else if (direction[0] == 'd')
    {
      digitalWrite(pinLEDRight, HIGH); // Acenda o LED Right
      // Desligue outros LEDs (caso estivessem acesos)
      digitalWrite(pinLEDUp, LOW);
      digitalWrite(pinLEDLeft, LOW);
      digitalWrite(pinLEDDown, LOW);
    }
    // Fecha a conexão com o cliente
    client.println("HTTP/1.1 200 OK\n\n");
    
    client.flush();
    client.stop();
    Serial.println("Fechando Conexão");
  }
}
