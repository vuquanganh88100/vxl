#define BLYNK_TEMPLATE_ID "TMPL6toyU2lXH"
#define BLYNK_TEMPLATE_NAME "VXL"
#define BLYNK_AUTH_TOKEN "PPJEKmVMTveD_YUpZu3RxH4cPqmRiKt6"
#include <DHT.h>
#include <Wire.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BlynkSimpleEsp32.h>

// gfx và ssh1306 control led
#define SCREEN_WIDTH 128 // OLED width,  in pixels
#define SCREEN_HEIGHT 64 // OLED height, in pixels
#define  DHT_PIN 4
#define DHT_TYPE DHT22 
DHT dht(DHT_PIN, DHT_TYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// connect blynk
char ssid[] = "Wokwi-GUEST"; // Use the available access point name
char pass[] = ""; // If it doesn't require a password, leave it empty
// char auth[]="PPJEKmVMTveD_YUpZu3RxH4cPqmRiKt6";


void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  display.display();
  delay(2000);
  display.clearDisplay();
    Blynk.begin( BLYNK_AUTH_TOKEN,ssid, pass);

}
void loop() {
  Blynk.run();

  double humidity = dht.readHumidity();
  double temperature = dht.readTemperature();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");

  display.print("Humidity: ");
  display.print(humidity);
  display.println("%");

  display.display();

  // Send temperature and humidity to Blynk virtual pins V0 and V1
  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V0, humidity);

  delay(2000);
}