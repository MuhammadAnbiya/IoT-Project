#include <LiquidCrystal.h>
#include <DHT.h>

// Definisi pin LCD (sesuai koneksi)
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Definisi pin DHT11
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.begin(16, 2); // Inisialisasi LCD 16x2
  dht.begin(); // Inisialisasi DHT11
}

void loop() {
  float suhu = dht.readTemperature(); // Membaca suhu dari DHT11
  float kelembaban = dht.readHumidity(); // Membaca kelembaban

  if (isnan(suhu) || isnan(kelembaban)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Suhu: ");
    lcd.print(suhu);
    lcd.print(" C");

    lcd.setCursor(0, 1);
    lcd.print("Kelembaban: ");
    lcd.print(kelembaban);
    lcd.print(" %");
  }

  delay(2000); // Update setiap 2 detik
}
