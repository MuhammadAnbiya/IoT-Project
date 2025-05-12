#include "DHT.h"

#define DHTPIN      27
#define DHTTYPE     DHT11
#define BUZZER_PIN  14
#define RELAY_PIN   12
#define LED_MERAH   4
#define LED_HIJAU   2

DHT dht(DHTPIN, DHTTYPE);
float suhu, kelembapan;

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_MERAH, OUTPUT);
  pinMode(LED_HIJAU, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH); 
  digitalWrite(LED_MERAH, LOW);
  digitalWrite(LED_HIJAU, LOW);
  noTone(BUZZER_PIN);

}

void loop() {
  kelembapan = dht.readHumidity();
  suhu = dht.readTemperature();

  if (isnan(kelembapan) || isnan(suhu)) {
    Serial.println("[DHT11] Gagal membaca data!");
    return;
  }

  Serial.print("[DHT11] Suhu: ");
  Serial.print(suhu);
  Serial.print("°C | Kelembapan: ");
  Serial.print(kelembapan);
  Serial.println("%");

  if (suhu > 31) {
    tone(BUZZER_PIN, 1000);
    digitalWrite(RELAY_PIN, LOW);  // Kipas menyala
    digitalWrite(LED_MERAH, HIGH);
    digitalWrite(LED_HIJAU, LOW);
    Serial.println("[ALERT] Suhu tinggi! Kipas & Buzzer ON, LED Merah ON");
  } else {
    noTone(BUZZER_PIN);
    digitalWrite(RELAY_PIN, HIGH); // Kipas mati
    digitalWrite(LED_MERAH, LOW);
    digitalWrite(LED_HIJAU, HIGH);
    Serial.println("[INFO] Suhu normal. Kipas & Buzzer OFF, LED Hijau ON");
  }
  
  delay(2000);
}
