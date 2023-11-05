// ----------------------------------------------------------------
// Testovano na:
// Arduino IDE: ESP32_IoT: Board / ESP32 Wrower Module
// VSCode: denky32
// 
//
//
// ----------------------------------------------------------------


// ----------------------------------------------------------------
// Librares
// ----------------------------------------------------------------
#include <Arduino.h>



//--------------------------------------------------------------
// Pins
//--------------------------------------------------------------
#define LED5 5
#define LED23 23



//--------------------------------------------------------------
// Leds
//--------------------------------------------------------------
struct Led 
{
  // pin LEDky
  uint8_t pin;
  // Promenna pro uchovani casu zmeny stavu
  unsigned long previousMillis;
  // Interval pro blikajici LED
  const long interval;
  // state variables
  bool on;
  // methods
  void update()
  {
    digitalWrite(pin, on ? HIGH : LOW);
  }
};

// Deklarace ledek
Led led_pin5 = { LED5, 0, 1000, false };
Led led_pin23 = { LED23, 0, 600, false };


// Kontrola, zda nema dojit ke zmene stavu LEDky
void CheckLedBliking(int ledPin, long interval, unsigned long &previousMillis)
{
  // Zjisteni aktualniho casu
  unsigned long currentMillis = millis();
  // Kontrola zda uplynul uceny interval
  if (currentMillis - previousMillis >= interval) {
    // Ulozeni posledniho casu, kdy jsem blikali
    previousMillis = currentMillis;

    // Cteni stavu LED a nastaveni opacneho stavu
    digitalWrite(ledPin, !digitalRead(ledPin));
  }
}



//--------------------------------------------------------------
// Setup
//-------------------------------------------------------------- 
void setup() 
{
  Serial.begin(115200);

  // ========================== Buttons and Leds ====================
  pinMode(led_pin5.pin, OUTPUT);
  pinMode(led_pin23.pin, OUTPUT);
}



//--------------------------------------------------------------
// Loop
//-------------------------------------------------------------- 
void loop() 
{
  // LED Pin 5
  CheckLedBliking(led_pin5.pin, led_pin5.interval, led_pin5.previousMillis);
  CheckLedBliking(led_pin23.pin, led_pin23.interval, led_pin23.previousMillis);
}





