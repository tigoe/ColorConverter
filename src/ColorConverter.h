
#ifndef ColorConverter_h
#define ColorConverter_h

#include "Arduino.h"

struct RGBColor {
  int red;
  int green;
  int blue;
  int white;
};

struct HSIColor {
  float hue;
  float saturation;
  float intensity;
};

class ColorConverter
{
  public:
    ColorConverter();
    struct RGBColor HSItoRGB(float hue, float saturation, float intensity);
    struct RGBColor HSItoRGBW(float hue, float saturation, float intensity);
    struct HSIColor RGBtoHSI (int red, int green, int blue);
    //TODO:
    //  struct HSIColor RGBWtoHSI (int red, int green, int blue, int white);
  private:

};

#endif
