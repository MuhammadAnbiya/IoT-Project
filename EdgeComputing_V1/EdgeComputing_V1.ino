// Definisi pin
const int ledMerah = 25;
const int ledHijau = 26;

void setup() {
  pinMode(ledMerah, OUTPUT);
  pinMode(ledHijau, OUTPUT);
}

void loop() {
  digitalWrite(ledMerah, HIGH);
  digitalWrite(ledHijau, LOW);
  delay(500);  // Tunggu 0.5 detik

  digitalWrite(ledMerah, LOW);
  digitalWrite(ledHijau, HIGH);
  delay(500);  // Tunggu 0.5 detik
}
