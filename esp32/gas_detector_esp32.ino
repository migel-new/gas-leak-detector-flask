#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// === KONFIGURASI WI-FI ===
const char* ssid = "NAMA_WIFI_KAMU";
const char* password = "PASSWORD_WIFI_KAMU";

// === KONFIGURASI SERVER ===
const char* serverUrl = "http://192.168.1.100:5000/gas-alert"; // GANTI DENGAN IP KOMPUTER + PORT FLASK

// === PIN ESP32 ===
const int MQ2_PIN = 34;   // Pin analog MQ-2 (gunakan pin ADC1: 32-39)
const int LED_PIN = 2;    // Built-in LED di ESP32
const int BUZZER_PIN = 18;

// === AMBANG BATAS GAS ===
const int GAS_THRESHOLD = 800; // Sesuaikan berdasarkan kalibrasi

void setup() {
  Serial.begin(115200);
  
  // Inisialisasi pin
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // Sambung ke Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Terhubung! IP: " + WiFi.localIP().toString());
}

void loop() {
  int gasValue = analogRead(MQ2_PIN);
  Serial.print("Nilai gas: ");
  Serial.println(gasValue);

  if (gasValue > GAS_THRESHOLD) {
    // Aktifkan indikator lokal
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    
    // Kirim notifikasi ke server Flask
    sendGasAlert("⚠️ Peringatan! Kebocoran gas terdeteksi di ruang laboratorium.");

    // Tahan selama 2 detik
    delay(2000);
    
    // Matikan buzzer (LED tetap nyala sebagai indikator)
    digitalWrite(BUZZER_PIN, LOW);
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(1000); // Baca setiap 1 detik
}

void sendGasAlert(const char* message) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    // Buat JSON payload
    StaticJsonDocument<200> doc;
    doc["message"] = message;
    String jsonBody;
    serializeJson(doc, jsonBody);

    int httpResponseCode = http.POST(jsonBody);
    
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("✅ Berhasil kirim ke server: " + response);
    } else {
      Serial.println("❌ Gagal kirim ke server. Kode: " + String(httpResponseCode));
    }
    
    http.end();
  } else {
    Serial.println("❌ Tidak terhubung ke Wi-Fi");
  }
}