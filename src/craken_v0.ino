#include <SSD1306Ascii.h>
#include <SSD1306AsciiAvrI2c.h>
#include <Adafruit_BMP085.h>

SSD1306AsciiAvrI2c display;
Adafruit_BMP085 bmp;
int sP;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {}
  }
  sP = bmp.readPressure();
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(&Adafruit128x64, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
  display.setFont(Adafruit5x7);
  display.set2X();
  // init done
  display.clear();
  showCrakenSplash(); // show splashscreen
}

void loop() {
  // put your main code here, to run repeatedly:
  // display.setTextSize(4);
  // display.setCursor(0,18);
  // display.setTextColor(0xFFFF, 0);
  // display.print("           ");
  display.setCursor(0,2);
  // display.setTextColor(WHITE);
  // display.setTextSize(2);
  display.print(bmp.readAltitude(100885)); // 100750 Cabin
  display.println(" m");
  display.print(bmp.readPressure());
  display.println(" Pa");
  display.print(bmp.readTemperature());
  display.println(" *C");
  delay(1000);
  // display.display();
}

void showCrakenSplash(void) {
  // display.setTextColor(WHITE);
  // display.setCursor(0,0);

  display.println("Craken v0");
  // display.display();
}
