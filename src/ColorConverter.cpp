#include "Arduino.h"
#include "ColorConverter.h"

/*
  This library is based on formulas and code from:
  http://www.cnblogs.com/Matrix420/p/4237713.html
  and
  http://blog.saikoled.com/post/43693602826/why-every-led-light-should-be-using-hsi
  and
  http://blog.saikoled.com/post/44677718712/how-to-convert-from-hsi-to-rgb-white

*/

ColorConverter::ColorConverter() {
  // empty initializer
}

struct RGBColor ColorConverter::HSItoRGBW(float hue, float saturation, float intensity) {
  struct RGBColor result = {0,0,0,0};        // the RGBW result you'll return
  hue = constrain(hue, 0, 360);              // constrain hue to 0-360
  hue = hue * PI / 180;                      // Convert to radians.
  saturation = constrain(saturation / 100, 0, 1); // constrain to 0-1
  intensity = constrain(intensity / 100, 0, 1);   // constrain to 0-1

  // if hue is in the red/green sector:
  if (hue < 2 * PI / 3) {
    result.red = saturation * 255 * intensity / 3 * (1L + cos(hue) / cos((PI / 3) - hue));
    result.green = saturation * 255 * intensity / 3 * (1L + (1 - cos(hue) / cos((PI / 3) - hue)));
    result.blue = 0;
    // if hue is in the green/blue sector:
  } else if (hue < 4 * PI / 3) {
    hue = hue - (2 * PI / 3);
    result.green = saturation * 255 * intensity / 3 * (1L + cos(hue) / cos((PI / 3) - hue));
    result.blue = saturation * 255 * intensity / 3 * (1L + (1 - cos(hue) / cos((PI / 3) - hue)));
    result.red = 0;
    // if hue is in the red/blue sector:
  } else {
    hue = hue - (4 * PI / 3);
    result.blue = saturation * 255 * intensity / 3 * (1L + cos(hue) / cos((PI / 3) - hue));
    result.red = saturation * 255 * intensity / 3 * (1L + (1 - cos(hue) / cos((PI / 3) - hue)));
    result.green = 0;
  }
  // white is a function of saturation and intensity regardless of hue:
  result.white = 255 * (1 - saturation) * intensity;

  // return result:
  return result;
}


struct RGBColor ColorConverter::HSItoRGB(float hue, float saturation, float intensity) {
  struct RGBColor result = {0,0,0,0};        // the RGB result you'll return
  hue = constrain(hue, 0, 360);              // constrain hue to 0-360
  hue = hue * PI / 180;                      // Convert to radians.
  saturation = constrain(saturation / 100, 0, 1); // constrain to 0-1
  intensity = constrain(intensity / 100, 0, 1);   // constrain to 0-1

  // if hue is in the red/green sector:
  if (hue < 2 * PI / 3) {
    result.red =255 * intensity / 3 * (1 + saturation * cos(hue) / cos((PI / 3) - hue));
    result.green =255 * intensity / 3 * (1 + saturation * (1 - cos(hue) / cos((PI / 3) - hue)));
    result.blue =255 * intensity / 3 * (1 - saturation);
    // if hue is in the green/blue sector:
  } else if (hue < 4 * PI / 3) {
    hue = hue - (2 * PI / 3);
    result.green =255 * intensity / 3 * (1 + saturation * cos(hue) / cos((PI / 3) - hue));
    result.blue =255 * intensity / 3 * (1 + saturation * (1 - cos(hue) / cos((PI / 3) - hue)));
    result.red =255 * intensity / 3 * (1 - saturation);
    // if hue is in the red/blue sector:
  } else {
    hue = hue - (4 * PI / 3);
    result.blue =255 * intensity / 3 * (1 + saturation * cos(hue) / cos((PI / 3) - hue));
    result.red =255 * intensity / 3 * (1 + saturation * (1 - cos(hue) / cos((PI / 3) - hue)));
    result.green =255 * intensity / 3 * (1 - saturation);
  }
  // not using white, so return 0:
  result.white = 0;

  // return result:
  return result;
}


struct HSIColor ColorConverter::RGBtoHSI (int red, int green, int blue) {
  struct HSIColor result = {0,0,0};
  // floats for calculating saturation and intensity:
  float sat = 0;
  float i = 0;
  // convert input values to range 0-1:
  float r = red / 255.0;
  float g = green / 255.0;
  float b = blue / 255.0;

  // find minimum and maximum of the three:
  float minimum = min(r, min(g, b));
  float maximum = max(r, max(g, b));
  // find intensity:
  i = (r + g + b) /3.0;
  // find saturation:
  if (i == 0 ) {
    sat = 0;
  } else {
    sat = 1.0 - minimum/i;
  }

  // find hue:
  result.hue = acos((r-g + r-b)/2 * sqrt((r-g)*(r-g) + (r-b)*(g-b)));
  // if b > g, hue = 360 degrees - hue:
  if (b > g ) {
    result.hue = 2*PI - result.hue;
  }
  //  if all colors equal, hue is irrelevant:
  if (minimum == maximum) {
    result.hue = 0;
  }
  // convert to degrees
  result.hue = result.hue * 180/PI;
  // convert to 0-100:
  result.intensity = i * 100;
  result.saturation = sat * 100;

  return result;
}
