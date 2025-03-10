#define ledRed1 2
#define ledYelow2 3
#define ledGreen3 4
#define buttonSpeedUp 6

int delayTime = 500; 
int fastDelay = 100;

void setup() {
  Serial.begin(9600);
  pinMode(buttonSpeedUp, INPUT_PULLUP);
  pinMode(ledRed1, OUTPUT);
  pinMode(ledYelow2, OUTPUT);
  pinMode(ledGreen3, OUTPUT);
}

void loop() {
  int isButtonSpeedPressed = digitalRead(buttonSpeedUp);
  int currentDelay = (isButtonSpeedPressed == LOW) ? fastDelay : delayTime;

  if (isButtonSpeedPressed == LOW) {
    Serial.println("Speed button pressed! Speeding up...");
  }digitalWrite(ledRed1, HIGH);
  delay(currentDelay);
  digitalWrite(ledRed1, LOW);

  digitalWrite(ledYelow2, HIGH);
  delay(currentDelay);
  digitalWrite(ledYelow2, LOW);

  digitalWrite(ledGreen3, HIGH);
  delay(currentDelay);
  digitalWrite(ledGreen3, LOW);
}
