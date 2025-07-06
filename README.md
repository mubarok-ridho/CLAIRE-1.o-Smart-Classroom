# CLAIRE - Classroom Audio Recorder & Analysis

CLAIRE is an AI-powered classroom tool designed to record, transcribe, and analyze lectures. Using advanced speech recognition and natural language processing (NLP), CLAIRE provides insights into speaker effectiveness and learning material clarity.

---

## 🚀 Features

- 🎤 **Audio Recording**: Automatically records classroom lectures using ESP32 and INMP441 microphone.
- 🔍 **Speaker Recognition**: Identifies speakers using pre-trained models for recognition.
- 🧠 **Speech-to-Text**: Transcribes spoken content into text using Whisper.
- 📊 **NLP Analysis**: Analyzes transcriptions to evaluate teaching effectiveness, clarity, and key topics.

---

## 🔧 Prerequisites

Before running the CLAIRE project, ensure you have the following installed:

- **Python 3.9** or higher
- **Arduino IDE** (for ESP32 code)
- **Required Libraries**: Install dependencies via `requirements.txt` (listed below)
- **Git** (for cloning the repository)

---

## 🛠️ Installation

Follow these steps to set up the project on your local machine:

### 1. Clone the Repository

Clone this repository to your local machine:

```bash
git clone https://github.com/your-username/claire.git
cd claire

### 2. Set Up Virtual Environment

It's highly recommended to use a virtual environment (venv) to avoid library conflicts. Here’s how you can set it up:

#### 2.1 Create a Virtual Environment

Create a new virtual environment in the project directory. This isolates the dependencies for this project from other Python projects on your machine.

Run the following command:

```bash
python -m venv venv-claire
