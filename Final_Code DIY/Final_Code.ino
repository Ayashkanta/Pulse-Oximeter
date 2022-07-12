//code begins
#include <LiquidCrystal.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
LiquidCrystal lcd(13,12,11,10,9,8);
#define REPORTING_PERIOD_MS 1000
PulseOximeter pox;
uint32_t tsLastReport= 0;
void onBeatDetected()
{
Serial.println("Beat!");
}
void setup()
{
Serial.begin(115200);
Serial.print("Initializing pulse oximeter..");
lcd.begin(16,2);
lcd.setCursor(0,0);
// this complete page contains the commands related to user interface
{
lcd.println("WELCOME USER");
delay(1000);
lcd.setCursor(0,1);
lcd.print("PULSE OXIMETER");
delay(2000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("MEMBERS");
delay(2000);
lcd.clear();
lcd.setCursor(0,0);
lcd.println("AYASHKANTA ");
lcd.setCursor(0,1);
lcd.print("MISHRA_20ME10027");
delay(3500);
lcd.clear();
lcd.setCursor(0,0);
lcd.println("CHAITANYA GAUR");
lcd.setCursor(0,1);
lcd.print("20MA20017");
delay(3500);
lcd.clear();
lcd.setCursor(0,0);
lcd.println("ADITYA PAL");
lcd.setCursor(0,1);
lcd.print("20BT10004");
delay(3500);
lcd.clear();
lcd.setCursor(0,0);
lcd.println("BURRA NITHISH");
lcd.setCursor(0,1);
lcd.print("20CS10018");
delay(3500);
lcd.clear();
}
lcd.print("Initializing...");
delay(3000);
lcd.clear();
if (!pox.begin()) {
Serial.println("FAILED");
for(;;);
} else {
Serial.println("SUCCESS");
}
pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
// Register a callback for the beat detection
pox.setOnBeatDetectedCallback(onBeatDetected);
}
void loop()
{
// Make sure to call update as fast as possible
pox.update();
if (millis()-tsLastReport > REPORTING_PERIOD_MS) {
Serial.print("Heart rate:");
Serial.print(pox.getHeartRate());
Serial.print("bpm / SpO2:");
Serial.print(pox.getSpO2());
Serial.println("%");
lcd.clear();
lcd.setCursor(0,0);
lcd.print("BPM : ");
lcd.print(pox.getHeartRate());
lcd.setCursor(0,1);
lcd.print("SpO2: ");
lcd.print(pox.getSpO2());
lcd.print("%");
tsLastReport = millis();
}
}
