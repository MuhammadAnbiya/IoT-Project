// ----------------------------
// Arduino Uno R3 Code
// ----------------------------
#include <DHT.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHT_PIN 2
#define DHTTYPE DHT11

#define MQ2_PIN A2
#define MQ7_PIN A3
#define MQ135_PIN A4
#define LDR_PIN A5

#define SERVO_PIN 3
#define GREEN_LED 4
#define RED_LED 5
#define BUZZER_PIN 6
#define RELAY_FAN 7
#define RELAY_LAMP 8

DHT dht(DHT_PIN, DHTTYPE);
Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

float suhu, kelembapan;
int ldrVal, mq2Val, mq7Val, mq135Val;
int servoPos = 0;
bool naik = true;

unsigned long lastMillis = 0;
const unsigned long interval = 2000;

void setup() {
  Serial.begin(9600);
  dht.begin();
  servo.attach(SERVO_PIN);

  pinMode(RELAY_FAN, OUTPUT);
  pinMode(RELAY_LAMP, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  digitalWrite(RELAY_FAN, HIGH);
  digitalWrite(RELAY_LAMP, HIGH);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);

  Wire.begin();
  lcd.begin(16, 2);
  lcd.backlight();

  Serial.println(F("=== Sistem Monitoring Siap ==="));
}

void loop() {
  if (millis() - lastMillis >= interval) {
    lastMillis = millis();

    kelembapan = dht.readHumidity();
    suhu = dht.readTemperature();

    if (!isnan(kelembapan) && !isnan(suhu)) {
      ldrVal = analogRead(LDR_PIN);
      mq2Val = analogRead(MQ2_PIN);
      mq7Val = analogRead(MQ7_PIN);
      mq135Val = analogRead(MQ135_PIN);


    Serial.println("Diterima: === Pembacaan Sensor ===");
    // DHT11
    Serial.print("Diterima: [DHT11] Suhu: ");
    Serial.print(suhu, 2);
    Serial.print("°C | Kelembapan: ");
    Serial.print(kelembapan, 2);
    Serial.println("%");
    // LDR
    Serial.print("Diterima: [LDR] Cahaya: ");
    Serial.print(ldrVal);
    if (ldrVal < 500) {
      Serial.println(" => Gelap");
    } else {
      Serial.println(" => Terang");
    }
    // MQ2
    Serial.print("Diterima: [MQ2] CH4: ");
    Serial.println(mq2Val);
    // MQ7
    Serial.print("Diterima: [MQ7] CO: ");
    Serial.println(mq7Val);
    // MQ135
    Serial.print("Diterima: [MQ135] NH3: ");
    Serial.println(mq135Val);

      if (suhu > 25) {
        tone(BUZZER_PIN, 1000);
        digitalWrite(RELAY_FAN, LOW);
        digitalWrite(RELAY_LAMP, HIGH);
        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, LOW);
        Serial.println("Diterima: [ALERT] Suhu tinggi! Kipas, Buzzer, LED Red ON & Lampu OFF");

      } else {
        noTone(BUZZER_PIN);
        digitalWrite(RELAY_FAN, HIGH);
        digitalWrite(RELAY_LAMP, LOW);
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
        Serial.println("Diterima: [ALERT] Suhu Normal :) Kipas, Buzzer, LED Red OFF & Lampu ON");

      }

      if (naik) {
        servoPos = 90;
        naik = false;
      } else {
        servoPos = 0;
        naik = true;
      }
      servo.write(servoPos);

      tampilkanLCD();

    }
  }
}
void tampilkanLCD() {
  String text1 = "    Temp:" + String((int)suhu) + (char)223 + "C Hum:" + String((int)kelembapan) + "% LDR:" + String(ldrVal);
  String text2 = "    CH4 :" + String(mq2Val) + "  CO :" + String(mq7Val) + " NH3:" + String(mq135Val);

  for (int i = 0; i < text1.length(); i++) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(text1.substring(i)); 
    lcd.setCursor(0, 1);
    lcd.print(text2.substring(i)); 
    delay(400);
  }
}




//// ----------------------------
//// ESP32 Code
//// ----------------------------
//HardwareSerial SerialArduino(2);
//
//String inputString = "";
//float suhu = 0, kelembapan = 0;
//int ldrVal = 0, mq2Val = 0, mq7Val = 0, mq135Val = 0;
//
//void setup() {
//  Serial.begin(9600);
//  SerialArduino.begin(9600, SERIAL_8N1, 16, 17); // RX, TX
//  Serial.println("=== ESP32 Monitoring Siap ===");
//}
//
//void loop() {
//  while (SerialArduino.available()) {
//    char c = SerialArduino.read();
//    if (c == '\n') {
//      if (inputString.indexOf("S:") != -1 && inputString.indexOf("H:") != -1) {
//        parseData(inputString);
//        tampilkanKeSerial();
//      }
//      inputString = "";
//    } else {
//      inputString += c;
//    }
//  }
//}
//
//void tampilkanKeSerial() {
//  Serial.println("Diterima: === Pembacaan Sensor ===");
//
//  Serial.print("Diterima: [DHT11] Suhu: ");
//  Serial.print(suhu, 2);
//  Serial.print((char)223);
//  Serial.print("C | Kelembapan: ");
//  Serial.print(kelembapan, 2);
//  Serial.println("%");
//
//  if (suhu > 30) {
//    Serial.println("Diterima: [ALERT] Suhu tinggi! Kipas, Buzzer & Lampu ON");
//  }
//
//  Serial.print("Diterima: [LDR] Cahaya: ");
//  Serial.print(ldrVal);
//  Serial.print(" => ");
//  Serial.println(ldrVal < 200 ? "Gelap" : "Terang");
//
//  Serial.print("Diterima: [MQ2] CH4: ");
//  Serial.println(mq2Val);
//
//  Serial.print("Diterima: [MQ7] CO: ");
//  Serial.println(mq7Val);
//
//  Serial.print("Diterima: [MQ135] NH3: ");
//  Serial.println(mq135Val);
//}
//
//void parseData(String data) {
//  suhu = getValue(data, "T");
//  kelembapan = getValue(data, "H");
//  ldrVal = (int)getValue(data, "L");
//  mq2Val = (int)getValue(data, "M2");
//  mq7Val = (int)getValue(data, "M7");
//  mq135Val = (int)getValue(data, "M135");
//}
//
//float getValue(String data, String key) {
//  int idx = data.indexOf(key + ":");
//  if (idx == -1) return 0;
//  int endIdx = data.indexOf(';', idx);
//  String val = (endIdx == -1)
//      ? data.substring(idx + key.length() + 1)
//      : data.substring(idx + key.length() + 1, endIdx);
//  return val.toFloat();
//}
