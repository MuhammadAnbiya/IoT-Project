#include <LiquidCrystal_I2C.h>

// Define the LCD pins
#define RS 2   // Register Select pin
#define EN 4   // Enable pin
#define D4 5   // Data pin 4
#define D5 18  // Data pin 5
#define D6 19  // Data pin 6
#define D7 21  // Data pin 7

// Create an LCD object
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 1, 0); // Set I2C address, I2C pin1, I2C pin2, RS pin, EN pin, D4 pin

void setup() {
  // Initialize the LCD
  lcd.begin(16, 2); // Initialize 16x2 LCD

  // Print a test message
  lcd.print("Hello, LCD!");
  lcd.setCursor(0, 1); // Go to the second line
  lcd.print("ESP32 Test");

  lcd.backlight(); // Turn on backlight
}

void loop() {
  // Put your code here
}
