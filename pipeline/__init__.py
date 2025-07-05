from .speaker import detect_speaker
from .transcriber import transcribe_audio
from .nlp import analyze_text

def run_pipeline(audio_path):
    print("[🎤] Jalankan speaker recognition...")
    speaker_result = detect_speaker(audio_path)

    print("[🔊] Jalankan Whisper STT...")
    transcript = transcribe_audio(audio_path)

    print("[📊] Analisis NLP...")
    analysis = analyze_text(transcript)

    return {
        "speaker": speaker_result["name"],
        "similarity": speaker_result["score"],
        "transcript": transcript,
        "analysis": analysis
    }
