# CLAIRE - Classroom Audio Recorder & Analysis

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

### 2. Set Up Virtual Environment
It's highly recommended to use a virtual environment (venv) to avoid library conflicts. Here’s how you can set it up:

#### 2.1 Create a Virtual Environment
Create a new virtual environment in the project directory. This isolates the dependencies for this project from other Python projects on your machine.

Run the following command:
```bash
python -m venv venv-claire
```