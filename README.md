# Gas Leak Detector with ESP32 + Telegram Voice Alert

![MIT License](https://img.shields.io/github/license/migel-new/gas-leak-detector-flask)
![Python](https://img.shields.io/badge/Python-3.8%2B-blue)
![ESP32](https://img.shields.io/badge/ESP32-Arduino_Core-green)

Sistem IoT sederhana untuk mendeteksi kebocoran gas menggunakan **sensor MQ-2** dan **ESP32**, dengan notifikasi otomatis ke **Telegram** — termasuk **voice note dinamis dalam bahasa Indonesia** yang di-generate menggunakan **Google Text-to-Speech (gTTS)**.

> Dibuat sebagai eksplorasi AIoT oleh mahasiswa D3 Teknik Elektronika.

---

## 🔧 Fitur Utama
- ✅ Deteksi gas real-time via sensor MQ-2
- ✅ Notifikasi teks ke Telegram saat ambang batas terlampaui
- ✅ **Voice note otomatis** dari teks (tanpa file suara statis!)
- ✅ Indikator lokal: LED & buzzer di ESP32
- ✅ REST API sederhana berbasis Flask (Python)

---

## 📦 Teknologi yang Digunakan
| Komponen | Teknologi |
|--------|----------|
| **Mikrokontroler** | ESP32 (Arduino Core) |
| **Sensor** | MQ-2 (gas combustible) |
| **Server** | Python + Flask |
| **Text-to-Speech** | `gTTS` (Google Text-to-Speech) |
| **Notifikasi** | Telegram Bot API |
| **Komunikasi** | HTTP/JSON over Wi-Fi |

---

## 🚀 Cara Menjalankan

### 1. Persiapan Server (Komputer)
```bash
# Install dependensi
pip install -r server/requirements.txt

# Salin template konfigurasi
copy server/config.example.py server/config.py

# Edit server/config.py → isi BOT_TOKEN & CHAT_ID asli

# Jalankan server
python server/app.py
