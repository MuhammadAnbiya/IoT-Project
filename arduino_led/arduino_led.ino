const int led1 = 9;  // LED untuk 1 jari
const int led2 = 10; // LED untuk 3 jari
const int led3 = 11; // LED untuk 5 jari

bool led1_state = false;
bool led2_state = false;
bool led3_state = false;

void setup() {
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    if (Serial.available() > 0) {
        char received = Serial.read();

        // Jika '1' diterima, nyalakan LED1 tanpa mematikan lainnya
        if (received == '1') {
            led1_state = true;
        } 
        // Jika '3' diterima, nyalakan LED2 tanpa mematikan lainnya
        else if (received == '3') {
            led2_state = true;
        } 
        // Jika '5' diterima, nyalakan LED3 tanpa mematikan lainnya
        else if (received == '5') {
            led3_state = true;
        } 
        // Jika '0' diterima (10 jari), matikan semua LED
        else if (received == '0') {
            led1_state = false;
            led2_state = false;
            led3_state = false;
        }

        // Perbarui status LED
        digitalWrite(led1, led1_state ? HIGH : LOW);
        digitalWrite(led2, led2_state ? HIGH : LOW);
        digitalWrite(led3, led3_state ? HIGH : LOW);
    }
}
