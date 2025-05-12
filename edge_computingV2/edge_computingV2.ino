#include <Wire.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#include <BH1750.h>
#include <ESP32Servo.h>

// ==== PIN SETUP ====
#define LED_MERAH 25
#define LED_HIJAU 26
#define BUZZER    27
#define DHTPIN    15
#define DHTTYPE   DHT22
#define SERVO_PIN 13
#define RELAY_PIN 33

#define MQ2_PIN   34
#define MQ135_PIN 35
#define MQ7_PIN   32

DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter;
Servo myservo;
LiquidCrystal lcd(2, 4, 5, 18, 19, 21);

// === Variabel waktu ===
unsigned long previousRelayMillis = 0;
unsigned long previousBuzzerMillis = 0;
unsigned long previousServoMillis = 0;
const unsigned long relayInterval = 5000;
const unsigned long buzzerInterval = 3000;
const unsigned long servoDelay = 10; // lebih cepat

bool relayState = false;
bool servoForward = true;
int servoAngle = 0;

void setup() {
  Serial.begin(115200);

  pinMode(LED_MERAH, OUTPUT);
  pinMode(LED_HIJAU, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  pinMode(MQ2_PIN, INPUT);
  pinMode(MQ135_PIN, INPUT);
  pinMode(MQ7_PIN, INPUT);

  dht.begin();
  Wire.begin();
  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
  myservo.attach(SERVO_PIN);
  lcd.begin(16, 2);

  Serial.println("Semua komponen siap...");
}

void loop() {
  unsigned long currentMillis = millis();

  // === Flip-flop LED Merah/Hijau ===
  static bool ledState = false;
  ledState = !ledState;
  digitalWrite(LED_MERAH, ledState);
  digitalWrite(LED_HIJAU, !ledState);

  // === Servo gerak bolak balik cepat ===
  if (currentMillis - previousServoMillis >= servoDelay) {
    previousServoMillis = currentMillis;
    myservo.write(servoAngle);
    if (servoForward) {
      servoAngle++;
      if (servoAngle >= 90) servoForward = false;
    } else {
      servoAngle--;
      if (servoAngle <= 0) servoForward = true;
    }
  }

  // === Relay (kipas) ON/OFF setiap 5 detik ===
  if (currentMillis - previousRelayMillis >= relayInterval) {
    previousRelayMillis = currentMillis;
    relayState = !relayState;
    digitalWrite(RELAY_PIN, relayState);
    Serial.print("Relay: ");
    Serial.println(relayState ? "ON" : "OFF");
  }

  // === Buzzer bunyi tiap 3 detik ===
  if (currentMillis - previousBuzzerMillis >= buzzerInterval) {
    previousBuzzerMillis = currentMillis;
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
  }

  // === Sensor ===
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  float lux = lightMeter.readLightLevel();
  int mq2 = analogRead(MQ2_PIN);
  int mq135 = analogRead(MQ135_PIN);
  int mq7 = analogRead(MQ7_PIN);

  // === Serial Monitor ===
  Serial.println("=== Pembacaan Sensor ===");
  Serial.print("DHT22 - Suhu: "); Serial.print(temp); Serial.print(" *C, Kelembapan: "); Serial.print(hum); Serial.println(" %");
  Serial.print("BH1750 - Intensitas Cahaya: "); Serial.print(lux); Serial.println(" lux");
  Serial.print("MQ-2 (Gas LPG/Asap): "); Serial.println(mq2);
  Serial.print("MQ-7 (Karbon Monoksida/CO): "); Serial.println(mq7);
  Serial.print("MQ-135 (Gas Beracun/Polusi Udara): "); Serial.println(mq135);
  Serial.println();

  // === Tampilkan ke LCD ===
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:"); lcd.print(temp, 1);
  lcd.print(" H:"); lcd.print(hum, 0);

  lcd.setCursor(0, 1);
  lcd.print("Lux:"); lcd.print(lux, 0);
  delay(1000); // Delay antar loop
}
