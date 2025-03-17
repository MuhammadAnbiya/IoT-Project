#define trigPin 9
#define echoPin 10
#define relayPin 7

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(relayPin, OUTPUT);
    Serial.begin(9600);

    // 🔹 Reset relay ke kondisi awal (lampu mati)
    digitalWrite(relayPin, HIGH);
    delay(1000); // Tunggu 1 detik sebelum mulai loop
}

void loop() {
    long duration;
    int distance;

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;

    Serial.print("Jarak: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance > 0 && distance < 10) {  
        digitalWrite(relayPin, LOW); // 🔹 Relay aktif (lampu menyala)
        Serial.println("Relay AKTIF! (Lampu nyala)");
    } else {
        digitalWrite(relayPin, HIGH); // 🔹 Relay mati (lampu mati)
        Serial.println("Relay MATI! (Lampu mati)");
    }

    delay(500);
}
