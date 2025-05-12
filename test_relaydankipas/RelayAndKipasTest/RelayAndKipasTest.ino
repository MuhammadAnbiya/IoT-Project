#define RELAY_PIN 12

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("Tes relay mulai...");
  digitalWrite(RELAY_PIN, HIGH); // Pastikan relay mati saat awal
}

void loop() {
  Serial.println("Relay ON (CLOSE)");
  digitalWrite(RELAY_PIN, LOW);  // Aktifkan relay
  delay(3000);

  Serial.println("Relay OFF (OPEN)");
  digitalWrite(RELAY_PIN, HIGH); // Nonaktifkan relay
  delay(3000);
}

//
//int lampu=12;
//
//void setup(){
//  Serial.begin(9600);
//  pinMode(lampu,OUTPUT);
//}
//
//void loop(){
//  digitalWrite(lampu, HIGH);
//  delay(5000);
//  digitalWrite(lampu,LOW);
//  delay(2000);
//}
