// Simple I2C test for cheap china 128x32 oled.
// Using SSD1306Ascii library
// to attach two Oleds with the same address (0x3C)
// to a ESP32 devkit
//
// Richard G. 4.1.2023


#include <SPI.h>
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"


// define the SDA and SCL pins for the two I2C ports
#define SDA_1 21
#define SCL_1 22
#define SDA_2 18
#define SCL_2 19
TwoWire I2C_1 = TwoWire(0);
TwoWire I2C_2 = TwoWire(1);


SSD1306AsciiWire OLED1(I2C_1);
SSD1306AsciiWire OLED2(I2C_2);

#define I2C_ADDRESS 0x3C

// Define proper RST_PIN if required.
#define RST_PIN -1

int zz;
int past = millis();

void setup() {
  I2C_1.begin(SDA_1, SCL_1, 400000L);
  I2C_2.begin(SDA_2, SCL_2, 400000L);

#if RST_PIN >= 0
  OLED1.begin(&Adafruit128x32, I2C_ADDRESS, RST_PIN);
#else   // RST_PIN >= 0
  OLED1.begin(&Adafruit128x32, I2C_ADDRESS);
#endif  // RST_PIN >= 0


  OLED1.setFont(Adafruit5x7);  // what font to use?

  uint32_t m = micros();       // what time is it?
  OLED1.clear();
  // first row
  OLED1.println("set1X test"); // some test output

  // second row
  OLED1.set2X();               // twice the size
  OLED1.println("set2X test");

  // third row
  OLED1.set1X();
  OLED1.print("micros: ");
  OLED1.print(micros() - m);

#if RST_PIN >= 0
  OLED2.begin(&Adafruit128x32, I2C_ADDRESS, RST_PIN);
#else   // RST_PIN >= 0
  OLED2.begin(&Adafruit128x32, I2C_ADDRESS);
#endif  // RST_PIN >= 0

  OLED2.setFont(Adafruit5x7);

  //  uint32_t m = micros();
  OLED2.clear();
  // first row
  OLED2.println("set1X test2");

  // second row
  OLED2.set2X();
  OLED2.println("set2X 2");

  // third row
  OLED2.set1X();
  OLED2.print("Second Oled ");
  OLED2.print(micros() - m);
  delay(2000);
  OLED1.clear();
  OLED2.clear();
  past = millis();
}

void loop() {
  int now = millis();

  // OLED1.clear();         // not reqired, just slows down.
  OLED1.setCursor(0, 0);    // where do we print?
  OLED1.println("OLED 1");  

  OLED1.println(String(1000 - zz) + " ");   // spaces at the end help to keep it clean

  OLED1.println("12345678901234567890");    // all we can show in a line
  OLED1.println(String(now - past) + " ");  // how many millis does it take to come here again?

  // now the second display
  OLED2.setCursor(0, 0);
  OLED2.print("OLED 2");

  OLED2.set2X();
  OLED2.setCursor(75, 0);                  // x means pixel, y means pixelx8.
  OLED2.print(String(zz) + "  ");

  OLED2.set1X();
  OLED2.setCursor(0, 3);
  OLED2.print(String(now - past) + " ");

  zz++;                                    // a counter
  if (zz > 1000) { zz = 0; }
  past = now;
}
