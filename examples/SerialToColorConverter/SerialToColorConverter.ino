#include <ColorConverter.h>

ColorConverter converter;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);
  Serial.setTimeout(11);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    char c = Serial.read();

    if (c == 'h') {
      float h = Serial.parseInt();
      float s = Serial.parseInt();
      float l = Serial.parseInt();
      RGBColor color = converter.HSItoRGB(h, s, l);
      Serial.print(color.red);
      Serial.print(" ");
      Serial.print(color.green);
      Serial.print(" ");
     Serial.println(color.blue);
    }

    if (c == 'H') {
      float h = Serial.parseInt();
      float s = Serial.parseInt();
      float l = Serial.parseInt();
      RGBColor color = converter.HSItoRGBW(h, s, l);
      Serial.print(color.red);
      Serial.print(" ");
      Serial.print(color.green);
      Serial.print(" ");
      Serial.print(color.blue);
      Serial.print(" ");
      Serial.println(color.white);
    }
    if (c == 'r') {
      float r = Serial.parseInt();
      float g = Serial.parseInt();
      float b = Serial.parseInt();
      HSIColor color = converter.RGBtoHSI(r, g, b);

      Serial.print(r);
      Serial.print(" ");
      Serial.print(g);
      Serial.print(" ");
      Serial.println(b);

      Serial.print(color.hue);
      Serial.print(" ");
      Serial.print(color.saturation);
      Serial.print(" ");
      Serial.println(color.intensity);
    }
    Serial.println();
  }
}
