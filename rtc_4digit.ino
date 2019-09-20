#include <TM1637Display.h>
 
const int CLK = D6; //Set the CLK pin connection to the display
const int DIO = D5; //Set the DIO pin connection to the display
 
int numCounter = 0;
 
TM1637Display display(CLK, DIO); //set up the 4-Digit Display.
TM1637Display  showDots();
 //******************************  4 digit 7 segment *********************************************************************

  #include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;
//******************************** rtc ******************************************************************************


void setup()
{
 display.setBrightness(0x0a); //set the diplay to maximum brightness
 //********************************************************************** rtc set up**********************************
 Serial.begin(9600);
    Wire.begin();
    RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  //RTC.adjust(DateTime(2019, 8, 26, 1, , 3));
  
  }
 //RTC.adjust(DateTime(2019, 8, 26, 1, 46, 5));
}
//**********************************************************************************************************
 int colon=1;
int a=0;
 void loop()
{  
  DateTime now = RTC.now(); 
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println(); 
    delay(1000);
    int hour1=now.hour();
    int minute1=now.minute();
    
    
    /*
     *  int num=10;
 for(k=0; k <= 1; k++) {
    display.showNumberDecEx(num, (0x80 >> k), true);
    delay(500);
  
  //  delay(TEST_DELAY);
  }
     * 
     */

     
    numCounter=((hour1*100)+minute1);
    Serial.println(" time ti be displayed in rtc");
    Serial.println(numCounter);
 
 
 
 display.showNumberDec(numCounter); //Display the numCounter value;

}
