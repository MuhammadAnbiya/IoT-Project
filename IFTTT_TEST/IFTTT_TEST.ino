#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define RELAY_PIN    23  // Relay terhubung ke pin 23 ESP32

#define WIFI_SSID    "anbi"
#define WIFI_PASS    "12345678"

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "muhammadanbiya"
#define AIO_KEY         ""

WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Ganti feed sesuai milikmu di dashboard
Adafruit_MQTT_Subscribe relayFeed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/fan_relay");

void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  Serial.print("Menghubungkan ke WiFi: ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Tersambung");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  mqtt.subscribe(&relayFeed);
}

void loop() {
  MQTT_connect();

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(1000))) {
    if (subscription == &relayFeed) {
      String value = (char *)relayFeed.lastread;
      Serial.print("Data diterima: ");
      Serial.println(value);

      if (value == "1") {
        digitalWrite(RELAY_PIN, LOW);
        Serial.println("Relay ON");
      } else {
        digitalWrite(RELAY_PIN, HIGH);
        Serial.println("Relay OFF");
      }
    }
  }
}

void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) return;

  Serial.print("Menghubungkan ke MQTT... ");
  uint8_t retries = 3;

  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Coba lagi dalam 5 detik...");
    mqtt.disconnect();
    delay(5000);
    retries--;
    if (retries == 0) {
      while (1);
    }
  }
  Serial.println("Terhubung ke MQTT!");
}
