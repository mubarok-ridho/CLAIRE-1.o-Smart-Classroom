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
2. Set Up Virtual Environment
It's highly recommended to use a virtual environment (venv) to avoid library conflicts. Here’s how you can set it up:

Create a Virtual Environment:

bash
Copy
Edit
python -m venv venv-claire
Activate the Virtual Environment:

On Windows:

bash
Copy
Edit
.\venv-claire\Scripts\activate
On Mac/Linux:

bash
Copy
Edit
source venv-claire/bin/activate
3. Install Dependencies
Once the virtual environment is activated, install the required libraries:

bash
Copy
Edit
pip install -r requirements.txt
This will install all necessary libraries, including Flask, SpeechBrain, Whisper, and other machine learning and data processing dependencies.

🚀 Usage
1. Running the Backend
To start the backend server, run:

bash
Copy
Edit
python app.py
The server will be available at:

Local: http://127.0.0.1:5000

Local Network: http://<Your-IP>:5000

The backend will handle requests to upload audio, process it with SpeechBrain for speaker recognition, and convert it into text using Whisper.

2. ESP32 Setup for Audio Recording
The ESP32 is used to capture audio in real-time:

Upload the Code: Upload the ESP32 code (claire.ino) using the Arduino IDE.

Wi-Fi Credentials: Make sure to set the Wi-Fi credentials and backend URL correctly in the ESP32 code.

Recording and Upload: The ESP32 will automatically start recording audio based on the set schedule and upload the audio file to the backend server for processing.

3. Testing
Backend Testing: Test the backend by sending .wav files to the /upload-audio endpoint using tools like Postman or curl.

ESP32 Testing: Once powered on, the ESP32 will begin recording audio and automatically upload it to the Flask backend for processing.

🔍 Model Details
🧠 Speaker Recognition (SpeechBrain)
SpeechBrain provides the pre-trained model used for speaker recognition.

The model works by identifying speakers based on their voice characteristics, and it matches them to the closest registered speaker.

📝 Speech-to-Text (Whisper)
Whisper, a speech-to-text model by OpenAI, is used for transcribing the recorded audio.

Whisper provides accurate transcription from audio to text, which is then processed for analysis.

📊 NLP for Effectiveness Evaluation
Once the text is generated, Natural Language Processing (NLP) is used to analyze the content:

Effectiveness Score: Evaluates how clear and impactful the lecture content is.

Topic Extraction: Identifies key topics covered during the lecture.

Redundancy Detection: Measures any unnecessary repetition in the speech.

🤝 Contributing
We welcome contributions! Here's how you can contribute to the CLAIRE project:

Fork the repository.

Create a new branch (git checkout -b feature-name).

Commit your changes (git commit -m 'Add feature').

Push to your fork (git push origin feature-name).

Create a pull request.

Please refer to the Contributing Guidelines for more detailed instructions.

📝 License
This project is licensed under the MIT License - see the LICENSE file for details.

📚 Acknowledgments
SpeechBrain: For speaker recognition and voice processing.

Whisper: For speech-to-text transcription.

ESP32: For capturing classroom audio in real-time.

Flask: For backend development and API creation.

✅ Step 2 - Ready to Run!
You’re almost ready to start using the CLAIRE project! Here’s how to finalize the setup and ensure everything works smoothly:

1. Make Sure Your ESP32 is Ready:
Upload the claire.ino code from Arduino IDE to your ESP32.

Ensure that the Wi-Fi credentials and server URL in the code are correct. This will allow your ESP32 to connect to the correct network and communicate with the Flask backend.

2. Test the Backend:
Once your Flask backend is running (python app.py), try sending a .wav file to http://127.0.0.1:5000/upload-audio to ensure that everything is working.

You can use Postman or curl for testing the endpoint, sending a POST request with the audio file.

3. Test ESP32 with Backend:
Power on your ESP32. It will automatically start recording audio at the specified intervals.

Once recording is complete, the ESP32 will upload the audio file to the Flask backend.

Check the backend logs to confirm that the audio file has been received and processed. The logs should show the results of the speaker recognition and transcription process.

4. Review the Analysis:
After processing, review the output in the backend to see the results of the speaker recognition, transcription, and NLP analysis (effectiveness score, key topics, etc.).

Now you are ready to fully test the CLAIRE project in real classroom environments!

With this setup, you should be able to easily run the CLAIRE system, from setting up the backend to uploading and analyzing recorded audio.

📌 Final Note:
Once everything is set up, you can continuously improve and test CLAIRE in real classroom environments to monitor teaching effectiveness, improve lesson planning, and enhance learning experiences.