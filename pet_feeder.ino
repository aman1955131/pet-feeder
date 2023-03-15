#define BLYNK_TEMPLATE_ID "TMPLmg_AZPEF"
#define BLYNK_DEVICE_NAME "pet feeder"
#define BLYNK_AUTH_TOKEN "jh9hmElTg1cPIZVZo8Ze9fEmjd5e181q"
#define BLYNK_PRINT Serial

#include<BlynkSimpleEsp8266.h>
#include<ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

char auth[] = BLYNK_AUTH_TOKEN;
BlynkTimer timer;
WiFiClient client;

Servo servo;

const char* ssid  = "OP";
const char* password  = "12346789";

BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello");
  delay(2000);
  Blynk.begin(auth, ssid, password);
  WiFi.mode(WIFI_STA);
  Serial.print("connected to ssid");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  servo.attach(D4); // attach servo to pin D1
}

void loop() {
  Blynk.run();
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to");
  lcd.setCursor(0, 1);
  lcd.print("HITAM");
}

BLYNK_WRITE(V1) { // receive servo angle from Blynk app
  int angle = param.asInt();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Feeding pet");
  servo.write(angle);
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Done Feeding");
}
