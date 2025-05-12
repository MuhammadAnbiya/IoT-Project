#include <ESP32Servo.h>

Servo myServo;

void setup() {
  myServo.attach(13); // Pin sinyal servo
  Serial.begin(115200);
  Serial.println("Servo siap");
}

void loop() {
  Serial.println("Putar ke 0 derajat");
  myServo.write(0);
  delay(2000);

  Serial.println("Putar ke 90 derajat");
  myServo.write(90);
  delay(2000);
}

//#include <ESP32Servo.h>
//
//Servo myServo;
//
//void setup() {
//  myServo.attach(13);
//  Serial.begin(115200);
//}
//
//void loop() {
//  // Gerak pelan dari 0 ke 180
//  for (int pos = 0; pos <= 180; pos++) {
//    myServo.write(pos);
//    delay(20); // Semakin besar, semakin lambat
//  }
//
//  delay(1000); // Tahan posisi
//
//  // Gerak pelan dari 180 ke 0
//  for (int pos = 180; pos >= 0; pos--) {
//    myServo.write(pos);
//    delay(20);
//  }
//
//  delay(1000);
//}


//#include <Servo.h> // Library untuk Arduino Uno
//
//Servo myServo;
//
//void setup() {
//  myServo.attach(9); // Gunakan pin digital 9 pada Arduino Uno
//  Serial.begin(9600);
//  Serial.println("Servo siap");
//}
//
//void loop() {
//  Serial.println("Putar ke 0 derajat");
//  myServo.write(0);
//  delay(2000);
//
//  Serial.println("Putar ke 90 derajat");
//  myServo.write(90);
//  delay(2000);
//}
