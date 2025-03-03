const int led1 = 9;  // LED untuk 1 jari
const int led2 = 10; // LED untuk 3 jari
const int led3 = 11; // LED untuk 5 jari

void setup() {
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    if (Serial.available() > 0) {
        char received = Serial.read();
        
        // Matikan semua LED terlebih dahulu
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);

        // Nyalakan LED berdasarkan input dari Python
        if (received == '1') {
            digitalWrite(led1, HIGH);
        } 
        else if (received == '3') {
            digitalWrite(led2, HIGH);
        } 
        else if (received == '5') {
            digitalWrite(led3, HIGH);
        } 
        else if (received == '0') {
            // Semua LED mati jika terbaca 10 jari
            digitalWrite(led1, LOW);
            digitalWrite(led2, LOW);
            digitalWrite(led3, LOW);
        }
    }
}
