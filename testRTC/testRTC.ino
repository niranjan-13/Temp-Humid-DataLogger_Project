#include "RTClib.h" //--> Download RTClib.h: https://github.com/adafruit/RTClib
//----------------------------------------------

RTC_DS1307 rtc; //--> Initialize RTC_DS1307

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("Initializing RTC DS1307...");
  delay(100);

  //----------------------------------------------Initializing RTC DS1307
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  //----------------------------------------------

  Serial.println("Successfully Initializing the RTC DS1307");
  Serial.println();

  Serial.println("Starting to run RTC DS1307...");
  delay(100);

  //----------------------------------------------Checks whether the DS1307 RTC can be run or not
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled (Set the time and date based on your computer time and date)
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //-> If that doesn't work, use this line of code outside of "if (! rtc.isrunning())"
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  //----------------------------------------------

  //----------------------------------------------Set the Date and Time on the DS1307 RTC
  Serial.println("Setting the Date and Time...");
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //-> sets the RTC to the date & time this sketch was compiled (Set the time and date based on your computer time and date)
  //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0)); //--> Set Date and Time manually
  delay(100);
  Serial.println("Successfully Setting Date and Time");
  Serial.println();
  // If the time and date are successfully set, then deactivate the code line (make the code a comment), then re-upload the code.
  // if not done then the time and date will return to the beginning when it was set when arduino is reset or restarted.
  //----------------------------------------------

  Serial.println("Successfully running RTC DS1307");
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:

  //----------------------------------------------Printing Date and Time to Serial Monitor
  DateTime now = rtc.now();
  Serial.print("Date ");
  Serial.print(now.day(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.year(), DEC);
  Serial.print(" | Time ");   
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  delay(1000);
  //----------------------------------------------
}