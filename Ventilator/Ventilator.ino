/* Ventilator 
 *  by Ndukwu Pius Onyema 
 *  This example code is in apublic domain
 *  
 *  allows you to control a Ventilator Operated by a servo pressing down on a ressucitation bag
 */

#include <EEPROM.h>

#include <VarSpeedServo.h> 
/*
  Sweep
  by BARRAGAN <http://barraganstudio.com> 
  Adapted by Philip van Allen <philvanallen.com> for the VarSpeedServo.h library (October 2013)
  This example code is in the public domain
  
  Sweep a servo back and forth from 0-180 degrees, 180-0 degrees
  Uses the wait feature of the 2013 version of VarSpeedServo to stop the code until the servo finishes moving
  
  Note that servos usually require more power than is available from the USB port - use an external power supply!
*/
/*
  LiquidCrystal Library - Hello World

  Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
  library works with all LCD displays that are compatible with the
  Hitachi HD44780 driver. There are many of them out there, and you
  can usually tell them by the 16-pin interface.

  This sketch prints "Hello World!" to the LCD
  and shows the time.

  The circuit:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)

  Library originally added 18 Apr 2008
  by David A. Mellis
  library modified 5 Jul 2009
  by Limor Fried (http://www.ladyada.net)
  example added 9 Jul 2009
  by Tom Igoe
  modified 22 Nov 2010
  by Tom Igoe
  modified 7 Nov 2016
  by Arturo Guadalupi

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:

#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
VarSpeedServo myServo;

// Buttons
const int SAVE_BUTTON = 8;
const int INCREAMENT_BUTTON = 6;
const int DECREAMENT_BUTTON = 13;
const int MENU_BUTTON = 7; // FOR MAKING SELECTIONS
// Variables and Constant values

const int maxSpeed=255;
// the addresses are the location where the values are stored in the EEPROM, research arduino EEPROM to
//understand better

const int max_degreeAddress=0;
const int min_degreeAddress=1;
const int SpeedAddress=2;
long PreviousTime=0;
int menuCount = 0;
int max_degreeHolder = 0;// Holds the value for max_degree so when SAVE_BUTTON is pressed the value is saved to max_degree
int max_degree = 0;
int min_degreeHolder = 0;
int min_degree = 0;
int SpeedHolder = 0;
int Speed = 0; // to control the time the servo takes to move


void setup() {
  
  Serial.begin(9600);
  Serial.println("code has started");
  lcd.begin(16, 2 );
  // SET PINS AS INPUT_PULLUP, THIS WILL KEEP THEM HIGH WHEN NOT PRESSED
  pinMode(MENU_BUTTON, INPUT_PULLUP);
  pinMode(INCREAMENT_BUTTON, INPUT_PULLUP);
  pinMode(DECREAMENT_BUTTON, INPUT_PULLUP);
  pinMode(SAVE_BUTTON, INPUT_PULLUP);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // pin to control servo motor
  myServo.attach(9);
  // Print a message to the LCD.
  lcd.print("Ventilator");
  delay(1000);
  lcd.clear();
  lcd.print("press menu");
// check the values that has been stored in the respective addresses and update the respective value
  max_degree==EEPROM.read(max_degreeAddress);
  min_degree==EEPROM.read(min_degreeAddress);
  Speed=EEPROM.read(SpeedAddress);
  
  max_degreeHolder=EEPROM.read(max_degreeAddress);
  min_degreeHolder=EEPROM.read(min_degreeAddress);
  SpeedHolder=EEPROM.read(SpeedAddress);
}

void loop() {
  
  // this will cause the servo to move between the min_degree and the max_degree
myServo.write(min_degree,Speed,true);
myServo.write(max_degree,Speed,true);

// this allows us to switch between settings
  if (digitalRead(MENU_BUTTON) == LOW) {
    Serial.println(digitalRead(MENU_BUTTON));
    menuCount++; // adds one to menuCount variable
    Serial.print("MENU=");
    Serial.println(menuCount);
    delay(500);
  }
  
  else {
    menuCount += 0;// just add 0 to it 
  }

  if (menuCount == 5) {// when menuCount reaches 4 it should go back to 0
    menuCount = 0;
  }
  switch (menuCount) {
    // when menuCount==1 it will change the settingsto min_degreeHolder setting
    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("minDistanc 0-180");
      lcd.setCursor(0, 1);
      lcd.print(min_degreeHolder);
      Serial.print("minDistance=");
      Serial.println( min_degreeHolder);
      break; //escape the case when it is no longer valid
   // changes the setting to max_degreeHolder setting
    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("maxDepth 0-180");
      lcd.setCursor(0, 1);
      lcd.print(max_degreeHolder);
      Serial.print("maxDepth=");
      Serial.println(max_degreeHolder);
      break;

// changes settings to SpeedHolder setting
    case 3:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("     Speed     ");
      lcd.setCursor(0, 1);
      lcd.print(SpeedHolder);
       Serial.print("Speed=");
      Serial.println(SpeedHolder);
      break;

       case 4:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("PressSAVEtoReset");
      lcd.setCursor(0, 1);
      lcd.print("        ");
       Serial.print("RESET");
    
      break;
  }

  while (menuCount == 1) {
    //when menuCount equals one , anything we do will affect only min_degree and min_degreeHolder variablr
    if (digitalRead(INCREAMENT_BUTTON) == LOW) {
      min_degreeHolder+=10;
      delay(500);
    }
    // when the decrement button is pressed min_degree holder reduces by 1
    if (digitalRead(DECREAMENT_BUTTON) == LOW) {
      min_degreeHolder-=10;
      delay(500);
    }
    if(min_degreeHolder>=180){
      min_degreeHolder=0;
    }

     
    if (digitalRead(SAVE_BUTTON) == LOW) {
      min_degree = min_degreeHolder;
      Serial.println("min_degree=");
      Serial.println(min_degree);
      lcd.setCursor(0, 1);
      lcd.print("    saved    ");
      delay(500);
      lcd.setCursor(0, 1);
      lcd.print(min_degree);
      EEPROM.update(min_degreeAddress,min_degree);
    }
    break;
  }

  while (menuCount == 2) {
    // when menuCount equals one , anything we do will affect only min_degree and min_degreeHolder variablr
    if (digitalRead(INCREAMENT_BUTTON) == LOW) {
      max_degreeHolder+=10;
      delay(500);
    }
    // when the decrement button is pressed min_degree holder reduces by 1
    if (digitalRead(DECREAMENT_BUTTON) == LOW) {
      max_degreeHolder-=10;
      delay(500);
    }
     // set max_degreeHolder back to zero if it reaches 180
    if(max_degreeHolder>=180){
      max_degreeHolder=0;
    }


    if (digitalRead(SAVE_BUTTON) == LOW) {
      max_degree = max_degreeHolder;
      Serial.println("max_degree=");
      Serial.println(max_degree);
      lcd.setCursor(0, 1);
      lcd.print("    saved    ");
      delay(500);
      lcd.setCursor(0, 1);
      lcd.print(max_degree);
       EEPROM.update(max_degreeAddress,max_degree);
    }
    break;
  }

  while (menuCount == 3) {
    // when menuCount equals one , anything we do will affect only min_degree and min_degreeHolder variablr
    if (digitalRead(INCREAMENT_BUTTON) == LOW) {
      SpeedHolder+=10;
      delay(500);
    }
    // when the decrement button is pressed min_degree holder reduces by 1
    if (digitalRead(DECREAMENT_BUTTON) == LOW) {
      SpeedHolder-=10;
      delay(500);
    }

    if( SpeedHolder>=maxSpeed){
      SpeedHolder=0;
    }


    if (digitalRead(SAVE_BUTTON) == LOW) {
      Speed = SpeedHolder;
      Serial.println("Speed=");
      Serial.println(Speed);
      lcd.setCursor(0, 1);
      lcd.print("    saved    ");
      delay(500);
      lcd.setCursor(0, 1);
      lcd.print(Speed);
       EEPROM.update(SpeedAddress,Speed);
    }
    break;
  }
 while(menuCount==4){
  if(digitalRead(SAVE_BUTTON)==LOW){
    Speed=0;
    max_degree=0;
    max_degreeHolder=0;
    min_degree=0;
    min_degreeHolder=0;
    EEPROM.update(min_degreeAddress,0);
    EEPROM.update(max_degreeAddress,0);
    EEPROM.update(SpeedAddress,0);
   lcd.setCursor(0,1);
   lcd.print("Reset Done"); 
  }
break;
  }
}
