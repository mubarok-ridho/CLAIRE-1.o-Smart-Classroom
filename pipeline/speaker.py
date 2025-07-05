from speechbrain.inference.speaker import SpeakerRecognition
import os

def detect_speaker(test_audio_path, ref_folder="data/references_voice"):
    verifier = SpeakerRecognition.from_hparams(
        source="speechbrain/spkrec-ecapa-voxceleb",
        savedir="pretrained_models/ecapa"
    )

    best_score = -1.0
    best_speaker = "unknown"

    for speaker_name in os.listdir(ref_folder):
        speaker_path = os.path.join(ref_folder, speaker_name)
        if not os.path.isdir(speaker_path):
            continue

        scores = []
        for file in os.listdir(speaker_path):
            if not file.endswith(".wav"):
                continue
            ref_file = os.path.join(speaker_path, file)
            score = verifier.verify_files(ref_file, test_audio_path)
            score_val = float(score[0])  # ← Ambil angka di dalam tuple
            scores.append(score_val)




        if scores:
            avg_score = sum(scores) / len(scores)
            if avg_score > best_score:
                best_score = avg_score
                best_speaker = speaker_name

    return {
        "name": best_speaker,
        "score": float(round(best_score, 3))
    }
