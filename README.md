# CLAIRE - Classroom Listening and Analytics for Insightful Realtime Evaluation

[![PyPI version](https://badge.fury.io/py/claire.svg)](https://badge.fury.io/py/claire)


CLAIRE is an AI-powered classroom tool designed to record, transcribe, and analyze lectures. Using advanced speech recognition and natural language processing (NLP), CLAIRE provides insights into speaker effectiveness and learning material clarity.

---

## 🚀 Features

- 🎤 **Audio Recording**: Automatically records classroom lectures using **ESP32** and **INMP441** microphone.
- 🔍 **Speaker Recognition**: Identifies speakers using pre-trained models.
- 🧠 **Speech-to-Text**: Transcribes spoken content using **Whisper**.
- 📊 **NLP Analysis**: Analyzes transcriptions for teaching effectiveness, clarity, and key topics.

---

## 🔧 Installation

### Clone the Repository

Clone the project to your local machine:

```bash
git clone https://github.com/your-username/claire.git
cd claire

```

### ⚙️ Set Up Virtual Environment
It's highly recommended to use a virtual environment (venv) to avoid library conflicts. Here’s how you can set it up:

Create and activate a virtual environment:
```bash
python -m venv venv-claire
```

Activate the environment:

Windows:
```bash
.\venv-claire\Scripts\activate
```

Mac/Linux:
```bash
source venv-claire/bin/activate
```

don't forget to install the library needed :
```bash
pip install -r requirements.txt
```
### 👩🏻‍💻 Usage
Running the Backend with this command:
```bash
python app.py
```

#### The server will be available at:
- Local: http://127.0.0.1:5000
- Local Network: http://<Your-IP>:5000

#### ESP32 Setup for Audio Recording
- Upload the code (claire.ino) to your ESP32 using Arduino IDE.
- Set Wi-Fi credentials and backend URL in the ESP32 code.
- The ESP32 will automatically record and upload audio for processing.

