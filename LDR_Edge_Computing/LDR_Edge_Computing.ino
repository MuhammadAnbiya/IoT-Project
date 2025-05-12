#include <Arduino.h>

int ldrPin = 34;  // LDR dihubungkan ke pin GPIO34 (A0)
unsigned long startTime;  // Variabel untuk menyimpan waktu mulai
const unsigned long duration = 30000;  // Durasi 2 menit (120.000 ms)

void setup() {
  Serial.begin(115200);
  pinMode(ldrPin, INPUT);
  startTime = millis();  // Simpan waktu mulai
}

void loop() {
  unsigned long currentTime = millis();  // Waktu sekarang dalam milidetik
  int ldrValue = analogRead(ldrPin);  // Membaca nilai analog dari LDR
  Serial.println(ldrValue);  // Menampilkan nilai LDR di serial monitor

  // Cek apakah sudah lebih dari 2 menit
  if (currentTime - startTime >= duration) {
    Serial.println("Pengambilan data selesai.");
    while (true);  // Hentikan program setelah 2 menit
  }

  delay(100);  // Tunggu 1 detik sebelum membaca lagi
}
