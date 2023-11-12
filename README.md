# ESP32-0-Template1
**Startovací šablona pro projekty s deskou IoT ESP-WROOM-32**
```
$ git tag --list -n1
v0.1    Vychozí šablona s dvěma blikajícími LED pomocí funce mills()
v0.2    Čtyři tlačítka, pomocí kterých lze měnit stav čtyř LEDek
v0.3    Přidán NeoPixel WS2812B, který reaguje na stisk tlačítek
v0.4    Přidán I2C OLED displej 128x64 pro výpis informací
v0.5    Přidáno teplotní čidlo Dallas Temperature DS18B20

```
## v0.5 - Přidáno teplotní čidlo Dallas Temperature DS18B20
**Wiring v0.5**
![Wiring v0.2](img/Wiring_v0.5.jpg?raw=true)

**Funkcionalita:**
* Na displeji se po určitém intervalu aktualizuje hodnota teploty vyčtená z čidla
* Každé stisknutí tlačítka je vypsáno na OLED displeji
* Modré LEDky blikají v určitých intervalech nezávisle na další aktivitě
* Po stisknutí konkrétního tlačítka se změní stav konkrétní LED na NeoPixel pásce WS2812B

Aby čtení teploty neblokovalo hlavní smyčku **loop()**, je zde použita knihovna **NonBlockingDallas**,
která tuto problematiku řeší.

Použité knihovny pro teplotní čidlo Dallas Temperature DS18B20:
* **OneWire**: https://github.com/PaulStoffregen/OneWire.git
* **NonBlockingDallas**: https://github.com/Gbertaz/NonBlockingDallas.git


## v0.4 - Přidán I2C OLED displej 128x64 pro výpis informací
**Wiring v0.4**
![Wiring v0.2](img/Wiring_v0.4.jpg?raw=true)

**Funkcionalita:**
* Každé stisknut tlačítka je vypsáno na OLED displeji
* Modré LEDky blikají v určitých intervalech nezávisle na další aktivitě
* Po stisknutí konkrétního tlačítka se změní stav konkrétní LED na NeoPixel pásce WS2812B

Použité knihovny pro I2C OLED:
* **Adafruit_SSD1306**: https://github.com/adafruit/Adafruit_SSD1306.git
* **Adafruit-GFX-Library**: https://github.com/adafruit/Adafruit-GFX-Library

## v0.3 - Přidán NeoPixel WS2812B, který reaguje na stisk tlačítek
**Wiring v0.3**
![Wiring v0.2](img/Wiring_v0.3.jpg?raw=true)

**Funkcionalita:**
* Modré LEDky blikají v určitých intervalech nezávisle na další aktivitě
* Po stisknutí konkrétního tlačítka se změní stav konkrétní LED na NeoPixel pásce WS2812B

Použitá knihovna pro NeoPixel:
* **Adafruit_NeoPixel**: https://github.com/adafruit/Adafruit_NeoPixel

## v0.2 - Čtyři tlačítka, pomocí kterých lze měnit stav čtyř LEDek
**Wiring v0.2**
![Wiring v0.2](img/Wiring_v0.2.jpg?raw=true)

**Funkcionalita:**
* Po stisknutí konkrétního tlačítka se změní stav modré LEDky

U konroly stavu tlačítek vycházím z jednoho z projektů **Steph's µLab**, kde jsou ošetřeny záchvěvy během sepnutí a rozepnutí tlačítka:
https://m1cr0lab-esp32.github.io/remote-control-with-websocket/button-setup/

```cpp
  void read()
  {
    // Přečte napětí na pinu připojeného k tlačítku
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
```

## v0.1 - Vychozí šablona s dvěma blikajícími LED pomocí funce mills()
**Wiring v0.1**

![Wiring v0.1](img/Wiring_v0.1.jpg?raw=true)

**Funkcionalita:**
* Dve modré LEDky mění svůj stav (off/on) v určitých intervalech

Změna stavu LEDek je kontrolováno pomocí funkce millis(), aby bylo možné ve funkci loop() provádět i další operace.
```cpp
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
```

**Pinout desky IoT ESP-WROOM-32**
![ESP32 Pinout](img/ESP32_pinout.jpg?raw=true)