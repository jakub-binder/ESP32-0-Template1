# ESP32-0-Template1
**Startovací šablona pro projekty s deskou IoT ESP-WROOM-32**
```
$ git tag --list -n1
v0.1    Vychozí šablona s dvěma blikajícími LED pomocí funce mills()
v0.2    Čtyři tlačítka, pomocí kterých lze měnit stav čtyř LEDek
```



## v0.1 - Čtyři tlačítka, pomocí kterých lze měnit stav čtyř LEDek
**Wiring v0.2**
![Wiring v0.2](img/Wiring_v0.2.jpg?raw=true)

U konroly stavu tlačítek vycházím z jednoho z projektů **Steph's µLab**, kde jsou ošetřeny záchvěvy během sepnutí a rozepnutí tlačítka:
https://m1cr0lab-esp32.github.io/remote-control-with-websocket/

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

## v0.0 - Vychozí šablona s dvěma blikajícími LED pomocí funce mills()
**Wiring v0.1**
![Wiring v0.1](img/Wiring_v0.1.jpg?raw=true)

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

https://github.com/Gbertaz/NonBlockingDallas.git
