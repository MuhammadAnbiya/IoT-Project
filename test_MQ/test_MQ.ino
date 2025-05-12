#define MQ2_PIN   35  // Asap & LPG
#define MQ7_PIN   33  // Karbon monoksida
#define MQ135_PIN 34  // Kualitas udara umum

void setup() {
  Serial.begin(115200);
  Serial.println("Tes Sensor Gas MQ-series");
}

void loop() {
  int smokeGas = analogRead(MQ2_PIN);
  int carbonMonoxide = analogRead(MQ7_PIN);
  int airQuality = analogRead(MQ135_PIN);

  Serial.print("Asap & Gas Mudah Terbakar (MQ-2): ");
  Serial.print(smokeGas);
  Serial.print(" | CO (MQ-7): ");
  Serial.print(carbonMonoxide);
  Serial.print(" | Kualitas Udara (MQ-135): ");
  Serial.println(airQuality);

  delay(1000);
}
