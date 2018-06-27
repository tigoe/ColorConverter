/*
   Serial to color converter

   This sketch lets you test the color converter. To do so, open the serial monitor
   and send one of these strings:

   h xx xx xx\n
   A hue, saturation, intensity string that will return the corresponding RGB values
   hue: 0-360, saturation: 0-100, intensity: 0-100

   H xx xx xx\n
   A hue, saturation, intensity string that will return the corresponding RGBW values
   hue: 0-360, saturation: 0-100, intensity: 0-100

   r h xx xx xx\n
   A red, green, blue string that will return the corresponding HSI values
   red: 0-255,. green: 0-255, blue: 0-255

   created 26 June 2018
   by Tom Igoe
*/

#include <ColorConverter.h>

ColorConverter converter;
void setup() {
  Serial.begin(9600);       // initialize serial communication
  while (!Serial);          // wait until serial monitor is opened
  Serial.setTimeout(10);    // set timeout for parseInt() to 10 ms
}

void loop() {
  if (Serial.available()) {   // if there's any serial data,
    char c = Serial.read();   // read one byte

    if (c == 'h') {       // if byte was h:
      float h = Serial.parseInt();    // read ASCII numeric strings
      float s = Serial.parseInt();
      float i = Serial.parseInt();
      // do the conversion:
      RGBColor color = converter.HSItoRGB(h, s, i);
      // print the results:
      Serial.print(color.red);
      Serial.print(" ");
      Serial.print(color.green);
      Serial.print(" ");
      Serial.println(color.blue);
    }

    if (c == 'H') {       // if byte was H:
      float h = Serial.parseInt();    // read ASCII numeric strings
      float s = Serial.parseInt();
      float i = Serial.parseInt();
      // do the conversion:
      RGBColor color = converter.HSItoRGBW(h, s, i);
      // print the results:
      Serial.print(color.red);
      Serial.print(" ");
      Serial.print(color.green);
      Serial.print(" ");
      Serial.print(color.blue);
      Serial.print(" ");
      Serial.println(color.white);
    }
    if (c == 'r') {      // if byte was r:
      float r = Serial.parseInt();    // read ASCII numeric strings
      float g = Serial.parseInt();
      float b = Serial.parseInt();
      // do the conversion:
      HSIColor color = converter.RGBtoHSI(r, g, b);
      // print the results:
      Serial.print(color.hue);
      Serial.print(" ");
      Serial.print(color.saturation);
      Serial.print(" ");
      Serial.println(color.intensity);
    }
    Serial.println(); // add a blank line
  }
}
