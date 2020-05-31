/**
 * Prototype MIDI controller using:
 *  Arduino Micro
 *  Adafruit Trellis
 * 
 * By: Jae Lee @ Treobytes
 */

 #include <Wire.h>
 #include "Adafruit_Trellis.h"

 #define NUMKEYS 16
 #define INTPIN A2  

 Adafruit_Trellis matrix = Adafruit_Trellis();
 Adafruit_TrellisSet trellis = Adafruit_TrellisSet(&matrix);

/**
 * Vin -> V5
 * Ground -> ground
 * I2C SDA -> SDA
 * I2C SCL -> SCL
 * 
 * On initi, all LEDs will light up then turn off
 */
void setup() {
  Serial.begin(9600);

  // INT pin requires a pullup
  pinMode(INTPIN, INPUT_PULLUP);
  digitalWrite(INTPIN, HIGH);

  trellis.begin(0x70);

  // light up all the LEDs in order
  for (uint8_t i=0; i<NUMKEYS; i++) {
    trellis.setLED(i);
    trellis.writeDisplay();
    delay(50);
  }
  // then turn them off
  for (uint8_t i=0; i<NUMKEYS; i++) {
    trellis.clrLED(i);
    trellis.writeDisplay();
    delay(50);
  }

}

void loop() {
  delay(30);  // 30ms delay is required

  // If a button was just pressed or released
  if (trellis.readSwitches()) {
    // go through every button
    for (uint8_t i=0; i<NUMKEYS; i++) {
      // if pressed
      if (trellis.justPressed(i)) {
        Serial.print("v"); 
        Serial.println(i);
        trellis.setLED(i);
      } 
      // if released
      if (trellis.justReleased(i)) {
        Serial.print("^");
        Serial.println(i);
        trellis.clrLED(i);
      }
    }
    // send LED request
    trellis.writeDisplay();
  }
}
