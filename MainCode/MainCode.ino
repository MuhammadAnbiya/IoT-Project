#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "ThingSpeak.h"

// --- Konfigurasi Jaringan ---
const char* ssid = "anbi";
const char* password = "12345678";

// --- Konfigurasi ThingSpeak ---
unsigned long myChannelNumber = 2988136;
const char * myWriteAPIKey = "T9CYY5ZP014O5EIQ";

// --- Inisialisasi Klien ---
WiFiClient client;

// --- Konfigurasi Sensor dan Aktuator ---
const int gasSensorPin = A0;
const int buzzerPin = D1;

// --- KONFIGURASI KALIBRASI PPM ---
#define RL_VALUE 5000.0   // Nilai resistor beban (Load Resistor) pada modul MQ-2 (umumnya 5KΩ)
#define R0 6924.87        // <<< NILAI HASIL R0
#define LPG_SLOPE -2.53
#define LPG_INTERCEPT 1.28

// PERBAIKAN: Menggunakan ambang batas yang realistis untuk LPG
const float gasThresholdPPM = 0.06;

// --- Variabel Kontrol ---
bool alreadySent = false;
unsigned long lastCheck = 0;
const long checkInterval = 20000; // Kirim data setiap 20 detik (aman untuk ThingSpeak)

void setup() {
  Serial.begin(115200);

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Terhubung ke WiFi!");

  ThingSpeak.begin(client);
}

// Fungsi untuk menghitung PPM dari nilai analog
float getPPM() {
  float sensor_volt;
  float RS_gas;
  float ratio;

  int sensorValue = analogRead(gasSensorPin);
  sensor_volt = (float)sensorValue * (3.3 / 1023.0);
  RS_gas = (3.3 * RL_VALUE) / sensor_volt - RL_VALUE;
  
  if(RS_gas < 0) RS_gas = 0; // Menghindari nilai negatif

  ratio = RS_gas / R0;
  if(ratio < 0) ratio = 0;

  // Hitung PPM menggunakan persamaan logaritmik: log(PPM) = m*log(ratio) + b
  double ppm_log = (log10(ratio) * LPG_SLOPE) + LPG_INTERCEPT;
  float ppm = pow(10, ppm_log);
  
  return ppm;
}

// Fungsi untuk URL Encoding
String urlencode(String str) {
  String encodedString="";
  char c;
  char code0;
  char code1;
  for (int i =0; i < str.length(); i++){
    c=str.charAt(i);
    if (c == ' '){
      encodedString+='+';
    } else if (isalnum(c)){
      encodedString+=c;
    } else{
      code1=(c & 0xf)+'0';
      if ((c & 0xf) > 9) code1=(c & 0xf) - 10 + 'A';
      c=(c>>4)&0xf;
      code0=c+'0';
      if (c > 9) code0=c - 10 + 'A';
      encodedString+='%';
      encodedString+=code0;
      encodedString+=code1;
    }
   }
   return encodedString;
}

// Fungsi notifikasi yang telah diperbarui
void sendTelegramNotification() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    String message = "⚠️ Peringatan! Gas bocor terdeteksi. Mohon periksa sekarang!";
    String url = "http://api.callmebot.com/text.php?source=web&user=@MuhammadAnbiya&text=" + urlencode(message);

    Serial.println("Mengirim notifikasi Telegram dengan URL baru...");
    
    // PERBAIKAN: Menambah waktu tunggu ke 10 detik (10000 milidetik)
    http.setTimeout(10000); 
    
    http.begin(client, url);
    int httpCode = http.GET();
    
    if (httpCode > 0) {
      Serial.println("✅ Notifikasi Telegram terkirim! Kode: " + String(httpCode));
    } else {
      Serial.println("❌ Gagal kirim notifikasi. Error: " + http.errorToString(httpCode));
    }
    http.end();
  }
}

void sendToThingSpeak(float gasValue) {
  int httpCode = ThingSpeak.writeField(myChannelNumber, 1, gasValue, myWriteAPIKey);
  if (httpCode == 200) {
    Serial.println("✅ Data PPM terkirim ke ThingSpeak.");
  } else {
    Serial.println("❌ Gagal kirim ke ThingSpeak. Kode Error: " + String(httpCode));
  }
}

void loop() {
  if (millis() - lastCheck > checkInterval) {
    lastCheck = millis();

    float ppm = getPPM();
    Serial.print("Tingkat Gas: ");
    Serial.print(ppm, 2);
    Serial.println(" PPM");

    sendToThingSpeak(ppm);

    if (ppm > gasThresholdPPM) {
      digitalWrite(buzzerPin, HIGH);
      
      if (!alreadySent) {
        sendTelegramNotification();
        alreadySent = true;
      }
    } else {
      digitalWrite(buzzerPin, LOW);
      alreadySent = false;
    }
  }
}
