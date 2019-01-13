#include <Adafruit_NeoPixel.h>                                // This code require "Adafruit NeoPixel" Library.
#include <Keyboard.h>                                         // This code require "Adafruit NeoPixel" Library.

const int ledPin = 7;                                         // Which pin on the Arduino is connected to the NeoPixels?
const int numLeds = 1;                                        // How many NeoPixels are attached to the Arduino?
unsigned long LEDTimer = 0;                                   // Unsigned long variables are extended size variables for number storage, and store 32 bits (4 bytes)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds, ledPin, NEO_GRB + NEO_KHZ800); 

void setup() {                                                // Run once.
  strip.begin();                                              // Initializes the NeoPixel library.
  strip.setBrightness(70);                                    // Set the brightness of the LED(Strip).
  pinMode(2, INPUT);                                          // Set pin 2 to input.
  pinMode(5, INPUT);                                          // Set pin 2 to input.
  Keyboard.begin();                                           // Initializes the Keyboard library.
}

void loop() {                                                 // Run repeatedly.


  if (digitalRead(2) == HIGH) {
    Keyboard.press('a');
    strip.setPixelColor(0, 255, 110, 170);
    strip.show();

  }
  else
  {
    Keyboard.release('a');
                                                              // If pin 2 is triggered(high) then press "a" key & display pink on the LED(Strip), else release the "a" key.                   
  }
  if (digitalRead(5) == HIGH) {
    Keyboard.press('s');
    strip.setPixelColor(0, 255, 255, 255);
    strip.show();
  }                         
  else
  {
    Keyboard.release('s');
                                                              // If pin 5 is triggered(high) then press "s" key & display white on the LED(Strip), else release the "s" key.
  }
  if (digitalRead(2) == LOW && digitalRead(5) == LOW) { 
    strip.setPixelColor(0, 0, 0, 0);
    strip.show();                                              
  }                                                           // If Pin 2 & 5 is not triggered(low) then reset the LED(Strip).


  if (digitalRead(2) == LOW  && digitalRead(5) == LOW) {
    LEDTimer++;
  }                                                           // If Pin 2 and 5 is not triggered(low) then start the timer(LEDTimer).
  
  if (digitalRead(2) == HIGH  || digitalRead(5) == HIGH) {
    LEDTimer = 0; 
  }                                                           // If Pin 2 or 5 is triggered(high) then reset the timer(LEDTimer).

  if (LEDTimer >= 180000UL)  {                                // If LEDTimer is bigger or equal to 180000 then...

    rainbow(30);                                              // Run rainbow, colour changing delay 30 millisecond.
  }


}


void rainbow(uint8_t wait) { 
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i * 1 + j) & 255));       // Input a value 0 to 255 to get a color value.`
      LEDTimer = 0;
    }
    strip.show();// Display on the LED Strip.
    if (digitalRead(2) == HIGH  || digitalRead(5) == HIGH) {
    }
    delay(wait);                                              // Delay for each colour change.
  }
}


uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
                                                             // The colours are a transition r - g - b - back to r.
}
