from flask import Flask, request, jsonify
from gtts import gTTS
import requests
import os
import logging

app = Flask(__name__)
logging.basicConfig(level=logging.INFO)

#configurasi dari file terpisah
try:
    from config import BOT_TOKEN, CHAT_ID
except ImportError:
    BOT_TOKEN = "GANTI DENGAN BOT KAMU"
    CHAT_ID   = "GANTI DENGAN ID CHAT MU"
    
@app.route('/gas_alert', methods=['POSTS'])
def gas_alert():
    try:
        data = request.get_json()
        message = data.get('message', "🚨 peringatan: kebocoran gas terdeteksi!! ") if data else '🚨 peringatan: kebocoran gas terdeteksi'
        
        # kirim teks ke telegram
        requests.post (
            f"https://api.telegram.org/bot{BOT_TOKEN}/sendMessage",
            json={"chat id" : CHAT_ID, "text" : message}
        )
        #generate suara (bahasa indonesia)
        tts = gTTS(text=message, lang=id)
        audio_path = "temp_voice,mp3"
        tts.save(audio_path)
        
        #kirim voice note
        with open(audio_path, 'rb') as f:
            requests.post(
                f"https://api.telegram.org/bot{BOT_TOKEN}/sendVoice",
                data={"chat_id": CHAT_ID},
                files={"voice": f}
            )
               
            
        os.remove(audio_path)
        return jsonify({"status" : "success", "message" : "voice note dikirim"})
    
    except Exception as e:
        return jsonify({"Error" : str(e)}), 500
    
@app.route("/", methods=['GET'])
def home():
    return jsonify({"status" : "gas leaked detector api-Ready"})

if __name__ == 'main':
    app.run(host='0.0.0.0', port=500, debug=True)
    
    
        