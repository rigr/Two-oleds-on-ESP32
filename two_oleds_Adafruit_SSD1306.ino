#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define I2C_FREQ 400000
#define SDA_1 21
#define SCL_1 22
#define SDA_2 18
#define SCL_2 19
TwoWire I2C_1 = TwoWire(0);
TwoWire I2C_2 = TwoWire(1);

int zz;
int past = millis();
Adafruit_SSD1306 OLED1 = Adafruit_SSD1306(128, 32, &I2C_1);
Adafruit_SSD1306 OLED2 = Adafruit_SSD1306(128, 32, &I2C_2);

void setup() {

  I2C_1.begin(SDA_1, SCL_1);
  I2C_2.begin(SDA_2, SCL_2);

  // put your setup code here, to run once:
  OLED1.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Address 0x3C for 128x32
  OLED2.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Address 0x3C for 128x32
  OLED1.display();
  OLED2.display();
  delay(1000);

  // Clear the buffer.
  OLED1.clearDisplay();
  OLED1.display();
  OLED2.clearDisplay();
  OLED2.display();

  // text display tests

  OLED1.setTextSize(1);
  OLED1.setTextColor(SSD1306_WHITE);
  OLED1.setCursor(0, 0);
  OLED1.print("This is some text");
  OLED1.print("it works!");
  OLED1.println("more text here");
  OLED1.println("and even more");
  OLED1.setCursor(0, 0);
  OLED1.display();  // actually display all of the above

  // text display tests
  // OLED2.invertDisplay(true);  
  OLED2.setTextSize(2);
  OLED2.setTextColor(SSD1306_WHITE);
  OLED2.setCursor(0, 0);
  OLED2.println("This is");
  OLED2.println("OLED 2");
  OLED2.setCursor(0, 0);
  OLED2.display();  // actually display all of the above
  delay(2000);

  OLED1.clearDisplay();
  OLED1.display();
  OLED2.clearDisplay();
  OLED2.display();
}

void loop() {
  // put your main code here, to run repeatedly:
  // OLED1.clearDisplay();
  // OLED1.display();
  // OLED2.clearDisplay();
  // OLED2.display();  
  int now = millis();
  OLED1.setCursor(0, 0);
  OLED2.setCursor(0, 0);
  OLED1.fillRect(0, 0, 128, 32, BLACK);
  OLED2.fillRect(0, 0, 128, 32, BLACK);


  OLED1.println("OLED 1  " + String(1000 - zz));
  OLED1.println("123456789012345678901");
  OLED1.println("ABCDEFGHIJKLMNOPQRSTU");
  OLED1.println(String(now - past));
  OLED2.println("OLED 2");
  OLED2.println(String(zz));
  
  // delay(100);
  // yield();

  OLED1.display();
  OLED2.display();
  zz++;
  if (zz > 1000) { zz = 0; }
  past = now;
}
