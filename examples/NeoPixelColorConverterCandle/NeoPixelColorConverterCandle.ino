/*
  NeoPixel Candle using ColorConverter

  This sketch uses the Adafruit DotStar library to drive a strip of
  WS2812 LEDs and the ColorConverter library to to HSI to RGB conversion.
  The pixels should fade slowly from orange to red and back cyclically.

  This assumes you're using RGB NeoPixels and not RGBW NeoPixels.

  created 28 Jun 2018
  by Tom Igoe
*/
#include <Adafruit_NeoPixel.h>
#include <ColorConverter.h>

const int neoPixelPin = 5;
const int pixelCount = 7;    // number of pixels
int change = 1;              // increment to change hue by

// set up strip:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixelCount, neoPixelPin, NEO_GRBW + NEO_KHZ800);
ColorConverter converter;

int h = 10;         // hue
int s = 100;        // saturation
int i = 100;        // intensity

void setup() {
  Serial.begin(9600);
  strip.begin();    // initialize pixel strip
  strip.clear();    // turn all LEDs off
  strip.show();     // update strip
}

void loop() {
  // create a single color from hue, sat, intensity:
  RGBColor color = converter.HSItoRGBW(h, s, i);

  // loop over all the pixels:
  for (int pixel = 0; pixel < pixelCount; pixel++) {
    // set the color for this pixel:
    strip.setPixelColor(pixel, color.red, color.green, color.blue, color.white);
  }
  strip.show();   // update the strip
  delay(100);

  // increment hue to fade from red (0) to reddish orange (15) and back:
  h = h + change;
  Serial.println(h);
  if (h < 0 || h > 20) {
    change = -change;
  }
}
