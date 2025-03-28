/*********************************************************************
This is a library for our Monochrome OLEDs based on SSD1305 drivers

  Pick one up today in the adafruit shop!
  ------> https://www.adafruit.com/products/2675

These displays use SPI or I2C to communicate, 3-5 pins are required to  
interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen below must be included in any redistribution
*********************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1305.h>

// Used for software SPI

// Used for software or hardware SPI
#define OLED_CS 21
#define OLED_DC 14

// Used for I2C or SPI
#define OLED_RESET 15

// software SPI
//Adafruit_SSD1305 display(128, 32, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
// hardware SPI - use 7Mhz (7000000UL) or lower because the screen is rated for 4MHz, or it will remain blank!
Adafruit_SSD1305 display(128, 64, &SPI, OLED_DC, OLED_RESET, OLED_CS, 4000000UL);

double speed = 35.0;
double eff = 96.0;
double voltage = 130.0;
double current = 12.0;
double max_v = 4.20;
double min_v = 4.19;
double motorTemp = 85.7;
double mcTemp = 82.3;
int delayTime = millis();

void setup()   {                
  Serial.begin(9600);
  Serial.println("SSD1305 OLED test");
  
  if ( ! display.begin(0x3C) ) {
     Serial.println("Unable to initialize OLED");
     while (1) yield();
  }

  // init done
  display.display(); // show splashscreen
  delay(1000);
  display.clearDisplay();   // clears the screen and buffer
}


void loop() {
  display.clearDisplay();
  updateSpeed();
  updateEff();

  if (millis() - delayTime >= 2500) {
    updateTemps();
  }
  else {
    updateVC();
  }

  if (millis() - delayTime >= 5000) {
    delayTime = millis();
  }
  delay(100);
  display.display();
  current += 1;
  voltage += 1;
  mcTemp += 0.1;
  motorTemp += 0.1;
  speed += 0.1;
  eff += 0.1;

}



void updateSpeed() {
  display.setTextSize(3);
  display.setTextWrap(false);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("S:"+ String(speed,1));
}

void updateEff() {
  display.setTextSize(3);
  display.setTextWrap(false);
  display.setTextColor(WHITE);
  display.setCursor(0,28);
  display.println("E:"+ String(eff,1));
}

void updateTemps() {
  display.setTextSize(1);
  display.setTextWrap(false);
  display.setTextSize(WHITE);
  display.setCursor(0, 56);
  display.print("Motor:");
  display.print(motorTemp,1);
  display.print(" MC:");
  display.print(mcTemp,1);
}

void updateVC() {
  display.setTextSize(1);
  display.setTextWrap(false);
  display.setTextSize(WHITE);
  display.setCursor(0, 56);
  display.print("V:");
  display.print(voltage,1);
  display.print(" C:");
  display.print(current,1);
}

