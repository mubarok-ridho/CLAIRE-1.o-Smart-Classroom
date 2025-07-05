import re
import numpy as np
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics import pairwise_distances
from transformers import pipeline

# === Load summarizer dari Hugging Face (pakai model ringan)
summarizer = pipeline("summarization", model="sshleifer/distilbart-cnn-12-6")

def clean_text(text):
    return re.sub(r"[^a-zA-Z0-9\s]", "", text.lower())

def analyze_text(text):
    cleaned = clean_text(text)
    words = cleaned.split()
    num_words = len(words)

    # === TF-IDF untuk ekstrak topik dan menghitung entropi fokus ===
    vectorizer = TfidfVectorizer(stop_words='english', max_features=10)
    X = vectorizer.fit_transform([cleaned])
    feature_names = vectorizer.get_feature_names_out()
    tfidf_values = X.toarray()[0]

    topic_focus = [feature_names[i] for i in np.argsort(tfidf_values)[::-1]]

    # === Entropy untuk lihat apakah topik tersebar luas (kurang fokus) ===
    tfidf_dist = tfidf_values / (np.sum(tfidf_values) + 1e-9)
    entropy = -np.sum(tfidf_dist * np.log2(tfidf_dist + 1e-9))
    focus_score = 1 - (entropy / np.log2(len(tfidf_values) + 1e-9))  # 0 = sangat tersebar, 1 = fokus

    # === Redundansi: jika banyak pengulangan kata
    redundancy_score = len(set(words)) / (len(words) + 1e-9)  # 1 = tidak redundant

    # === Klarifikasi dan efektivitas
    clarity_score = focus_score * redundancy_score
    effectiveness = int(min(100, num_words * clarity_score / 1.5))
    is_effective = effectiveness >= 60

    # === Ringkasan
    try:
        summary_result = summarizer(text, max_length=50, min_length=25, do_sample=False)
        summary = summary_result[0]["summary_text"]
    except:
        summary = "Ringkasan tidak tersedia."

    return {
        "effectiveness": effectiveness,
        "is_effective": is_effective,
        "topic_focus": topic_focus[:5],
        "clarity_score": round(clarity_score, 2),
        "redundancy": round(1 - redundancy_score, 2),
        "summary": summary
    }
