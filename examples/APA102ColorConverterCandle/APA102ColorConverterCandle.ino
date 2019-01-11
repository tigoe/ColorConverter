/*
  APA102 Candle using ColorConverter

  This sketch uses the Adafruit DotStar library to drive a strip of
  APA102 LEDs and the ColorConverter library to to HSI to RGB conversion.
  The pixels should fade slowly from orange to red and back cyclically.

  This assumes you're using Sparkfun's Illumenati boards for the APA102s,
  and that you're using the built-in SPI SCLK and MOSI pins for control.

  created 11 Jan 2019
  by Tom Igoe
*/
#include <Adafruit_DotStar.h>
#include <ColorConverter.h>

const int pixelCount = 8;    // number of pixels
int change = 1;              // increment to change hue by

// set up strip:
Adafruit_DotStar strip = Adafruit_DotStar(pixelCount, DOTSTAR_BGR);
ColorConverter converter;

int h = 10;         // hue
int s = 100;        // saturation
int i = 100;        // intensity

void setup() {
  strip.begin();    // initialize pixel strip
  strip.clear();    // turn all LEDs off
  strip.show();     // update strip
}

void loop() {
  // create a single color from hue, sat, intensity:
  RGBColor color = converter.HSItoRGB(h, s, i);

  // loop over all the pixels:
  for (int pixel = 0; pixel < pixelCount; pixel++) {
    // set the color for this pixel:
    strip.setPixelColor(pixel, color.red, color.green, color.blue);    
    strip.show();   // update the strip
    delay(100);
  }

  // increment hue to fade from red (0) to reddish orange (15) and back:
  h = h + change;
  if (h < 0 || h > 15) {
    change = -change;
  }
}
