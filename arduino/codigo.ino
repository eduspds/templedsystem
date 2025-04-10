#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "DHTesp.h"

// Credenciais Wi-Fi
const char* ssid = "Redmi Note 10";
const char* password = "nicholee8914000";

// Credenciais do Firebase
#define API_KEY "AIzaSyCiLX81O5YZVrhrkzRr8jgephcNFbbgAGY"
#define DATABASE_URL "https://monitortemp-2b4ff-default-rtdb.firebaseio.com/"  // use a URL do seu projeto

// Objeto Firebase
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Sensor DHT
DHTesp dht;
const int DHT_PIN = 18;  // GPIO14

// LEDs
const int LED_VERDE = 23;  // GPIO26
const int LED_VERMELHO = 22; // GPIO27

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  dht.setup(DHT_PIN, DHTesp::DHT11);

  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado ao Wi-Fi");

  // Configuração do Firebase
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  TempAndHumidity data = dht.getTempAndHumidity();
  float temperatura = data.temperature;
  float umidade = data.humidity;

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" °C  | Umidade: ");
  Serial.print(umidade);
  Serial.println(" %");

  // Controle dos LEDs com base na temperatura
  if (temperatura < 30.0) {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
  } else {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
  }

  // Enviando dados ao Firebase
  if (Firebase.ready()) {
    Firebase.RTDB.setFloat(&fbdo, "/sensor/temperatura", temperatura);
    Firebase.RTDB.setFloat(&fbdo, "/sensor/umidade", umidade);
    Firebase.RTDB.setString(&fbdo, "/sensor/statusLED", temperatura < 30.0 ? "verde" : "vermelho");
  }

  delay(2000);  // espera 2 segundos entre as leituras
}
