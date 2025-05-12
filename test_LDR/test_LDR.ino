#define LDR_PIN 35

void setup() {
  Serial.begin(115200);
  pinMode(LDR_PIN, INPUT);
}

void loop() {
  int ldrValue = analogRead(LDR_PIN);
  Serial.print("Nilai LDR (ADC): ");
  Serial.println(ldrValue);

  delay(1000);
}
