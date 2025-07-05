from flask import Flask, request, jsonify
from datetime import datetime
import os
from pipeline import run_pipeline  # Import pipeline utama

app = Flask(__name__)
UPLOAD_FOLDER = "uploads"
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

@app.route("/")
def home():
    return "CLAIRE Backend Aktif 🚀"

@app.route("/upload-audio", methods=["POST"])
def upload_audio():
    # Ambil raw audio dari body request
    audio_data = request.data
    if not audio_data:
        return jsonify({"error": "No audio data received"}), 400

    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    filename = f"audio_{timestamp}.wav"
    filepath = os.path.join(UPLOAD_FOLDER, filename)

    with open(filepath, "wb") as f:
        f.write(audio_data)

    with open(filepath, "wb") as f:
        f.write(request.data)

    print(f"[✔] File diterima dan disimpan: {filepath}")

    # Debug: Pastikan pipeline dijalankan
    print("[⚙️] Memulai pipeline...")
    result = run_pipeline(filepath)
    print("[✅] Pipeline selesai.")

    # Log hasilnya
    print("[🧠] Hasil pipeline:")
    print(result)

    # Jalankan pipeline
    result = run_pipeline(filepath)
    return jsonify(result)

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
