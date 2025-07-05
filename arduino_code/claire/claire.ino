#include <WiFi.h>
#include <HTTPClient.h>
#include <SD.h>
#include <SPI.h>
#include <driver/i2s.h>

// ================= WIFI =================
const char* ssid = "amikompwt";
const char* password = "12345678";

// Ganti dengan alamat backend kamu
// const char* serverUrl = "http://192.168.1.100:8000/upload-audio";
const char* serverUrl = "http://192.168.7.241:5000/upload-audio";


// ================ PIN SETUP ================
#define I2S_WS      25
#define I2S_SD      33
#define I2S_SCK     26
#define SD_CS       5

// =============== RECORD CONFIG ============
#define SAMPLE_RATE     16000
#define RECORD_TIME_SEC 25
#define BUFFER_SIZE     1024

File audioFile;

void setup() {
  Serial.begin(115200);

  // --- WiFi ---
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Serial.println(WiFi.localIP());

  // --- SD Card ---
  if (!SD.begin(SD_CS)) {
    Serial.println("Gagal SD Card.");
    while (1);
  }
  Serial.println("SD Card Siap.");

  // --- I2S ---
  i2s_config_t i2s_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S_MSB,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = 512,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = I2S_SD
  };

  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);
  i2s_zero_dma_buffer(I2S_NUM_0);

  delay(1000);
  rekamAudioKeSD();
  uploadAudio();
}

void loop() {
  // tidak perlu
}

// ================== FUNGSI REKAM ===================
void rekamAudioKeSD() {
  Serial.println("Mulai rekaman 25 detik...");

  audioFile = SD.open("/rekaman.wav", FILE_WRITE);
  if (!audioFile) {
    Serial.println("Gagal membuka file untuk rekam.");
    return;
  }

  tulisHeaderWav(audioFile, SAMPLE_RATE, 16, 1);

  int totalBytes = SAMPLE_RATE * RECORD_TIME_SEC * 2;
  uint8_t buffer[BUFFER_SIZE];

  while (totalBytes > 0) {
    size_t bytesRead;
    i2s_read(I2S_NUM_0, buffer, BUFFER_SIZE, &bytesRead, portMAX_DELAY);
    audioFile.write(buffer, bytesRead);
    totalBytes -= bytesRead;
  }

  updateHeaderWav(audioFile);
  audioFile.close();
  Serial.println("Rekaman selesai dan disimpan di SD.");
}

// ================== FUNGSI UPLOAD ===================
void uploadAudio() {
  File file = SD.open("/rekaman.wav");
  if (!file) {
    Serial.println("Gagal membuka file WAV untuk upload.");
    return;
  }

  HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "audio/wav");

  WiFiClient* stream = http.getStreamPtr();

  Serial.println("Mengirim audio ke backend...");

  int httpResponseCode = http.sendRequest("POST", &file, file.size());

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("Respons server:");
    Serial.println(response);
  } else {
    Serial.printf("Upload gagal. Error: %d\n", httpResponseCode);
  }

  file.close();
  http.end();
}

// ================= HEADER WAV =====================
void tulisHeaderWav(File file, int sampleRate, int bitsPerSample, int channels) {
  byte header[44];
  int byteRate = sampleRate * channels * bitsPerSample / 8;

  memcpy(header, "RIFF", 4);
  uint32_t chunkSize = 0;
  memcpy(header + 4, &chunkSize, 4);
  memcpy(header + 8, "WAVE", 4);

  memcpy(header + 12, "fmt ", 4);
  uint32_t subchunk1Size = 16;
  memcpy(header + 16, &subchunk1Size, 4);
  uint16_t audioFormat = 1;
  memcpy(header + 20, &audioFormat, 2);
  memcpy(header + 22, &channels, 2);
  memcpy(header + 24, &sampleRate, 4);
  memcpy(header + 28, &byteRate, 4);
  uint16_t blockAlign = channels * bitsPerSample / 8;
  memcpy(header + 32, &blockAlign, 2);
  memcpy(header + 34, &bitsPerSample, 2);

  memcpy(header + 36, "data", 4);
  uint32_t subchunk2Size = 0;
  memcpy(header + 40, &subchunk2Size, 4);

  file.write(header, 44);
}

void updateHeaderWav(File file) {
  uint32_t fileSize = file.size();
  file.seek(4);
  uint32_t chunkSize = fileSize - 8;
  file.write((byte*)&chunkSize, 4);
  file.seek(40);
  uint32_t subchunk2Size = fileSize - 44;
  file.write((byte*)&subchunk2Size, 4);
}
