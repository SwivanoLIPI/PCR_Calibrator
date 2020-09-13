// Full Program for interfacing calibrator PCR using magnetic Indicator


#include <OneWire.h> 
#include <DallasTemperature.h>
#include "rgb_lcd.h"
#include "max6675.h"
#include <Wire.h>
#include <Adafruit_ADS1015.h>

// Using adc 16 bit 
Adafruit_ADS1115 ads;

const float multiplier = 0.1875F;
//const float multiplier = 0.125F;

//Define PIN 
int ktcSO = 8;
int ktcCS = 9;
int ktcCLK = 10;
int relayPin = 7;// define output pin for relay 
int led = 13 ; // LED on arduino
int digitalPin = 3; // linear Hall magnetic sensor digital interface
int digitalVal ; // digital readings

// Using MAX6675 as temperature sensor
MAX6675 ktc(ktcCLK, ktcCS, ktcSO);

// Using LCD as one Output
rgb_lcd lcd;
const int colorR = 255;
const int colorG = 255;
const int colorB = 0;
  
void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);// define pin 2 as output
  pinMode (led, OUTPUT); 
  pinMode (digitalPin, INPUT); 
  ads.setGain(GAIN_TWOTHIRDS);  //+/- 6.144V  1 bit = 0.1875mV (default)
  // ads.setGain(GAIN_ONE);        +/- 4.096V  1 bit = 0.125mV
  // ads.setGain(GAIN_TWO);        +/- 2.048V  1 bit = 0.0625mV
  // ads.setGain(GAIN_FOUR);       +/- 1.024V  1 bit = 0.03125mV
  // ads.setGain(GAIN_EIGHT);      +/- 0.512V  1 bit = 0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    +/- 0.256V  1 bit = 0.0078125mV 
  ads.begin();
  
}

void loop() {
 
 // Write the LCD temperature value
 lcd.begin(16, 2);
 lcd.setRGB(colorR, colorG, colorB);
 lcd.setCursor(0, 0);
 lcd.print(ktc.readCelsius()+0.5);
 lcd.print(char(223));
 lcd.print("C");
 
 // Read the digital interface

 // Temperature Interfacing to PC display
 Serial.print(ktc.readCelsius()+0.5);
 Serial.print("|");

 //Magnetic indicator
  digitalVal = digitalRead(digitalPin) ; 
  if (digitalVal == HIGH) // When magnetic field is present, Arduino LED is on
  {
    digitalWrite (led, HIGH);
  }
  else
  {
    digitalWrite (led, LOW);
  }
  
 // Read the ADS Magnetic interface to PC display
  
  //Using adc in pin A0
  adc0 = ads.readADC_SingleEnded(0);
  
  
  int16_t adc0
  
Serial.println((adc0 * multiplier)*1.023/5,8);

// Write to LCD the value of magnetic

lcd.setCursor(8, 0);
lcd.print((adc0 * multiplier)*1.023/5,8);
lcd.print(" mG");

delay(100);// 
}
