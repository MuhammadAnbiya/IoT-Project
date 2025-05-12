#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

void setup() {
  Serial.begin(9600);
  Wire.begin(21, 22);  // SDA, SCL khusus ESP32

  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println("Sensor BH1750 GY-302 siap.");
  } else {
    Serial.println("Gagal inisialisasi BH1750.");
    while (1);
  }
} 

void loop() {
  float lux = lightMeter.readLightLevel();
  Serial.print("Intensitas cahaya: ");
  Serial.print(lux);
  Serial.println(" lux");
  delay(1000);
}
