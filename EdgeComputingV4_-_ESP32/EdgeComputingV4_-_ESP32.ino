#include <Wire.h>
#include <LiquidCrystal_I2C.h>

HardwareSerial SerialArduino(2); // UART2
LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat I2C LCD

String inputString = "";

void setup() {
  Serial.begin(115200);
  SerialArduino.begin(9600, SERIAL_8N1, 16, 17); // RX = GPIO16, TX = GPIO17
  lcd.init();
  lcd.backlight();
}

void loop() {
  while (SerialArduino.available()) {
    char c = SerialArduino.read();
    if (c == '\n') {
      parseAndDisplay(inputString);
      inputString = "";
    } else {
      inputString += c;
    }
  }
}

void parseAndDisplay(String data) {
  Serial.println("Received: " + data);

  float temp = getValue(data, "S");
  float hum = getValue(data, "H");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:"); lcd.print(temp); lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("H:"); lcd.print(hum); lcd.print("%");
}

float getValue(String data, String key) {
  int idx = data.indexOf(key + ":");
  if (idx == -1) return 0;
  int endIdx = data.indexOf(';', idx);
  String val = (endIdx == -1) ? data.substring(idx + 2) : data.substring(idx + 2, endIdx);
  return val.toFloat();
}
