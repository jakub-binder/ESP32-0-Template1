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

#include <Adafruit_NeoPixel.h>


//--------------------------------------------------------------
// Pins
//--------------------------------------------------------------
#define LED5 5
#define LED18 18
#define LED19 19
#define LED23 23

// Buttons
#define BUTT1 25
#define BUTT2 26
#define BUTT3 27
#define BUTT4 14

// Neopixel
#define PIN_NEOPIXEL 4

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
Led led_pin18 = { LED18, 0, 1000, false };
Led led_pin19 = { LED19, 0, 1000, false };
Led led_pin23 = { LED23, 0, 100, false };


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
// Neopixel leds
//--------------------------------------------------------------
// https://github.com/adafruit/Adafruit_NeoPixel.git
#define NUM_PIXELS 4
Adafruit_NeoPixel pixels(NUM_PIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// Colors
uint32_t colors_black = pixels.Color(0,0,0);        // Black, #000000
uint32_t colors_white = pixels.Color(255,255,255);  // White, #FFFFFF
uint32_t colors_red = pixels.Color(255,0,0);        // Red, #FF0000
uint32_t colors_lime = pixels.Color(0,255,0);       // Lime, #00FF00
uint32_t colors_blue = pixels.Color(0,0,255);       // Blue, #0000FF
uint32_t colors_yellow = pixels.Color(255,255,0);   // Yellow, #FFFF00
uint32_t colors_aqua = pixels.Color(0,255,255);     // Aqua, #00FFFF
uint32_t colors_pink = pixels.Color(255,0,255);     // Fuchsia(Pink), #FF00FF
uint32_t colors_gray = pixels.Color(128,128,128);   // Gray, #808080
uint32_t colors_green = pixels.Color(0,128,0);      // Green, #008000
uint32_t colors_purple = pixels.Color(128,0,128);   // Purple, #800080

struct Led_neopixel
{
  //
  uint8_t led;    // Number of led
  bool on;        // State of led
  uint32_t color; // Color of Led
  void update()
  {
    if(on)
    {
      pixels.setPixelColor(led, color);
    }
    else
    {
      pixels.setPixelColor(led, colors_black);
    }
    
    pixels.show();
  }
};

Led_neopixel led_neopixel1 = { 0, false, colors_yellow };
Led_neopixel led_neopixel2 = { 1, false, colors_red };
Led_neopixel led_neopixel3 = { 2, false, colors_blue };
Led_neopixel led_neopixel4 = { 3, false, colors_green };

//--------------------------------------------------------------
// Buttons
//--------------------------------------------------------------
// Button debouncing
const uint8_t DEBOUNCE_DELAY = 10; // in milliseconds

struct Button
{
  // state variables
  uint8_t pin;                  // Definuje vstupní pin tlacitka
  bool lastReading;             // Definuje posledni nactenou hodnotu signalu (HIGH nebo LOW)
  uint32_t lastDebounceTime;    // Definuje poslední čas v milisekundách, kdy bylo provedeno poslední čtení
  uint16_t state;               // 16bitové celé číslo, které definuje stav tlačítka.. (viz tutorial)

  // metody určující logický stav tlačítak
  bool pressed()                { return state == 1; }      // Stisknuto
  bool released()               { return state == 0xffff; } // Uvolneno
  bool held(uint16_t count = 0) { return state > 1 + count && state < 0xffff; } // Drzeno

  // Metoda pro cteni fyzickeo stavu tlacitka
  void read()
  {
    // přečte napětí na pinu připojeném k tlačítku
    bool reading = digitalRead(pin);

    // Pokud se logická úroveň od posledního čtení změnila,
    // resetujeme časovač, který odpočítává potřebný čas
    // za nímž můžeme uvažovat o efektu skákání prošel.
    if (reading != lastReading) 
    {
      lastDebounceTime = millis();
    }
    // od chvíle, kdy jsme mimo fázi skákání
    // lze zjistit aktuální stav tlačítka
    if (millis() - lastDebounceTime > DEBOUNCE_DELAY) 
    {
      // don't forget that the read pin is pulled-up
      // ToDo Kontrola - zda to nemam naopak
      bool pressed = reading == HIGH;
      if (pressed) 
      {
        if (state  < 0xfffe) state++;
        else if (state == 0xfffe) 
          state = 2;
      } 
      else if (state) 
      {
        state = state == 0xffff ? 0 : 0xffff;
      }
    }
    // finally, each new reading is saved
    lastReading = reading;
  }
};
Button button1 = { BUTT1, HIGH, 0, 0 };
Button button2 = { BUTT2, HIGH, 0, 0 };
Button button3 = { BUTT3, HIGH, 0, 0 };
Button button4 = { BUTT4, HIGH, 0, 0 };

//--------------------------------------------------------------
// Setup
//-------------------------------------------------------------- 
void setup() 
{
  Serial.begin(115200);

  // ========================== Buttons and Leds ====================
  pinMode(led_pin5.pin, OUTPUT);
  pinMode(led_pin18.pin, OUTPUT);
  pinMode(led_pin19.pin, OUTPUT);
  pinMode(led_pin23.pin, OUTPUT);

  pinMode(button1.pin, INPUT);
  pinMode(button2.pin, INPUT);
  pinMode(button3.pin, INPUT);
  pinMode(button4.pin, INPUT);

  pixels.begin();
}



//--------------------------------------------------------------
// Loop
//-------------------------------------------------------------- 
void loop() 
{

  // Blikáni ledek
  CheckLedBliking(led_pin5.pin, led_pin5.interval, led_pin5.previousMillis);
  CheckLedBliking(led_pin23.pin, led_pin23.interval, led_pin23.previousMillis);
  

  button1.read();
  button2.read();
  button3.read();
  button4.read();

  if (button1.pressed())
  {
    //led_pin5.on = !led_pin5.on;
    //led_pin5.update();
    led_neopixel1.on = !led_neopixel1.on;
    led_neopixel1.update();
  }
  if (button2.pressed())
  {
    //led_pin18.on = !led_pin18.on;
    //led_pin18.update();
    led_neopixel2.on = !led_neopixel2.on;
    led_neopixel2.update();
  }
  if (button3.pressed())
  {
    //led_pin19.on = !led_pin19.on;
    //led_pin19.update();
    led_neopixel3.on = !led_neopixel3.on;
    led_neopixel3.update();
  }
  if (button4.pressed())
  {
    //led_pin23.on = !led_pin23.on;
    //led_pin23.update();
    led_neopixel4.on = !led_neopixel4.on;
    led_neopixel4.update();
  }
}





