#include <Adafruit_BMP085.h>
#include <SPI.h>
#include <SD.h>

//SSD1306AsciiAvrI2c display;
Adafruit_BMP085 bmp;
int sP;
const int chipSelect = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if (!bmp.begin()) {
    Serial.println("Bmp Error 1");
    while (1) {}
  }
  sP = bmp.readPressure();
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
//  display.begin(&Adafruit128x64, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
//  display.setFont(Adafruit5x7);
//  display.set2X();
//  // init done
//  display.clear();
//  showCrakenSplash(); // show splashscreen
  setupSD();
}
 
void loop() {
  // put your main code here, to run repeatedly:
  // display.setTextSize(4);
  // display.setCursor(0,18);
  // display.setTextColor(0xFFFF, 0);
  // display.print("           ");
//  display.setCursor(0,2);
//  // display.setTextColor(WHITE);
//  // display.setTextSize(2);
//  display.print(bmp.readAltitude(102270)); // 100750 Cabin
//  display.println(" m");
//  display.print(bmp.readPressure());
//  display.println(" Pa");
//  display.print(bmp.readTemperature());
//  display.println(" *C");
  loopSD();
  // display.display();
}

void setupSD() {
//  pinMode(10, OUTPUT);
//  digitalWrite(10, HIGH);
  if (!SD.begin(chipSelect)) {
    Serial.println("SD Error 1");
    while(1);
  }
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if(dataFile) {
    dataFile.println("BOOT");
    dataFile.close();
  }
   else {
    Serial.println("SD Error 2");
  }
}

void loopSD() {
  //display.setCursor(0,0);
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.print(millis());
    dataFile.print(",");
    dataFile.print(bmp.readAltitude());
    dataFile.print(",");
    dataFile.print(bmp.readAltitude(102270));
    dataFile.print(",");
    dataFile.print(bmp.readPressure());
    dataFile.print(",");
    dataFile.println(bmp.readTemperature());
    dataFile.close();
    // print to the serial port too:
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("SD Error 2");
  }
}

void showCrakenSplash(void) {
  // display.setTextColor(WHITE);
  // display.setCursor(0,0);

 // display.println("Craken v0");
  // display.display();
}
