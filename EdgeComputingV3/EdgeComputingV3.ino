#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <ESP32Servo.h>

#define DHTPIN      27
#define DHTTYPE     DHT11
#define BUZZER_PIN  14
#define RELAY_PIN   12
#define LDR_PIN     35
#define MQ2_PIN     32
#define MQ7_PIN     33
#define MQ135_PIN   34
#define LED_MERAH   4
#define LED_HIJAU   2
#define SERVO_PIN   13

DHT dht(DHTPIN, DHTTYPE);
Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variabel global
float suhu, kelembapan;
int ldrVal, mq2Val, mq7Val, mq135Val;
bool servoAktif = true;

// === FUNGSI DHT11, Relay, Buzzer, dan LED ===
void cekSuhuKelembapan() {
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
}

// === FUNGSI LDR ===
void bacaLDR() {
  ldrVal = analogRead(LDR_PIN);
  Serial.print("[LDR] Nilai Cahaya: ");
  Serial.print(ldrVal);
  if (ldrVal < 1000) {
    Serial.println(" => Gelap");
  } else {
    Serial.println(" => Terang");
  }
}

// === FUNGSI MQ ===
void bacaMQ() {
  mq2Val = analogRead(MQ2_PIN);    // CH4
  mq7Val = analogRead(MQ7_PIN);    // CO
  mq135Val = analogRead(MQ135_PIN); // NH3

  Serial.print("[MQ2] CH4: ");
  Serial.println(mq2Val);
  Serial.print("[MQ7] CO: ");
  Serial.println(mq7Val);
  Serial.print("[MQ135] NH3: ");
  Serial.println(mq135Val);
}

// === FUNGSI SERVO ===
void bukaTutupServo() {
  Serial.println("[SERVO] Buka Pakan (0°)");
  myServo.write(0);
  delay(2000);
  Serial.println("[SERVO] Tutup Pakan (90°)");
  myServo.write(90);
  delay(2000);
}

// === TAMPILKAN DATA KE LCD ===
void tampilkanLCD() {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print((int)suhu);
  lcd.print((char)223);
  lcd.print(" H:");
  lcd.print((int)kelembapan);
  lcd.print("% L:");
  lcd.print(ldrVal);

  lcd.setCursor(0, 1);
  lcd.print("CH4:");
  lcd.print(mq2Val / 100);
  lcd.print(" CO:");
  lcd.print(mq7Val / 100);
  lcd.print(" NH:");
  lcd.print(mq135Val / 100);
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  myServo.attach(SERVO_PIN);

  Wire.begin(21, 22); // SDA, SCL
  lcd.init();
  lcd.backlight();

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_MERAH, OUTPUT);
  pinMode(LED_HIJAU, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH); // Kipas mati di awal
  digitalWrite(LED_MERAH, LOW);
  digitalWrite(LED_HIJAU, LOW);
  noTone(BUZZER_PIN);

  Serial.println("=== Sistem Monitoring Siap ===");
}

void loop() {
  Serial.println("\n======= Pembacaan Sensor =======");

  cekSuhuKelembapan();
  bacaLDR();
  bacaMQ();

  // === Atur Servo Berdasarkan Suhu ===
  if (suhu <= 31) {
    if (!servoAktif) {
      myServo.attach(SERVO_PIN);
      servoAktif = true;
      Serial.println("[INFO] Servo diaktifkan kembali");
    }
    bukaTutupServo();
  } else {
    if (servoAktif) {
      myServo.detach();  // Matikan kontrol servo saat suhu tinggi
      servoAktif = false;
      Serial.println("[INFO] Servo dinonaktifkan karena suhu tinggi");
    }
  }

  tampilkanLCD();
  Serial.println("======= Akhir Pembacaan =======\n");
  delay(2000);
}
