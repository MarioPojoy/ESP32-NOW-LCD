#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>

#define I2C_SDA SDA
#define I2C_SCL SCL

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  float temp;
  float hum;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.print(len);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(myData.temp);
  Serial.print(" T: ");
  Serial.print(myData.temp);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("H: ");
  lcd.print(myData.hum);
  lcd.print("%");
  Serial.print(" H: ");
  Serial.println(myData.hum);
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);

  lcd.init(I2C_SDA, I2C_SCL); // initialize the lcd to use user defined I2C pins
	lcd.backlight();
	lcd.setCursor(0,0);
	lcd.print("Iniciando...");
}
 
void loop() {

}