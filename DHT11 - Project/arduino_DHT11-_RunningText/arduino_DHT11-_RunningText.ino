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
  float suhu = dht.readTemperature();  
  float kelembaban = dht.readHumidity();  

  if (isnan(suhu) || isnan(kelembaban)) {
    scrollText("Sensor Error!", 0);
  } else {
    String teks1 = "Suhu: " + String(suhu) + " C ";
    String teks2 = "Kelembaban: " + String(kelembaban) + " % ";
    String teks3 = "Kelompok 7";

    scrollText(teks1, 0); // Running text baris 1
    scrollText(teks2, 1); // Running text baris 2
    scrollText(teks3, 1); // Running text baris 2 setelah kelembaban
  }
}

// Fungsi untuk membuat teks berjalan
void scrollText(String text, int row) {
  for (int i = 0; i < text.length(); i++) {
    lcd.clear();
    lcd.setCursor(0, row);
    lcd.print(text.substring(i));  // Menampilkan bagian teks yang berjalan
    delay(300); // Kecepatan running text
  }
}
