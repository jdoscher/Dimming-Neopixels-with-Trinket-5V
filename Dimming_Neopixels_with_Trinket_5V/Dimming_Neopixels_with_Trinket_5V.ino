// This is a sketch to turn an Adafruit Trinket 5V into a Neopixel dimmer. This code makes them white.
//
// Big thanks to the entire Adafruit team for creating great products & building a fun community.
//
// Tested and works great with:
// Adafruit Trinket 5V ------------------> http://amzn.to/2wZZRoa (Use this guide for setting up the IDE https://learn.adafruit.com/introducing-trinket/setting-up-with-arduino-ide)
// Adafruit RGBW Neopixel Strip ---------> https://www.adafruit.com/product/2832
// Adafruit Turn Pot with Switch --------> https://www.adafruit.com/product/3393
// 
//  Written by Jay Doscher.  
//  BSD license, all text above must be included in any redistribution
// ****************************************************/
#include <Adafruit_NeoPixel.h>

// Mystery AVR code! Spooky!
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Define the number of lights in the Neopixel for addressing
#define NUM_LIGHTS  30

// Pin assignments, these are for a Trinket 5V
#define NEO_PIN 3
#define SWITCH_PIN 0
#define BRIGHT_PIN 1
#define AUTO_PIN 4

// Integer for the brightness value, starting off at 0
int val = 0;

// Initial brightness is 0
int brightval = 0;

// Call the Adafruit Neopixel library
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LIGHTS, NEO_PIN, NEO_GRBW + NEO_KHZ800);

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  // Initalize the Neopixels
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  pinMode(SWITCH_PIN, INPUT);
  pinMode(BRIGHT_PIN, INPUT);
}

void loop() {
    brightval = map(analogRead(BRIGHT_PIN), 0, 1023, 0, 255);
    val = digitalRead(SWITCH_PIN);
    if ((val == HIGH) && (analogRead(BRIGHT_PIN) > 20)) {
      for( int i = 0; i<NUM_LIGHTS; i++){
        brightval = map(analogRead(BRIGHT_PIN), 0, 1023, 0, 255);
        strip.setPixelColor(i, brightval,brightval,brightval,brightval);
        strip.show();
      }
  }
}
