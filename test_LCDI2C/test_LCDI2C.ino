#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // alamat, kolom, baris

// Lirik dan kecepatan (dalam milidetik per geseran)
String lyrics[7] = {
  "sudah terbiasa terjadi tanteee",
  "teman datang ketika lagi butuh sajaaa",
  "coba kalau lagi susah",
  "mereka semua menghilaaaaaaaaaaaaaaaaaang",
  "TANTEEEEEEEEEEEEEEEE",
  "TANTEEEEEEEEEEEEEEEE",
  "TANTEEEEEEEEEEEEEEEE",
};

int speeds[7] = {
  67, // 0.2 detik per geser
  60,
  65,
  70,
  70,
  70,
  70
};

void setup() {
  Wire.begin(21, 22);    // ESP32 SDA dan SCL
  lcd.begin(16, 2);      // Inisialisasi LCD
  lcd.backlight();       // Nyalakan backlight
  lcd.clear();
}

void loop() {
  for (int i = 0; i < 7; i++) {
    runText(lyrics[i], speeds[i]);
    delay(150);         // jeda antar lirik
    lcd.clear();
  }
}

void runText(String text, int speed) {
  text = "          " + text + "                  "; // padding spasi kanan-kiri

  for (int i = 0; i <= text.length() - 16; i++) {
    String segment = text.substring(i, i + 16);
    lcd.setCursor(0, 0);              // baris atas
    lcd.print(segment);               // tampilkan segmen
    delay(speed);                     // kecepatan scroll
  }
}
