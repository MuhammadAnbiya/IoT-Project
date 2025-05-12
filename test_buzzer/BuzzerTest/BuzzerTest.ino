//#define BUZZER_PIN 14
//
//void setup() {
//  pinMode(BUZZER_PIN, OUTPUT);
//  Serial.begin(115200);
//  Serial.println("Tes Buzzer dimulai");
//}
//
//void loop() {
//  Serial.println("Buzzer ON");
//  digitalWrite(BUZZER_PIN, HIGH);
//  delay(100);
//
//  Serial.println("Buzzer OFF");
//  digitalWrite(BUZZER_PIN, LOW);
//  delay(100);
//}


#define BUZZER_PIN 14

void setup() {
  Serial.begin(115200);
  Serial.println("Tes Buzzer dengan tone()");
}

void loop() {
  Serial.println("Tone 1000 Hz");
  tone(BUZZER_PIN, 1000); // 1000 Hz
  delay(1000);

  Serial.println("No Tone");
  noTone(BUZZER_PIN);
  delay(1000);
}


//#define BUZZER_PIN 2
//
//void setup() {
//  Serial.begin(9600); // Baudrate umum untuk Arduino UNO
//  Serial.println("Tes Buzzer dengan tone()");
//}
//
//void loop() {
//  Serial.println("Tone 1000 Hz");
//  tone(BUZZER_PIN, 1000); // Mainkan suara 1000 Hz
//  delay(1000);
//
//  Serial.println("No Tone");
//  noTone(BUZZER_PIN);     // Hentikan suara
//  delay(1000);
//}
