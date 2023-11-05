// Testovano na:
// Arduino IDE: ESP32_IoT: Board / ESP32 Wrower Module
// VSCode: denky32
// 


// ----------------------------------------------------------------
// Librares
// ----------------------------------------------------------------
#include <Arduino.h>



//--------------------------------------------------------------
// Pins
//--------------------------------------------------------------
#define LED5 5



//--------------------------------------------------------------
// Leds
//--------------------------------------------------------------
struct Led 
{
  // state variables
  uint8_t pin;
  bool on;
  // methods
  void update()
  {
    digitalWrite(pin, on ? HIGH : LOW);
  }
};

// Deklarace ledek
Led led_pin5 = { LED5, false };

//--------------------------------------------------------------
// Setup
//-------------------------------------------------------------- 
void setup() 
{
  Serial.begin(115200);

  // ========================== Buttons and Leds ====================
  pinMode(led_pin5.pin, OUTPUT);
}


void loop() 
{
  led_pin5.on = !led_pin5.on;
  led_pin5.update();

  delay(500);
}





