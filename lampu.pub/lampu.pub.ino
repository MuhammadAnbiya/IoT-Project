const int ledPin = 13; // Ganti dengan pin Arduino yang terhubung ke LED

void setup() {
  pinMode(ledPin, OUTPUT); // Set pin sebagai output
}

void loop() {
  digitalWrite(ledPin, HIGH);   // Nyalakan LED (set pin HIGH)
  delay(1000);                   // Tunggu 1 detik
  digitalWrite(ledPin, LOW);    // Matikan LED (set pin LOW)
  delay(1000);                   // Tunggu 1 detik
}
