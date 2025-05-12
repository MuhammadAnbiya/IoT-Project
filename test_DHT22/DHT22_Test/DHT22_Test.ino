//#include "DHT.h"
//
//#define DHTPIN 27        // Gunakan GPIO 27
//#define DHTTYPE DHT22    // Tipe sensor
//
//DHT dht(DHTPIN, DHTTYPE);
//
//void setup() {
//  Serial.begin(115200);
//  Serial.println("Mulai membaca sensor DHT22...");
//  dht.begin();
//}
//
//void loop() {
//  delay(2000);  // Baca setiap 2 detik (maksimal kecepatan sensor)
//
//  float h = dht.readHumidity();
//  float t = dht.readTemperature();
//
//  if (isnan(h) || isnan(t)) {
//    Serial.println("Gagal membaca dari sensor DHT22!");
//    return;
//  }
//
//  Serial.print("Suhu: ");
//  Serial.print(t);
//  Serial.print("°C  |  Kelembapan: ");
//  Serial.print(h);
//  Serial.println("%");
//}


#include "DHT.h"
#define DHTPIN 4         // Ubah ke pin yang kamu pakai
#define DHTTYPE DHT11    // GANTI dengan DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Gagal membaca dari sensor DHT22!");
  } else {
    Serial.print("Suhu: ");
    Serial.print(t);
    Serial.print("°C  |  Kelembapan: ");
    Serial.print(h);
    Serial.println("%");
  }

  delay(2000); // DHT22 hanya support 0.5 Hz (2 detik sekali)
}
