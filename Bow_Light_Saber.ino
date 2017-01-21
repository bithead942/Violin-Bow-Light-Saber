
/*
   Light Saber Violin Bow
   by Bithead942

    Board:  Arduino Mini Pro (5V, AtMega328)

  Control a strip of Adafruit DarkStar RGB LEDs

  A button controls the LEDs to simulate a light saber turning on/off.
  The system starts in an "off" mode.  Pressing the button turns it "on" and 
  a light pattern illuminates the LEDs in sequence from the bottom up.  Pressing the button again turns it "off" and 
  the inverse light pattern is used to turn the LEDs off from top to bottom.

  PINS USED:
  0   Tx
  1   Rx  
  5   DarkStar Data Pin
  6   DarkStar Clock Pin
  10  Button Pin (INPUT)
  11  Button power (+5V)

  The board and DarkStar require 5V.
  
*/

#include <Adafruit_DotStar.h>
#include <SPI.h>         

#define NUMPIXELS 31 // Number of LEDs in strip

// Here's how to control the LEDs from any two pins:
#define DATAPIN    4
#define CLOCKPIN   5
Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
// The last parameter is optional -- this is the color data order of the
// DotStar strip, which has changed over time in different production runs.
// Your code just uses R,G,B colors, the library then reassigns as needed.
// Default is DOTSTAR_BRG, so change this if you have an earlier strip.

int LightState = 0;  //off to start
int buttonPin = 10;
uint32_t colorRed = 0x00FF00;      // red
uint32_t colorBlack = 0x000000;   // black

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);  //power for switch

  strip.begin(); // Initialize pins for output

  strip.clear();
  //strip.setBrightness(125);  // 50% BRIGHTNESS
  strip.setBrightness(191);    // 75% BRIGHTNESS
  strip.show();  // Turn all LEDs off ASAP
}

void loop() {

  int ButtonState = 0;

  ButtonState = digitalRead(buttonPin);

  if (ButtonState == HIGH){
    if (LightState == 0) {
      SaberOn();
      LightState = 1;
    }
    else {
      SaberOff();
      LightState = 0;
    }
    delay(1000);
  }

}

void SaberOn(){
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, colorRed); // 'On' pixel 
    strip.show();                     // Refresh strip
    delay(20);                        // Pause 20 milliseconds (~50 FPS)
  }
}

void SaberOff(){
    for (int i = NUMPIXELS; i >= 0; i--) {
    strip.setPixelColor(i, colorBlack); // 'On' pixel
    strip.show();                     // Refresh strip
    delay(20);                        // Pause 20 milliseconds (~50 FPS)
  }
}

