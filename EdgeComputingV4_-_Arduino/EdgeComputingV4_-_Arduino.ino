#include <DHT.h>
#include <Servo.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define MQ2 A0
#define MQ7 A1
#define MQ135 A2
#define LDR A3

#define SERVO_PIN 3
#define GREEN_LED 4
#define RED_LED 5
#define BUZZER 6
#define RELAY_FAN 7
#define RELAY_LAMP 8

Servo servo;

void setup() {
  Serial.begin(9600);
  dht.begin();
  servo.attach(SERVO_PIN);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);
  pinMode(RELAY_LAMP, OUTPUT);
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  int mq2 = analogRead(MQ2);
  int mq7 = analogRead(MQ7);
  int mq135 = analogRead(MQ135);
  int ldr = analogRead(LDR);

  // Aktuator kontrol contoh sederhana
  digitalWrite(RELAY_FAN, temp > 25 ? HIGH : LOW);
  digitalWrite(RELAY_LAMP, ldr < 500 ? HIGH : LOW);

  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, mq135 > 400 ? HIGH : LOW);
  digitalWrite(BUZZER, mq2 > 300 ? HIGH : LOW);
  servo.write(mq7 > 400 ? 90 : 0);

  // Kirim data ke ESP32
  Serial.print("S:"); Serial.print(temp);
  Serial.print(";H:"); Serial.print(hum);
  Serial.print(";MQ2:"); Serial.print(mq2);
  Serial.print(";MQ7:"); Serial.print(mq7);
  Serial.print(";MQ135:"); Serial.print(mq135);
  Serial.print(";LDR:"); Serial.println(ldr);

  delay(2000);
}
